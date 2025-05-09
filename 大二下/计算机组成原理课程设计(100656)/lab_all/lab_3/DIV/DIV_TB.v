// 有符号除法器测试台
module DIV_tb();
    // 测试信号
    reg [31:0] dividend;
    reg [31:0] divisor;
    reg start;
    reg clock;
    reg reset;
    wire [31:0] q;
    wire [31:0] r;
    wire busy;

    DIV div_inst(
        .dividend(dividend),
        .divisor(divisor),
        .start(start),
        .clock(clock),
        .reset(reset),
        .q(q),
        .r(r),
        .busy(busy)
    );
    

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
        wait(!busy);
        // 预期结果: q = 5, r = 0
        #20;
        

        dividend = 32'd15;
        divisor = 32'hFFFFFFFD; // -3 的补码
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = -5, r = 0
        #20;
        

        dividend = 32'd123456;
        divisor = 32'd1024;  // 2^10
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 120, r = 576
        #20;

        dividend = 32'hFFFE1DC0; // -123456 的补码
        divisor = 32'd1024;      // 2^10
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = -120, r = -576
        #20;
                dividend = 32'hFFFFFFFB; // -5 的补码
        divisor = 32'd10;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 0, r = -5
        #20;
        

        dividend = 32'h80000000; // -2^31 的补码
        divisor = 32'hFFFFFFFF;  // -1 的补码
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = -2^31 (溢出但处理为返回INT_MIN), r = 0
        #20;
        

        dividend = 32'hFFFFFF9C; // -100 的补码
        divisor = 32'd0;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 0xFFFFFFFF (错误码), r = -100
        #20;
        

        dividend = 32'hFFFFFFEC; // -20 的补码
        divisor = 32'd6;
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = -3, r = -2
        #20;
        

        dividend = 32'hFFFFFF9C; // -100 的补码
        divisor = 32'hFFFFFFE2;  // -30 的补码
        start = 1;
        #10;
        start = 0;
        wait(!busy);
        // 预期结果: q = 3, r = -10
        #20;
         
    end

    
endmodule