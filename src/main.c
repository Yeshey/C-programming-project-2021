/*
Plano Inicial (first draft):
 Função Inicializar o Tabuleiro com 3-5 linhas/colunas aleatóriamente (quadrado) (usar initRandom();)
    -Verificar se temos um ficheiro binário “jogo.bin”, perguntar se quer retomar o jogo.
    -Função Perguntar se quer jogar contra outro jogador ou contra um automático 
 Função Escrevê-lo na consola
 Função Turno - diz se é jogador A ou B
    - chamada da função jogada 
        -Perguntar "qual é a sua jogada?"" na consola
        -Receber input
            -Escolha: Jogar(1), Ver tabuleiros anteriores(2), Pausar(3) 
                Pausar(3):
                    -guardar informação relevante num ficheiro binário “jogo.bin”
                Ver tabuleiros anteriores(2)
                    -se o utilizador indicar K=3, o programa
apresenta na consola a sucessão de estados do tabuleiro nas 3 últimas jogadas.
                Jogar(1):
                    -do tipo 1,2
                    -1,2P no caso de Pedra
                    -ou L (linha nova no fim do tabuleiro)
                    -ou C (coluna nova no fim do tabuleiro)
                    -  b (escolher outra opção, voltar atráz)
        - chamada da função restrições que diz se é válida ou não
            -se não válida, obriga a jogar outra vez
    - chama a função determina_resultado_jogo
            -condições que verificam se alguma diagonal / linha / coluna está preenchida com a mesma cor - vitória - guarda num ficheiro de texto com nome dado pelo utilizador e apaga “jogo.bin”
            -Nota de rodapé: Se o tabuleiro não for quadrado, será impossível terminar o jogo formando uma diagonal toda da mesma cor.
 Função restrições
    -válido:
        -jogador que joga pode:
            -jogar verde numa casa vazia
            -jogar amarelo numa casa verde
            -jogar vermelho numa casa amarela
            -jogar uma pedra numa casa vazia
            -Criar uma coluna ou linha
                -no caso de criar uma coluna ou linha, criar no máximo 2 destes por jogo
                -no caso de pedra, máximo 1 vez por jogo
 Função determina_resultado_jogo

Tabuleiro 4*4:
S - Stone
 ---------------
| G : Y :   : R |    
|---:---:---:---|
| S : G :   : Y |
|---:---:---:---| 
|   :   :   :   |
|---:---:---:---|
| S : G : Y : R |
 ---------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "header.h"

int main(){

    initRandom();
    welcome();
    initializer();
    printf("Thanks for playing!\n");

    return 0;
}

/*
Bug Tracker:
fgets should be changed to strtok or scanf (like scanf(" %99[^\n]s", buffer);) to prevent multiple error messages when long string inputed
on memory manipulation error in updatetablearray in certain situations it'll exit without freeing all 2D arrays
*/