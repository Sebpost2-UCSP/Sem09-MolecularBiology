#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <fstream>
using namespace std;

vector<vector<string>> Graph_substr;
string substrCurr;
vector<int> Abecedary(26, 0);

void print(vector<vector<int>> A)
{
  for (int i = 0; i < A.size(); i++)
  {
    for (int j = 0; j < A.size(); j++)
    {
      cout << "|" << A[i][j];
    }
    cout << "|\n";
  }
}

pair<int, pair<string, string>> ValorPonderado(string A, string B)
{
  int counter = 0;
  int max = 0;
  if (A == B)
  {
    return make_pair(A.length(), make_pair(A, B));
  }
  string substrA = "";
  string substrB = "";
  int substr_l = B.length();
  int indexA = 0, indexB = 0;
  //cout << "a: " << A << "\nB: " << B << endl;
  int minlen = A.length();
  if (A.length() > B.length())
  {
    minlen = B.length();
  }
  for (int i = 1; i < minlen; i++)
  {
    substrB = B.substr(0, minlen - i);
    substrA = A.substr(A.length() - minlen + i, A.length());
    //cout<<"SubstrA: "<<substrA<<"| SubstrB: "<<substrB<<endl;
    if (substrA == substrB)
    {
      //cout << "sub: " << substrA << endl;
      indexB = B.find(substrB);
      substrCurr = substrA;
      return make_pair(substrA.length(), make_pair(A, B));
    }
  }
  return make_pair(0, make_pair(A, B));
}

