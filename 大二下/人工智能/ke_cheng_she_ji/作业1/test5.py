from kanren import run, eq, var, conde
from kanren.core import lall, success, fail
import time

# 皇后之间不能互相攻击
def no_attack(q1, q2, col1, col2):
    def goal(s):

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
    
    # 只求解一半的问题
    half_n = (n + 1) // 2
    
    # 创建变量，每个变量表示一列中皇后所在的行
    queens = [var() for _ in range(n)]
    constraints = []
    
    # 第一个皇后限制在前半部分
    constraints.append(conde(*[[eq(queens[0], row)] for row in range(half_n)]))
    
    for i in range(1, n):
        constraints.append(conde(*[[eq(queens[i], row)] for row in range(n)]))
        for j in range(i):
            constraints.append(no_attack(queens[j], queens[i], j, i))
    
    partial_solutions = run(0, queens, *constraints)
    
    # 对称
    if n % 2 == 1 and half_n > 1:  # 奇数 
        middle = half_n - 1
        middle_solutions = [sol for sol in partial_solutions if sol[0] == middle]
        remaining = [sol for sol in partial_solutions if sol[0] != middle]
    else:
        middle_solutions = []
        remaining = partial_solutions
    
  
    full_solutions = list(partial_solutions)
    for sol in remaining:
        
        mirror_sol = tuple(n - 1 - pos for pos in sol)
        if mirror_sol not in full_solutions:
            full_solutions.append(mirror_sol)
    
    end_time = time.time()
    return full_solutions, end_time - start_time

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

'''各个版本只有solve_n_queens不一样,其他都一样'''

# #第一版
# def solve_n_queens(n):
#     start_time = time.time()
    
#     queens = [var() for _ in range(n)] 

#     domain_constraints = []
#     for q in queens:
#         domain_constraints.append(conde(*[[eq(q, i)] for i in range(n)]))
    

#     attack_constraints = []
#     for i in range(n):
#         for j in range(i+1, n):
#             attack_constraints.append(no_attack(queens[i], queens[j], i, j))
    
#     solutions = run(0, queens, *(domain_constraints + attack_constraints))
    
#     end_time = time.time()
#     runtime = end_time - start_time
    
#     return solutions, runtime

# #第二版
# def solve_n_queens(n):
#     start_time = time.time()
    
#     queens = [var() for _ in range(n)]
    
#     constraints = []
#     for i in range(len(queens)):
#         q = queens[i]
#         constraints.append(conde(*[[eq(q, row)] for row in range(n)]))
#         for j in range(i):
#             constraints.append(no_attack(queens[j], q, j, i))

#     solutions = run(0, queens, *constraints)
    
#     end_time = time.time()
#     return solutions, end_time - start_time




