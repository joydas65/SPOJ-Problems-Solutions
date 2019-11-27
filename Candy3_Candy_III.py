for _ in range(int(input())):
    
    h = input()
    n = int(input())
    s = 0
    
    for i in range(n):
        
        s += int(input())
        
    #print(s)
        
    if s % n == 0:
        
        print("YES")
        
    else:
        
        print("NO")
