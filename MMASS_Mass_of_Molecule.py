s = input().strip()

d = {'H':1,'C':12,'O':16}

atoms = ['H','C','O']

nums = [2,3,4,5,6,7,8,9]

st = ['(']

weight = 0

x = 0

for i in s:
    
    if i in atoms:
        
        st.append(d[i])
        
    elif i == '(':
        
        st.append(i)
        
    elif i == ')':
        
        x = 0
        
        while st[-1] != '(':
            
            x += st[-1]
            
            st.pop()
            
        st.pop()
        
        st.append(x)
        
    elif int(i) in nums:
        
        x = st[-1] * int(i)
        
        st.pop()
        
        st.append(x)
        
while st[-1] != '(':
    
    weight += st[-1]
    
    st.pop()
        
print(weight)
