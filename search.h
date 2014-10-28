#include <stdio.h>
#include "Index/index.h"

/* Constructor for Object that maintains word frequencies indexed by document
 * See Index/index.h for more details
 */
void list_init(char *file_name);

/* Destructor for LinkedIndexObjList
 * Call when list should be freed
 */
void list_dec(LinkedIndexObjList *list);


/* Search for files containing the given term. A query may contain
 * one or more terms. The search term will output the names of the files 
 * that contain ALL of the terms in the query
 */
char** sa(char **to_find);

/* Searches for files containing the given term. Similar to sa
 * but looks for any documents that contain any subset of terms in the
 * query
 */
char** so(char **to_find);
