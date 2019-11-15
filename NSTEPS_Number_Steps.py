for _ in range(int(input())):
    
    x,y = map(int, input().split())
    
    if x == y and x % 2 == 0:
        
        print(2*x)
        
    elif x == y and x % 2 == 1:
        
        print(2*x - 1)
        
    elif x - y == 2 and x % 2 == 0:
        
        print(x+y)
        
    elif x - y == 2 and x % 2 == 1:
        
        print(x+y-1)
        
    else:
        
        print("No Number")
