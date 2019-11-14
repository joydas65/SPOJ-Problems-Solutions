for _ in range(int(input())):
    
    a,b = map(str, input().split())
    
    a,b = a[::-1],b[::-1]
    
    x = int(a) + int(b)
    
    print(int(str(x)[::-1]))
