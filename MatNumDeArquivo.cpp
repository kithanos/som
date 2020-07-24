#include "MatNumDeArquivo.h"

MatNumDeArquivo::MatNumDeArquivo( char *nomeArquivo ) {
  ifstream arquivo;
  char nomeArq[ 200 ];
  strcpy( nomeArq, nomeArquivo );
  arquivo.open( nomeArq, ios::in );
  if( ! arquivo.is_open() ) {
    cout << "Falha na abertura do arquivo " << nomeArq << endl;
    exit( 1 );
  }
  numLinhas = 0;
  numColunas = 0;
  string linha;
  while( getline( arquivo, linha ) ) {
    cout << "Leu linha " << numLinhas++ << ": " << linha << endl;
    istringstream istrLinha;
    istrLinha.str( linha );
    double numero;
    if( numLinhas == 1 ) {
      while( istrLinha >> numero ) {
	cout << "  Leu número " << numero << endl;
	numColunas++;
      }
      cout << "  Quantidade de números na primeira linha: "
	   << numColunas << endl;
    }
    else { // Não é a primeira linha.
      int qtdNumeros = 0;
      while( istrLinha >> numero ) {
	cout << "  Leu número " << numero << endl;
	qtdNumeros++;
      }
      cout << "  Quantidade de números nesta linha: " << qtdNumeros << endl;
      if( qtdNumeros == numColunas ) {
	cout << "    Está igual à quantidade da primeira linha.\n";
      }
      else {
	cout << "    Em " << nomeArq << ",\n";
	cout << "    linha com tamanho diferente da primeira linha.\n";
	cout << "    Fim da execução com erro.\n";
	exit( 1 );
      }
    }
  }
  arquivo.close();
  cout << "\nNúmero de linhas lidas: " << numLinhas << endl;
  cout << "\nNúmero de elementos por linha: " << numColunas << endl;
  // Versão com alocação dinâmica:
  matDinam = new double*[ numLinhas ];
  for( int i = 0; i < numLinhas; i++ ) {
    matDinam[ i ] = new double[ numColunas ];
  }
  arquivo.open( nomeArq, ios::in );
  numLinhas = 0;
  while( getline( arquivo, linha ) ) {
    istringstream istrLinha;
    istrLinha.str( linha );
    double numero;
    int qtdNumeros = 0;
    while( istrLinha >> numero ) {
      matDinam[ numLinhas ][ qtdNumeros ] = numero;
      qtdNumeros++;
    }
    numLinhas++;
  }
  arquivo.close();
   cout << "\n\nmatDinam preenchida:\n\n";
  for( int indLinha = 0; indLinha < numLinhas; indLinha++ ) {
    for( int indColuna = 0; indColuna < numColunas; indColuna++ ) {
      cout << matDinam[ indLinha ][ indColuna ] << " ";
    }
    cout << endl;
  }
}

MatNumDeArquivo::~MatNumDeArquivo() {
  for( int i = 0; i < numLinhas; i++ ) {
    delete [] matDinam[ i ];
  }
  delete [] matDinam;
}

int MatNumDeArquivo::getNumLinhas() {
  return numLinhas;
}

int MatNumDeArquivo::getNumColunas() {
  return numColunas;
}

double *MatNumDeArquivo::getPtLinha( int numLinha ) {
  if( numLinha <= numLinhas ) {
    return matDinam[ numLinha ];
  }
  else {
    cout << "numLinha inválido em MatNumDeArquivo::getPtLinha( int numLinha ).\n";
    exit( 1 );
  }
}

void MatNumDeArquivo::gravaArquivo( char *nomeArquivo ) {
  ofstream arquivo;
  char nomeArq[ 200 ];
  strcpy( nomeArq, nomeArquivo );
  arquivo.open( nomeArq, ios::out );
  if( ! arquivo.is_open() ) {
    cout << "Falha na abertura do arquivo " << nomeArq << endl;
    exit( 1 );
  }
  for( int indLinha = 0; indLinha < numLinhas; indLinha++ ) {
    for( int indColuna = 0; indColuna < numColunas; indColuna++ ) {
      arquivo << matDinam[ indLinha ][ indColuna ] << " ";
    }
    arquivo << endl;
  }
  arquivo.close();
}
