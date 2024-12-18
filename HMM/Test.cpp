#include <iostream>
#include <vector>
#include <string>

int main() {
    std::vector<std::string> input = {
        "VGA--HAGEY",
        "V----NVDEV",
        "VEA--DVAGH",
        "VKG------D",
        "VYS--TYETS",
        "FNA--NIPKH",
        "IAGADNGAGY"
    };

    // Initialize an array to store letter counts for each column
    const int numRows = 26; // One row for each letter (a-z)
    const int numCols = input[0].size();
    std::vector<std::vector<int>> letterCounts(numRows, std::vector<int>(numCols, 0));

    // Iterate through each column
    for (size_t col = 0; col < numCols; ++col) {
        for (size_t row = 0; row < input.size(); ++row) {
            char c = std::tolower(input[row][col]);
            if (std::isalpha(c)) {
                int letterIndex = c - 'a';
                letterCounts[letterIndex][col]++;
            }
        }
    }

    // Print the results
    for (int row = 0; row < numRows; ++row) {
        char letter = 'a' + row;
        std::cout << letter << ": ";
        for (int col = 0; col < numCols; ++col) {
            std::cout << letterCounts[row][col] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
