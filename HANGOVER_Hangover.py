while True:

    n = float(input())
    
    if n == 0.0:
        
        break
    
    s,i,ans = 0,2,0
    
    while s < n:
        
        s += (1/i)
        
        ans += 1
        
        i += 1
        
    print(ans,"card(s)")
