for _ in range(int(input())):
    
    n = int(input())
    
    men = list(map(int, input().split()))
    
    women = list(map(int, input().split()))
    
    men = sorted(men)
    
    women = sorted(women)
    
    ans = 0
    
    for i in range(n-1,-1,-1):
        
        ans += (men[i] * women[i])
        
    print(ans)
