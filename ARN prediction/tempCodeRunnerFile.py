n = len(sequence)
  dp = [[0]*n for _ in range(n)]

  for i in range(n):
      for j in range(n):
          if j<i-1:
            if is_complementary(sequence[i], sequence[j]):
                dp[i][j] = max(dp[i][j-1], dp[i+1][j], dp[i+1][j-1] + 1)
            else:
                dp[i][j] = max(dp[i][j-1], dp[i+1][j])

            for k in range(i+1, j):
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j])
  return dp