def decodeCount(word):
    n = len(word)
    if n == 0:
        return 0
        
    dp = [0] * (n + 1)
    dp[0] = 1
    dp[1] = 1 if word[0] != '0' else 0
    
    for i in range(2, n+1):
        if word[i - 1] != '0':
            dp[i] += dp[i-1]
            
        twoDigit = int(word[i-2:i])
        
        if 10 <= twoDigit and twoDigit <= 26:
            dp[i] += dp[i-2]
            
    return dp[n]

while True:
    word = input()
    if word == "0":
        break
    print(decodeCount(word))
