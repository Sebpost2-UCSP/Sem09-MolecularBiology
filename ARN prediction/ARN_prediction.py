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

def nussinov(Secuencia):
    n = len(Secuencia)
    dp = [[0] * n for _ in range(n)]
    traceback = [[''] * n for _ in range(n)]  

    for gap in range(1, n):
        for i in range(n - gap):
            j = i + gap
            energy = reglas0(Secuencia[i], Secuencia[j])
            if energy != 0:
                dp[i][j] = min(dp[i][j - 1], dp[i + 1][j], dp[i + 1][j - 1] - energy)
                if dp[i][j] == dp[i + 1][j - 1] - energy:
                    traceback[i][j] = f"{Secuencia[i]}-{Secuencia[j]}"  # Base pair formed
            else:
                dp[i][j] = min(dp[i][j - 1], dp[i + 1][j])

            for k in range(i + 1, j):
                if dp[i][j] == dp[i][k] + dp[k + 1][j]:
                    traceback[i][j] = f"{traceback[i][k]} {traceback[k + 1][j]}"

    def backtrack(i, j):
        if i >= j:
            return ""
        elif traceback[i][j]:
            return f"{backtrack(i, j - 1)} {traceback[i][j]}"
        else:
            return f"{backtrack(i + 1, j)}"

    shortest_path = backtrack(0, n - 1)
    return dp, shortest_path

def print_TraceBack(shortest_path):
    path_list = shortest_path.split()
    reversed_list=path_list[::-1]
    for i in range(len(reversed_list)):
        print(f" {reversed_list[i]}")
        print(" | |")
    middle = len(Secuencia) // 2
    middle1= len(Secuencia) // 2-1
    print(f" {Secuencia[middle]}-{Secuencia[middle1]}")
    print(" / \\")
    print("|   |")
    print(" \\ /")

def print_matrix(matrix):
    for row in matrix:
        print(row)

Secuencia = "ACUCGAUUCCGAG"
Matriz, ShortP = nussinov(Secuencia)

print("Matriz de pares emparejados:")
print_matrix(Matriz)

print("Camino mas corto")
print_TraceBack(ShortP)
