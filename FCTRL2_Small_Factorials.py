arr = [0 for i in range(101)]

arr[0] = 1

for i in range(1,101):
    
    arr[i] = i * arr[i-1]

for _ in range(int(input())):
    
    print(arr[int(input())])
