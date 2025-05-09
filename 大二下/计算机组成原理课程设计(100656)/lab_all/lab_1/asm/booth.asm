.text
# $2 : 存储被乘数
# $3 : 存储乘数
# $4 : 存储结果的高32位部分
# $5 : 存储结果的低32位部分
# $6 : 循环计数器，控制循环次数
# $7 : 临时寄存器，存储乘数的最低位
# $8 : 临时寄存器，用于比较操作
# $9 : 临时寄存器，用于存储前一位
# $10: 临时寄存器，用于位操作
main:
    addi $2, $0, 16    
    addi $3, $0, -1     

    addi $4, $0, 0      
    addi $5, $0, 0      
    addi $6, $0, 32 
    addi $9, $0, 0    
    
loop:
    beq $6, $0, done   

    andi $7, $3, 1      
   
    beq $7, $9, shift  
    

    bne $7, $0, sub_op  
    
    add $4, $4, $2    
    j shift
    
sub_op:
    sub $4, $4, $2    
    
shift:
    add $9, $7, $0    
    
    andi $10, $4, 1
    
    srl $5, $5, 1
    
    beq $10, $0, no_set_msb
    ori $5, $5, 0x80000000  
    
no_set_msb:
    sra $4, $4, 1

    srl $3, $3, 1

    addi $6, $6, -1

    j loop
    
done:
