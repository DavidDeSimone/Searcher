//TODO Make index.c function calls take list parameter, so list isnt a global
//in index.c

#include "search.h"

#define NO_WRITE "no_file_write_XCAD"
#define MAX_INPUT 250

#ifndef TRUE
#define TRUE 1
#endif

LinkedIndexObjListPtr list_init(char *file_name) {
  LinkedIndexObjListPtr list = create();
  checkContents(file_name, NO_WRITE);

  return list;
}

void list_dec(LinkedIndexObjList *list) {
  FileIndexPtr f_front;
  IndexObjPtr i_front;

  i_front = list->front;

  while(i_front != NULL) {
    f_front = i_front->file_list->front;

    while(f_front != NULL) {
      f_front = f_front->next;
      free(f_front);
    }

    i_front = i_front->next;
    free(i_front);
  }

  free(list);
}

char** sa(str_arr to_find) {
  //TODO
  return NULL;
}

char** so(str_arr to_find) {
  //TODO
  return NULL;
}

void printr(str_arr to_print) {
  int i;
  
  for(i = 0; i < to_print->size; i++) {
    printf("Result: %s\n", to_print->strs[i]);
  }

}

void decr(str_arr to_free) {
  int i;

  for(i = 0; i < to_free->size; i++) {
    free(to_free->strs[i]);
  }

  free(to_free);
}

str_arr peel(char *input) {
  //TODO
  return NULL;
}

int main(int argc. char **args) {
  ListIndexObjListPtr list;  
  str_arr to_find;
  str_arr results;
  char *input = malloc(sizeof(char) * MAX_INPUT);

  if(argc != 2) {
    printf("Invalid number of command line arguments!\n");
    return -1;
  }

  list = list_init(args[1]);

  while(TRUE) {
    scanf("%s", &input);

    /* Tokenize input based on space seperator
     * First token should be the command so or sa
     */
    to_find = peel(input);
    
    char *comm = to_find->strs[0];

    if(strcmp(comm, "sa") == 0) {
      results = sa(to_find);
      printr(results);
      decr(results);
    } else
      if(strcmp(comm, "so") == 0) {
	results = so(to_find);
	printr(results);
	decr(results);
      } else {
	printf("Error, invalid command!\n");
      }



  }

  
  list_dec(list);
  return 0;
}
