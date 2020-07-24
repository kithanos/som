#! /usr/bin/octave -qf
arg_list = argv();
numLinhasSOM = str2num( arg_list{ 1 } );
numColunasSOM = str2num( arg_list{ 2 } );
numComponVetor = str2num( arg_list{ 3 } );
nomeArqResultado = arg_list{ 4 };
numNeuronios = numLinhasSOM * numColunasSOM;
matAleatoria = rand( numNeuronios, numComponVetor );
save( "-ascii", nomeArqResultado, "matAleatoria" );
disp( matAleatoria )
