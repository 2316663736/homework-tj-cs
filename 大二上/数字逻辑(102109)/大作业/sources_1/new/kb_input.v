module kb_input(
    input wire clk,             
    input wire rst,              
    input wire PS2_CLK,          
    input wire PS2_DATA,         
    output reg [7:0] key_code,  
    output reg key_valid,         
    output reg key_released      
);

    localparam [1:0] IDLE = 2'b00, RECEIVE = 2'b01,DONE = 2'b10;
        
    reg [1:0] state;
    reg [7:0] data;          // 现在接受的
    reg [3:0] bit_cnt;       
    reg f0_received;      //标记是否收到了F0,因为F0后面的那个才是键码     
    reg [2:0] PS2_CLK_sync;
    always @(posedge clk) begin
        PS2_CLK_sync <= {PS2_CLK_sync[1:0], PS2_CLK};
    end
    
    // 检测PS2_CLK的下降沿
    wire PS2_CLK_negedge = PS2_CLK_sync[2] & ~PS2_CLK_sync[1];
    
    //主状态机
    always @(posedge clk) begin
        if (rst) begin
            state <= IDLE;
            bit_cnt <= 0;
            data <= 8'h00;
            key_code <= 8'h00;
            key_valid <= 1'b0;
            key_released <= 1'b0;
            f0_received <= 1'b0;
        end
        else begin
            key_valid <= 1'b0;
            key_released <= 1'b0;
            
            case (state)
                IDLE: begin
                    if (PS2_CLK_negedge && !PS2_DATA) begin  // Start bit
                        state <= RECEIVE;
                        bit_cnt <= 4'd0;
                        data <= 8'h00;
                    end
                end
                
                RECEIVE: begin
                    if (PS2_CLK_negedge) begin
                        if (bit_cnt < 8) begin
                            data <= {PS2_DATA, data[7:1]};
                            bit_cnt <= bit_cnt + 1'b1;
                        end
                        else if (bit_cnt == 8) begin  // Parity bit
                            bit_cnt <= bit_cnt + 1'b1;
                        end
                        else begin  // Stop bit
                            state <= DONE;
                        end
                    end
                end
                
                DONE: begin
                    state <= IDLE;
                    //认为F0后面的那个才是键码
                    if (data == 8'hF0) begin
                        f0_received <= 1'b1;
                    end
                    else if (f0_received) begin
                        key_code <= data;
                        key_released <= 1'b1;
                        f0_received <= 1'b0;
                    end
                    else begin
                        key_code <= data;
                        key_valid <= 1'b1;
                    end
                end
                
                default: state <= IDLE;
            endcase
        end
    end

endmodule