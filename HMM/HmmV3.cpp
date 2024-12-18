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
    std::cout<<"-----------LEYENDO INPUT---------\n";
    std::string line;
    while (std::getline(File, line))
    {
      Lines.push_back(line);
      std::cout<<line<<std::endl;
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
    Emisiones.resize(26, std::vector<int>(Lines[0].size(), 0));
    for (size_t col = 0; col < Lines[0].size(); ++col)
    {
      for (size_t row = 0; row < Lines.size(); ++row)
      {
        char c = std::tolower(Lines[row][col]);
        if (std::isalpha(c))
        {
          int letterIndex = c - 'a';
          //std::cout<<letterIndex<<" | "<<col<<std::endl;
          //std::cout<<columnLetterCounts.size();
          Emisiones[letterIndex][col]++;
          LetrasUnicas.insert(c);
        }
      }
    }
  }

  void HeuristicaColumnas()
  {
    std::cout<<"----------ELIMINANDO COLUMNAS CON HEURISTICA------\n";
    Columnas.resize(Lines[0].size());
    int LineLength = Lines[0].length(), Umbral = LineLength / 2, Count = 0;
    bool CurrColumna = 1;
    for (int i = 0; i < LineLength; i++)
    {
      Estados++;
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
          Estados--;
          std::cout<<"Columna: "<<i<<", Eliminada\n";
        }
      }
      Count=0;
      Columnas[i] = CurrColumna;
      CurrColumna = 1;
    }
  }

  void ProbabilidadTransicion()
  {
    std::vector<bool>insertions(Lines[0].size(),0);
    Transiciones.resize(Estados, std::vector<int>(3, 0));
    int iterator = 0, OffConcurrente=0;
    for (int i = 0; i < Lines[0].size(); i++)
    {
      for (int j = 0; j < Lines.size(); j++)
      {
        //std::cout<<"Lines: "<<Lines[j][i]<<std::endl;
        if (Columnas[i])
        {
          OffConcurrente=0;
          if(insertions[j]){
            //std::cout<<"\n-----------"<<"j: "<<j<<" | i: "<<i<<" \n";
            insertions[j]=0;
          }
          else if (Lines[j][i] == '-')
          {
            Transiciones[iterator][2]++;
            //std::cout<<"D"<<std::endl;
          }
          else{
            Transiciones[iterator][0]++;
            //std::cout<<"M"<<i<<std::endl;
          }
        }
        else{
          if(OffConcurrente==0){
            if(std::isalpha(Lines[j][i])){
                Transiciones[iterator][1]++;
                //std::cout<<"I"<<std::endl;
                OffConcurrente++;
                insertions[j]=1;
            }
          }
        }
      }
      if (Columnas[i]){
        iterator++;
      }
    }
  }

  void PrintTransiciones(){
    std::cout<<"-----------PROBABILIDADES DE TRANSICION-----------\n";
    for(int i=0; i<Estados;i++){
      if (i==0){
        std::cout<<"Begin";
      }
      else{
        std::cout<<"M"<<i;
      }
      if(i==Estados-1){
        std::cout<<": End="<<float(Transiciones[i][0])/(Estados-1)+1/3;
      }
      else{
        std::cout<<": M"<<i+1<<"="<<float(Transiciones[i][0])/(Estados-1)+1/3;
      }
      std::cout<<" | I"<<i<<"="<<float(Transiciones[i][1])/(Estados-1)+1/3<<" | D"<<i+1<<"="<<float(Transiciones[i][2])/(Estados-1)+1/3<<std::endl;

    }
  }

  void PrintEmisiones(){
    char count='a';
    int MinusColumns=0;
    std::cout<<"-------PROBABILIDADES DE EMISION----------\n";
    for (size_t i = 0; i < Emisiones[i].size(); ++i) {
      if(!Columnas[i]){
        MinusColumns++;
        continue;
      }
      std::cout<<"M"<<i-MinusColumns<<": ";
      for (size_t j = 0; j < Emisiones.size(); ++j) {
        if(Emisiones[j][i]!=0){
          std::cout <<char('a'+j)<<"="<< float(Emisiones[j][i])/(Estados-1)+(1/20) << " | ";
        } 
      }
      std::cout << std::endl;
    }
  }

  int GetEstados(){
    return Estados;
  }

private:
  std::unique_ptr<Reader> RPointer;
  std::vector<std::string> Lines;
  std::vector<bool> Columnas;
  std::vector<std::vector<int>> Emisiones;
  std::unordered_set<char> LetrasUnicas;
  std::vector<std::vector<int>> Transiciones;
  int Estados=0;
};

int main()
{
  HmmProfile Test("Input.txt");
  Test.ProbabilidadEmision();
  Test.HeuristicaColumnas();
  Test.ProbabilidadTransicion();
  std::cout<<"Estados: "<<Test.GetEstados()-1<<std::endl;
  Test.PrintTransiciones();
  Test.PrintEmisiones();
}