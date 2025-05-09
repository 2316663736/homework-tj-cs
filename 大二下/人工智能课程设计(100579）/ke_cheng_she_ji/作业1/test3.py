from kanren import run, eq, var, conde
from kanren.core import lall, success, fail
import time

# 使用有效的约束方法，避免直接对变量进行算术操作
def no_attack(q1, q2, col1, col2):
    def goal(s):
        # 获取变量的值，如果已经绑定的话
        q1_val = q1 if not hasattr(q1, '_id') else s.get(q1, q1)
        q2_val = q2 if not hasattr(q2, '_id') else s.get(q2, q2)
        
        # 如果任一变量未绑定，则延迟评估
        if hasattr(q1_val, '_id') or hasattr(q2_val, '_id'):
            return success(s)
        
        # 行相等检查
        if q1_val == q2_val:
            return fail(s)
        
        # 对角线检查
        if abs(q1_val - q2_val) == abs(col1 - col2):
            return fail(s)
        
        return success(s)
    return goal

def solve_n_queens(n):
    start_time = time.time()
    
    # 创建变量，每个变量表示一列中皇后所在的行
    queens = [var() for _ in range(n)]
    

    domain_constraints = []
    for q in queens:
        domain_constraints.append(conde(*[[eq(q, i)] for i in range(n)]))
    

    attack_constraints = []
    for i in range(n):
        for j in range(i+1, n):
            attack_constraints.append(no_attack(queens[i], queens[j], i, j))
    
    solutions = run(0, queens, *(domain_constraints + attack_constraints))
    
    end_time = time.time()
    runtime = end_time - start_time
    
    return solutions, runtime

def main():
    n=8
    solutions, runtime = solve_n_queens(n)
    print(f"找到 {len(solutions)} 个解决方案，用时 {runtime:.4f} 秒")
    
    for solution in solutions:
        print(solution)
# def main():
#     while True:
#         try:
#             n = int(input("请输入皇后数量 (输入0退出): "))
#             if n == 0:
#                 break
#             elif n < 4:
#                 print("请输入至少4的值以获得有意义的解")
#                 continue
                
#             solutions, runtime = solve_n_queens(n)
#             print(f"找到 {len(solutions)} 个解决方案，用时 {runtime:.4f} 秒")
            
#             for i, solution in enumerate(solutions):
#                         print(solution)
                
#         except ValueError:
#             print("请输入有效的整数")

if __name__ == "__main__":
    main()

