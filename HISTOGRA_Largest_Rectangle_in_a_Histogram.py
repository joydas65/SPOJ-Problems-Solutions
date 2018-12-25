while True:
    
    ans = 0

    index = 0
    
    histograms = []
    
    temp = 0
    
    x = list(map(int, input().split()))
    
    if x[0] == 0:
        
        break
        
    x = x[1:]
        
    while index < len(x):
        
        if histograms == [] or (x[histograms[-1]] <= x[index]):
            
            histograms.append(index)
            
            index += 1
            
        else:
            
            stackTop = histograms.pop()
            
            if histograms == []:
                
                temp = x[stackTop] * index
                
            else:
                
                temp = x[stackTop] * (index - histograms[-1] - 1)
                
            ans = max(ans,temp)
            
    while histograms != []:
        
        stackTop = histograms.pop()
        
        if histograms == []:
                
            temp = x[stackTop] * index
                
        else:
                
            temp = x[stackTop] * (index - histograms[-1] - 1)
            
        ans = max(ans,temp)
        
    print(ans)
    
    ans = 0
