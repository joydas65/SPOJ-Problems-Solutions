val = 1

while True:
    
    s = input()
    
    if s[0] == '-':
        
        break
        
    else:
        
        opening, ans = 0, 0
        
        for i in s:
            
            if i == '{':
                
                opening += 1
                
            elif i == '}':
                
                if opening > 0:
                
                    opening -= 1
                
                else:

                    opening += 1

                    ans += 1
                
        ans += opening // 2
        
        print(val,end = "")
        
        print(". {one}".format(one = ans))
        
        val += 1
