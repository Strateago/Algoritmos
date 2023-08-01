#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lista{
    int V;
    struct lista *next;
}Arestas;

typedef struct{
    Arestas *Head;
    Arestas *Tail;
}Fila;

typedef struct tabela{
    Arestas *Head;
    int Valor;
}Grafo;

Arestas *list_insert(Arestas *Vector, int V){
    Arestas *New = (Arestas*) malloc (sizeof(Arestas));
    New->next = Vector->next;
    New->V = V;
    Vector->next = New;
    return Vector;
}

Arestas *list_delete(Arestas *Vector){
    Arestas *Del = Vector->next;
    Vector->next = Del->next;
    free(Del);
    return Vector;
}

Arestas *Dequeue(Arestas *Head, Arestas **Tail, int *V){
    *V = Head->next->V;
    Head = list_delete(Head);
    if(Head->next == NULL){
        *Tail = Head;
    }
    return Head;
}

Grafo *contract(Grafo *grafo, int V1, int V2, int *Nos_restantes, int *Grau_No, int Nos){
    Arestas *Aux1;
    Arestas *Aux2;
    int Valores1 = grafo[V1].Valor;
    int Valores2 = grafo[V2].Valor;
    int NosIguais = 0;
    if(Valores1 != Valores2){
        (*Nos_restantes)--;
        Aux1 = grafo[Valores1].Head;
        Aux2 = grafo[Valores2].Head;
        while(Aux2->next != NULL){
            if(Aux1->next != NULL && Aux1->next->V == Aux2->next->V){
                NosIguais = 1;
                Aux2 = list_delete(Aux2);
                Aux1 = grafo[Valores1].Head;
            }
            else{
                NosIguais = 0;
            }
            if(Aux1->next == NULL && NosIguais == 0){
                Aux1 = list_insert(Aux1, Aux2->next->V);
                Aux2 = list_delete(Aux2);
                Aux1 = grafo[Valores1].Head;
            }
            else if(NosIguais == 0){
                Aux1 = Aux1->next;
            }
        }
        Aux1 = grafo[Valores1].Head;
        while(Aux1 != NULL){
            if(Aux1->next != NULL && (Aux1->next->V == Valores1 || Aux1->next->V == Valores2)){
                Aux1 = list_delete(Aux1);
            }
            else{
                Aux1 = Aux1->next;
            }
        }
        for(int a = 0; a < Nos; a++){
            NosIguais = 0;
            Aux1 = grafo[grafo[a].Valor].Head;
            if(grafo[a].Valor == Valores2){
                grafo[a].Valor = Valores1;
            }
            while(Aux1 != NULL){
                if(Aux1->next != NULL && Aux1->next->V == Valores2){
                    Aux1->next->V = Valores1;
                }
                if(Aux1->next != NULL && Aux1->next->V == Valores1){
                    NosIguais++;
                }
                if(NosIguais == 2){
                    NosIguais--;
                    Aux1 = list_delete(Aux1);
                }
                Aux1 = Aux1->next;
            }
        }
    }
    Aux1 = grafo[Valores1].Head->next;
    while(Aux1 != NULL){
        (*Grau_No)++;
        Aux1 = Aux1->next;
    }
    return grafo;
}

int menor_caminho(Grafo *grafo, int No1, int No2, int Nos){
    int D[Nos], U, V;
    for(int a = 0; a < Nos; a++){
        D[a] = -1;
    }
    Fila New;
    Arestas *E;
    New.Head = (Arestas*) malloc (sizeof(Arestas));
    New.Tail = New.Head;
    New.Head->next = NULL;
    New.Tail = list_insert(New.Tail, grafo[No1].Valor);
    New.Tail = New.Tail->next;
    D[grafo[No1].Valor] = 0;
    while(New.Head != New.Tail){
        New.Head = Dequeue(New.Head, &New.Tail, &U);
        E = grafo[U].Head->next;
        while(E != NULL){
            V = E->V;
            if(D[V] == -1){
                D[V] = D[U] + 1;
                New.Tail = list_insert(New.Tail, V);
                New.Tail = New.Tail->next;
            }
            if(V == grafo[No2].Valor){
                return D[V];
            }
            E = E->next;
        }
    }
    return D[grafo[No2].Valor];
}

int main(){ 
    int V, E, No1, No2, X, V_rest, Grau_No = 0, Dist;
    Grafo *grafo;
    char Operacao[4];
    scanf("%d %d", &V, &E);
    V_rest = V;
    grafo = (Grafo*) malloc (V * sizeof(Grafo));
    for(int a = 0; a < V; a++){
        grafo[a].Head = (Arestas*) malloc (sizeof(Arestas));
        grafo[a].Head->next = NULL;
        grafo[a].Head->V = -1;
        grafo[a].Valor = a;
    }
    for(int a = 0; a < E; a++){
        scanf("%d %d", &No1, &No2);
        grafo[No1].Head = list_insert(grafo[No1].Head, No2);
        grafo[No2].Head = list_insert(grafo[No2].Head, No1);
    }
    scanf("%d", &X);
    for(int a = 0; a < X; a++){
        Grau_No = 0;
        scanf(" %3[^ ]", Operacao);
        scanf("%d %d", &No1, &No2);
        if(strcmp(Operacao, "CTR") == 0){
            grafo = contract(grafo, No1, No2, &V_rest, &Grau_No, V);
            printf("%d %d\n", V_rest, Grau_No);
        }
        else if(strcmp(Operacao, "DIS") == 0){
            Dist = menor_caminho(grafo, No1, No2, V);
            printf("%d\n", Dist);
        }
    }
    return 0;
}
