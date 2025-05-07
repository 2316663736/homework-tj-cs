module MULTU( 
    input clk,           
    input reset,          
    input [31:0] a,       
    input [31:0] b,       
    output [63:0] z     
);


    reg [63:0] result;

    wire [63:0] stored0, stored1, stored2, stored3, stored4, stored5, stored6, stored7;
    wire [63:0] stored8, stored9, stored10, stored11, stored12, stored13, stored14, stored15;
    wire [63:0] stored16, stored17, stored18, stored19, stored20, stored21, stored22, stored23;
    wire [63:0] stored24, stored25, stored26, stored27, stored28, stored29, stored30, stored31;
    

    wire [63:0] add1_0, add1_1, add1_2, add1_3, add1_4, add1_5, add1_6, add1_7;
    wire [63:0] add1_8, add1_9, add1_10, add1_11, add1_12, add1_13, add1_14, add1_15;
    wire [63:0] add2_0, add2_1, add2_2, add2_3, add2_4, add2_5, add2_6, add2_7;
    wire [63:0] add3_0, add3_1, add3_2, add3_3;
    wire [63:0] add4_0, add4_1;
    wire [63:0] final_sum;
    

    assign stored0 = b[0] ? {32'b0, a} : 64'b0;
    assign stored1 = b[1] ? {31'b0, a, 1'b0} : 64'b0;
    assign stored2 = b[2] ? {30'b0, a, 2'b0} : 64'b0;
    assign stored3 = b[3] ? {29'b0, a, 3'b0} : 64'b0;
    assign stored4 = b[4] ? {28'b0, a, 4'b0} : 64'b0;
    assign stored5 = b[5] ? {27'b0, a, 5'b0} : 64'b0;
    assign stored6 = b[6] ? {26'b0, a, 6'b0} : 64'b0;
    assign stored7 = b[7] ? {25'b0, a, 7'b0} : 64'b0;
    assign stored8 = b[8] ? {24'b0, a, 8'b0} : 64'b0;
    assign stored9 = b[9] ? {23'b0, a, 9'b0} : 64'b0;
    assign stored10 = b[10] ? {22'b0, a, 10'b0} : 64'b0;
    assign stored11 = b[11] ? {21'b0, a, 11'b0} : 64'b0;
    assign stored12 = b[12] ? {20'b0, a, 12'b0} : 64'b0;
    assign stored13 = b[13] ? {19'b0, a, 13'b0} : 64'b0;
    assign stored14 = b[14] ? {18'b0, a, 14'b0} : 64'b0;
    assign stored15 = b[15] ? {17'b0, a, 15'b0} : 64'b0;
    assign stored16 = b[16] ? {16'b0, a, 16'b0} : 64'b0;
    assign stored17 = b[17] ? {15'b0, a, 17'b0} : 64'b0;
    assign stored18 = b[18] ? {14'b0, a, 18'b0} : 64'b0;
    assign stored19 = b[19] ? {13'b0, a, 19'b0} : 64'b0;
    assign stored20 = b[20] ? {12'b0, a, 20'b0} : 64'b0;
    assign stored21 = b[21] ? {11'b0, a, 21'b0} : 64'b0;
    assign stored22 = b[22] ? {10'b0, a, 22'b0} : 64'b0;
    assign stored23 = b[23] ? {9'b0, a, 23'b0} : 64'b0;
    assign stored24 = b[24] ? {8'b0, a, 24'b0} : 64'b0;
    assign stored25 = b[25] ? {7'b0, a, 25'b0} : 64'b0;
    assign stored26 = b[26] ? {6'b0, a, 26'b0} : 64'b0;
    assign stored27 = b[27] ? {5'b0, a, 27'b0} : 64'b0;
    assign stored28 = b[28] ? {4'b0, a, 28'b0} : 64'b0;
    assign stored29 = b[29] ? {3'b0, a, 29'b0} : 64'b0;
    assign stored30 = b[30] ? {2'b0, a, 30'b0} : 64'b0;
    assign stored31 = b[31] ? {1'b0, a, 31'b0} : 64'b0;
    

    assign add1_0 = stored0 + stored1;
    assign add1_1 = stored2 + stored3;
    assign add1_2 = stored4 + stored5;
    assign add1_3 = stored6 + stored7;
    assign add1_4 = stored8 + stored9;
    assign add1_5 = stored10 + stored11;
    assign add1_6 = stored12 + stored13;
    assign add1_7 = stored14 + stored15;
    assign add1_8 = stored16 + stored17;
    assign add1_9 = stored18 + stored19;
    assign add1_10 = stored20 + stored21;
    assign add1_11 = stored22 + stored23;
    assign add1_12 = stored24 + stored25;
    assign add1_13 = stored26 + stored27;
    assign add1_14 = stored28 + stored29;
    assign add1_15 = stored30 + stored31;
    

    assign add2_0 = add1_0 + add1_1;
    assign add2_1 = add1_2 + add1_3;
    assign add2_2 = add1_4 + add1_5;
    assign add2_3 = add1_6 + add1_7;
    assign add2_4 = add1_8 + add1_9;
    assign add2_5 = add1_10 + add1_11;
    assign add2_6 = add1_12 + add1_13;
    assign add2_7 = add1_14 + add1_15;
    

    assign add3_0 = add2_0 + add2_1;
    assign add3_1 = add2_2 + add2_3;
    assign add3_2 = add2_4 + add2_5;
    assign add3_3 = add2_6 + add2_7;
    

    assign add4_0 = add3_0 + add3_1;
    assign add4_1 = add3_2 + add3_3;
    

    assign final_sum = add4_0 + add4_1;
    

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            result <= 64'b0;
        end else begin
            result <= final_sum;
        end
    end
    

    assign z = result;
    
endmodule