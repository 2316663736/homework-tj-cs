module top(
    input CLK100MHZ,               
    input CPU_RESETN,              
    input PS2_CLK,                // PS/2 时钟
    input PS2_DATA,               // PS/2 键盘输入数据
    input SW0,                    // LED控制LD0-15亮不亮
    input SW8,                    // 控制麦克风模式
    input SW14,                   // 与SW15一起控制自动播放音乐
    input SW15,                   
    input M_DATA,                 // 麦克风数据输入
    output M_CLK,                 // 麦克风时钟
    output M_LRSEL,                
    output wire [15:0] LED,        // 0到7用于显示按下的键码，后面暂时没用
    output wire AUD_PWM,          // 声音播放
    output wire AUD_SD,           
    output wire LED16_B,          // 三色灯LED16的blue
    output wire LED16_G,          
    output wire LED16_R,          
    output wire LED17_B,         
    output wire LED17_G,         
    output wire LED17_R,           
    output wire [6:0] SEG,        // 七段数码管显示控制
    output wire [7:0] AN,         
    output wire [3:0] VGA_RED_O,  // VGA的 red
    output wire [3:0] VGA_GREEN_O,// VGA的 green 
    output wire [3:0] VGA_BLUE_O, // VGA的 blue 
    output wire VGA_HS,           //  horizontal sync
    output wire VGA_VS            //  vertical sync
);
    
    wire [7:0] key_code, auto_key_code, mic_key_code;
    wire key_valid, key_released;
    wire auto_key_valid, auto_key_released;
    wire mic_key_valid, mic_key_released;
    wire [2:0] led16_rgb, led17_rgb;
    wire [15:0] LED0_15;
    
    // 输入源选择逻辑
    wire mic_mode = SW8;
    wire auto_play_enable = SW14 || SW15;
    
    // 根据模式选择最终的按键信号
    wire [7:0] final_key_code = auto_play_enable ? auto_key_code : mic_mode ? mic_key_code : key_code;                           
    wire final_key_valid = auto_play_enable ? auto_key_valid :  mic_mode ? mic_key_valid : key_valid;                        
    wire final_key_released = auto_play_enable ? auto_key_released : mic_mode ? mic_key_released : key_released;

 
    
 
    // 键盘输入
    kb_input keyboard_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN),.PS2_CLK(PS2_CLK),.PS2_DATA(PS2_DATA),.key_code(key_code),.key_valid(key_valid), .key_released(key_released) );   
    // 麦克风控制单元
    mic_control mic_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN),.M_DATA(M_DATA),.M_CLK(M_CLK),.M_LRSEL(M_LRSEL),.key_code(mic_key_code),.key_valid(mic_key_valid),.key_released(mic_key_released));   
    // 自动播放模式下，模拟键盘输入
    auto_play auto_play_unit ( .clk(CLK100MHZ),.rst(~CPU_RESETN),.sw14(SW14),.sw15(SW15),.key_code(auto_key_code),.key_valid(auto_key_valid),.key_released(auto_key_released)); 
        // 声音播放
    audio_out audio_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN), .key_code(final_key_code), .key_valid(final_key_valid),  .key_released(final_key_released),.audio_pwm(AUD_PWM),.audio_sd(AUD_SD));   
    // LED控制器
  led_controller led_unit ( .clk(CLK100MHZ),.rst(~CPU_RESETN),.key_code(final_key_code),.key_valid(final_key_valid), .key_released(final_key_released),.sw0(SW0),.led(LED0_15),.led16_rgb(led16_rgb),.led17_rgb(led17_rgb));
        // 七段数码管显示
    display_control display_unit (.clk(CLK100MHZ),.rst(~CPU_RESETN),.key_code(final_key_code),.key_valid(final_key_valid),.seg(SEG),.an(AN) ); 
    // VGA显示
    vga_controller vga_unit (.CLK100MHZ(CLK100MHZ),.CPU_RESETN(CPU_RESETN),.key_code(final_key_code),.key_valid(final_key_valid), .key_released(final_key_released),.VGA_RED_O(VGA_RED_O),.VGA_GREEN_O(VGA_GREEN_O),.VGA_BLUE_O(VGA_BLUE_O),.VGA_HS(VGA_HS),.VGA_VS(VGA_VS));

    // RGB LED输出分配
    assign LED16_R = led16_rgb[2];
    assign LED16_G = led16_rgb[1];
    assign LED16_B = led16_rgb[0];
    assign LED17_R = led17_rgb[2];
    assign LED17_G = led17_rgb[1];
    assign LED17_B = led17_rgb[0];
    assign LED = LED0_15;
endmodule