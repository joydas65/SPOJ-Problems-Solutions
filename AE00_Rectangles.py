n = int(input())

i,ans = 1,0

while i*i <= n:
    
    ans += ((n//i) - i + 1)
    
    i += 1
    
print(ans)
