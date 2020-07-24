// Modo de uso:

//./som -i nomeArqInicNeuronios.ascii -e nomeArqEntradas.ascii
//        -r nomeArqRotulosEntradas.txt
//        -l numLinhasSOM -c numEntrPorEpoca
//        -b alfaIni -f alfaFin -s sigmaIni -g sigmaFin
//        -d tipoDistancia -n nomeArqNeuroniosFinais -z atualizaSOM
//        -q nomeArqSeqVencUltEpoca -o nomeArqCoordVencUltEpoca
//        -a numAplicArqEntradas -u seGeraFigVenced

// em que:

//nomeArqInicNeuronios.ascii é um arquivo que contém, em cada
//uma de suas L linhas, os N valores dos pesos iniciais de um
//neurônio, separados por espaços.

// nomeArqEntradas.ascii é um arquivo contendo uma série de entradas
// para o SOM.

// nomeArqRotulosEntradas.txt é um arquivo contendo uma série de rótulos
// (nomes) para as entradas do arquivo nomeArqEntradas.ascii.

// numLinhasSOM é o número de linhas do SOM, supondo-se que ele seja uma
// matriz bidimensional. O número de colunas é calculado, pelo
// programa, a partir do numLinhasSOM e do número de neurônios encontrados
// no arquivo de neurônios iniciais.

// numEntrPorEpoca é o número de entradas diferentes na execução do
// SOM. Cada entrada é um vetor. Como elas podem aparecer de forma
// cíclica no arquivo de entradas, o usuário indica quantas entradas
// diferentes existem no arquivo, para o programa saber quando há
// mudança de ciclos (ou seja, de épocas) na aplicação das
// entradas. Útil, por exemplo, quando entradas embaralhadas e
// repetidas estiverem num mesmo arquivo.

// alfaIni e alfaFin são valores inicial e final para o fator de
// aprendizagem.

// sigmaIni e sigmaFin são valores inicial e final para a função de
// vizinhança.

// tipoDistancia pode ser: Euclid ou Manhat

// nomeArqNeuroniosFinais é o nome de um arquivo que receberá os
// valores finais dos neurônios.

// atualizaSOM é sim se o SOM deve ser atualizado durante o
// funcionamento e nao se o SOM for usado só para classificação, sem
// mudanças de posições dos neurônios. Se atualizaSOM for nao, os
// valores de alfa e de sigma são irrelevantes.

// nomeArqSeqVencUltEpoca é o nome de um arquivo que receberá a lista
// de índices de neurônios vencedores na última época de execução, na
// sequência em que ocorrerem.

// nomeArqCoordVencUltEpoca é o nome de um arquivo que receberá a
// lista de coordenadas dos neurônios vencedores, na sequência em que
// ocorrerem. Considera-se que as linhas e as colunas do SOM são
// numeradas a partir de 1.

// numAplicArqEntradas é o número de vezes em que as entradas do
// arquivo de entradas deverão ser aplicadas. Por exemplo, se valer 10,
// todo o conjunto de entradas do arquivo de entradas será aplicado 10
// vezes, do início ao fim, de forma cíclica, sempre na mesma sequência.

// seGeraFigVenced é sim ou não, conforme se desejar a geração de
// figuras de neurônios vencedores. A figura da matriz U sempre é gerada.

// Exemplo de uso:
// ./som.m -i neurInic.ascii -e entradasSom.ascii -r nomeArqRotulosEntradas.txt
//         -l 4 -c 3
//         -b 0.1 -f 0.01 -s 15 -g 1
//         -d Euclid -n neuroniosFinais.ascii -z sim -q indVencedores.ascii
//         -o coordVencedores.ascii -a 1

#include <algorithm>    // std::random_shuffle
#include <ctime>       // std::time
#include <cstdlib>      // std::rand, std::srand
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <vector>
#include "MatNumDeArquivo.h"
#include "cv.h"

using namespace cv;
using namespace std;

