#include <fstream>
#include <memory>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Reader
{
public:
  Reader(string Filename)
  {
    this->Filename = Filename;
    File = std::ifstream(Filename);
    if (!File.is_open())
    {
      std::cerr << "Error al abrir el archivo: " << Filename << std::endl;
      return;
    }
  }

  ~Reader()
  {
    File.close();
  }

  void ReadLines()
  {
    std::string line;
    while (std::getline(File, line))
    {
      Lines.push_back(line);
    }
  }

  std::vector<std::string> GetLines()
  {
    return Lines;
  }

private:
  string Filename;
  std::ifstream File;
  std::vector<std::string> Lines;
};

class HmmProfile
{
public:
  string Input;

  HmmProfile(std::string Filename)
  {
    RPointer = std::make_unique<Reader>(Filename);
    RPointer->ReadLines();
    Lines = RPointer->GetLines();
  }

  void ProbabilidadEmision()
  {
    Emisiones.resize(Lines[0].size(), std::vector<int>(26, 0));
    for (size_t col = 0; col < Lines[0].size(); ++col)
    {
      for (size_t row = 0; row < Lines.size(); ++row)
      {
        char c = std::tolower(Lines[row][col]);
        if (std::isalpha(c))
        {
          int letterIndex = c - 'a';
          Emisiones[letterIndex][col]++;
          LetrasUnicas.insert(c);
        }
      }
    }
  }

  void HeuristicaColumnas()
  {
    Columnas.resize(Lines.size());
    int LineLength = Lines[0].length(), Umbral = LineLength / 2, Count = 0;
    bool CurrColumna = 1;
    for (int i = 0; i < LineLength; i++)
    {
      for (int j = 0; j < Lines.size(); j++)
      {
        if (Lines[j][i] == '-')
        {
          Count++;
        }
        if (Count >= Umbral)
        {
          j = Lines.size() - 1;
          CurrColumna = 0;
        }
      }
      Columnas[i] = CurrColumna;
      CurrColumna = 0;
    }
  }

  void ProbabilidadTransicion()
  {
    Transiciones.resize(Lines[0].size(), std::vector<int>(3, 0));
    int iterator = 0;
    for (int i = 0; i < Columnas.size(); i++)
    {
      for (int j = 0; j < Lines.size(); j++)
      {
        if (Columnas[i])
        {
          if (Lines[j][i] == '-')
          {
            Transiciones[j][2]++;
          }
          else{
            Transiciones[j][0]++;
          }
        }
        else{
          if(std::isalpha(Lines[j][i])){
              Transiciones[j][1]++;
          }
        }
      }
    }
  }

  void PrintTransiciones(){
    for(int i=0; i<Columnas.size();i++){
      if (i==0){
        std::cout<<"Begin";
      }
      else{
        std::cout<<"M"<<i;
      }
      if(i==Columnas.size()-1){
        std::cout<<": End="<<Transiciones[i][0];
      }
      else{
        std::cout<<": M"<<i+1<<"="<<Transiciones[i][0];
      }
      std::cout<<" | I="<<Transiciones[i][1]<<" | D="<<Transiciones[i][2]<<std::endl;

    }
  }

private:
  std::unique_ptr<Reader> RPointer;
  std::vector<std::string> Lines;
  std::vector<bool> Columnas;
  std::vector<std::vector<int>> Emisiones;
  std::unordered_set<char> LetrasUnicas;
  std::vector<std::vector<int>> Transiciones;
};

int main()
{
  HmmProfile Test("Input.txt");
  Test.ProbabilidadEmision();
  Test.HeuristicaColumnas();
  Test.ProbabilidadTransicion();
  Test.PrintTransiciones();
}