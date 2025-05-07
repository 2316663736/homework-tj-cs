from itertools import permutations
from kanren import run, var, membero, goalify
import time
N=4
start_time = time.time()
def check_diagons(queens:tuple):
    for i in range(N):
        for j in range(i+1,N):
            if i+queens[i]==j+queens[j] or i-queens[i]==j-queens[j]:
                return False
    return True
all_permutations=tuple(permutations(range(N)))
queens=var("queens")
x=var("x")
so= run(
        0,
            queens,
            membero(queens, all_permutations),
            (goalify(check_diagons),( queens,),True)
    )
print(
   so
)
print(f"用时 {time.time()-start_time:.4f} 秒")





