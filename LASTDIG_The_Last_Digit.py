d = dict()
d[0] = (0,0)
d[1] = (1,1)
d[2] = (2,4,8,6)
d[3] = (3,9,7,1)
d[4] = (4,6)
d[5] = (5,5)
d[6] = (6,6)
d[7] = (7,9,3,1)
d[8] = (8,4,2,6)
d[9] = (9,1)

for _ in range(int(input())):
    
    a,b = map(int, input().split())
    
    if b == 0:
        
        print(1)
        
    else:
    
        v = len(d[a % 10])
        
        print(d[a % 10][(b % v) - 1])
