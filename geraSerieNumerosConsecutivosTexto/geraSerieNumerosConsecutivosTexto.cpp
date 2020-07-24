// Recebe número limite N e gera série de 0 até (N-1).

#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

main( int argc, char **argv ) {
  int opcaoGetopt, N;
  while( ( opcaoGetopt = getopt( argc, argv, "n:" ) ) != -1 ) {
    switch( opcaoGetopt ) {
    case 'n':
      N = atoi( optarg );
      break;
    }
  }
  for( int i = 0; i < N; i++ ) {
    cout << setw( 5 ) << setfill( '0' ) << i << endl;
  }
  return 0;
}
