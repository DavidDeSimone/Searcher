#include "search.h"
#ifndef TRUE
#define TRUE 1
#endif


int main(int argc. char **args) {
  ListIndexObjList list;
  char input[50];
  char **to_find;


  if(argc != 2) {
    printf("Invalid number of command line arguments!\n");
    return -1;
  }

  list = list_init(args[1]);

  while(TRUE) {
    scanf("%s", &input);
    


  }


  list_dec(list);
  return 0;
}
