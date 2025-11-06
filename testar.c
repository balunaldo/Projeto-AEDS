#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "TConj.h"

int main() {
    TConj A, B, C, D;
    int num, i = 0;
    setlocale(LC_ALL, "Portuguese");
    SetConsoleOutputCP(1252);
    inicializar(&A);
    srand(42);//n° de aleatórios

    for( i=0; i<20; i++) {
        inserir_elemento(&A, rand()%40); //colocar 20 números aleatórios em A
    }    
    printf("Conjunto A (depois de 20 insercoes):\n");
    imprimir(A);

    //remover 10 aleatórios
    while(A.n>10) {
        remover_elemento(&A, A.elementos[rand()%A.n]);
    }    
    printf("\nConjunto A (depois de 10 remocoes):\n");
    imprimir(A);
    
    
    if (testar_elemento(A, 9) == -1) {
        printf("\nO elemento 9 nao esta em A\n"); //verificar se 9 está em A
    }else{
        printf("\nO elemento 9 esta em A\n");
    }
    B = gerar_conjunto(10);
    imprimir(B);    
    num = conj2num(B);
    printf("N° gerado: %d\n", num);    
    C = num2conj(num);
    imprimir(C);
    
    if (comparar(B, C)) {
        printf("B e C são iguais\n");
    }else{
        printf("B e C são diferentes\n");
    }

    //testa operações
    printf("\nD = Uniao(A, B):\n");
    D = uniao(A, B);
    imprimir(D);
    printf("\nD = Interseccao(A, B):\n");
    D = inter(A, B);
    imprimir(D);
    printf("\nD = Subtracao(A, B):\n");
    D = subtrair(A, B);
    imprimir(D);

    //liberar memória
    liberar_memoria(&A);
    liberar_memoria(&B);
    liberar_memoria(&C);
    liberar_memoria(&D);

    return 0;
}