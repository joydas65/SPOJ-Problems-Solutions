while True:

    n = int(input())
    
    num = n
    
    if n == -1:
        
        break
    
    v,arr = 0,[]
    
    while num >= 1:
        
        x = int(input())
        
        arr.append(x)
        
        v += x
        
        num -= 1
        
    if v % n != 0:
        
        print("-1")
        
    else:
        
        f,ans = v//n,0
        
        for i in arr:
            
            if i > f:
                
                ans += (i - f)
                
        print(ans)
