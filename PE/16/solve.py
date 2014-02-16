answer = 0
x = 2**1000
while x:
    answer += x % 10
    x /= 10
print(answer)
