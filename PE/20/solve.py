def P(x):
    ans = 1
    for i in range(1, x + 1):
        ans *= i
    return ans

answer = 0
x = P(100)
while x:
    answer += x % 10
    x /= 10
print(answer)
