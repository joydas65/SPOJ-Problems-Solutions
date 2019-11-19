from collections import defaultdict

import sys

def compute(n, d):
    
    if n == 0:
        
        return 0
    
    x = d[n]
    
    if x == 0:
        
        x = max(n, compute(n//2, d) + compute(n//3, d) + compute(n//4, d))
        
        d[n] = x
    
    return x
    
d = defaultdict(lambda : 0)

for line in sys.stdin:
    
    print(compute(int(line), d))
