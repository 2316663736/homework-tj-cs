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
    
    queens = [var() for _ in range(n)]
    
    constraints = []
    for i in range(len(queens)):
        q = queens[i]
        constraints.append(conde(*[[eq(q, row)] for row in range(n)]))
        for j in range(i):
            constraints.append(no_attack(queens[j], q, j, i))

    solutions = run(0, queens, *constraints)
    
    end_time = time.time()
    return solutions, end_time - start_time

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

