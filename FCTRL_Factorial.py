for _ in range(int(input())):
    
    n = int(input())
    
    c,i = 0,5
    
    while n//i >= 1:
        
        c += (n//i)
        
        i *= 5
        
    print(c)
