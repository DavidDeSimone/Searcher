#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <ftw.h>
#include <unistd.h>
#include "listcoll.h"
#include "index.h"
#define FILE_NOT_FOUND -2


LinkedIndexObjListPtr list;

int main(int argc, char **args) {
  int err = 0;
  char *to_write;
  char *to_read;

  if(argc != 3) {
    printf("Error, incorrect number of command line arguments!\n");
    return -1;
  }

  to_read = malloc(sizeof(char) * strlen(args[2]) + 1);
  to_write = malloc(sizeof(char) * strlen(args[1]) + 1);

  strcpy(to_write, args[1]);
  strcpy(to_read, args[2]);

  //Initalize LinkedObjList structure
  list = create();

  checkContents(to_read, to_write);

  free(to_write);
  free(to_read);
  return 0;
}

/* Checks the file to read. Calls appropriate function  
 * based on function content
 */
void checkContents(char *to_read, char *to_write) {
 
  if(isDir(to_read) == 1) {
    printf("Reading Dir %s\n", to_read);
    readDir(to_read);
  } else 
    if(isDir(to_read) == FILE_NOT_FOUND) {

      printf("File Not Found");
      return;

    } else {
      readFile(to_read, to_read);
  }

  writeFile(to_write);
}

/* Function used to determine if a pathname is a directory
 * Returns 0 if false, 1 if true
 */
int isDir(char *to_read) {

  struct stat s;
  if(stat(to_read, &s) == 0) {

    if(s.st_mode & S_IFDIR) {
      return 1;
    } else if(s.st_mode & S_IFREG) {
      return 0;
    } else {
      printf("Error, not found\n");
      return -1;
    }

  } else {
    return FILE_NOT_FOUND;
  }
}


/*
 *
 */
char* apdir(char *base, char *to_append) {
  char *ret = malloc(sizeof(char) * (strlen(base) + strlen(to_append)) + 2);

  strcpy(ret, base);
  if(base[strlen(base) - 1] != '/') {
    strcat(ret, "/");
  }
  strcat(ret, to_append);

  return ret;
}


/* Read directory, and for each file in the directory, calls 
 * readFile(). If another directory is found, recursivly calls
 * readDir(). 
 */
void readDir(char *to_read) {

  //Read directory
  DIR *dir;
  struct dirent *dent;
  char buff[200];
  char *path;

  strcpy(buff, to_read);
  
  dir = opendir(buff);
  
  if(dir != NULL) {

    //Look over Dir contents
    while((dent = readdir(dir)) != NULL) {

      /* We don't want to read the current or previous dirs */
      if(strcmp(dent->d_name, ".") != 0 && 
	 strcmp(dent->d_name, "..") != 0) {
	
	path = apdir(to_read, dent->d_name);
      if(isDir(path)) {
	printf("Reading directory %s\n", path);
	readDir(path);
      } else {
	printf("Reading file %s\n", path);
	readFile(path, dent->d_name);
      }


      }
    }

  }


  closedir(dir);
}


/*
 * Changes all characters in the given string to their lower case versions
 */
char* toLower(char *str) {
  int i;

  for(i = 0; i < strlen(str); i++) {
    str[i] = tolower(str[i]);
  }

  return str;
}

/* Reads a file given by to_read. Creates a hashmap for given file.
 * Tokenizes each word of the file. Constructs an wrapper object for the word
 * and hashes it. If a collision occures, occurrence will be raised by collision
 * object. Adds hashmap into hashmap array upon complition. 
 */
void readFile(char *to_read, char *d_name) {
  FILE *fp;

  //Read in the file
  fp = fopen(to_read, "r");

  //Get file size
  fseek(fp, 0L, SEEK_END);
  int size = ftell(fp);
  //Seek back to start
  fseek(fp, 0L, SEEK_SET); 

  char line[size];

  


  while(fgets(line, size, fp) != NULL) {
    //Tokenize String
    char *token;

    token = strtok(line, " !@#$%^&*()_+=-\\\";\n\t\v\b\r\a,./'[]{}<>?:\"{}|~`");

    while(token != NULL) {

      char *toMake = malloc(sizeof(strlen(token)));
      strcpy(toMake, token);

      //Lower the case of the string
      toMake = toLower(toMake);

      //Create Index Obj
      IndexObjPtr obj = create_index(toMake, to_read); 

      //Add Index Obj
      add(list, obj);	


      //Move to next token
      token = strtok(NULL, " !@#$%^&*()_+=-\\\";\n\t\v\b\r\a,./'[]{}<>?:\"{}|~`");
    }

  }

  fclose(fp);
}



void writeFile(char *to_write) {
  // printls(list);
  
  //If the file is not found already on disk
  if(isDir(to_write) == FILE_NOT_FOUND) {
    //open the file
    writeList(list, to_write);
    //write the contents of the file from the data strucutre
  } else {
    //the file exists on disk

    char buff;
    //Prompt confirmation of deletion
    printf("File/Dir already exists, delete? [y/n]\n");

    scanf("%c", &buff);

    if(buff == 'y') {
      if(isDir(to_write)) {
	int status = remove(to_write);

	//If the dir is non empty
	if(status == 0) {
	  writeList(list, to_write);
	} else {
	  rmrf(to_write);
	  writeList(list, to_write);
	}

      } else {
	int status = remove(to_write);
	writeList(list, to_write);
      }

    } else {
      printf("Confirm non-delete\n");
    }
    //if the file is a directory
    //delete with recursive system call


    //else just delete file and overwrite

  }


}

void writeList(LinkedIndexObjListPtr list, char *to_write) {
  FILE *fp;

  fp = fopen(to_write, "w");

  IndexObjPtr curr = list->front;

  if(curr == NULL) {
    return;
  }




  do {

    fprintf(fp, "<list> ");
    fprintf(fp, "%s", curr->word);
    fprintf(fp, "\n\n");
    

    FileIndexPtr f_curr = curr->file_list->front;

    int i = 0;
    while(f_curr != NULL) {
      fprintf(fp, "%s", f_curr->file_name);
      fprintf(fp, " ");
      fprintf(fp, "%d", f_curr->freq);
      fprintf(fp, " ");

      if((i % 5) == 4) {
	fprintf(fp, "\n");
      }

      i++;
      f_curr = f_curr->next;
    }
    fprintf(fp, "\n\n</list>\n\n");


  } while((curr = curr->next) != NULL);


  fclose(fp);
}

int unc(const char *fpath, const struct stat *sb, int typeflag, struct FTW *ftwbuf) {
  int st = remove(fpath);
  
  return st;
}

int rmrf(char *path) {
  return nftw(path, unc, 64, FTW_DEPTH | FTW_PHYS);
}
