module audio_out(
    input wire clk,                  
    input wire rst,                  
    input wire [7:0] key_code,        
    input wire key_valid,            
    input wire key_released,        
    output reg audio_pwm,             
    output reg audio_sd             
);

    //哆啦咪法索拉稀
    parameter DO_FREQ  = 100_000_000/523;   // 523Hz (C4)
    parameter RE_FREQ  = 100_000_000/587;   // 587Hz (D4)
    parameter MI_FREQ  = 100_000_000/659;   // 659Hz (E4)
    parameter FA_FREQ  = 100_000_000/698;   // 698Hz (F4)
    parameter SO_FREQ  = 100_000_000/784;   // 784Hz (G4)
    parameter LA_FREQ  = 100_000_000/880;   // 880Hz (A4)
    parameter SI_FREQ  = 100_000_000/988;   // 988Hz (B4)
    
    reg [31:0] freq_divider;      
    reg [31:0] counter;           
    reg sound_on;
    reg [7:0] current_key;

    // 音频放大器控制
    always @(posedge clk or posedge rst) begin
        if (rst)
            audio_sd <= 1'b0;
        else
            audio_sd <= 1'b1;
    end

    // 音量控制
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            current_key <= 8'h00;
            sound_on <= 1'b0;
        end
        else if (key_released) begin
            sound_on <= 1'b0;
        end
        else if (key_valid) begin
            current_key <= key_code;
            sound_on <= 1'b1;
        end
    end

    // 频率选择
    always @(*) begin
        if (sound_on) begin
            case (current_key)
                8'h1A: freq_divider = DO_FREQ;  // Z   （DO）
                8'h22: freq_divider = RE_FREQ;  // X   （RE）
                8'h21: freq_divider = MI_FREQ;  // C   （MI）
                8'h2A: freq_divider = FA_FREQ;  // V   （FA）
                8'h32: freq_divider = SO_FREQ;  // B   （SO）
                8'h31: freq_divider = LA_FREQ;  // N   （LA）
                8'h3A: freq_divider = SI_FREQ;  // M   （SI）
                default: freq_divider = 32'd0;
            endcase
        end
        else begin
            freq_divider = 32'd0;
        end
    end

    // PWM生成
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            counter <= 32'd0;
            audio_pwm <= 1'b0;
        end
        else begin
            if (freq_divider == 32'd0 || !sound_on) begin
                audio_pwm <= 1'b0;
                counter <= 32'd0;
            end
            else begin
                if (counter >= freq_divider) begin
                    counter <= 32'd0;
                end
                else begin
                    counter <= counter + 1;
                end
                audio_pwm <= (counter < freq_divider/2) ? 1'b1 : 1'b0;
            end
        end
    end

endmodule