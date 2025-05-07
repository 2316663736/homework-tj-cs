module display_control(
    input wire clk,                   
    input wire rst,                   
    input wire [7:0] key_code,       
    input wire key_valid,            
    output reg [6:0] seg,            
    output reg [7:0] an             
);

 
    reg [3:0] current_number;        //当前显示的数字
    reg [2:0] current_position;      //当前显示位置
    reg display_active;              //显示是否处于激活状态
    reg [2:0] scan_count;           // 用于显示扫描
    reg [19:0] refresh_counter;     //用于显示刷新


    reg [6:0] decoded_segments;
        always @(*) begin
            case(current_number)
                4'd0: decoded_segments = 7'b1000000;  // 0
                4'd1: decoded_segments = 7'b1111001;  // 1
                4'd2: decoded_segments = 7'b0100100;  // 2
                4'd3: decoded_segments = 7'b0110000;  // 3
                4'd4: decoded_segments = 7'b0011001;  // 4
                4'd5: decoded_segments = 7'b0010010;  // 5
                4'd6: decoded_segments = 7'b0000010;  // 6
                4'd7: decoded_segments = 7'b1111000;  // 7
                default: decoded_segments = 7'b1111111; // All off
            endcase
        end


    initial begin
        current_number = 4'hF;
        current_position = 3'd0;
        display_active = 1'b0;
        refresh_counter = 0;
        scan_count = 0;
    end

    // 根据按键存储显示值
    always @(posedge clk) begin
        if (rst) begin
            current_number <= 4'hF;
            current_position <= 3'd0;
            display_active <= 1'b0;
        end
        else if (key_valid) begin
            display_active <= 1'b1;
            case (key_code)
                8'h1A: begin 
                    current_number <= 4'd1;
                    current_position <= 3'd0;
                end
                8'h22: begin   
                    current_number <= 4'd2;
                    current_position <= 3'd1;
                end
                8'h21: begin   
                    current_number <= 4'd3;
                    current_position <= 3'd2;
                end
                8'h2A: begin 
                    current_number <= 4'd4;
                    current_position <= 3'd3;
                end
                8'h32: begin 
                    current_number <= 4'd5;
                    current_position <= 3'd4;
                end
                8'h31: begin  
                    current_number <= 4'd6;
                    current_position <= 3'd5;
                end
                8'h3A: begin  
                    current_number <= 4'd7;
                    current_position <= 3'd6;
                end
                default: begin
                    display_active <= 1'b0;
                end
            endcase
        end
    end

   
    always @(posedge clk) begin
        refresh_counter <= refresh_counter + 1;
        scan_count <= refresh_counter[19:17];
    end

 
    always @(posedge clk) begin
        if (!display_active || rst) begin
            an <= 8'b11111111; 
            seg <= 7'b1111111;   
        end
        else begin
            if (scan_count == current_position) begin
                seg <= decoded_segments;   
                an <= ~(8'b1 << current_position);
            end
            else begin
                an <= 8'b11111111;
                seg <= 7'b1111111;
            end
        end
    end

endmodule