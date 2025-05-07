module led_controller(
    input wire clk,                  
    input wire rst,                  
    input wire [7:0] key_code,        
    input wire key_valid,
    input wire key_released,
    input wire sw0,                   // LED控制开关
    output reg [15:0] led,           // LED0-15
    output reg [2:0] led16_rgb,      // LED16 RGB
    output reg [2:0] led17_rgb       // LED17 RGB
);
    // LED渐变参数
    parameter FADE_STEPS = 32;              
    parameter FADE_SPEED = 1000000;         
    
    //  LED渐变控制寄存器
    reg [2:0] current_rgb;       
    reg [2:0] target_rgb;        
    reg [31:0] fade_counter;     
    reg fade_active;             
    reg [5:0] fade_step;         

    // LED0-15 控制
    always @(posedge clk) begin
        if (rst || sw0)
            led <= 16'h0000;
        else if (key_valid || key_released) begin
            led[15:8] <= 8'b00000000;
            led[7:0] <= key_code;
        end
    end

    // LED16-17 RGB渐变控制
    always @(posedge clk) begin
        if (rst || sw0) begin
            current_rgb <= 3'b000;
            target_rgb <= 3'b000;
            fade_counter <= 0;
            fade_active <= 0;
            fade_step <= 0;
            led16_rgb <= 3'b000;
            led17_rgb <= 3'b000;
        end
        else begin
            // 检测新的按键
            if (key_valid) begin
                case (key_code)
                    8'h1A: target_rgb <= 3'b100;  // Z  
                    8'h22: target_rgb <= 3'b010;  // X 
                    8'h21: target_rgb <= 3'b001;  // C  
                    8'h2A: target_rgb <= 3'b110;  // V  
                    8'h32: target_rgb <= 3'b101;  // B  
                    8'h31: target_rgb <= 3'b011;  // N 
                    8'h3A: target_rgb <= 3'b111;  // M  
                endcase
                fade_active <= 1'b1;
                fade_step <= 0;
            end
            
            // 渐变处理
            fade_counter <= fade_counter + 1;
            if (fade_active && fade_counter >= FADE_SPEED) begin
                fade_counter <= 0;
                if (fade_step < FADE_STEPS) begin
                    fade_step <= fade_step + 1;
                    
                    // 对每个颜色分量进行渐变
                    if (current_rgb[0] != target_rgb[0]) begin
                        if (fade_step >= (FADE_STEPS/2))
                            current_rgb[0] <= target_rgb[0];
                    end
                    if (current_rgb[1] != target_rgb[1]) begin
                        if (fade_step >= (FADE_STEPS/2))
                            current_rgb[1] <= target_rgb[1];
                    end
                    if (current_rgb[2] != target_rgb[2]) begin
                        if (fade_step >= (FADE_STEPS/2))
                            current_rgb[2] <= target_rgb[2];
                    end
                end
                else begin
                    fade_active <= 1'b0;
                    current_rgb <= target_rgb;
                end
            end
            
            // 更新LED显示
            led16_rgb <= current_rgb;
            led17_rgb <= current_rgb;
        end
    end

endmodule