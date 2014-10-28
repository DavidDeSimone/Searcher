#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listcoll.h"

LinkedIndexObjListPtr create() {
  LinkedIndexObjListPtr list = malloc(sizeof(struct LinkedIndexObjList));

  list->front = NULL;
  list->curr_file_name = NULL;

  return list;
}

void add(LinkedIndexObjListPtr list_ptr, IndexObjPtr obj_toadd) {
  

  if(obj_toadd->file_list == NULL) {
    /*As this is a new entry, create the file list object */
      FileIndexListPtr file_list = create_file_index_list();
      obj_toadd->file_list = file_list;
  }

  //If the list is empty
  if(list_ptr->front == NULL) {
    list_ptr->front = obj_toadd;

    addFileIndex(obj_toadd->file_list, obj_toadd->curr_file);
    return;
  } 

  //Iterate over the linked list
  IndexObjPtr curr = list_ptr->front;
  IndexObjPtr prev = NULL;

  do {
    /*if our key equals the current items key
      update the file-index sub-structure and return*/
    if(strcmp(curr->word,obj_toadd->word) == 0) {
      addFileIndex(curr->file_list, obj_toadd->curr_file);
      
      free(obj_toadd);
      return;
    } 
    
    /*if we our key is less then the current items key
      insert out item in the list*/
    if(strcmp(obj_toadd->word,curr->word) < 0) {
      
      /* If previous is null, we are inserting to the front of the 
       list */
      if(prev == NULL) {
	obj_toadd->next = list_ptr->front;
	list_ptr->front = obj_toadd;
      } else {
	prev->next = obj_toadd;
	obj_toadd->next = curr;
      }

     

      /* Update the file index substructure */
      addFileIndex(obj_toadd->file_list, obj_toadd->curr_file);
      return;
    }
    
    prev = curr;
  } while((curr = curr->next) != NULL);

  //if we reach the end of the list
  //insert at the end
  prev->next = obj_toadd;
  obj_toadd->next = NULL;
  
  addFileIndex(obj_toadd->file_list, obj_toadd->curr_file);
}

void insertFileIndex(FileIndexListPtr file_list, FileIndexPtr file_index) {

  if(file_index == NULL) {
    printf("Improper file index\n");
    return;
  }


  if(file_list == NULL) {
    printf("Null List");
    return;
  }

  if(file_list->front == NULL) {
    file_list->front = file_index;
    return;
  }

  //Iterate over linked list
  //If we see an entry less then our item
  //insert at that point

  FileIndexPtr curr = file_list->front;
  FileIndexPtr prev = NULL;

  do {
    if(curr->freq < file_index->freq) {
      if(prev == NULL) {
	file_index->next = file_list->front;
	file_list->front = file_index;
	return;
      }

      prev->next = file_index;
      file_index->next = curr;
      return;
    }

    prev = curr;
  } while((curr = curr->next) != NULL);

  prev->next = file_index;
  file_index->next = NULL;


}

/*
 *
 */
void addFileIndex(FileIndexListPtr file_list, char *curr_file) {

  if(file_list == NULL) {
    printf("Error, null list found");
    return;
  }
  

  /* If the list is empty */
  if(file_list->front == NULL) {

  /* Create the FileIndex Object
     Add it to the front of the list*/
    FileIndexPtr file_index = create_file_index(curr_file);
    insertFileIndex(file_list, file_index); 
    
    return;
  }

  FileIndexPtr curr = file_list->front;
  FileIndexPtr prev = NULL;


  /* Iterate over linked list */

  do {

  /* If we see the file object in our list
     remove it, increase its freq, add it back to list */
    if(strcmp(curr->file_name, curr_file) == 0) {
      /* If we are inserting into the front of the list*/
      if(prev == NULL) {
	FileIndexPtr tmp = curr;
	tmp->freq += 1;

	insertFileIndex(file_list, tmp);
	return;
      }

      FileIndexPtr tmp = curr;
      prev->next = curr->next;

      tmp->freq += 1;
      
      insertFileIndex(file_list, tmp);

      return;
    }



  /* If we do not see the file object
     Create the file object, and add it to list*/
    prev = curr;
  } while((curr = curr->next) != NULL);

  FileIndexPtr file_index = create_file_index(curr_file);
  insertFileIndex(file_list, file_index); 

}


//TODO: Check is this function is responsible for creating
// inital node for file index list
IndexObjPtr create_index(char *name, char *file_name) {
  IndexObjPtr obj = malloc(sizeof(struct IndexObj));

  obj->word = malloc(sizeof(char) * strlen(name) + 1);

  //Assign name
  strcpy(obj->word, name);
  
  obj->file_list = malloc(sizeof(struct FileIndexList));
  obj->file_list->front = NULL;

  obj->next = NULL;

  obj->curr_file = file_name;

  return obj;
}

FileIndexListPtr create_file_index_list() {
  FileIndexListPtr ret = malloc(sizeof(struct FileIndex));
  ret->front = NULL;

  return ret;
}

FileIndexPtr create_file_index(char *file_name) {
  FileIndexPtr ret = (FileIndexPtr)malloc(sizeof(struct FileIndex));

  ret->file_name = malloc(sizeof(char) * strlen(file_name));
  strcpy(ret->file_name, file_name);

  ret->freq = 1;

  ret->next = NULL;

  return ret;
}

void printls(LinkedIndexObjListPtr ls) {
  IndexObjPtr curr = ls->front;

  do {
    printf("%s\n", curr->word);

    FileIndexPtr f_curr = curr->file_list->front;

    while(f_curr != NULL) {
      printf("\t Filename: %s, Freq: %d\n", f_curr->file_name, f_curr->freq);
      f_curr = f_curr->next;
    }


  } while((curr = curr->next) != NULL);


}
