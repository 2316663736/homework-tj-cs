`timescale 1ns/1ps
module DIVU_tb();
    // 测试信号
    reg [31:0] dividend;
    reg [31:0] divisor;
    reg start;
    reg clock;
    reg reset;
    wire [31:0] q;
    wire [31:0] r;
    wire busy;
    
    DIVU divu_inst(
        .dividend(dividend),
        .divisor(divisor),
        .start(start),
        .clock(clock),
        .reset(reset),
        .q(q),
        .r(r),
        .busy(busy)
    );
    
    // 时钟生成
    initial begin
        clock = 0;
        forever #5 clock = ~clock;
    end
    

    initial begin
        // 初始复位
        reset = 1;
        dividend = 0;
        divisor = 1;
        start = 0;
        #20;
        reset = 0;
        #10;

        dividend = 32'd20;
        divisor = 32'd4;
        start = 1;
        #10;
        start = 0;
        wait(!busy);  // 等待除法完成
        // 预期结果: q = 5, r = 0
        #20;

        dividend = 32'd17;
        divisor = 32'd5;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 3, r = 2
        #20;
        
        dividend = 32'd1234567;
        divisor = 32'd1000;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 1234, r = 567
        #20;

        dividend = 32'd123456;
        divisor = 32'd1024;  // 2^10
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 120, r = 576
        #20;
        
        dividend = 32'd98765;
        divisor = 32'd1;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 98765, r = 0
        #20;

        dividend = 32'd5;
        divisor = 32'd10;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 0, r = 5
        #20;
        

        dividend = 32'd123;
        divisor = 32'd0;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 0xFFFFFFFF (错误码), r = 123
        #20;
        

        dividend = 32'hFFFFFFFF;
        divisor = 32'd2;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 0x7FFFFFFF, r = 1
        #20;

        dividend = 32'd9876543;
        divisor = 32'd12345;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 800, r = 1443
        
    end

endmodule