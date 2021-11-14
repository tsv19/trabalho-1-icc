Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Alunos:
Tiago Serique Valadares - GRR20195138 - tsv19
Fernanda Yukari Kawasaki - GRR20185057 - fyk18

--------------------------------------------------------------------------------

Para executar o código, basta rodar os comandos:
$ make
$ ./newtonSNL -o sample.out < sample.in

O arquivo de input eh feito pela entrada padrao;
O arquivo para output eh feito usando o parametro "-o". Se nao for especificado,
o output vai para a saida padrao

--------------------------------------------------------------------------------

O trabalho desenvolvido resolve varios sistemas nao lineares utilizando o metodo
de Newton.


O arquivo de input eh recebido pela entrada padrao (stdin) e os valores de cada
bloco sao lidos em loop e armazenados na struct SNL_T, o que pode ser visto na
funcao "le_input". O loop ocorre ate chegar no final do arquivo, e em cada
iteracao o sistema do bloco lido eh resolvido.


A estrutura SNL_T contem os seguintes elementos:
- unsigned int n:       eh a dimensao do sistema. Fornecida pelo usuario na entrada padrao
- int **expressoes:		vetor F(X) com as expressoes das funcoes nao lineares que compoem o sistema.
                        As expressoes sao objetos evaluator.
- void ***derivadas:	matriz F'(X) com as derivadas das equacoes nao lineares.
                        Os valores armazenados sao objetos evaluator
- double *incognitas:	aproximacao das incognitas X (de x1 ate xn). A aproximacao
                        inicial eh dada pelo usuario
- double *termos_indep: vetor de termos independentes. Contem os valores - F(X)

Note que expressoes e derivadas sao os proprios objetos evalutor. Como ambos precisam
ser calculados varias vezes nas iteracoes de Newton com valores X que variam, decidimos
guardar os evaluators e chamar somente a funcao evaluator_evaluate().


Para resolver o sistema, foi utilizado o metodo de Newton, que consiste em aproximar
os valores das incognitas usando ate max_iter iteracoes, ou ate que os valores sejam
menores que a tolerancia estabelecida.


Em cada iteracao do metodo de Newton, o sistema linear
J(X^(i)) * delta^(i) = - F(X^(i))
eh resolvido internamente utilizando a eliminacao de Gauss. O sistema triangular
resultante eh resolvido com a retrosubstituicao.

X^(i+1) = X^(i) + delta^(i)