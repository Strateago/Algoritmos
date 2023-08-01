#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Vertice {
  int V;
  int P;
  struct Vertice *Next;
} No;

typedef struct {
  int V;
  int P;
} Heap;

typedef struct {
  No *Head;
  No *Tail;
} Fila;

typedef struct {
  No *Aresta;
} grafo;

typedef struct {
  int V;
  int *array;
} Tabela;

No *list_insert(No *Vector, int V, int P) {
  No *New = (No *)malloc(sizeof(No));
  New->Next = Vector->Next;
  New->V = V;
  New->P = P;
  Vector->Next = New;
  return Vector;
}

No *list_delete(No *Vector) {
  No *Del = Vector->Next;
  Vector->Next = Del->Next;
  free(Del);
  return Vector;
}

Fila Cancela(Fila P, int Id) {
  No *Aux = P.Head;
  while (Aux != NULL) {
    if (Aux->Next != NULL && Aux->Next->V == Id) {
      Aux = list_delete(Aux);
      if (Aux->Next == NULL) {
        P.Tail = Aux;
      }
    }
    Aux = Aux->Next;
  }
  return P;
}

void bubble_up(Heap *heap, int tam) {
  Heap aux;
  while (tam > 0 && heap[tam].P <= heap[(tam - 1) / 2].P) {
    aux = heap[tam];
    heap[tam] = heap[(tam - 1) / 2];
    heap[(tam - 1) / 2] = aux;
    tam = (tam - 1) / 2;
  }
}

Heap *heap_insert(Heap *heap, int V, int P, int *tam_h, int *TAM_MAX) {
  if (*tam_h == *TAM_MAX) {
    *TAM_MAX = 2 * (*TAM_MAX);
    heap = (Heap*)realloc(heap, (*TAM_MAX) * sizeof(Heap));
  }
  heap[(*tam_h)].V = V;
  heap[(*tam_h)].P = P;
  bubble_up(heap, (*tam_h));
  (*tam_h)++;
  return heap;
}

void heapify(Heap *heap, int i, int tam_h) {
  Heap aux;
  int l = (2 * i) + 1, r = (2 * i) + 2, m = i;
  if (l < tam_h && heap[l].P <= heap[m].P) {
    m = l;
  }
  if (r < tam_h && heap[r].P <= heap[m].P) {
    m = r;
  }
  if (m != i) {
    aux = heap[m];
    heap[m] = heap[i];
    heap[i] = aux;
    heapify(heap, m, tam_h);
  }
}

int heap_extract(Heap *heap, int *d, int *tam_h) {
  Heap retorno;
  Heap aux;
  retorno = heap[0];
  if (*tam_h > 0) {
    aux = heap[0];
    heap[0] = heap[(*tam_h) - 1];
    heap[(*tam_h) - 1] = aux;
    (*tam_h)--;
    heapify(heap, 0, *tam_h);
  }
  *d = retorno.P;
  return retorno.V;
}

int *Dijkstra(grafo *Grafo, int Origem, int Nos) {
  int *D, tam_heap = 0, tamMAX = 1, u, d, V, W, found;
  No *e;
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  D = (int *)malloc(Nos * sizeof(int));
  for (int a = 0; a < Nos; a++) {
    D[a] = -1;
  }
  D[Origem] = 0;
  heap = heap_insert(heap, Origem, 0, &tam_heap, &tamMAX);
  for (int a = 0; a < Nos; a++) {
    u = heap_extract(heap, &d, &tam_heap);
    e = Grafo[u].Aresta->Next;
    while (e != NULL) {
      V = e->V;
      W = e->P;
      if (d + W < D[V] || D[V] == -1) {
        D[V] = d + W;
        found = 0;
        for (int b = 0; b < tam_heap && found == 0; b++) {
          if (heap[b].V == V) {
            heap[b].P = D[V];
            bubble_up(heap, b);
            found = 1;
          }
        }
        if (found == 0) {
          heap = heap_insert(heap, V, D[V], &tam_heap, &tamMAX);
        }
      }
      e = e->Next;
    }
  }
  return D;
}

int Delivery(Tabela *Rest, int Pos_E, Fila *P, int N) {
  int Nova_pos, Dist = -1, R;
  for (int a = 0; a < N; a++) {
    if (Dist == -1 ||
        Dist > Rest[a].array[Pos_E] + Rest[a].array[P->Head->Next->P]) {
      Dist = Rest[a].array[Pos_E] + Rest[a].array[P->Head->Next->P];
      R = Rest[a].V;
    }
  }
  Nova_pos = P->Head->Next->P;
  printf("%d %d %d %d %d\n", P->Head->Next->V, Pos_E, R, Nova_pos, Dist);
  P->Head = list_delete(P->Head);
  if (P->Head->Next == NULL) {
    P->Tail = P->Head;
  }
  return Nova_pos;
}

int main() {
  int V, E, N, M;
  int No1, No2, Dist, Rest, Id, Local, Pedidos = 0, Moto, primeiro = 1, Inicio;
  int *Entregadores;
  char Operacao[4];
  Tabela *Restaurantes;
  Fila P;
  grafo *Grafo;
  P.Head = (No *)malloc(sizeof(No));
  P.Head->Next = NULL;
  P.Tail = P.Head;
  scanf("%d %d %d %d", &V, &E, &N, &M);
  Restaurantes = (Tabela *)malloc(N * sizeof(Tabela));
  Entregadores = (int *)malloc(M * sizeof(int));
  Grafo = (grafo *)malloc(V * sizeof(grafo));
  for (int a = 0; a < V; a++) {
    Grafo[a].Aresta = (No *)malloc(sizeof(No));
    Grafo[a].Aresta->Next = NULL;
  }
  for (int a = 0; a < E; a++) {
    scanf("%d %d %d", &No1, &No2, &Dist);
    Grafo[No1].Aresta = list_insert(Grafo[No1].Aresta, No2, Dist);
    Grafo[No2].Aresta = list_insert(Grafo[No2].Aresta, No1, Dist);
  }
  for (int a = 0; a < N; a++) {
    scanf("%d", &Rest);
    if (primeiro == 1) {
      Inicio = Rest;
      primeiro = 0;
    }
    Restaurantes[a].V = Rest;
    Restaurantes[a].array = Dijkstra(Grafo, Rest, V);
  }
  for (int a = 0; a < M; a++) {
    Entregadores[a] = Inicio;
  }
  while (scanf(" %3[^ ]", Operacao), strcmp(Operacao, "END") != 0) {
    if (strcmp(Operacao, "NEW") == 0) {
      scanf("%d %d", &Id, &Local);
      Pedidos++;
      P.Tail = list_insert(P.Tail, Id, Local);
      P.Tail = P.Tail->Next;
      printf("+%d %d\n", Id, Pedidos);
    }
    if (strcmp(Operacao, "CEL") == 0) {
      scanf("%d", &Id);
      if (P.Head->Next != NULL) {
        P = Cancela(P, Id);
        Pedidos--;
        printf("-%d %d\n", Id, Pedidos);
      }
    }
    if (strcmp(Operacao, "DLV") == 0) {
      scanf("%d", &Moto);
      if (P.Head->Next != NULL) {
        Pedidos--;
        Entregadores[Moto] = Delivery(Restaurantes, Entregadores[Moto], &P, N);
      }
    }
  }
  return 0;
}
