#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

std::vector<std::string> FirstTest={{"ATTGCCATT"},{"ATGGCCATT"},{"ATCCAATTTT"},{"ATCTTCTT"},{"ACTGACC"}};

std::string BRCA_A[2]={"TGCCGGCAGGGATGTGCTTG","TGCTTGCAGTTTGCTTTCACTGATGGA"};
std::string BRCA_B[2]={"GTTTAGGTTTTTGCTTATGCAGCATCCA","TCAGGTACCCTGACCTTCTCTGAAC"};
std::string BRCA_C[2]={"GGAAAAGCACAGAACTGGCCAACA","GTGGGTTGTAAAGGTCCCAAATGGT"};
std::string BRCA_D[2]={"GCCAGTTGGTTGATTTCCACCTCCA","TGCCTTGGGTCCCTCTGACTGG"};
std::string BRCA_E[2]={"ACCCCCGACATGCAGAAGCTG","GTGGTGCATTGATGGAAGGAAGCA"};
std::string BRCA_F[2]={"TGACGTGTCTGCTCCACTTCCA","AGTGAGAGGAGCTCCCAGGGC"};

std::vector<std::string*>BRCA{BRCA_A,BRCA_B,BRCA_C,BRCA_D,BRCA_E,BRCA_F};

void print(std::vector<std::vector<int>> m) {
    std::cout<<"\n";
    for (int i = 0; i < m.size(); i++) {
        for (int j = 0; j < m.size(); j++) {
            std::cout << "|" << m[i][j];
        }
        std::cout << "|\n";
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

std::pair<int, std::pair<std::string,std::string>> needleman_wunsch(const std::string& str1, const std::string& str2 ) {
    int m = str1.length();
    int n = str2.length();
    int gap_penalty=-2;

    // Create score and direction matrices
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
    std::vector<std::vector<int>> direction(m + 1, std::vector<int>(n + 1, 0));

    // Initialize gaps (first row and column)
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i * gap_penalty;
        direction[i][0] = -1; // Gap in str1
    }

    for (int j = 0; j <= n; j++) {
        dp[0][j] = j * gap_penalty;
        direction[0][j] = -2; // Gap in str2
    }

    //print(dp, m, n);
    //print(direction, m, n);

    // Calculate score and direction for each cell
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int match = (str1[i - 1] == str2[j - 1]) ? 1 : -1;
            int up = dp[i - 1][j] + gap_penalty;
            int left = dp[i][j - 1] + gap_penalty;
            int diag = dp[i - 1][j - 1] + match;

            dp[i][j] = max(max(up, left), diag);
            if (dp[i][j] == up) {
                direction[i][j] = -1; // Up
            }
            else if (dp[i][j] == left) {
                direction[i][j] = -2; // Left
            }
            else {
                direction[i][j] = -3; // Diagonal
            }
        }
    }

    // Backtrack to reconstruct alignment
    std::string alignment1, alignment2;
    int i = m, j = n;

    while (i > 0 && j > 0) {
        int dir = direction[i][j];
        if (dir == -3) {
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
        else {
            alignment1.push_back('-');
            alignment2.push_back(str2[j - 1]);\
            j--;
        }
    }

    // Handle remaining characters at the beginning
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

    // Reverse alignments for proper order
    std::reverse(alignment1.begin(), alignment1.end());
    std::reverse(alignment2.begin(), alignment2.end());

    return std::make_pair(dp[m][n], std::make_pair(alignment1,alignment2));
}

void Star_alignment(std::vector<std::string>Cadenas){

    int CadenasSize=Cadenas.size();
    int raw_score=0, max_stringSize=0;
    std::string first_alignment="",second_alignment="";
    std::pair<int, std::pair<std::string,std::string>> alignment;
    std::vector<std::vector<int>> Scores(CadenasSize,std::vector<int>(CadenasSize));
    std::vector<std::vector<std::vector<std::string>>> Alignments(CadenasSize, 
    std::vector<std::vector<std::string>>(CadenasSize, 
    std::vector<std::string>(2)));
    std::vector<int> Row_Scores(CadenasSize);
    for(int i=0; i<CadenasSize; i++){
        for(int j=0; j<i; j++){
            alignment = needleman_wunsch(Cadenas[i], Cadenas[j]);
            raw_score=alignment.first;
            first_alignment=alignment.second.first;
            second_alignment=alignment.second.second;
            Scores[i][j]=raw_score;
            Scores[j][i]=raw_score;
            Alignments[i][j][0]=first_alignment;
            Alignments[i][j][1]=second_alignment;
            Alignments[j][i][0]=second_alignment;
            Alignments[j][i][1]=first_alignment;
            Row_Scores[i]+=raw_score;
            Row_Scores[j]+=raw_score;
            std::cout <<"\nAlineando cadena numero "<<i<<" Con cadena numero "<<j<<"\n"<< Alignments[i][j][0]+"\n"+Alignments[i][j][1] << std::endl;
        }
        if(max_stringSize<first_alignment.length()){
            max_stringSize=first_alignment.length();
        }
    }
    print(Scores);

    int max=Row_Scores[0];
    int max_index=0;
    for(int i=1; i<Row_Scores.size(); i++){
        if(Row_Scores[i]>max){
            max=Row_Scores[i];
            max_index=i;
        }
    }
    std::cout<<"\nEl maximo score es: "<<max<< ", y su numero de cadena es: "<<max_index<<".\n\nSecuencias alineadas con cadena S"<<max_index<<":"<<std::endl;

    while(max_stringSize>Alignments[max_index][1][0].length()){
            Alignments[max_index][1][0]+="-";
        }
    std::cout<<Alignments[max_index][1][0]<<std::endl;

    for(int i=0; i<Row_Scores.size(); i++){
        if(Alignments[max_index][i][1].length()==0){
            continue;
        }
        while(max_stringSize>Alignments[max_index][i][1].length()){
            Alignments[max_index][i][1]+="-";
        } 
        std::cout<<Alignments[max_index][i][1]<<std::endl;
    }
}

int main() {
    char Modo='F';

    int alineado=0;

    std::cout<<"Ingresar el modo, (F)->Mostrar muestras directas\n(R)->Mostrar muestras reversas,\
    (W)->Mostrar ambas muestras, \n(T)->Mostrar el primer caso de prueba.\n";

    std::cin>>Modo;
    if (Modo=='F'){
        alineado=0;
    }
    else if(Modo=='R'){
        alineado=1;
    }
    else if (Modo=='W'){
        alineado=2;
    }
    else if (Modo=='T'){
        alineado=3;
    }

    std::vector<std::string>cadenas;

    if (alineado!=3){
        if(alineado!=2){
            for(int i=0; i<6; i++){
                cadenas.insert(cadenas.end(),(BRCA[i][alineado]));
            }
        }
        else{
            for(int i=0; i<6; i++){
                for(int j=0; j<2;j++){
                    cadenas.insert(cadenas.end(),(BRCA[i][j]));
                }
            }
        }
        Star_alignment(cadenas);
    }
    else{
        Star_alignment(FirstTest);
    }

    return 0;
}