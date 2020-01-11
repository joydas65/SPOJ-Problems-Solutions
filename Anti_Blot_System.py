for _ in range(int(input())):
    x = input()
    
    s = input()
    
    h = s.replace('=','+').split('+')
    
    v1,v2,v3 = -1,-1,-1
    
    try:
        v1 = int(h[0])
    except ValueError:
        v1 = None
        
    try:
        v2 = int(h[1])
    except ValueError:
        v2 = None
        
    try:
        v3 = int(h[2])
    except ValueError:
        v3 = None
        
    if v1 == None:
        print(str(v3-v2)+" + "+str(v2)+" = "+str(v3))
        
    elif v2 == None:
        print(str(v1)+" + "+str(v3-v1)+" = "+str(v3))
        
    else:
        
        print(str(v1)+" + "+str(v2)+" = "+str(v1+v2))
