#define _GNU_SOURCE

#include "parser.h"

LinkedIndexObjListPtr readld(char *file_name) {
  FILE *to_open;
  char *line;
  size_t len = 0;
  int read;

  LinkedIndexObjListPtr list = create();

  to_open = fopen(file_name, "r");

  if(!to_open) {
    printf("File not found!\n");
    return NULL;
  }
  
  /* Read in the file line by line */
  while((read = getline(&line, &len, to_open)) != -1) {
    #ifdef DEBUG
    printf("Read in line %s\n", line);
    #endif

    char *token = strtok(line, " \n");

    while(token != NULL) {
      if(strcmp("<list>", token) != 0 && strcmp("</list>", token) != 0 && strlen(token) > 0) {

	/* Allocate memory on heap for token */
	char tmp[strlen(token) + 1];
	strcpy(tmp, token);

	char *tok_a = malloc((strlen(tmp) + 1) * sizeof(char));
	strcpy(tok_a, tmp);

	IndexObjPtr to_add = create_index(tok_a, NO_FILE);
	to_add->file_list = create_file_index_list();

	char *second_line = NULL;

	/*After we see a <list> tag, we read in each line until we see a </list> tag */
	while((read = getline(&second_line, &len, to_open)) != -1 && strcmp("</list>\n", second_line) != 0) {

		#ifdef DEBUG
		printf("Reading Sub-line: %s\n", second_line);
		#endif

		/* If we are not seeing an empty line 
		 or single newline */
		if(strcmp("\n", second_line) != 0) {

		  char *s_token = strtok(second_line, " \n");

		  while(s_token != NULL) {
		    #ifdef DEBUG
		    printf("Token: %s\n", s_token);
		    #endif

		    if(strlen(s_token) > 0) {
		      char tmp2[strlen(s_token) + 1];
		      strcpy(tmp2, s_token);

		      char *tok_a2 = malloc((strlen(tmp2) + 1) * sizeof(char));
		      strcpy(tok_a2, tmp2);

		      addFileIndex(to_add->file_list, tok_a2);
		    }

		    s_token = strtok(NULL, " \n");
		    s_token = strtok(NULL, " \n");
		  }
		}
	}
		      
	insert_index(list, to_add);

      }

      token = strtok(NULL, " \n");
    }
  }	      	      

  fclose(to_open);
  return list;
}
