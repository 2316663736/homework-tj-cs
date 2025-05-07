module mic_control(
    input wire clk,               
    input wire rst,              
    input wire M_DATA,            
    output wire M_CLK,           
    output wire M_LRSEL,         
    output reg key_valid,        
    output reg [7:0] key_code,   
    output reg key_released      
);

 
    parameter VOLUME_BASE = 8'd15;    // 基础音量阈值
    parameter VOLUME_STEP = 8'd12;    // 音量步进值
    parameter SILENCE_COUNT = 20;      // 静音检测计数器阈值
    
    // 输出频率限制参数 (0.25秒 = 25000000个时钟周期 @100MHz)
    parameter OUTPUT_LIMIT = 25000000;
    
    // 定义7个音符的键码
    localparam KEY_DO = 8'h1A;  // Z   （DO）
    localparam KEY_RE = 8'h22;  // X   （RE）
    localparam KEY_MI = 8'h21;  // C   （MI）
    localparam KEY_FA = 8'h2A;  // V   （FA）
    localparam KEY_SO = 8'h32;  // B   （SO）
    localparam KEY_LA = 8'h31;  // N   （LA）
    localparam KEY_SI = 8'h3A;  // M   （SI）
    
    // 麦克风时钟生成 (3MHz)
    reg [4:0] clk_cnt;
    reg mic_clk;
    
    // 输出频率限制计数器
    reg [31:0] output_counter;
    reg output_ready;
    
    // 静音检测计数器
    reg [4:0] silence_counter;
    reg was_silent;
    
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            clk_cnt <= 5'd0;
            mic_clk <= 1'b0;
        end
        else if (clk_cnt >= 5'd16) begin
            clk_cnt <= 5'd0;
            mic_clk <= ~mic_clk;
        end
        else begin
            clk_cnt <= clk_cnt + 1'b1;
        end
    end
    
    assign M_CLK = mic_clk;
    assign M_LRSEL = 1'b0;

    // PDM数据处理
    reg [7:0] pdm_acc;          // PDM累加器
    reg [7:0] sample_cnt;       // 采样计数器
    reg [7:0] volume;           // 当前音量值
    reg [7:0] last_volume;      // 上一次的音量值
    reg [2:0] current_note;     // 当前音符状态
    reg [2:0] last_note;        // 上一个音符状态
    reg [19:0] debounce_cnt;    // 去抖动计数器
    reg note_active;            // 音符激活状态
    
    // 输出频率限制逻辑
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            output_counter <= 0;
            output_ready <= 1'b1;
        end
        else begin
            if (output_counter >= OUTPUT_LIMIT) begin
                output_counter <= 0;
                output_ready <= 1'b1;
            end
            else begin
                output_counter <= output_counter + 1;
                if (key_valid)
                    output_ready <= 1'b0;
            end
        end
    end
    
    // PDM采样和音量计算
    always @(posedge mic_clk or posedge rst) begin
        if (rst) begin
            pdm_acc <= 8'd0;
            sample_cnt <= 8'd0;
            volume <= 8'd0;
            last_volume <= 8'd0;
        end
        else begin
            if (sample_cnt < 8'd128) begin
                pdm_acc <= pdm_acc + M_DATA;
                sample_cnt <= sample_cnt + 1'b1;
            end
            else begin
                last_volume <= volume;
                volume <= pdm_acc;
                pdm_acc <= 8'd0;
                sample_cnt <= 8'd0;
            end
        end
    end
    
    // 静音检测和音符处理
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            current_note <= 3'd0;
            last_note <= 3'd0;
            key_valid <= 1'b0;
            key_released <= 1'b0;
            key_code <= 8'h00;
            debounce_cnt <= 20'd0;
            note_active <= 1'b0;
            silence_counter <= 0;
            was_silent <= 1'b1;
        end
        else begin
            // 默认复位键盘信号
            key_valid <= 1'b0;
            key_released <= 1'b0;
            
            // 音量检测和去抖动
            if (debounce_cnt < 20'h3FFFF) begin
                debounce_cnt <= debounce_cnt + 1'b1;
            end
            else begin
                debounce_cnt <= 20'd0;
                last_note <= current_note;
                
                // 静音检测
                if (volume < VOLUME_BASE) begin
                    if (silence_counter < SILENCE_COUNT)
                        silence_counter <= silence_counter + 1;
                    else if (!was_silent && note_active) begin
                        key_released <= 1'b1;
                        note_active <= 1'b0;
                        was_silent <= 1'b1;
                    end
                end
                else begin
                    silence_counter <= 0;
                    was_silent <= 1'b0;
                    
                    // 只有当output_ready为1时才处理新的音符
                    if (output_ready) begin
                        // 计算音符索引
                        if (volume >= VOLUME_BASE + (VOLUME_STEP * 6))
                            current_note <= 3'd7;  // SI
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 5))
                            current_note <= 3'd6;  // LA
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 4))
                            current_note <= 3'd5;  // SO
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 3))
                            current_note <= 3'd4;  // FA
                        else if (volume >= VOLUME_BASE + (VOLUME_STEP * 2))
                            current_note <= 3'd3;  // MI
                        else if (volume >= VOLUME_BASE + VOLUME_STEP)
                            current_note <= 3'd2;  // RE
                        else
                            current_note <= 3'd1;  // DO
                            
                        // 音符变化时触发按键事件
                        if (current_note != last_note || !note_active) begin
                            note_active <= 1'b1;
                            key_valid <= 1'b1;
                            case (current_note)
                                3'd1: key_code <= KEY_DO;
                                3'd2: key_code <= KEY_RE;
                                3'd3: key_code <= KEY_MI;
                                3'd4: key_code <= KEY_FA;
                                3'd5: key_code <= KEY_SO;
                                3'd6: key_code <= KEY_LA;
                                3'd7: key_code <= KEY_SI;
                                default: key_code <= 8'h00;
                            endcase
                        end
                    end
                end
            end
        end
    end

endmodule