void Greedy(vector<string> A,vector<string> B)
{
  // Creamos el grafo dirigido
  vector<vector<int>> Graph(A.size(), vector<int>(A.size(), 0));
  vector<vector<int>> Graph_txt(A.size(), vector<int>(A.size(), 0));
  std::vector<std::vector<std::vector<std::string>>> Graph_string(A.size(), std::vector<std::vector<std::string>>(A.size(), std::vector<std::string>(2, "")));
  string VPstr, VP2str;
  pair<int, pair<string, string>> VP, VP2;
  for (int i = 0; i < A.size(); i++)
  {
    for (int j = 0; j < A.size(); j++)
    {
      if (i != j)
      {
        VP = ValorPonderado(A[i], A[j]);
        VPstr=substrCurr;
        Graph_txt[i][j] = VP.first;
        VP2=ValorPonderado(A[i],B[j]);
        VP2str=substrCurr;
        if(VP.first>VP2.first){
          Graph_substr[i][j]=VPstr;
          Graph[i][j] = VP.first;
          Graph_string[i][j][0] = VP.second.first;
          Graph_string[i][j][1] = VP.second.second;
        }
        else{
          Graph_substr[i][j]=VP2str;
          Graph[i][j] = VP2.first;
          Graph_string[i][j][0] = VP2.second.first;
          Graph_string[i][j][1] = VP2.second.second;
        }
        //std::cout<<"i: "<<i<<"| j: "<<j<<endl;
        //cout<<"A= "<<VP.second.first<<"\nB= "<<VP.second.second<<endl;
        //cout<<"OVERLAPstr="<<substrCurr<<endl;
        //cout<<"OVERLAP_VALUE="<<VP.first<<endl;
      }
    }
  }

  ofstream outfile("out.txt");

    // Check if file opened successfully
    if (outfile.is_open()) {
        // Write each element of the array to the file
        for (int i = 0; i < A.size(); i++) {
            for (int j = 0; j < A.size(); j++) {
                outfile << Graph_txt[i][j];

                // Add a space after each element (optional)
                if (j < A.size() - 1) {
                    outfile << " ";
                }
            }
            // Add a newline after each row
            outfile << endl;
        }
    }

  vector<int> Row(A.size(), 0);
  std::vector<int>::iterator it;
  Row[0] = 0;

  // Ordenamos las aristas por peso, las mas pesadas primero
  vector<string> Result;
  vector<string> ResultSubstr;
  string currstr, currstr2, currSubStr;
  int max = 0, max_id = 0;
  for (int i = 0; i < A.size(); i++)
  {
    if (max < Graph[i][0])
    {
      max = Graph[i][0];
      currstr = Graph_string[i][0][0];
      currstr2 = Graph_string[i][0][1];
      currSubStr = Graph_substr[i][0];
      Row[1] = i;
    }
  }

  print(Graph);
  max = 0;
  Result.push_back(currstr2);
  Result.push_back(currstr);
  ResultSubstr.push_back(currSubStr);
  ResultSubstr.push_back(currSubStr);
  max_id = Row[1];
  int last_max_id=max_id;
  for (int j = 2; j < A.size(); j++)
  {
    for (int k = 0; k < A.size(); k++)
    {
      // cout<<"i: "<<j<<" j: "<<k<<endl;
      if (find(Row.begin(), Row.end(), k) != Row.end())
      {
        continue;
      }
      //cout<<"j: "<<Row[Result.size()-1]<<" k: "<<k<<endl;
      //cout<<Graph[k][Row[Result.size()-1]]<<endl;
      if (Graph[k][Row[Result.size() - 1]] > max && k != Row[Result.size() - 1])
      {
        max_id = k;
        max = Graph[k][Row[Result.size() - 1]];
      }
    }
    max = 0;
    if(last_max_id==max_id){
      break;
    }
    last_max_id=max_id;
    //cout<<"MAX_ID="<<max_id<<endl;
    Row[j] = max_id;
    if(Result[Result.size()-1]==Graph_string[max_id][Row[Result.size() - 1]][0]){
      Result.push_back(Graph_string[max_id][Row[Result.size() - 1]][1]);
    }
    else{
      Result.push_back(Graph_string[max_id][Row[Result.size() - 1]][0]);
    }
    ResultSubstr.push_back(Graph_substr[max_id][Row[ResultSubstr.size() - 1]]);
    //cout<<"R: "<<Result[Result.size()-1]<<endl;
    //cout<<"Rs: "<<ResultSubstr[ResultSubstr.size()-1]<<endl;
  }

  int indexA = 0, indexB = 0;

  std::reverse(Result.begin(), Result.end());
  std::reverse(ResultSubstr.begin(), ResultSubstr.end());

  for (int i = 1; i < Result.size(); i++)
  {
    indexA = Result[i - 1].find(ResultSubstr[i-1]);
    indexB = Result[i].find(ResultSubstr[i-1]);
    Result[i].insert(0, indexA, '-');
    //cout<<"I: "<<i<<endl;
    if (Result[i - 1].length() > Result[i].length())
    {
      Result[i].insert(Result[i].length(), Result[i - 1].length() - Result[i].length(), '-');
    }
    else
    {
      Result[i - 1].insert(Result[i - 1].length(), Result[i].length() - Result[i - 1].length(), '-');
    }
  }

  for (int i = 0; i < Result.size() - 1; i++)
  {
    int TotalLength = Result[Result.size() - 1].length() - Result[i].length();
    Result[i].insert(Result[i].length(), TotalLength, '-');
  }

  string StringResult;
  for (int i = 0; i < Result[0].length(); i++)
  {
    for (int j = 0; j < Result.size(); j++)
    {
      if (Result[j][i] == '-')
      {
        continue;
      }
      Abecedary[int(Result[j][i] - 65)] += 1;
    }
    int index = max_element(Abecedary.begin(), Abecedary.end()) - Abecedary.begin();
    StringResult += char(index + 65);
    fill(Abecedary.begin(), Abecedary.end(), 0);
  }
  Result.push_back(StringResult);

  for (int i = 0; i < Result.size(); i++)
  {
    cout << Result[i] << endl;
  }

  for (int i = 0; i < Row.size(); i++)
  {
    cout << Row[i] << "->";
  }
  cout << endl;
}

int main()
{
  string A = "ATCCGTTGAAGCCGCGGGC";
  string B = "TTAACTCGAGG";
  string C = "TTAAGTACTGCCCG";
  string D = "ATCTGTGTCGGG";
  string E = "CGACTCCCGACACA";
  string F = "CACAGATCCGTTGAAGCCGCGGG";
  string G = "CTCGAGTTAAGTA";
  string H = "CGCGGGCAGTACTT";

  vector<string> Sequences(8, "");
  Sequences[0] = A;
  Sequences[1] = B;
  Sequences[2] = C;
  Sequences[3] = D;
  Sequences[4] = E;
  Sequences[5] = F;
  Sequences[6] = G;
  Sequences[7] = H;

  vector<string> SequencesReverse(8, "");
  SequencesReverse=Sequences;
  for(int i=0; i<Sequences.size();i++){
    std::reverse(SequencesReverse[i].begin(),SequencesReverse[i].end());
    //cout<<SequencesReverse[i]<<endl;
  }

  Graph_substr.resize(A.size());
  for (int i = 0; i < A.size(); i++)
  {
    Graph_substr[i].resize(A.size(), "");
  }

  Greedy(Sequences,SequencesReverse);
}