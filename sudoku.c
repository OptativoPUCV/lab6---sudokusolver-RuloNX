#include <string.h>
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
   
   for (int i = 0; i < 9; i++) {
      int seen[10] = {0};
        for (int j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (seen[num])
                    return 0;
                seen[num] = 1;
            }
      }
   }

    for (int j = 0; j < 9; j++) {
       int seen[10] = {0};
       for (int i = 0; i < 9; i++) {
          int num = n->sudo[i][j];
          if (num != 0) {
             if (seen[num]) return 0;
             seen[num] = 1;
         }
      }
    }

    for (int k = 0; k < 9; k += 3) {
        for (int l = 0; l < 9; l += 3) {
            int seen[10] = {0};
            for (int i = k; i < k + 3; i++) {
                for (int j = l; j < l + 3; j++) {
                    int num = n->sudo[i][j];
                    if (num != 0) {
                        if (seen[num])
                            return 0;
                        seen[num] = 1;
                    }
                }
            }
        }
    }

    return 1;
}





List* get_adj_nodes(Node* n){
    List* list = createList();
    int i, j, k;
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                for(k = 1; k < 10; k++){
                    Node *adj = copy(n);
                    adj->sudo[i][j] = k;
                    if(is_valid(adj)){
                        pushBack(list, adj);
                    }
                    else {
                        free(adj);
                    }
                }
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){
   for(int i=0;i<9;i++){
      for(int j=0;j<9;j++){
         if(n->sudo[i][j]==0)
            return 0;
      }
   }
   return 1;
}

Node* DFS(Node* initial, int* cont){
    List* stack = createList();
    pushBack(stack, initial);

    while (!isEmpty(stack)){
        Node* current = popBack(stack);
        (*cont)++;

        if(is_final(current)){
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* temp = adj_nodes->head;
        while (temp != NULL){
            pushBack(stack, temp->data);
            temp = temp->next;
        }
        destroyList(adj_nodes);
    }
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