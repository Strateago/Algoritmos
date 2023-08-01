#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ST {
  struct ST *left;
  struct ST *right;
  int V;
} ST;

ST *rotate_left(ST *root) {
  ST *R = root->right;
  ST *Rl = R->left;
  R->left = root;
  root->right = Rl;
  return R;
}

ST *rotate_right(ST *root) {
  ST *L = root->left;
  ST *Lr = L->right;
  L->right = root;
  root->left = Lr;
  return L;
}

ST *insert_st(ST *root, int V, int *D) {
  if (root == NULL) {
    root = (ST *)malloc(sizeof(ST));
    if (root == NULL) {
      printf("Falha Alocacao\n");
      exit(1);
    }
    root->V = V;
    root->left = NULL;
    root->right = NULL;
    printf("%d\n", *D);
    return root;
  } else if (V > root->V) {
    (*D)++;
    root->right = insert_st(root->right, V, D);
    root = rotate_left(root);
    return root;
  } else if (V < root->V) {
    (*D)++;
    root->left = insert_st(root->left, V, D);
    root = rotate_right(root);
    return root;
  }
  printf("%d\n", *D);
  return root;
}

ST *search_st(ST *root, int V, int *D, int *E) {
  if (root == NULL) {
    printf("%d\n", *D);
    *E = 0;
    return NULL;
  } else if (V == root->V) {
    printf("%d\n", *D);
    return root;
  } else if (V > root->V) {
    (*D)++;
    root->right = search_st(root->right, V, D, E);
    if (*E == 1) {
      root = rotate_left(root);
    }
    return root;
  } else if (V < root->V) {
    (*D)++;
    root->left = search_st(root->left, V, D, E);
    if (*E == 1) {
      root = rotate_right(root);
    }
    return root;
  }
}

ST *delete_st_min(ST *root, int *V) {
  if (root->left == NULL) {
    ST *R = root->right;
    int Value = root->V;
    free(root);
    *V = Value;
    return R;
  } else {
    ST *L = delete_st_min(root->left, V);
    root->left = L;
    return root;
  }
}

ST *delete_st(ST *root, int V, int *D, int *E, int *New_V, int *Pai_V) {
  ST *R, *L;
  if (root == NULL) {
    *E = 0;
    printf("%d\n", *D);
    return NULL;
  } else if (V > root->V) {
    (*D)++;
    root->right = delete_st(root->right, V, D, E, New_V, Pai_V);
    if (root->right == NULL || root->right->V == *New_V) {
      *Pai_V = root->V;
    } else if (root->right->V == *Pai_V && *E == 1) {
      root = rotate_left(root);
    }
    return root;
  } else if (V < root->V) {
    (*D)++;
    root->left = delete_st(root->left, V, D, E, New_V, Pai_V);
    if (root->left == NULL || root->left->V == *New_V) {
      *Pai_V = root->V;
    } else if (root->left->V == *Pai_V && *E == 1) {
      root = rotate_right(root);
    }
    return root;
  } else if (V == root->V) {
    printf("%d\n", *D);
    if (root->left == NULL) {
      R = root->right;
      free(root);
      if (R != NULL) {
        *New_V = R->V;
      }
      return R;
    } else if (root->right == NULL) {
      L = root->left;
      free(root);
      if (L != NULL) {
        *New_V = L->V;
      }
      return L;
    } else {
      root->right = delete_st_min(root->right, &root->V);
      *New_V = root->V;
      return root;
    }
  }
}

int main() {
  char Entrada[4];
  int Valor, D, Enable, New_V, Pai_V;
  ST *root = NULL;
  while (scanf(" %3[^ ]", Entrada), strcmp(Entrada, "END") != 0) {
    D = 0;
    Enable = 1;
    scanf("%d", &Valor);
    if (strcmp(Entrada, "FND") == 0) {
      root = search_st(root, Valor, &D, &Enable);
    } else if (strcmp(Entrada, "INS") == 0) {
      root = insert_st(root, Valor, &D);
    } else if (strcmp(Entrada, "DEL") == 0) {
      root = delete_st(root, Valor, &D, &Enable, &New_V, &Pai_V);
    }
  }
  return 0;
}
