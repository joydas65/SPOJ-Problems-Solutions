while True:
    
    n = int(input())
    
    if n == 0:
        
        break
    
    s = input()
    
    l = len(s)
    
    k,c,arr = 0,0,[]
    
    while True:
        
        if c % 2 == 0:
            
            arr.append(s[k:k+n])
            
        else:
            
            arr.append(s[k:k+n][::-1])
            
        k += n
        
        if k >= l:
            
            break
        
        c += 1
        
    c = 0
    
    #print(arr)
    
    while c < n:
        
        for i in arr:
            
            print(i[c],end="")
            
        c += 1
        
    print()
        
        
