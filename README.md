Trabalho 1 - CI1164 (2021-1 ERE)
Prof. Dr. Guilherme Alex Derenievicz

Alunos:
Tiago Serique Valadares - GRR20195138 - tsv19
Fernanda Yukari Kawasaki - GRR20185057 - fyk18

--------------------------------------------------------------------------------
# Execucao

Para executar o código, basta rodar os comandos:
$ make
$ ./newtonSNL -o sample.out < sample.in

O arquivo de input eh feito pela entrada padrao;
O arquivo para output eh feito usando o parametro "-o". Se nao for especificado,
o output vai para a saida padrao

--------------------------------------------------------------------------------

# Entrada
O trabalho desenvolvido resolve varios sistemas nao lineares utilizando o metodo
de Newton.

O arquivo de input eh recebido pela entrada padrao (stdin) e os valores de cada
bloco sao lidos em loop e armazenados na struct SNL_T, o que pode ser visto na
funcao "le_input". O loop ocorre ate chegar no final do arquivo, e em cada
iteracao o sistema do bloco lido eh resolvido.

--------------------------------------------------------------------------------

# Estruturas de dados
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
guardar os evaluators e chamar somente a funcao "evaluator_evaluate". As funcoes
"gera_matriz_derivadas" e "le_input" geram os evaluators para derivadas e expressoes
respectivamente, utilizando a funcao "evaluator_create".

Outra estrutura relevante eh a result_jacobiana, que contem os resultados das derivadas
parciais da matriz jacobiana utilizando o vetor de incognitas da iteracao.

--------------------------------------------------------------------------------
# Resolvendo o sistema

## Metodo de Newton
Para resolver o sistema, foi utilizado o metodo de Newton, que consiste em aproximar
os valores das incognitas X usando ate max_iter iteracoes, ou ate que os valores sejam
menores que a tolerancia estabelecida. Isso eh feito na funcao newtonMetod.

Em cada iteracao do metodo de Newton, o sistema linear
J(X^(i)) * delta^(i) = - F(X^(i))
precisa ser resolvido internamente utilizando a eliminacao de Gauss. O sistema triangular
resultante eh resolvido com a retrossubstituicao. Assim, obtemos o delta,
que permite que a nova aproximacao de X seja obtida.

## Eliminacao de Gauss
A eliminacao de Gauss eh feita na funcao "eliminacao_gauss", que consiste na
eliminacao progressiva de variaveis na matriz de coeficientes. A equacao
pivo p e a equacao k sao selecionadas, e o objetivo eh remover a variavel xp de k.
Para isso, multiplicamos a equacao pivo por m e subtraimos o resultado da linha k.

    m_p = J_k / J_p
    onde J_k eh o coeficiente da linha e coluna onde queremos remover a variavel e
    J_p eh o coeficiente do pivo.

    Assim, o calculo feito eh:
    eq_k = eq_k − m_k_p ∗ eq_p

Alem disso, tambem eh feito o pivoteamento parcial, em que as linhas sao trocadas de ordem para que
o maior valor em modulo de cada coluna esteja na diagonal a fim de reduzir os erros
numericos (como cancelamento subtrativo) e evitar casos onde o 0 esta na diagonal principal (o que gera divisao por 0).
O resultado sera uma matriz triangular superior.

## Retrossubstituicao
Em seguida, eh feito o processo da retrossubstituicao na funcao "retrossub", no qual
substituimos progressivamente os valores de delta da ultima linha ate a primeira. Como a
matriz eh triangular superior, em cada linha mais um valor de delta eh encontrado,
e os valores anteriores auxiliam no calculo dos proximos delta.

## Nova Aproximacao
Após obter o delta, basta somar com os valores de X para obter a proxima aproximacao,
tendo em vista a propria definicao de delta, que eh a diferenca entre a nova aproximacao
e a antiga.
X^(i+1) = X^(i) + delta^(i)

Esse processo eh feito em ate max_iter iteracoes, ou ate que os valores sejam
proximos o suficiente. Para verificar isso, a norma do vetor de incognitas e 
do vetor de deltas eh calculada.

--------------------------------------------------------------------------------

# Erros

