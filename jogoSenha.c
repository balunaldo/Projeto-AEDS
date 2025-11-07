#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "TConj.h"

int main(){
    setlocale(LC_ALL, "Portuguese");
    srand(time(NULL));

    TConj senhaGerada;
    int nvl, maxTentativas, tamanhoSenha;

    printf("Jogo da Senha\n");
    printf("Niveis: \n");
    printf("1. Facil (3 numeros)\n");
    printf("2. Dificil (4 numeros)\n");
    printf("3. Nivel de teste (4 numeros, senha visivel)\n");
    
    printf("Escolha o nivel desejado: ");
    scanf("%d", &nvl);
    printf("Digite o número máximo de tentativas: ");
    scanf("%d", &maxTentativas);

    switch(nvl){
        case 1:
            tamanhoSenha = 3;
            senhaGerada = gerar_conjunto(tamanhoSenha);
            break;
        case 2:
            tamanhoSenha = 4;
            senhaGerada = gerar_conjunto(tamanhoSenha);
            break;
        case 3:
            tamanhoSenha = 4;
            senhaGerada = gerar_conjunto(tamanhoSenha);
            printf("Senha gerada: ");
            imprimir(senhaGerada);
            break;
        default:
            printf("Nivel invalido! Encerrando o jogo.\n");
            return 0;
    }

    printf("O jogo começou! Tente adivinhar a senha.\n");
    int tent = 0;
    int acerto = 0;
    while(tent < maxTentativas){
        int numTent;
        printf("\nTentativa %d -> Digite seu palpite: ", tent + 1);
        scanf("%d", &numTent);

        TConj palpite = numConjJogo(numTent, tamanhoSenha);

        int posicaoCorreta = 0;
        for(int i = 0; i<tamanhoSenha; i++){
            int digSenha, digPalpite;
            get_elemento(senhaGerada, i, &digSenha);
            get_elemento(palpite, i, &digPalpite);
            if(digSenha == digPalpite){
                posicaoCorreta++;
            }            
        }
        TConj erros = inter(senhaGerada, palpite);
        int posicaoErrada = erros.n - posicaoCorreta;
        liberar_memoria(&erros);
        if(posicaoCorreta == tamanhoSenha){
            acerto = 1;
            liberar_memoria(&palpite);
            break;
        }
        printf("Posicao correta(s): %d, Posicao errada(s): %d\n", posicaoCorreta, posicaoErrada);
        liberar_memoria(&palpite);
        tent++;
    }

    if(acerto){
        printf("\nParabens, você acertou %d tentativas!\n", tent + 1);
    }else{
        printf("\nFim de jogo! Você nao adivinhou a senha.\n");
        printf("A senha era: ");
        imprimir(senhaGerada);
    }
    liberar_memoria(&senhaGerada);
    return 0;
}