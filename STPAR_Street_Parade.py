n = int(input())

while n != 0:

    arr = list(map(int, input().split()))

    l = [i for i in range(1,n+1)]

    INDEX = 0

    stack = [0 for i in range(n)]

    top = -1

    flag = 0

    for i in range(n):

        if arr[i] == l[INDEX]:

            INDEX += 1

        else:

            while top >= 0:

                if stack[top] == l[INDEX]:

                    INDEX += 1

                else:

                    break

                top -= 1

            stack[top + 1] = arr[i]

            top += 1

            temp = top

            while temp > 0:

                if stack[temp] > stack[temp - 1]:

                    flag = 1

                    break

                temp -= 1

            if flag == 1:

                break

    if flag == 1:

        print("no")

    else:

        print("yes")
        
    n = int(input())
