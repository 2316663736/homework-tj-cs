.text
# $2-$6  :待排序数组 (排序前：5,3,8,1,6；排序后：1,3,5,6,8)
# $7     外循环计数器 (从n-1递减到0)
# $8     内循环索引 (从0递增，用于遍历未排序部分)
# $9     内循环终止值 (外循环剩余次数)
# $10    当前元素的值 (用于比较交换)
# $11    下一个元素的值 (用于比较交换)
# $12    比较结果 (1=需要交换，0=不需要交换)
# $13-$16 : 存储常数值0-3 
main:
    addi $2, $0, 5    
    addi $3, $0, 3   
    addi $4, $0, 8     
    addi $5, $0, 1   
    addi $6, $0, 6     
    
    addi $7, $0, 4   
    
outer_loop:
    beq $7, $0, sort_done
    
    addi $8, $0, 0     
    add $9, $0, $7    
    
inner_loop:
    beq $8, $9, inner_done
    
    addi $13, $0, 0    
    addi $14, $0, 1    
    addi $15, $0, 2   
    addi $16, $0, 3   
    
    beq $8, $13, load_01 
    beq $8, $14, load_12
    beq $8, $15, load_23 
    beq $8, $16, load_34  
    j inner_next         # 正常不会运行到
    
load_01:

    add $10, $0, $2    
    add $11, $0, $3 

    slt $12, $11, $10   
    beq $12, $0, inner_next  
    
    add $2, $0, $11     
    add $3, $0, $10    
    j inner_next
    
load_12:
    add $10, $0, $3    
    add $11, $0, $4    
    
    slt $12, $11, $10 
    beq $12, $0, inner_next    

    add $3, $0, $11     
    add $4, $0, $10     
    j inner_next
    
load_23:
    add $10, $0, $4
    add $11, $0, $5  
    
    slt $12, $11, $10 
    beq $12, $0, inner_next  
    
    add $4, $0, $11  
    add $5, $0, $10     
    j inner_next
    
load_34:
    add $10, $0, $5    
    add $11, $0, $6    
    
    slt $12, $11, $10  
    beq $12, $0, inner_next 
    
    add $5, $0, $11     
    add $6, $0, $10     
    
inner_next:
    addi $8, $8, 1
    j inner_loop
    
inner_done:
    addi $7, $7, -1
    j outer_loop
    
sort_done:
  