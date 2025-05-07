module vga_controller(
   input wire CLK100MHZ,           
   input wire CPU_RESETN,          
   input wire [7:0] key_code,      
   input wire key_valid,
   input wire key_released,           
   output reg [3:0] VGA_RED_O,     
   output reg [3:0] VGA_GREEN_O,   
   output reg [3:0] VGA_BLUE_O,    
   output reg VGA_HS,              
   output reg VGA_VS              
);

    
   parameter H_ACTIVE = 640;
   parameter H_FP = 16;    
   parameter H_SYNC = 96;  
   parameter H_BP = 48;    
   parameter H_TOTAL = 800;
   parameter V_ACTIVE = 480;
   parameter V_FP = 10;    
   parameter V_SYNC = 2;   
   parameter V_BP = 33;    
   parameter V_TOTAL = 525;

   // 音符
   parameter NOTE_WIDTH = 80;    
   parameter NOTE_HEIGHT = 80;   
   parameter NOTE_X = H_ACTIVE/2;
   parameter NOTE_Y = V_ACTIVE/8;

   // 音乐条
   parameter MAX_BAR_HEIGHT = 200;    // 最大可能的高度
   parameter MIN_BAR_HEIGHT = 60;     // 最小可能的高度
   parameter BAR_Y = V_ACTIVE;        // 底部位置
   parameter BAR_WIDTH = 15;          // 条形宽度
   parameter BAR_SPACING = 20;        // 间距
   parameter BAR_COUNT = 10;           // 音乐条数量
   parameter BAR_START_X = (H_ACTIVE - (BAR_COUNT * (BAR_WIDTH + BAR_SPACING))) / 2;

   //动画变化的信息（音乐条的）
   parameter ANIM_SPEED = 500000;    
   parameter HEIGHT_SPEED = 800000;   

 
   reg [9:0] h_count;
   reg [9:0] v_count;
   reg [1:0] clk_div;
   reg [11:0] note_color;
   reg display_active;
   
   // 控制音乐条的动画
   reg [31:0] anim_counter;
   reg [31:0] height_counter;
   reg [7:0] bar_heights [9:0];      
   reg [7:0] total_heights [9:0];     
   reg [9:0] bar_directions;          
   reg [31:0] bar_speeds[9:0];      
   reg [9:0] bar_active;              
   reg [9:0] height_directions;      
   integer i;

 
   initial begin
       h_count = 0;
       v_count = 0;
       clk_div = 0;
       anim_counter = 0;
       height_counter = 0;
       bar_directions = 0;
       bar_active = 0;
       display_active = 0;
       note_color = 0;
       height_directions = 0;
       
       for (i = 0; i < 10; i = i + 1) begin
           bar_heights[i] = 0;
           total_heights[i] = MIN_BAR_HEIGHT;
           case (i)
               0: bar_speeds[i] = ANIM_SPEED;
               1: bar_speeds[i] = ANIM_SPEED + 100000;
               2: bar_speeds[i] = ANIM_SPEED - 50000;
               3: bar_speeds[i] = ANIM_SPEED + 50000;
               4: bar_speeds[i] = ANIM_SPEED - 100000;
               5: bar_speeds[i] = ANIM_SPEED + 75000;
               6: bar_speeds[i] = ANIM_SPEED - 125000;
               7: bar_speeds[i] = ANIM_SPEED + 50000;
               8: bar_speeds[i] = ANIM_SPEED + 30000;
               9: bar_speeds[i] = ANIM_SPEED - 30000;
           endcase
       end
   end

  
   always @(posedge CLK100MHZ) begin
       clk_div <= clk_div + 1;
   end

 
   always @(posedge CLK100MHZ) begin
       if (!CPU_RESETN) begin
           for (i = 0; i < 10; i = i + 1) begin
               total_heights[i] <= MIN_BAR_HEIGHT;
               height_directions[i] <= 0;
           end
           height_counter <= 0;
       end
       else begin
           height_counter <= height_counter + 1;
           
           for (i = 0; i < 10; i = i + 1) begin
               if (height_counter % (HEIGHT_SPEED + i * 50000) == 0) begin
                   if (!height_directions[i]) begin
                       if (total_heights[i] >= MAX_BAR_HEIGHT) begin
                           height_directions[i] <= 1;
                           total_heights[i] <= total_heights[i] - 1;
                       end
                       else begin
                           total_heights[i] <= total_heights[i] + 1;
                       end
                   end
                   else begin
                       if (total_heights[i] <= MIN_BAR_HEIGHT) begin
                           height_directions[i] <= 0;
                           total_heights[i] <= total_heights[i] + 1;
                       end
                       else begin
                           total_heights[i] <= total_heights[i] - 1;
                       end
                   end
               end
           end
       end
   end

 
   always @(posedge CLK100MHZ) begin
       if (!CPU_RESETN) begin
           anim_counter <= 0;
           bar_directions <= 0;
           bar_active <= 0;
           for (i = 0; i < 10; i = i + 1) begin
               bar_heights[i] <= 0;
           end
       end
       else begin
           anim_counter <= anim_counter + 1;
           
           for (i = 0; i < BAR_COUNT; i = i + 1) begin
               if (anim_counter % bar_speeds[i] == 0) begin
                   if (key_valid && (
                   (i == 0 && key_code == 8'h1A) || // Z
                   (i == 1 && key_code == 8'h22) || // X
                   (i == 2 && key_code == 8'h21) || // C
                   (i == 3 && key_code == 8'h2A) || // V
                   (i == 4 && key_code == 8'h32) || // B
                   (i == 5 && key_code == 8'h31) || // N
                   (i == 6 && key_code == 8'h3A) || // M
                   (i == 7 && key_code == 8'h3B) || // ,
                   (i == 8) ||                       
                   (i == 9)                           
               )) begin
                       bar_active[i] <= 1;
                       if (bar_heights[i] < total_heights[i] - 10)
                           bar_heights[i] <= bar_heights[i] + 5;
                   end
                   else begin
                       if (bar_active[i]) begin
                           if (!bar_directions[i]) begin
                               if (bar_heights[i] >= total_heights[i] * 3/4)
                                   bar_directions[i] <= 1;
                               else
                                   bar_heights[i] <= bar_heights[i] + 2;
                           end
                           else begin
                               if (bar_heights[i] <= 10)
                                   bar_directions[i] <= 0;
                               else
                                   bar_heights[i] <= bar_heights[i] - 2;
                           end
                       end
                       else begin
                           if (anim_counter[23])
                               bar_active[i] <= 1;
                       end
                   end
               end
           end
       end
   end

   //不同按键对应的音符的颜色（七个）
   always @(posedge CLK100MHZ) begin
       if (!CPU_RESETN) begin
           display_active <= 1'b0;
           note_color <= 12'h000;
       end
       else if (key_released) begin
           display_active <= 1'b0;
       end
       else if (key_valid) begin
           display_active <= 1'b1;
           case (key_code)
               8'h1A: note_color <= 12'hF0F;  
               8'h22: note_color <= 12'h90F;  
               8'h21: note_color <= 12'h44F;  
               8'h2A: note_color <= 12'h4AF;  
               8'h32: note_color <= 12'h4FF;  
               8'h31: note_color <= 12'h4FA;  
               8'h3A: note_color <= 12'h4F4;  
               8'h3B: note_color <= 12'hAF4; 
               default: display_active <= 1'b0;
           endcase
       end
   end

   // VGA时序与同步信号生成
   always @(posedge CLK100MHZ) begin
       if (!CPU_RESETN) begin
           h_count <= 0;
           v_count <= 0;
       end
       else if (clk_div == 2'b11) begin
           if (h_count == H_TOTAL-1) begin
               h_count <= 0;
               if (v_count == V_TOTAL-1)
                   v_count <= 0;
               else
                   v_count <= v_count + 1;
           end
           else
               h_count <= h_count + 1;
       end
   end

 
   always @(posedge CLK100MHZ) begin
       if (!CPU_RESETN) begin
           VGA_HS <= 1'b1;
           VGA_VS <= 1'b1;
       end
       else begin
           VGA_HS <= ~(h_count >= H_ACTIVE + H_FP &&   h_count < H_ACTIVE + H_FP + H_SYNC);
           VGA_VS <= ~(v_count >= V_ACTIVE + V_FP &&  v_count < V_ACTIVE + V_FP + V_SYNC);
       end
   end
 
   wire display_region;
   wire is_note_region;
   wire [18:0] bg_addr;
   wire [12:0] note_addr;
   wire [2:0] current_bar;
   wire in_bar_column;
   wire in_active_bar_region;
   
   //判断当前位置是不是音符
   assign display_region = (h_count < H_ACTIVE) && (v_count < V_ACTIVE);
   assign is_note_region = (h_count >= NOTE_X - NOTE_WIDTH/2) && (h_count < NOTE_X + NOTE_WIDTH/2) &&(v_count >= NOTE_Y - NOTE_HEIGHT/2) &&(v_count < NOTE_Y + NOTE_HEIGHT/2);
                        
   assign note_addr = (h_count - (NOTE_X - NOTE_WIDTH/2)) +(v_count - (NOTE_Y - NOTE_HEIGHT/2)) * NOTE_WIDTH;
   
   assign bg_addr = h_count + v_count * H_ACTIVE;
   assign current_bar = (h_count - BAR_START_X) / (BAR_WIDTH + BAR_SPACING);
   
   // 检查当前位置是不是在音乐条
   assign in_bar_column = (h_count >= BAR_START_X) && (h_count < BAR_START_X + BAR_COUNT * (BAR_WIDTH + BAR_SPACING)) && ((h_count - BAR_START_X) % (BAR_WIDTH + BAR_SPACING) < BAR_WIDTH);
   assign in_active_bar_region = in_bar_column && (v_count > BAR_Y - bar_heights[current_bar]) && (v_count <= BAR_Y);

 
   wire [11:0] bg_pixel_data;
   wire [11:0] note_pixel_data;
   //读取背景（640*480）
   blk_mem_gen_0 background_rom (
       .clka(CLK100MHZ),
       .addra(bg_addr),
       .douta(bg_pixel_data)
   );
   //读取音符（80*80）
   blk_mem_gen_1 note_rom (
       .clka(CLK100MHZ),
       .addra(is_note_region ? note_addr : 13'd0),
       .douta(note_pixel_data)
   );

 
 
   always @(*) begin
       if (display_region) begin
           if (display_active && is_note_region && note_pixel_data != 12'h000) begin
               // 显示音符
               //对于音符的显示，是去除掉其中黑色部分，在把剩余部分赋值为特定的颜色
               VGA_RED_O = (note_color[11:8] & note_pixel_data[11:8]);
               VGA_GREEN_O = (note_color[7:4] & note_pixel_data[7:4]);
               VGA_BLUE_O = (note_color[3:0] & note_pixel_data[3:0]);
           end
        else if (in_active_bar_region) begin
        //显示音乐条
                case (current_bar)
                    0: begin 
                        VGA_RED_O = 4'hF ;
                        VGA_GREEN_O = 4'h0;
                        VGA_BLUE_O = 4'hF  ;
                    end
                    1: begin 
                        VGA_RED_O = 4'h9 ;
                        VGA_GREEN_O = 4'h0;
                        VGA_BLUE_O = 4'hF ;
                    end
                    2: begin 
                        VGA_RED_O = 4'h4 ;
                        VGA_GREEN_O = 4'h4 ;
                        VGA_BLUE_O = 4'hF  ;
                    end
                    3: begin
                        VGA_RED_O = 4'h4 ;
                        VGA_GREEN_O = 4'hA  ;
                        VGA_BLUE_O = 4'hF  ;
                    end
                    4: begin
                        VGA_RED_O = 4'h4 ;
                        VGA_GREEN_O = 4'hF ;
                        VGA_BLUE_O = 4'hF ;
                    end
                    5: begin
                        VGA_RED_O = 4'h4  ;
                        VGA_GREEN_O = 4'hF  ;
                        VGA_BLUE_O = 4'hA ;
                    end
                    6: begin
                        VGA_RED_O = 4'h4 ;
                        VGA_GREEN_O = 4'hF ;
                        VGA_BLUE_O = 4'h4  ;
                    end
                    7: begin 
                        VGA_RED_O = 4'hA ;
                        VGA_GREEN_O = 4'hF ;
                        VGA_BLUE_O = 4'h4  ;
                    end
                    8: begin 
                        VGA_RED_O = 4'h0;
                        VGA_GREEN_O = 4'hF ;
                        VGA_BLUE_O = 4'h4 ;
                    end
                    9: begin 
                        VGA_RED_O = 4'hA  ;
                        VGA_GREEN_O = 4'h0;
                        VGA_BLUE_O = 4'h4 ;
                    end
                   
                endcase
           end
           else begin
               // 为所有其他区域显示背景
               VGA_RED_O = bg_pixel_data[11:8];
               VGA_GREEN_O = bg_pixel_data[7:4];
               VGA_BLUE_O = bg_pixel_data[3:0];
           end
       end
       else begin
           VGA_RED_O = 4'h0;
           VGA_GREEN_O = 4'h0;
           VGA_BLUE_O = 4'h0;
       end
   end

endmodule