#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;

class MatNumDeArquivo {
private:
  double **matDinam;
  int numLinhas, numColunas;
public:
  MatNumDeArquivo( char *nomeArquivo );
  ~MatNumDeArquivo();
  int getNumLinhas();
  int getNumColunas();
  double *getPtLinha( int numLinha );
  void gravaArquivo( char *nomeArquivo );
};
