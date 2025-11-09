#include "TConj.h"

void inicializar(TConj* pA){
    pA->capacidade = 10;
    pA->n = 0;           
    pA->elementos = (int*) malloc(pA->capacidade * sizeof(int)); //alocar memória
    if (pA->elementos == NULL) {
        printf("Erro!\n");
        exit(1); 
    }
}

void realocar_memoria(TConj* pA){
    int nova_capacidade = pA->capacidade + 10; //aumentar capacidade em 10
    int* novos_elementos = (int*) realloc(pA->elementos, nova_capacidade * sizeof(int)); //realocar memória pro tamanho necessario
    if (novos_elementos == NULL) {
        printf("Erro: Falha na realocação de memória!\n");
        exit(1);
    }
    pA->elementos = novos_elementos;
    pA->capacidade = nova_capacidade; //atualizar capacidade
}

void liberar_memoria(TConj* pA){
    if(pA->elementos != NULL){
        free(pA->elementos);   
        pA->elementos = NULL;
    }
    pA->n = 0;
    pA->capacidade = 0;
}

int testar_elemento(TConj A, int elem){
    int i;
    for(i = 0; i < A.n; i++){
        if (A.elementos[i] == elem) {
            return i; //retornar posição
        }
    }
    return -1;
}

int inserir_elemento(TConj* pA, int elem){ //inserir elemento no conjunto
    if(testar_elemento(*pA, elem) != -1){
        return 0; //falha = 0
    }else if (pA->n == pA->capacidade) {
        realocar_memoria(pA); 
    }
    pA->elementos[pA->n] = elem;
    pA->n++; 
    return 1;
}

int remover_elemento(TConj* pA, int elem){
    int posicao = testar_elemento(*pA, elem); //pos vai receber a posicao do elem
    if(posicao == -1){
        return 0;
    }
    int i;
    for(i = posicao; i < pA->n - 1; i++){
        pA->elementos[i] = pA->elementos[i + 1]; //deslocar à esquerda
    }
    pA->n--;
    return 1;
}

int set_elemento(TConj* pA, int elem, int posicao){
    if(posicao<0 || posicao>=pA->n){
        return 0; //mostra que é invalida
    }
    pA->elementos[posicao] = elem;
    return 1; 
}

int get_elemento(TConj A, int posicao, int* pelem){
    while(posicao >= A.n){
        return 0;
    }
    *pelem = A.elementos[posicao]; //atribuir valor ao ponteiro
    return 1; 
}

TConj gerar_conjunto(int n){
    TConj C;
    inicializar(&C);
    do{ //gerar elem aleatorios até o valor n
        int elem_aleatorio = rand() % 10; 
        inserir_elemento(&C, elem_aleatorio);
    }while(C.n<n);
    return C; 
}

TConj num2conj(int n){
    TConj C;
    inicializar(&C); //inicializar conjunto e inserir dígitos
    if(n == 0){
        inserir_elemento(&C, 0);
        return C;
    }else if(n < 0){
        n = -n; //ver negativos
    }
    while(n > 0){
        int digito = n % 10; 
        inserir_elemento(&C, digito); //enqt houver digitos inserir no conjunto
        n = n/10; 
    }
    return C;
}

int conj2num(TConj A){ //converter conjunto em número 
    int num_final = 0;
    int i;
    for (i = 0; i < A.n; i++) { //for para cada elemento do conjunto e construir número
        num_final = num_final * 10 + A.elementos[i];
    }
    return num_final;
}

int comparar(TConj A, TConj B){
    if (A.n != B.n) {
        return 0;
    }
    int i;
    for(i = 0; i < A.n; i++){ //verificar se elem de A tá em B
        if (testar_elemento(B, A.elementos[i]) == -1) {
            return 0;
        }
    }
    return 1;
}

void imprimir(TConj A){
    printf("Conjunto %d %d: {", A.n, A.capacidade);
    int i;
    for (i = 0; i < A.n; i++) {
        printf("%d", A.elementos[i]); //imprimir elem do conjunto na pos i
        if (i < A.n - 1) {
            printf(", ");
        }
    }
    printf("} \n");
}

TConj uniao(TConj A, TConj B){ //juntar dois conjuntos e retornar o resultado numa variavel C
    TConj C;
    inicializar(&C);
    int i;
    for (i = 0; i < A.n; i++) {//for para inserir elem de A e B em C
        inserir_elemento(&C, A.elementos[i]);
    }
    for (i = 0; i < B.n; i++) {
        inserir_elemento(&C, B.elementos[i]);
    }
    return C; 
}
TConj inter(TConj A, TConj B){ //mostrar os elem comuns entre os 2 conjuntos
    TConj C;
    inicializar(&C);
    int i = 0;
    while(i<A.n) {
        if (testar_elemento(B, A.elementos[i]) != -1) {
            inserir_elemento(&C, A.elementos[i]);
        }
        i++;
    }
    return C;
}

TConj subtrair(TConj A, TConj B){ //tirar de A os elem presentes em B tbm
    TConj C;
    inicializar(&C);
    int i = 0;
    while(i<A.n){
        if (testar_elemento(B, A.elementos[i]) == -1) {
            inserir_elemento(&C, A.elementos[i]);
        }
        i++;
    }
    return C;
}

TConj numConjJogo(int n, int tam){ //função do jogo q converte o n° do palpite em conjunto
    TConj C;
    inicializar(&C);

    if(tam == 3){//inserir os digitos de acordo com o tamanho
        inserir_elemento(&C, n/100);
        inserir_elemento(&C, (n/10)%10);
        inserir_elemento(&C, n%10);
    }else if(tam == 4){//
        inserir_elemento(&C, n/1000);
        inserir_elemento(&C, (n/100)%10);
        inserir_elemento(&C, (n/10)%10);
        inserir_elemento(&C, n%10);       
    }

    return C;
}