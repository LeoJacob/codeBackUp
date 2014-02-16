def P(x):
    ans = 1
    for i in range(1, x + 1):
        ans *= i
    return ans

print(P(40) / P(20) / P(20))
