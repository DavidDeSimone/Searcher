#include <stdio.h>
#include <string.h>
#include "Index/index.h"

struct str_link_t {
  char *str;
  str_link next;
};

typedef str_link_t* str_link;

struct str_arr_t {
  str_link front;
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
str_arr sa(LinkedIndexObjListPtr list, str_arr to_find);

/* Searches for files containing the given term. Similar to sa
 * but looks for any documents that contain any subset of terms in the
 * query
 */
str_arr so(LinkedIndexObjListPtr list, str_arr to_find);

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

/* Adds a passed string to the linked list string
 * structure
 */
void add_str(str_arr list, str_link link);

/* Creator for String Linked List
 */
str_arr create_str_arr();

/* Creates a string link for the 
 * String Linked List object
 */
str_link create_str_link(char *str);
