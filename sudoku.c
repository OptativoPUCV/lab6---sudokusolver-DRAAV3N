#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node *n) {
  int filas[9][10] = {0}; // Para verificar numeros en filas
  int cols[9][10] = {0}; // Para verificar numeros en columnas
  int subm[9][10] = {0}; // Para verificar numeros en submatrices de 3x3

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      int elem = n->sudo[i][j];
      if (n->sudo[i][j] != 0){
        //Si el numero ya existe en la fila, retorna 0.
        if (filas[i][elem]) return 0;
        filas[i][elem] = 1;
        //Si el numero ya existe en la columna, retorna 0.
        if (cols[j][elem]) return 0;
        cols[j][elem] = 1;
        // Verificar submatriz
        int subm_num = (i/3)*3 + (j/3);
        //Si el numero ya existe en la matriz, retorna 0.
        if (subm[subm_num][elem]) return 0;
        subm[subm_num][elem] = 1;
      }
    }
  }
  return 1;
}


//Funcion que genera una lista de los nodos adyacentes al nodo recibido
List* get_adj_nodes(Node* nodo){
  List* list = createList();
  //Se recorre la matriz
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      //Si el valor en 
      if(nodo->sudo[i][j] == 0){
        for(int k = 1 ; k < 10 ; k++){
          Node* adj = copy(nodo);
          adj->sudo[i][j] = k;
          if(is_valid(adj)) pushBack(list, adj);
        }
        return list;
      }
    }
  }
  return list;
}

//recorre el cada casilla del nodo, verificando si hay algun valor diferente de 0.
int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *S = createStack();
  push(S, initial);
  while(S != NULL){
    Node* n = top(S); //saco el nodo del tope de la pila
    pop(S); //luego lo elmino de la pila
    if(is_final(n)){
      return n;
    }
    else{
      List* adj = get_adj_nodes(n); //obtener todos los nodos adyacentes al nodo
      //Agregarlos al stack uno por uno.
      while(first(adj) != NULL){
        push(S, first(adj));
        popFront(adj);
      }
    }
  }
  free(S);
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/