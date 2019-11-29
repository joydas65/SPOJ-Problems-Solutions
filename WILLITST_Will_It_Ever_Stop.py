n = int(input())

if n % 3 == 0:
    
    print("NIE")
    
else:
    
    flag = 0
    
    while n > 1:
        
        if n % 3 == 0:
            
            flag = 1
            
            break
        
        if n % 2 == 0:
            
            n //= 2
            
        else:
            
            n = (n*3) + 3
            
    if flag == 1:
        
        print("NIE")
        
    else:
        
        print("TAK")
