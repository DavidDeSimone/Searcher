#ifndef SEARCH_H
#define SEARCH_H

#define _GNU_SOURCE
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Index/index.h"
#include "Index/listcoll.h"
#include "parser.h"

#ifndef TRUE
#define TRUE 1
#endif

#define NO_WRITE "no_file_write_XCAD"
#define MAX_INPUT_S 250

struct str_link_s {
  char *str;
  struct str_link_s *next;
};

typedef struct str_link_s* str_link;

struct str_arr_s {
  str_link front;
  size_t size;
};

typedef struct str_arr_s* str_arr;

/* Constructor for Object that maintains word frequencies indexed by document
 * See Index/index.h for more details
 */
LinkedIndexObjListPtr list_init(char *file_name);

/* Destructor for LinkedIndexObjList
 * Call when list should be freed
 */
void list_dec(LinkedIndexObjListPtr list);

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

/* Searched for the given string str in the
 * linked list to_find. Returns 1 if to_find contains
 * str, 0 otherwise
 */
int contains_str(str_arr to_find, char *str);

/* Returns a Linked List containing all the elements
 * the first and second list have in common
 * If the lists have nothing in common, returns NULL
 */
str_arr get_common(str_arr first_list, str_arr second_list);

void readListFromDisk(LinkedIndexObjListPtr list, char *file_name);

#endif
