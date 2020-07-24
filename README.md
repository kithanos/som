# som

Aplicação da técnica SOM com interface gráfica.

Requistos:

--------------------------------------COMPILAÇÃO------------------------------------------------

Editar o arquivo CMakeLists.txt com a versão do cmake instalada.

Para compilar, execute em no terminal:

>> cmake .

>> make

Pacotes necessários:
OpenCV
GSL
cmake
tkinter

Programa compilado e testado em:
GNU 5.4.0
cmake version 3.5.1
GNU Octave, version 4.0.0

OBS: Caso precise compilar o programa mais de uma vez, apagar todos os arquivos e pasta gerados pelo cmake,
(não apagar o CMakeLists.txt)

--------------------------------------EXECUÇÃO--------------------------------------------------

Para executar com a interface gráfica, digite em um terminal:

>> ./tkinterSom.py

Preencher os campos na janela na inteface de acordo com os seus arquivos de dados.

Exemplo, de acordo com os arquivos de dados fornecidos em /Dados

programa em: Local dos arquivos na máquina do usuário.

num.linhas SOM: É o número de linhas do SOM, supondo-se que ele seja uma
matriz bidimensional. O número de colunas é calculado, pelo
programa, a partir do numLinhasSOM e do número de neurônios encontrados
no arquivo de neurônios iniciais.

arq. vetores iniciais: É um arquivo que contém, em cada
uma de suas L linhas, os N valores dos pesos iniciais de um
neurônio, separados por espaços.

arq. vetores de entrada: É um arquivo contendo uma série de entradas
para o SOM. (veja /Dados/dados.ascii para modelo de arquivo/exemplo).

arq. rótulos de entrada:
é um arquivo contendo uma série de rótulos. (nomes) para as entradas do arquivo nomeArqEntradas.ascii.
(veja /Dados/rotulos.txt para modelo de arquivo/exemplo)

Para gerar arquivos de rótulos para os seus arquivos de dados (ou outros), execute o programa em 
/geraSerieNumerosConsecutivosTexto

núm.entradas por época: É o número de entradas diferentes na execução do
SOM. Cada entrada é um vetor. Como elas podem aparecer de forma
cíclica no arquivo de entradas, o usuário indica quantas entradas
diferentes existem no arquivo, para o programa saber quando há
mudança de ciclos (ou seja, de épocas) na aplicação das
entradas. Útil, por exemplo, quando entradas embaralhadas e
repetidas estiverem num mesmo arquivo.

num. aplicações (eṕocas) arq. entradas: 
É o número de vezes em que as entradas do
arquivo de entradas deverão ser aplicadas. Por exemplo, se valer 10,
todo o conjunto de entradas do arquivo de entradas será aplicado 10
vezes, do início ao fim, de forma cíclica, sempre na mesma sequência.

tipo de distância: Escolha entre Euclides ou Manhattan.
Veja mais em: https://pt.wikipedia.org/wiki/Geometria_do_t%C3%A1xi

SOM com atualização (sim para treino)?: 
É sim se o SOM deve ser atualizado durante o
funcionamento e não se o SOM for usado só para classificação, sem
mudanças de posições dos neurônios. Se atualizaSOM for nao, os
valores de alfa e de sigma são irrelevantes.

Gera figuras de neurônios vencedores?:
conforme se desejar a geração de figuras de neurônios vencedores. 
A figura da matriz U sempre é gerada.

alfa inic e alfa final: São valores inicial e final para o fator de
aprendizagem.

sigma inic e sigma final: São valores inicial e final para a função de
vizinhança.

arq.neurônios finais: É o nome de um arquivo que receberá os
valores finais dos neurônios.

arq.seq.neurônios vencedores: É o nome de um arquivo que receberá os
o número do neurônio vencedor para a época final.

arq.coordenadas neurônios vencedores: É o nome de um arquivo que receberá os
a coordenada do neurônio vencedor para a época final.