int main( int argc, char **argv ) {
  char nomeArqInicNeuronios[ 200 ], nomeArqEntradas[ 200 ],
    nomeArqRotulosEntradas[ 200 ],
    nomeArqNeuroniosFinais[ 200 ], nomeArqSeqVencUltEpoca[ 200 ],
    nomeArqCoordVencUltEpoca[ 200 ];
  const double infinito = std::numeric_limits<double>::infinity();
  nomeArqInicNeuronios[ 0 ] = 0;
  nomeArqEntradas[ 0 ] = 0;
  nomeArqRotulosEntradas[ 0 ] = 0;
  nomeArqNeuroniosFinais[ 0 ] = 0;
  nomeArqSeqVencUltEpoca[ 0 ] = 0;
  nomeArqCoordVencUltEpoca[ 0 ] = 0;
  char tipoDistancia[ 50 ];
  tipoDistancia[ 0 ] = 0;
  int numLinhasSOM = -1, numEntrPorEpoca = -1;
  long int numAplicArqEntradas = -1;
  double alfaIni = -1, alfaFin = -1, sigmaIni = -1, sigmaFin = -1;
  char atualizaSOM[ 5 ], seGeraFigVenced[ 5 ];
  atualizaSOM[ 0 ] = 0;
  seGeraFigVenced[ 0 ] = 0;
  int opcaoGetopt;
  while( ( opcaoGetopt =
	   getopt( argc, argv, "a:b:c:d:e:f:g:i:l:n:o:q:r:s:u:z:" ) ) != -1 )
    switch( opcaoGetopt ) {
    case 'a':
      numAplicArqEntradas = atol( optarg );
      break;
    case 'b':
      alfaIni = atof( optarg );
      break;
    case 'c':
      numEntrPorEpoca = atoi( optarg );
      break;
    case 'd':
      strcpy( tipoDistancia, optarg );
      break;
    case 'e':
      strcpy( nomeArqEntradas, optarg );
      break;
    case 'f':
      alfaFin = atof( optarg );
      break;
    case 'g':
      sigmaFin = atof( optarg );
      break;
    case 'i':
      strcpy( nomeArqInicNeuronios, optarg );
      break;
    case 'l':
      numLinhasSOM = atoi( optarg );
      break;
    case 'n':
      strcpy( nomeArqNeuroniosFinais, optarg );
      break;
    case 'o':
      strcpy( nomeArqCoordVencUltEpoca, optarg );
      break;
    case 'q':
      strcpy( nomeArqSeqVencUltEpoca, optarg );
      break;
    case 'r':
      strcpy( nomeArqRotulosEntradas, optarg );
      break;
    case 's':
      sigmaIni = atof( optarg );
      break;
    case 'u':
      strcpy( seGeraFigVenced, optarg );
      break;
    case 'z':
      strcpy( atualizaSOM, optarg );
      break;
    }
  if( numAplicArqEntradas <= 0 ) {
    cout << "Número de aplicações do arq. de entrada inválido.\n";
    return -1;
  }
  else {
    cout << "numAplicArqEntradas = " << numAplicArqEntradas << endl;
  }
  if( numEntrPorEpoca <= 0 ) {
    cout << "Número de entradas por época inválido.\n";
    return -1;
  }
  else {
    cout << "numEntrPorEpoca = " << numEntrPorEpoca << endl;
  }
  if( strlen( nomeArqEntradas ) == 0 ) {
    cout << "Faltou: -e nomeArqEntradas.\n";
    return -1;
  }
  else {
    cout << "nomeArqEntradas = " << nomeArqEntradas << endl;
  }
  if( strlen( nomeArqRotulosEntradas ) == 0 ) {
    cout << "Faltou: -r nomeArqRotulosEntradas.\n";
    return -1;
  }
  else {
    cout << "nomeArqRotulosEntradas = " << nomeArqRotulosEntradas << endl;
  }
  if( strlen( nomeArqInicNeuronios ) == 0 ) {
    cout << "Faltou: -i nomeArqInicNeuronios.\n";
    return -1;
  }
  else {
    cout << "nomeArqInicNeuronios = " << nomeArqInicNeuronios << endl;
  }
  if( strlen( nomeArqNeuroniosFinais ) == 0 ) {
    cout << "Faltou: -n nomeArqNeuroniosFinais.\n";
    return -1;
  }
  else {
    cout << "nomeArqNeuroniosFinais = " << nomeArqNeuroniosFinais << endl;
  }
  if( strlen( nomeArqSeqVencUltEpoca ) == 0 ) {
    cout << "Faltou: -q nomeArqSeqVencUltEpoca.\n";
    return -1;
  }
  else {
    cout << "nomeArqSeqVencUltEpoca = " << nomeArqSeqVencUltEpoca << endl;
  }
  if( strlen( nomeArqCoordVencUltEpoca ) == 0 ) {
    cout << "Faltou: -o nomeArqCoordVencUltEpoca.\n";
    return -1;
  }
  else {
    cout << "nomeArqCoordVencUltEpoca = " << nomeArqCoordVencUltEpoca
	 << endl;
  }
  if( numLinhasSOM <= 0 ) {
    cout << "Número de linhas inválido.\n";
    return -1;
  }
  else {
    cout << "numLinhasSOM = " << numLinhasSOM << endl;
  }
  if( alfaIni < 0 ) {
    cout << "alfaIni inválido.\n";
    return -1;
  }
  else {
    cout << "alfaIni = " << alfaIni << endl;
  }
  if( alfaFin < 0 ) {
    cout << "alfaFin inválido.\n";
    return -1;
  }
  else {
    cout << "alfaFin = " << alfaFin << endl;
  }
  if( sigmaIni < 0 ) {
    cout << "sigmaIni inválido.\n";
    return -1;
  }
  else {
    cout << "sigmaIni = " << sigmaIni << endl;
  }
  if( sigmaFin < 0 ) {
    cout << "sigmaFin inválido.\n";
    return -1;
  }
  else {
    cout << "sigmaFin = " << sigmaFin << endl;
  }
  if( strlen( tipoDistancia ) == 0 ) {
    cout << "Faltou: -d tipoDistancia.\n";
    return -1;
  }
  else {
    cout << "tipoDistancia = " << tipoDistancia << endl;
  }
  if( strlen( seGeraFigVenced ) == 0 ) {
    cout << "Faltou: -u seGeraFigVenced.\n";
    return -1;
  }
  else {
    cout << "seGeraFigVenced = " << seGeraFigVenced << endl;
  }
  if( strlen( atualizaSOM ) == 0 ) {
    cout << "Faltou: -z atualizaSOM.\n";
    return -1;
  }
  else {
    cout << "atualizaSOM = " << atualizaSOM << endl;
  }
  MatNumDeArquivo neuronios( nomeArqInicNeuronios );
  MatNumDeArquivo entradas( nomeArqEntradas );
  int numNeuronios = neuronios.getNumLinhas();
  cout << "O arquivo tem " << numNeuronios << " neurônios.\n";
  int numDimensoes = neuronios.getNumColunas();
  cout << "Cada neurônio tem " << numDimensoes << " dimensões.\n";
  int numColunasSOM = numNeuronios / numLinhasSOM;
  list<string> ltRotulos;
  // A seguir, vetor com um elemento para cada entrada a ser aplicada
  // ao SOM. Pode ter repetições:
  vector<string> vtRotulosComRepet;
  ifstream arqRotulos;
  arqRotulos.open( nomeArqRotulosEntradas, ios::in );
  if( ! arqRotulos.is_open() ) {
    cout << "Falha na abertura do arquivo " << nomeArqRotulosEntradas << endl;
    exit( 1 );
  }
  string umRotuloEntrada;
  cout << "\n\nLeitura do arquivo de rótulos:\n\n";
  while( getline( arqRotulos, umRotuloEntrada ) ) {
    cout << umRotuloEntrada << endl;
    ltRotulos.push_back( umRotuloEntrada );
    vtRotulosComRepet.push_back( umRotuloEntrada );
  }
  arqRotulos.close();
  cout << "\n\nEis o conteúdo final do vtRotulosComRepet:\n\n";
  for( int i = 0; i < vtRotulosComRepet.size(); i++ ) {
    cout << "vtRotulosComRepet[ " << i << " ] = "
	 << vtRotulosComRepet[ i ] << endl;
  }
  cout << "Tamanho original da ltRotulos: " << ltRotulos.size() << endl;
  ltRotulos.sort();
  ltRotulos.unique();
  cout << "Tamanho da ltRotulos após remoção de repetições: "
       << ltRotulos.size() << endl;
  vector<string> vtRotulosSemRepet;
  list<string>::iterator itLtRotulos;
  for( itLtRotulos = ltRotulos.begin(); itLtRotulos != ltRotulos.end();
       itLtRotulos++ ) {
    vtRotulosSemRepet.push_back( *itLtRotulos );
  }
  cout << "\n\nEis o conteúdo final da ltRotulos:\n\n";
  for( itLtRotulos = ltRotulos.begin(); itLtRotulos != ltRotulos.end();
       itLtRotulos++ ) {
    cout << *itLtRotulos << endl;
  }
  cout << "\n\nEis o conteúdo do vtRotulosSemRepet:\n\n";
  for( int i = 0; i < vtRotulosSemRepet.size(); i++ ) {
    cout << "vtRotulosSemRepet[ " << i << " ] = "
	 << vtRotulosSemRepet[ i ] << endl;
  }
  int numCores = vtRotulosSemRepet.size();
  map<string,Scalar> mpRotuloCor;
  for( int indCor = 0; indCor < numCores; indCor++ ) {
    int compoCor = indCor * 255 / ( numCores - 1 );
    Scalar cor( compoCor, compoCor, compoCor );
    mpRotuloCor[ vtRotulosSemRepet[ indCor ] ] = cor;
  }
  cout << "\n\nEis o conteúdo do mpRotuloCor:\n\n";
  for( int i = 0; i < vtRotulosSemRepet.size(); i++ ) {
    cout << "rotulo: " << vtRotulosSemRepet[ i ]
	 << ", cor: " << mpRotuloCor[ vtRotulosSemRepet[ i ] ] << endl;
  }
  int raioCircFig = 20;
  int numLinhasPixeis = numLinhasSOM * 4 * raioCircFig;
  int numColunasPixeis = numColunasSOM * 4 * raioCircFig;
  // Monta Mat para imagem de SOM, com fundo preto:
  Mat matMascFdPreto =
    Mat::zeros( numLinhasPixeis, numColunasPixeis, CV_8UC3 );
  // Monta Mat para imagem de SOM, com fundo não preto:
  Mat matMascFdCor( numLinhasPixeis, numColunasPixeis, CV_8UC3,
		    Scalar( 0.027 * 255, 0.8 * 255, 0.319 * 255 ) );
  if( seGeraFigVenced[ 0 ] == 's' ) {
    for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
      line( matMascFdPreto,
	    Point( numColunasPixeis / ( 2 * numColunasSOM ),
		   numLinhasPixeis / ( 2 * numLinhasSOM ) +
		   linhaSOM * numLinhasPixeis / numLinhasSOM ),
	    Point( ( 2 * numColunasSOM - 1 ) * numColunasPixeis /
		   ( 2 * numColunasSOM ),
		   numLinhasPixeis / ( 2 * numLinhasSOM ) +
		   linhaSOM * numLinhasPixeis / numLinhasSOM ),
	    Scalar( 255, 255, 255 ), 1, 8 );
    }
    for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
      line( matMascFdPreto,
	    Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		   colunaSOM * numColunasPixeis / numColunasSOM,
		   numLinhasPixeis / ( 2 * numLinhasSOM ) ),
	    Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		   colunaSOM * numColunasPixeis / numColunasSOM,
		   ( 2 * numLinhasSOM - 1 ) * numLinhasPixeis /
		   ( 2 * numLinhasSOM ) ),
	    Scalar( 255, 255, 255 ), 1, 8 );
    }
    for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
      for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
	circle( matMascFdPreto,
		Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		       colunaSOM * numColunasPixeis / numColunasSOM,
		       numLinhasPixeis / ( 2 * numLinhasSOM ) +
		       linhaSOM * numLinhasPixeis / numLinhasSOM ),
		raioCircFig, Scalar( 255, 0, 0 ), -1, 8, 0 );
      }
    }
    imwrite( "mascaraSOM.png", matMascFdPreto );
    for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
      line( matMascFdCor,
	    Point( numColunasPixeis / ( 2 * numColunasSOM ),
		   numLinhasPixeis / ( 2 * numLinhasSOM ) +
		   linhaSOM * numLinhasPixeis / numLinhasSOM ),
	    Point( ( 2 * numColunasSOM - 1 ) * numColunasPixeis /
		   ( 2 * numColunasSOM ),
		   numLinhasPixeis / ( 2 * numLinhasSOM ) +
		   linhaSOM * numLinhasPixeis / numLinhasSOM ),
	    Scalar( 0, 0, 0 ), 1, 8 );
    }
    for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
      line( matMascFdCor,
	    Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		   colunaSOM * numColunasPixeis / numColunasSOM,
		   numLinhasPixeis / ( 2 * numLinhasSOM ) ),
	    Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		   colunaSOM * numColunasPixeis / numColunasSOM,
		   ( 2 * numLinhasSOM - 1 ) * numLinhasPixeis /
		   ( 2 * numLinhasSOM ) ),
	    Scalar( 0, 0, 0 ), 1, 8 );
    }
    for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
      for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
	circle( matMascFdCor,
		Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		       colunaSOM * numColunasPixeis / numColunasSOM,
		       numLinhasPixeis / ( 2 * numLinhasSOM ) +
		       linhaSOM * numLinhasPixeis / numLinhasSOM ),
		raioCircFig, Scalar( 255, 0, 0 ), -1, 8, 0 );
      }
    }
    imwrite( "mascaraSOMcor.png", matMascFdCor );
  }
  // A matDistTopologicas guarda, em cada posição (i,j), a distância
  // topológica entre o neurônio i e o neurônio j no SOM.
  int matDistTopologicas[ numNeuronios ][ numNeuronios ];
  for( int i = 0; i < numNeuronios; i++ ) {
    for( int j = 0; j < numNeuronios; j++ ) {
      matDistTopologicas[ i ][ j ] = -1;
    }
  }
  for( int indUmNeuronio = 0; indUmNeuronio < numNeuronios;
       indUmNeuronio++ ) {
    int linhaUmNeuronio = indUmNeuronio / numColunasSOM;
    int colunaUmNeuronio = indUmNeuronio % numColunasSOM;
    for( int indOutroNeuronio = 0; indOutroNeuronio < numNeuronios;
	 indOutroNeuronio++ ) {
      int linhaOutroNeuronio = indOutroNeuronio / numColunasSOM;
      int colunaOutroNeuronio = indOutroNeuronio % numColunasSOM;
      matDistTopologicas[ indUmNeuronio ][ indOutroNeuronio ] =
	abs( linhaUmNeuronio - linhaOutroNeuronio ) +
	abs( colunaUmNeuronio - colunaOutroNeuronio );
    }
  }
  cout << "\n\nmatriz de distâncias topológicas:\n\n";
  for( int i = 0; i < numNeuronios; i++ ) {
    for( int j = 0; j < numNeuronios; j++ ) {
      cout << matDistTopologicas[ i ][ j ] << " ";
    }
    cout << endl;
  }
  cout << endl;
  int numEntradasArqEntradas = entradas.getNumLinhas();
  cout << "numEntradasArqEntradas = " << numEntradasArqEntradas << endl;
  srand( unsigned( time( 0 ) ) );
  vector<int> vtIndEntradas;
  // Prepara vetor de índices de entrada, para embaralhamento.
  for( int i = 0; i < numEntradasArqEntradas; i++ ) {
    vtIndEntradas.push_back( i );
  }
  long int numEntrTodasAsAplic = numEntradasArqEntradas * numAplicArqEntradas;
  cout << "numEntrTodasAsAplic = " << numEntrTodasAsAplic << endl;
  int *indSeqVencedores = new int[ numEntradasArqEntradas ];
  struct { int linha, coluna; } coordVencUltEpoca[ numEntradasArqEntradas ];
  double alfaDaEpoca = alfaIni;
  double sigmaDaEpoca = sigmaIni;
  long int numEpocas = numEntrTodasAsAplic / numEntrPorEpoca;
  long int indEntrTodasAsAplic = 0;
  cout << "O programa aplicará o arquivo de entradas numAplicArqEntradas = "
       << numAplicArqEntradas << " vezes.\n\n";
  for( int indAplicArqEntradas = 0; indAplicArqEntradas < numAplicArqEntradas;
       indAplicArqEntradas++ ) {
    cout << "indAplicArqEntradas = " << indAplicArqEntradas << endl;
    // Se for a última aplicação, mantém a ordem das entradas:
    if( indAplicArqEntradas == numAplicArqEntradas - 1 ) {
      for( int i = 0; i < numEntradasArqEntradas; i++ ) {
	vtIndEntradas[ i ] = i;
      }
    }
    else { // senão, embaralha:
      random_shuffle( vtIndEntradas.begin(), vtIndEntradas.end() );
    }
    for( vector<int>::iterator itIndEntradas = vtIndEntradas.begin();
	 itIndEntradas != vtIndEntradas.end();
	 itIndEntradas++ ) {
      int indEntrada = *itIndEntradas;
      int indNeurVencedor = -1;
      cout << "indEntrada = " << indEntrada << endl;
      long int indEpoca = indEntrTodasAsAplic / numEntrPorEpoca + 1;
      cout << "indEpoca = " << indEpoca << endl;
      if( atualizaSOM[ 0 ] == 's' ) {
	alfaDaEpoca =
	  alfaIni * pow( ( alfaFin / alfaIni ),
			 ( double( indEpoca ) / numEpocas ) );
	cout << "alfaDaEpoca = " << alfaDaEpoca << endl;
	sigmaDaEpoca =
	  sigmaIni * pow( ( sigmaFin / sigmaIni ),
			  ( double( indEpoca ) / numEpocas ) );
	cout << "sigmaDaEpoca = " << sigmaDaEpoca << endl;
      }
      double *umaEntrada = entradas.getPtLinha( indEntrada );
      double menorDist2 = infinito;
      double menorDistManhat = infinito;
      // busca pelo mais próximo:
      for( int indNeuronio = 0; indNeuronio < numNeuronios; indNeuronio++ ) {
	double *umNeuronio = neuronios.getPtLinha( indNeuronio );
	double difEntrNeur[ numDimensoes ];
	for( int i = 0; i < numDimensoes; i++ ) {
	  difEntrNeur[ i ] = umaEntrada[ i ] - umNeuronio[ i ];
	}
	if( tipoDistancia[ 0 ] == 'E' ) { // Euclid
	  double distEuclid2 = 0;
	  for( int i = 0; i < numDimensoes; i++ ) {
	    distEuclid2 += difEntrNeur[ i ] * difEntrNeur[ i ];
	  }
	  if( distEuclid2 < menorDist2 ) {
	    menorDist2 = distEuclid2;
	    indNeurVencedor = indNeuronio;
	  }
	}
	else { // Manhat
	  double distManhat = 0;
	  for( int i = 0; i < numDimensoes; i++ ) {
	    distManhat += abs( difEntrNeur[ i ] );
	  }
	  if( distManhat < menorDistManhat ) {
	    menorDistManhat = distManhat;
	    indNeurVencedor = indNeuronio;
	  }
	}
      }
      cout << "indNeurVencedor = " << indNeurVencedor << endl;
      int linhaVencedor = indNeurVencedor / numColunasSOM;
      int colunaVencedor = indNeurVencedor % numColunasSOM;
      cout << "\nlinha do vencedor no SOM: " << linhaVencedor << endl;
      cout << "coluna do vencedor no SOM: " << colunaVencedor << "\n\n";
      if( indAplicArqEntradas == ( numAplicArqEntradas - 1 ) ) {
	indSeqVencedores[ indEntrada ] = indNeurVencedor;
	coordVencUltEpoca[ indEntrada ].linha = linhaVencedor;
	coordVencUltEpoca[ indEntrada ].coluna = colunaVencedor;
      }
      if( indEpoca == numEpocas && seGeraFigVenced[ 0 ] == 's' ) {
	Mat matMostraVcdrFdPreto = matMascFdPreto.clone();
	int xVcdr = numColunasPixeis / ( 2 * numColunasSOM ) +
	  colunaVencedor * numColunasPixeis / numColunasSOM;
	int yVcdr = numLinhasPixeis / ( 2 * numLinhasSOM ) +
	  linhaVencedor * numLinhasPixeis / numLinhasSOM;
	circle( matMostraVcdrFdPreto, Point( xVcdr, yVcdr ), raioCircFig/2,
		Scalar( 255, 255, 255 ), -1, 8, 0 );
	circle( matMascFdCor, Point( xVcdr, yVcdr ), raioCircFig,
		mpRotuloCor[ vtRotulosComRepet[ indEntrada ] ], -1, 8, 0 );
	stringstream strstr;
	strstr << setw( 5 ) << setfill( '0' ) << indEntrada;
	string nomeArqImgFdPreto = "z_entrada_" + strstr.str() + ".png";
	imwrite( nomeArqImgFdPreto, matMostraVcdrFdPreto );
	string nomeArqImgFdCor = "x_entrada_" + strstr.str() + ".png";
	imwrite( nomeArqImgFdCor, matMascFdCor );
      }
      // ajuste de pesos:
      if( atualizaSOM[ 0 ] == 's' ) {
	for( int indNeuronio = 0; indNeuronio < numNeuronios; indNeuronio++ ) {
	  double *pesoAntigo = neuronios.getPtLinha( indNeuronio );
	  int distTopologica2 =
	    matDistTopologicas[ indNeuronio ][ indNeurVencedor ] *
	    matDistTopologicas[ indNeuronio ][ indNeurVencedor ];
	  double hc = exp( -distTopologica2 / 2 / sigmaDaEpoca / sigmaDaEpoca );
	  double difNeur[ numDimensoes ];
	  for( int i = 0; i < numDimensoes; i++ ) {
	    difNeur[ i ] = umaEntrada[ i ] - pesoAntigo[ i ];
	  }
	  double *pesoNovo = neuronios.getPtLinha( indNeuronio );
	  for( int i = 0; i < numDimensoes; i++ ) {
	    pesoNovo[ i ] = pesoAntigo[ i ] + alfaDaEpoca * hc * difNeur[ i ];
	  }
	}
      }
      indEntrTodasAsAplic++;
      cout << "indEntrTodasAsAplic = " << indEntrTodasAsAplic << endl;
    }
  }
  neuronios.gravaArquivo( nomeArqNeuroniosFinais );
  ofstream arqSeqVencedores;
  arqSeqVencedores.open( nomeArqSeqVencUltEpoca, ios::out );
  for( long int i = 0; i < numEntradasArqEntradas; i++ ) {
    arqSeqVencedores << indSeqVencedores[ i ] << endl;
  }
  arqSeqVencedores.close();
  ofstream arqCoordSeqVencedores;
  arqCoordSeqVencedores.open( nomeArqCoordVencUltEpoca, ios::out );
  for( long int i = 0; i < numEntradasArqEntradas; i++ ) {
    arqCoordSeqVencedores << coordVencUltEpoca[ i ].linha << ","
			  << coordVencUltEpoca[ i ].coluna << endl;
  }
  arqCoordSeqVencedores.close();
  // Geração de U-Matrix
  double uMatrixUnidim[ numNeuronios ];
  for( int indUmNeuronio = 0; indUmNeuronio < numNeuronios;
       indUmNeuronio++ ) {
    double *umNeuronio = neuronios.getPtLinha( indUmNeuronio );
    int linhaUmNeuronio = indUmNeuronio / numColunasSOM;
    int colunaUmNeuronio = indUmNeuronio % numColunasSOM;
    int numVizinhos = 0;
    double somaDist = 0;
    for( int indOutroNeuronio = 0; indOutroNeuronio < numNeuronios;
	 indOutroNeuronio++ ) {
      int linhaOutroNeuronio = indOutroNeuronio / numColunasSOM;
      int colunaOutroNeuronio = indOutroNeuronio % numColunasSOM;
      if( matDistTopologicas[ indUmNeuronio ][ indOutroNeuronio ] == 1 ) {
	numVizinhos++;
	double *outroNeuronio = neuronios.getPtLinha( indOutroNeuronio );
	for( int dim = 0; dim < numDimensoes; dim++ ) {
	  double delta = umNeuronio[ dim ] - outroNeuronio[ dim ];
	  somaDist += delta * delta;
	}
      }
    }
    uMatrixUnidim[ indUmNeuronio ] = sqrt( somaDist ) / numVizinhos;
  }
  double minValUMatrix = infinito;
  double maxValUMatrix = 0;
  cout << "\n\nuMatrixUnidim:\n\n";
  for( int indUmNeuronio = 0; indUmNeuronio < numNeuronios;
       indUmNeuronio++ ) {
    cout << "uMatrixUnidim[ " << setw( 4 ) << indUmNeuronio
	 << " ] = " << uMatrixUnidim[ indUmNeuronio ] << endl;
    if( uMatrixUnidim[ indUmNeuronio ] < minValUMatrix ) {
      minValUMatrix = uMatrixUnidim[ indUmNeuronio ];
    }
    if( uMatrixUnidim[ indUmNeuronio ] > maxValUMatrix ) {
      maxValUMatrix = uMatrixUnidim[ indUmNeuronio ];
    }
  }
  cout << "\n\nminValUMatrix = " << minValUMatrix;
  cout << "\nmaxValUMatrix = " << maxValUMatrix << endl;
  // Monta Mat para U-Matrix:
  Mat matUMatrix( numLinhasPixeis, numColunasPixeis, CV_8UC3,
		    Scalar( 0.027 * 255, 0.8 * 255, 0.319 * 255 ) );
  for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
    line( matUMatrix,
	  Point( numColunasPixeis / ( 2 * numColunasSOM ),
		 numLinhasPixeis / ( 2 * numLinhasSOM ) +
		 linhaSOM * numLinhasPixeis / numLinhasSOM ),
	  Point( ( 2 * numColunasSOM - 1 ) * numColunasPixeis /
		 ( 2 * numColunasSOM ),
		 numLinhasPixeis / ( 2 * numLinhasSOM ) +
		 linhaSOM * numLinhasPixeis / numLinhasSOM ),
	  Scalar( 0, 0, 0 ), 1, 8 );
  }
  for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
    line( matUMatrix,
	  Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		 colunaSOM * numColunasPixeis / numColunasSOM,
		 numLinhasPixeis / ( 2 * numLinhasSOM ) ),
	  Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		 colunaSOM * numColunasPixeis / numColunasSOM,
		 ( 2 * numLinhasSOM - 1 ) * numLinhasPixeis /
		 ( 2 * numLinhasSOM ) ),
	  Scalar( 0, 0, 0 ), 1, 8 );
  }
  for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
    for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
      int indNeur = linhaSOM * numColunasSOM + colunaSOM;
      int corNeur = 255 * ( uMatrixUnidim[ indNeur ] - maxValUMatrix )
	/ ( minValUMatrix - maxValUMatrix );
      circle( matUMatrix,
	      Point( numColunasPixeis / ( 2 * numColunasSOM ) +
		     colunaSOM * numColunasPixeis / numColunasSOM,
		     numLinhasPixeis / ( 2 * numLinhasSOM ) +
		     linhaSOM * numLinhasPixeis / numLinhasSOM ),
	      raioCircFig, Scalar( corNeur, corNeur, corNeur ), -1, 8, 0 );
    }
  }
  imwrite( "uMatrix.png", matUMatrix );
  // Escreve matriz U normalizada na tela. Poderá escrevê-la em arquivo.
  // 0 é o mínimo (branco nas figs). 1 é o máximo (preto nas figs).
  ofstream arqMatrUNormalizada;
  arqMatrUNormalizada.open( "matrizUNormalizada.ascii", ios::out );
  for( int linhaSOM = 0; linhaSOM < numLinhasSOM; linhaSOM++ ) {
    for( int colunaSOM = 0; colunaSOM < numColunasSOM; colunaSOM++ ) {
      int indNeur = linhaSOM * numColunasSOM + colunaSOM;
      double valNormalizado = ( uMatrixUnidim[ indNeur ] - minValUMatrix )
	/ ( maxValUMatrix - minValUMatrix );
      arqMatrUNormalizada << " " << valNormalizado;
    }
    arqMatrUNormalizada << endl;
  }
  arqMatrUNormalizada.close();
  return 0;
}
