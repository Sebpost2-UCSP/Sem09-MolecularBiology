#include <iostream>
#include <vector>
#include <string>

std::string Bacteria = "tcaagcgtta gagaagtcat tatgtgataa aaaaattcaa cttggtatca acttaactaa\
 gggtcttggt gctggtgctt tgcctgatgt tggtaaaggt gcagcagaag aatcaattga\
 tgaaattatg gagcatataa aagatagcca tatgctcttt atcacagcag ggatgggtgg\
 tggtactgga acaggtgctg caccggtaat tgcaaaagca gccagagaag caagagcggt\
 agttaaagat aaaggagcaa aagaaaaaaa gatactgact gttggagttg taactaagcc\
 gttcggtttt gaaggtgtgc gacgtatgcg cattgcagag cttggacttg aagagttgca\
 aaaatacgta gatacactta ttgtcattcc caatcaaaat ttatttagaa ttgctaacga\
 gaaaactaca tttgctgacg catttcaact cgccgataat gttctgcata ttggcataag\
 aggagtaact gatttgatga tcatgccagg actgattaat cttgattttg ctgatataga\
 aacagtaatg agtgagatgg gtaaagcaat gattggtact ggagaggcag aaggagaaga\
 tagggcaatt agcgctgcag aggctgcgat atctaatcca ttacttgata atgtatcaat\
 gaaaggtgca caaggaatat taattaatat tactggtggt ggagatatga ctctatttga\
 agttgatgct gcagccaata gagtgcgtga agaagtcgat gaaaatgcaa atataatatt\
 tggtgccact tttgatcagg cgatggaagg aagagttaga gtttctattc ttgcaactgg\
 cattgatagc tgtaacgaca attcatctgt taatcaaaac aagatcccag cagaggaaaa\
 aaattttaaa tggccttata atcaagttcc tatatcagaa acaaaagaat atgcttcaac\
 tgagcaaaca aacgaaagag ttaagtgggg cagcaatgtt tatgatatac cagcttatct\
 aagaagaaaa aaataatgca attttggcta ctcaagtcgg";

std::string Sars_Cov = "attaaaggtt tataccttcc caggtaacaa accaaccaac tttcgatctc ttgtagatct\
 gttctctaaa cgaactttaa aatctgtgtg gctgtcactc ggctgcatgc ttagtgcact\
 cacgcagtat aattaataac taattactgt cgttgacagg acacgagtaa ctcgtctatc\
 ttctgcaggc tgcttacggt ttcgtccgtg ttgcagccga tcatcagcac atctaggttt\
 cgtccgggtg tgaccgaaag gtaagatgga gagccttgtc cctggtttca acgagaaaac\
 acacgtccaa ctcagtttgc ctgttttaca ggttcgcgac gtgctcgtac gtggctttgg\
 agactccgtg gaggaggtct tatcagaggc acgtcaacat cttaaagatg gcacttgtgg\
 cttagtagaa gttgaaaaag gcgttttgcc tcaacttgaa cagccctatg tgttcatcaa\
 acgttcggat gctcgaactg cacctcatgg tcatgttatg gttgagctgg tagcagaact\
 cgaaggcatt cagtacggtc gtagtggtga gacacttggt gtccttgtcc ctcatgtggg\
 cgaaatacca gtggcttacc gcaaggttct tcttcgtaag aacggtaata aaggagctgg\
 tggccatagt tacggcgccg atctaaagtc atttgactta ggcgacgagc ttggcactga\
 tccttatgaa gattttcaag aaaactggaa cactaaacat agcagtggtg ttacccgtga\
 actcatgcgt gagcttaacg gaggggcata cactcgctat gtcgataaca acttctgtgg\
 ccctgatggc taccctcttg agtgcattaa agaccttcta gcacgtgctg gtaaagcttc\
 atgcactttg tccgaacaac tggactttat tgacactaag aggggtgtat actgctgccg\
 tgaacatgag catgaaattg cttggtacac ggaacgttct gaaaagagct atgaattgca\
 gacacctttt gaaattaaat tggcaaagaa atttgacacc ttcaatgggg aatgtccaaa";

std::string Influenza = " atggaagcaa tatcactgat gactatacta ctggtggtaa caacaagtaa tgcagacaaa\
 atctgcatcg gtcaccaatc aacaaattcc acggaaactg tagacacgct aacagaaaca\
 aatgttcctg taacacaagc caaagaattg ctccacacag aacacaatgg gatgctatgt\
 gcaacaaatc tgggacgtcc tcttatccta gacacatgca ccattgaagg actgatctat\
 ggcaacccat cttgtgacat gctgttagga ggaagggaat ggtcctacat cgtcgaaaga\
 ccgtccgcag taaatggaac atgctaccct ggaaatgtag aaaacctaga ggaacttaga\
 acacttttta gctcctctag ttcttaccaa agagtccaac tctttccaga ctcaatctgg\
 aatgtgactt acactgggac aagcaaatca tgttcagatt cattctatag gaatatgaga\
 tggttaactc aaaagaatgg gggttatcca attcaagatg cccagtacac aaacaatagg\
 ggaaaggaca ttcttttcgt gtggggcata catcatccac caaccgatac tgcacagacg\
 aatttatata caaggaccga cacaacaaca agtgtaacaa cggagacttt agataggacc\
 ttcaaaccat tgatagggcc aaggcccctt gtcaatggtc taattggaag aattaattac\
 tattggtcgg tactaaaacc aggccaaacg ttgcgagtga gatcaaatgg aaatctaatt\
 gctccatggt ttggacatgt tctctcaggt gagagccatg tgagaatcct gagaactgat\
 ttaagcagcg gtaattgtgt ggtacaatgc cagactgaaa aaggtggcct aaacagtaca\
 atgccatttc acaacatcag caaatatgct tttgggacct gtcccaaata tattggagtc\
 aagagtctca aactggcaat tggccttaga aacgtacatg ctaggtcaag tagaggacta\
 ttcggagcga tagctggatt catagaagga ggttggccag gactagtcgc cggttggtat";

