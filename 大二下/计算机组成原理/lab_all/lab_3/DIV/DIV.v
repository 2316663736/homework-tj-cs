module DIV(
    input [31:0] dividend,     // 被除数
    input [31:0] divisor,      // 除数
    input start,               // 启动除法运算
    input clock,               // 时钟
    input reset,               // 高电平有效
    output [31:0] q,           // 商
    output [31:0] r,           // 余数
    output busy                // 除法器忙标志位
);

    // 内部寄存器和信号定义
    reg [31:0] reg_q;          // 存储商的寄存器
    reg [31:0] reg_r;          // 存储余数的寄存器
    reg [31:0] reg_b;          // 存储除数的寄存器
    reg [5:0] count;           // 计数器，用于追踪已经处理的位数
    reg busy_reg;              // 忙状态寄存器
    reg r_sign;                // 余数符号标志
    reg dividend_sign;         // 记录被除数符号
    reg divisor_sign;          // 记录除数符号
    reg busy2;                 // 辅助忙状态变量
    
    // 处理结果的中间变量
    wire [32:0] sub_add;       // 加减法器结果
    wire [31:0] abs_dividend;  // 被除数的绝对值
    wire [31:0] abs_divisor;   // 除数的绝对值
    wire [31:0] final_r;       // 最终的余数
    wire [31:0] final_q;       // 最终的商
    
    // 计算绝对值
    assign abs_dividend = dividend[31] ? (~dividend + 1) : dividend;
    assign abs_divisor = divisor[31] ? (~divisor + 1) : divisor;
    
    // 加减法操作，非恢复余数法
    assign sub_add = r_sign ? 
                    ({reg_r, reg_q[31]} + {1'b0, reg_b}) : 
                    ({reg_r, reg_q[31]} - {1'b0, reg_b});
    
    // 最终结果的处理
    assign final_q = (dividend_sign ^ divisor_sign) ? (~reg_q + 1) : reg_q;
    
    // 纠正余数计算 - 余数符号应与被除数相同
    // 如果被除数为负，则余数为负；如果被除数为正，则余数为正
    // 此外，需要进行一步额外的校正
    wire [31:0] temp_r;
    assign temp_r = r_sign ? (reg_r + reg_b) : reg_r;  // 如果最后一步是减法且为负，需要恢复
    assign final_r = dividend_sign ? (~temp_r + 1) : temp_r;
    
    // 输出赋值
    assign q = final_q;
    assign r = final_r;
    assign busy = busy_reg;
    
    always @(posedge clock or posedge reset) begin
        if (reset) begin
            // 复位所有寄存器
            count <= 6'b0;
            busy_reg <= 1'b0;
            busy2 <= 1'b0;
            reg_q <= 32'b0;
            reg_r <= 32'b0;
            reg_b <= 32'b0;
            r_sign <= 1'b0;
            dividend_sign <= 1'b0;
            divisor_sign <= 1'b0;
        end 
        else begin
            busy2 <= busy_reg;
            
            if (start && !busy_reg) begin
                // 开始除法计算，初始化寄存器
                reg_r <= 32'b0;
                r_sign <= 1'b0;
                
                // 保存原始符号
                dividend_sign <= dividend[31];
                divisor_sign <= divisor[31];
                
                // 使用绝对值进行计算
                reg_q <= abs_dividend;
                reg_b <= abs_divisor;
                
                count <= 6'b0;
                busy_reg <= 1'b1;
            end 
            else if (busy_reg) begin
                // 执行除法迭代过程
                reg_r <= sub_add[31:0];        // 更新余数
                r_sign <= sub_add[32];         // 判断结果符号
                reg_q <= {reg_q[30:0], ~sub_add[32]}; // 移位并更新商位
                
                count <= count + 6'b1;         // 计数器加1
                
                // 完成32次迭代后，结束计算
                if (count == 6'd31) begin
                    busy_reg <= 1'b0;
                end
            end
        end
    end
endmodule
