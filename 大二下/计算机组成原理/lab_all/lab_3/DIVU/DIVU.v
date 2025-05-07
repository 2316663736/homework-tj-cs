module DIVU(
    input [31:0] dividend,    
    input [31:0] divisor,      
    input start,               
    input clock,              
    input reset,               
    output [31:0] q,         
    output [31:0] r,          
    output busy                
);


    reg [31:0] reg_q;        
    reg [31:0] reg_r;          
    reg [31:0] reg_b;         
    reg [5:0] count;           
    reg busy_reg;            
    reg r_sign;             
    

    reg zero_divisor;         
    reg divisor_power_of_2;    
    reg [4:0] shift_amount;   
    reg div_small;           
    

    reg [1:0] state;
    parameter IDLE = 2'b00;    
    parameter SPECIAL = 2'b01; 
    parameter CALC = 2'b10;   
    parameter DONE = 2'b11;  
    

    wire is_power_of_2 = (divisor & (divisor - 1)) == 0 && divisor != 0;
    
    function [4:0] count_trailing_zeros;
        input [31:0] value;
        reg [4:0] count;
        begin
            count = 0;
            if (value[15:0] == 0) begin count = count + 16; value = value >> 16; end
            if (value[7:0] == 0)  begin count = count + 8;  value = value >> 8;  end
            if (value[3:0] == 0)  begin count = count + 4;  value = value >> 4;  end
            if (value[1:0] == 0)  begin count = count + 2;  value = value >> 2;  end
            if (value[0] == 0)    begin count = count + 1;  end
            count_trailing_zeros = count;
        end
    endfunction
    

    wire [32:0] sub_add1 = r_sign ? 
                         ({reg_r, reg_q[31]} + {1'b0, reg_b}) : 
                         ({reg_r, reg_q[31]} - {1'b0, reg_b});
    
    wire r_sign_next = sub_add1[32];
    wire [32:0] sub_add2 = r_sign_next ? 
                         ({sub_add1[31:0], reg_q[30]} + {1'b0, reg_b}) : 
                         ({sub_add1[31:0], reg_q[30]} - {1'b0, reg_b});
    

    assign q = reg_q;
    assign r = r_sign ? (reg_r + reg_b) : reg_r;
    assign busy = busy_reg;
    

    always @(posedge clock or posedge reset) begin
        if (reset) begin

            reg_q <= 32'b0;
            reg_r <= 32'b0;
            reg_b <= 32'b0;
            count <= 6'b0;
            busy_reg <= 1'b0;
            r_sign <= 1'b0;
            state <= IDLE;
            zero_divisor <= 1'b0;
            divisor_power_of_2 <= 1'b0;
            shift_amount <= 5'b0;
            div_small <= 1'b0;
        end else begin
            case (state)
                IDLE: begin
                    if (start && !busy_reg) begin
                        busy_reg <= 1'b1;
                        
                        zero_divisor <= (divisor == 32'b0);
                        
                        divisor_power_of_2 <= is_power_of_2;
                        
                        shift_amount <= count_trailing_zeros(divisor);
                        
                        div_small <= (dividend < divisor);
                        
                        reg_q <= dividend;
                        reg_b <= divisor;
                        reg_r <= 32'b0;
                        r_sign <= 1'b0;
                        count <= 6'b0;
                        
                        state <= SPECIAL;
                    end
                end
                
                SPECIAL: begin
                    if (zero_divisor) begin
                        reg_q <= 32'hFFFFFFFF; 
                        reg_r <= dividend;    
                        state <= DONE;
                    end else if (div_small) begin
                        reg_q <= 32'b0;
                        reg_r <= dividend;
                        state <= DONE;
                    end else if (divisor_power_of_2) begin
                        reg_q <= dividend >> shift_amount;
                        reg_r <= dividend & ((1 << shift_amount) - 1);
                        state <= DONE;
                    end else begin
                        state <= CALC;
                    end
                end
                
                CALC: begin
                    if (count < 32) begin
                        if (count <= 30) begin  
                            reg_r <= sub_add2[31:0];
                            r_sign <= sub_add2[32];
                            
                            reg_q <= {reg_q[29:0], ~sub_add1[32], ~sub_add2[32]};
                           
                            count <= count + 6'b10;
                        end else begin
                            reg_r <= sub_add1[31:0];
                            r_sign <= sub_add1[32];
                            reg_q <= {reg_q[30:0], ~sub_add1[32]};
                            count <= count + 6'b1;
                        end
                    end else begin
                        state <= DONE;
                    end
                end
                
                DONE: begin
                    busy_reg <= 1'b0;
                    state <= IDLE;
                end
            endcase
        end
    end

endmodule


