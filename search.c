#include "search.h"

LinkedIndexObjListPtr list_init(char *file_name) {
  LinkedIndexObjListPtr list = create();
  checkContents(list, file_name, NO_WRITE);

  return list;
}

void list_dec(LinkedIndexObjListPtr list) {
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

str_arr sa(LinkedIndexObjListPtr list, str_arr to_find) {
  //TODO
  return NULL;
}

str_arr so(LinkedIndexObjListPtr list, str_arr to_find) {
  str_arr return_list = create_str_arr();

  //Iterate over the words in the list
  IndexObjPtr front = list->front;

  while(front != NULL) {
  //If word is in list
    if(contains_str(to_find, front->word)) {
	//iterate over file links, add each to the return list
	FileIndexPtr file = front->file_list->front;
	while(file != NULL) {
	  str_link link = create_str_link(file->file_name);
	  add_str(return_list, link);

	  file = file->next;
	}
      }

      front = front->next;
  }  
  


  return return_list;
}

void printr(str_arr to_print) {
  str_link link = to_print->front;

  while(link != NULL) {
    printf("%s\n", link->str);
    link = link->next;
  }

}

void decr(str_arr to_free) {
  str_link free_link = to_free->front;

  while(free_link != NULL) {
    free(free_link->str);

    free_link = free_link->next;
    free(free_link);
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
    char *tk = malloc(strlen(token) * sizeof(char) + 1);
    strncpy(tk, token, strlen(token));

    str_link link = create_str_link(tk);

    /*Add it to the linked list*/
    add_str(list, link);
    token = strtok(NULL, splits);
  }


  return list;
}

void add_str(str_arr list, str_link link) {
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
  str_arr ret = malloc(sizeof(struct str_arr_s));
  ret->front = NULL;
  ret->size = 0;

  return ret;
}

str_link create_str_link(char *str) {
  /* String must be allocated before call */
  str_link link = malloc(sizeof(struct str_link_s));
  link->str = str;
  link->next = NULL;

  return link;
}

int contains_str(str_arr to_find, char *str) {
  str_link link = to_find->front;

  while(link != NULL) {
    if(strcmp(str, link->str) == 0) {
      return 1;
    }
    link = link->next;
  }


  return 0;
}


int main(int argc, char **args) {
  LinkedIndexObjListPtr list;  
  str_arr to_find;
  str_arr results;
  char *input = malloc(sizeof(char) * MAX_INPUT_S);

  if(argc != 2) {
    printf("Invalid number of command line arguments!\n");
    return -1;
  }

  list = list_init(args[1]);

  while(TRUE) {
    scanf("%s", input);

    /* Tokenize input based on space seperator
     * First token should be the command so or sa
     */
    to_find = peel(input);
    
    char *comm = to_find->front->str;

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
