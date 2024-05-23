#include <vector>
#include <algorithm>
#include <iostream>

int Reglas0(char a, char b) {
    if((a == 'A' && b == 'U') || (a == 'U' && b == 'A') ||
            (a == 'C' && b == 'G') || (a == 'G' && b == 'C')){
              return 1;
    }
    else{
      return 0;
    }
}

int Reglas1(char a, char b) {
    if((a == 'G' && b == 'U') || (a == 'U' && b == 'G')){
      return 1;
    }
    else if((a == 'A' && b == 'U') || (a == 'U' && b == 'A')){
      return 4;
    }
    else if((a == 'C' && b == 'G') || (a == 'G' && b == 'C')){
      return 5;
    }
    else{
      return 0;
    }
}

std::vector<std::vector<int>> nussinov(std::string sequence) {
    int n = sequence.length();
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
    int energy=0;

    for (int gap = 1; gap < n; gap++) {
        for (int i = 0, j = gap; j < n; i++, j++) {
            energy=Reglas0(sequence[i], sequence[j]);
            if (energy)
                dp[i][j] = std::min({dp[i][j - 1], dp[i + 1][j], dp[i + 1][j - 1] - energy});
            else
                dp[i][j] = std::min(dp[i][j - 1], dp[i + 1][j]);

            for (int k = i + 1; k < j; k++)
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }
    }

    return dp;
}


int main() {
    std::string sequence = "GGAAAUCC";
    std::vector<std::vector<int>> matrix = nussinov(sequence);

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
          if(j<i-1){
            std::cout << "-" << " ";
          }
          else{
            std::cout << matrix[i][j] << " ";
          }
        }
        std::cout << std::endl;
    }

    return 0;
}
