.text
#$2,$3:临时存储斐波那契数
#$4 :表示取第n个斐波那契数
#$5 :作为计数器，判断循环是否结束
#$7 :用于对特殊情况特判
#$1 :最后存储结果
main:
    addi $2, $0, 0      
    addi $3, $0, 1    
    addi $4, $0, 7      
    
    # 特殊情况判断
    addi $7, $0, 1     
    beq $4, $0, fib_zero
    beq $4, $7, fib_one   
    
    # 初始化循环计数器
    addi $5, $0, 1      # 从位置1开始（已有0和1）
    
fibonacci_loop:
    beq $5, $4, fibonacci_done
    
    add $6, $2, $3
    
    add $2, $0, $3    
    add $3, $0, $6   
    
    addi $5, $5, 1

    j fibonacci_loop
    
fib_zero:
    add $1, $0, $2
    j end_program
    
fib_one:
    add $1, $0, $3
    j end_program
    
fibonacci_done:
    add $1, $0, $3
    
end_program:
