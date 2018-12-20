priority = dict()

priority['^'] = 5

priority['/'] = 4

priority['*'] = 4

priority['-'] = 3

priority['+'] = 3

priority['('] = 2

letters = "abcdefghijklmnopqrstuvwxyz"

operators = "^/*+-"

output = ""

st = []

for _ in range(int(input())):
    
    s = input()
    
    for i in s:
        
        if i in letters:
            
            output += i
            
        elif i == '(':
            
            st.append(i)
            
        elif i == ')':
            
            while True:
                
                if st[-1] == '(':
                    
                    break
                
                output += st[-1]
                
                st.pop()
                
            st.pop()
            
        elif i in operators:
            
            while st != [] and priority[st[-1]] >= priority[i]:
                
                output += st[-1]
                
                st.pop()
                
            st.append(i)
            
    print(output)
    
    output = ""
    
    st = []
