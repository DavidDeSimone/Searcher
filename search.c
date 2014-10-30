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

char** sa(LinkedIndexObjListPtr list, str_arr to_find) {
  //TODO
  return NULL;
}

char** so(LinkedIndexObjListPtr list, str_arr to_find) {
  //TODO
  return NULL;
}

void printr(str_arr to_print) {
  str_link link = str_arr->front;

  while(link != NULL) {
    printf("%s\n", link->str);
    link = link->next;
  }

}

void decr(str_arr to_free) {
  str_link = to_free->front;

  while(str_link != NULL) {
    free(str_link->str);

    str_link = str_link->next;
    free(link);
  }

  free(to_free);
}

str_arr peel(char *input) {
  str_arr list = create_str_arr();
  const char splits[2] = " ";
  char *token;

  /*Tokenize the String*/
  token = strtok(input, splits);

  
  /*For each token*/
  while(token != NULL) {
    /*Create a String Object */
    char *tk = malloc(len(token) * sizeof(char) + 1);
    strncpy(tk, token, len(token));

    str_link link = create_str_link(tk);

    /*Add it to the linked list*/
    add_str(list, link);
    token = strtok(NULL, splits);
  }


  return list;
}

void addStr(str_arr list, str_link link) {
  if(list->front == NULL) {
    list->front = link;
    list->size = 1;
    return;
  }

  /*List is non-empty, insert to front */
  link->next = list->front;
  list->front = link;
  list->size += 1;
}

str_arr create_str_arr() {
  str_arr ret = malloc(sizeof(struct str_arr_t));
  ret->front = NULL;
  ret->size = 0;

  return ret;
}

str_link create_str_link(char *str) {
  /* String must be allocated before call */
  str_link link = malloc(sizeof(struct str_link_t));
  link->str = str;
  link->next = NULL;

  return link;
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
      results = sa(list, to_find);
      printr(results);
      decr(results);
    } else
      if(strcmp(comm, "so") == 0) {
	results = so(list, to_find);
	printr(results);
	decr(results);
      } else {
	printf("Error, invalid command!\n");
      }

  }

  
  list_dec(list);
  return 0;
}
