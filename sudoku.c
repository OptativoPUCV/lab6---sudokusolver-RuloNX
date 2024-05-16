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

int is_valid(Node* n){
    // Check rows and columns
    int i, j, k;
    int row[9] = {0};
    int col[9] = {0};
    
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            k = n->sudo[i][j];
            if (k < 1 || k > 9 || row[k - 1] || col[k - 1]) {
                return 0;
            }
            row[k - 1] = 1;
            col[k - 1] = 1;
        }
        for (k = 0; k < 9; k++) {
            row[k] = 0;
            col[k] = 0;
        }
    }

    // Check 3x3 subgrids
    int row_start, col_start;
    
    for (row_start = 0; row_start < 9; row_start += 3) {
        for (col_start = 0; col_start < 9; col_start += 3) {
            for (i = row_start; i < row_start + 3; i++) {
                for (j = col_start; j < col_start + 3; j++) {
                    k = n->sudo[i][j];
                    if (k < 1 || k > 9 || row[k - 1] || col[k - 1]) {
                        return 0;
                    }
                    row[k - 1] = 1;
                    col[k - 1] = 1;
                }
            }
            for (k = 0; k < 9; k++) {
                row[k] = 0;
                col[k] = 0;
            }
        }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
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