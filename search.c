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
  str_arr return_list = create_str_arr();

  IndexObjPtr front = list->front;

  //Iterate over the words
  while(front != NULL) {
    
    //If the current item is a word we are looking for
    if(contains_str(to_find, front->word)) {
      //if return list is empty
      //Initalize it with every item
      //in the current files index
      if(return_list->front == NULL) {
	FileIndexPtr file = front->file_list->front;
	while(file != NULL) {
	  str_link link = create_str_link(file->file_name);
	  add_str(return_list, link);

	  file = file->next;

	}



      } else {
      //Remove items from return list
      //if they are not in the current
      //items file index
	str_arr diff_list = create_str_arr();

	FileIndexPtr file = front->file_list->front;
	while(file != NULL) {
	  str_link link = create_str_link(file->file_name);
	  add_str(diff_list, link);

	  file = file->next;
	}

	str_arr returned = get_common(diff_list, return_list);
	free(return_list);
	return_list = returned;


      }
    }


  }


  return return_list;
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

str_arr get_common(str_arr first_list, str_arr second_list) {
  //TODO
  return NULL;
}

void printr(str_arr to_print) {
  printf("Printing Output List:\n");

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
  char *token;

  /*Tokenize the String*/
  token = strtok(input, " \n");

  
  /*For each token*/
  while(token != NULL) {
    printf("Token %s, size %d\n", token, strlen(token));
    /*Create a String Object */
    char *tk = malloc((strlen(token) * sizeof(char)) + 1);
    strcpy(tk, token);

    str_link link = create_str_link(tk);

    /*Add it to the linked list*/
    add_str(list, link);
    printf("Added Token: %s\n", tk);

    token = strtok(NULL, " \n");
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


char* get_command(str_arr to_get) {

  if(to_get == NULL) {
    return NULL;
  }

  str_link front = to_get->front;

  while(front != NULL) {

    //The last item in the linked list is 
    //the command we are interested in
    if(front->next == NULL) {
      return front->str;
    }

    front = front->next;
  }

  return NULL;
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
    fgets(input, MAX_INPUT_S, stdin);

    /* Tokenize input based on space seperator
     * First token should be the command so or sa
     */
    to_find = peel(input);
    
    char *comm = get_command(to_find);

    printf("Testing Command: %s\n", comm); 
    if(strcmp(comm, "sa") == 0) {
      results = sa(list, to_find);
      printr(results);
      decr(results);
    } else
      if(strcmp(comm, "so") == 0) {
	results = so(list, to_find);
	printr(results);
	decr(results);
      }
        if(strcmp(comm "q") == 0) {
	  //End the program
	  decr(to_find);
	  break;

         } else {
	printf("Error, invalid command!\n");
      }

    decr(to_find);

  }

  free(input);
  list_dec(list);
  return 0;
}