void print(std::vector<std::vector<int>> m, int sizeRow, int sizeCol) {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            std::cout << "|" << m[i][j];
        }
        std::cout << "|\n";
    }
}

bool count_vec(std::vector<bool> vec) {
    for (int i = 0; i < 3; i++) {
        if (vec[i] != 0) {
            return 1;
        }
    }
    return 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void needleman_wunsch(const std::string& str1, const std::string& str2) {
    int m = str1.length();
    int n = str2.length();
    int Gap_valor = -2;

    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> direction(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * Gap_valor;
        direction[i][0] = -1;
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * Gap_valor;
        direction[0][j] = -2;
    }

    int paths = 0;
    int counter = -1;
    std::vector<std::vector<int>> direction_copy(m + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> TotalDirections(m + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<std::vector<bool>>> Paths_v(m + 1, std::vector<std::vector<bool>>(n + 1, std::vector<bool>(4, 0)));
    while (paths != counter) {
        direction_copy = direction;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                int match = (str1[i - 1] == str2[j - 1]) ? 1 : -1;
                int Arriba = dp[i - 1][j] + Gap_valor;
                int Izquierda = dp[i][j - 1] + Gap_valor;
                int Diagonal = dp[i - 1][j - 1] + match;

                dp[i][j] = max(max(Arriba, Izquierda), Diagonal);

                if (dp[i][j] == Arriba) {
                    TotalDirections[i][j]++;
                    //Paths_v[i][j][0] = 1;
                }
                if (dp[i][j] == Izquierda) {
                    TotalDirections[i][j]++;
                    //Paths_v[i][j][1] = 1;
                }
                if (dp[i][j] == Diagonal) {
                    TotalDirections[i][j]++;
                    //Paths_v[i][j][2] = 1;
                }

                if (TotalDirections[i][j] > 1 and Paths_v[i][j][3]==0) {
                    paths += 1;
                    std::cout << "i: " << i << " | j:" << j << "\n";
                    TotalDirections[i][j] = 0;
                }

                Paths_v[i][j][3] = 1;

                if (dp[i][j] == Arriba and Paths_v[i][j][0]!=1) {
                    direction_copy[i][j] = -1; // Arriba
                    Paths_v[i][j][0] = 1;
                    //dp[i - 1][j] = -10000000;
                }
                if (dp[i][j] == Izquierda and Paths_v[i][j][1] != 1) {
                    direction_copy[i][j] = -2; // Izquierda
                    Paths_v[i][j][1] = 1;
                    //dp[i][j - 1] = -10000000;
                }
                if(dp[i][j]==Diagonal and Paths_v[i][j][2] != 1) {
                    direction_copy[i][j] = -3; // Diagonal
                    Paths_v[i][j][2] = 1;
                    //dp[i - 1][j - 1] = -10000000;
                }
            }
        }

        //print(dp, m + 1, n + 1);
        print(direction_copy, m+1, n+1);
        std::string alignment1;
        std::string alignment2;
        int i = m, j = n;

        while (i > 0 && j > 0) {
            int dir = direction_copy[i][j];
            if (dir == -3) {
                //std::cout << "Working?: " << str1[i-1] << " | " << str2[i-1] << "\n";
                alignment1.push_back(str1[i - 1]);
                alignment2.push_back(str2[j - 1]);
                i--;
                j--;
            }
            else if (dir == -1) {
                alignment1.push_back(str1[i - 1]);
                alignment2.push_back('-');
                i--;
            }
            else if (dir == -2) {
                alignment1.push_back('-');
                alignment2.push_back(str2[j - 1]);
                j--;
            }
        }

        while (i > 0) {
            alignment1.push_back(str1[i - 1]);
            alignment2.push_back('-');
            i--;
        }
        while (j > 0) {
            alignment1.push_back('-');
            alignment2.push_back(str2[j - 1]);
            j--;
        }

        std::reverse(alignment1.begin(), alignment1.end());
        std::reverse(alignment2.begin(), alignment2.end());

        std::cout << alignment1<<"\n"<<alignment2 << std::endl;

        counter++;
    }
    std::cout << "Puntaje total: " << dp[m][n] << std::endl;
}

int main() {
    std::string sequence1, sequence2;
    int gap_penalty;

    sequence1 = "abb";
    sequence2 = "ab";

    needleman_wunsch(sequence1, sequence2);

    return 0;
}