def reglas0(a, b):
    if ((a == 'A' and b == 'U') or (a == 'U' and b == 'A') or
            (a == 'C' and b == 'G') or (a == 'G' and b == 'C')):
        return 1
    else:
        return 0
    
def reglas1(a, b):
    if ((a == 'G' and b == 'U') or (a == 'U' and b == 'G')):
        return 1
    if ((a == 'A' and b == 'U') or (a == 'U' and b == 'A')):
        return 4
    if ((a == 'C' and b == 'G') or (a == 'G' and b == 'C')):
        return 5
    else:
        return 0

def nussinov(sequence):
    n = len(sequence)
    dp = [[0]*n for _ in range(n)]

    for gap in range(1, n):
        for i in range(n-gap):
            j = i + gap
            energy=reglas0(sequence[i], sequence[j])
            if energy!=0:
                dp[i][j] = min(dp[i][j-1], dp[i+1][j], dp[i+1][j-1] - energy)
            else:
                dp[i][j] = min(dp[i][j-1], dp[i+1][j])

            for k in range(i+1, j):
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j])
    return dp

sequence = "GGAAAUCC"
matrix = nussinov(sequence)

for row in matrix:
    print(row)
