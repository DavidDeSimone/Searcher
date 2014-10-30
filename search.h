#include <stdio.h>
#include <string.h>
#include "Index/index.h"

struct str_arr_t {
  char **strs;
  size_t size;
};

typedef struct str_arr_t* str_arr;

/* Constructor for Object that maintains word frequencies indexed by document
 * See Index/index.h for more details
 */
LinkedIndexObjListPtr list_init(char *file_name);

/* Destructor for LinkedIndexObjList
 * Call when list should be freed
 */
void list_dec(LinkedIndexObjList *list);

/* Search for files containing the given term. A query may contain
 * one or more terms. The search term will output the names of the files 
 * that contain ALL of the terms in the query
 */
char** sa(str_arr to_find);

/* Searches for files containing the given term. Similar to sa
 * but looks for any documents that contain any subset of terms in the
 * query
 */
char** so(str_arr to_find);

/* Prints the given 2D array of strings
 */
void printr(str_arr to_print);

/* Deallocates the given 2D array of strings
 */
void decr(str_arr to_free);

/* Tokenizes the input based on space
 * Wrapper for strtok
 */
str_arr peel(char *input);
