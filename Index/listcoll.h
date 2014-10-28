#ifndef LISTCOLL_H
#define LISTCOLL_H
#endif

/*
 * Object used for counting frequency for a word in a document
 * file_name: the name of the file the word is contained in
 * freq: the frequnecy of the word
 * next: the next file in the linked list
 */

struct FileIndex {
  char *file_name;
  int freq;
  struct FileIndex *next;
};

typedef struct FileIndex* FileIndexPtr;

struct FileIndexList {
  FileIndexPtr front;
};

typedef struct FileIndexList* FileIndexListPtr;

/* Object for an indexed word in the document.
 * word: the word itself
 * FileIndexListPtr: pointer to the FileIndexList, the list of files and the number of occurences the word has in each file
 * next: the next object in the linked list
 * curr_file: the current file being examined in context. When hashed, the index object will identify with the file referneced by this string, and increase/ create the frequency in the corresponding FileIndex
 */
struct IndexObj {
  char *word;
  FileIndexListPtr file_list;
  struct IndexObj *next;
  char *curr_file;
};

typedef struct IndexObj* IndexObjPtr;

/*
 * Data Strucuture to handle collision in a linked list enviroment
 * Structure in this case is NOT generic, and is made for the context of 
 * handling word:document frequency
 *
 * To assist in easy adding during the addCallBack function, the linked list 
 * will be supplied with a "current file" string. This string represents what file to add frequency to in the add callback. 
 */

struct LinkedIndexObjList {
  IndexObjPtr front;
  char *curr_file_name;
};

typedef struct LinkedIndexObjList* LinkedIndexObjListPtr;

/* Functions for addition to sorted list
 */
LinkedIndexObjListPtr create();
void add(LinkedIndexObjListPtr list, IndexObjPtr to_add);
void addFileIndex(FileIndexListPtr file_list, char *curr_file);
/*
 * Constructor for IndexObj
 */

IndexObjPtr create_index(char *name, char *filename);

FileIndexListPtr create_file_index_list();
FileIndexPtr create_file_index(char *file_name);
void printls(LinkedIndexObjListPtr ls);
