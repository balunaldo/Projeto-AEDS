#ifndef TCONJ_H
#define TCONJ_H
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>   

typedef struct {
    int* elementos; 
    int n;          
    int capacidade; 
}TConj;

//tconj.h vai declarar as funções, basicamente nada além
void inicializar(TConj* pA);
void realocar_memoria(TConj* pA);
void liberar_memoria(TConj* pA);

int inserir_elemento(TConj* pA, int elem);
int remover_elemento(TConj* pA, int elem);
int set_elemento(TConj* pA, int elem, int pos);
int get_elemento(TConj A, int pos, int* pelem);
int testar_elemento(TConj A, int elem);

TConj gerar_conjunto(int n);
TConj num2conj(int num);

int conj2num(TConj A);
int comparar(TConj A, TConj B);
void imprimir(TConj A);

TConj uniao(TConj A, TConj B);
TConj inter(TConj A, TConj B);
TConj subtrair(TConj A, TConj B);

TConj numConjJogo(int n, int tam);
#endif