#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define FILENAME_LEN 256

typedef struct File {
  char* filename;
  struct File* next;
} File;

typedef File* FileList;

typedef struct Cell {
  ino_t inode;
  FileList files;
  int nbr;
  struct Cell* next;
} Cell;

typedef Cell* List;

typedef struct HashTable {
  int size;
  List* buckets;
} HashTable;


Cell* createCell(ino_t inode) {
  Cell* newCell = (Cell*)calloc(1, sizeof(Cell));
  if (newCell == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    exit(1);
  }

  newCell->inode = inode;
  newCell->nbr = 1;
  newCell->files = NULL;
  newCell->next = NULL;
  return newCell;
}


List addFirst(Cell* cell, List list) {
  cell->next = list;
  return cell;
}


FileList addFile(char* filename, FileList list) {
  File* cell = malloc(sizeof(File));
  cell->filename = filename;
  cell->next = list;
  return cell;
}


Cell* find(ino_t inode, List list) {
  Cell* curr = list;
  while (curr != NULL) {
    if (curr->inode == inode) {
      return curr;
    }
    curr = curr->next;
  }
  return NULL;
}


void deleteFileList(FileList list) {
  File* curr = list;
  File* next;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}


void deleteList(List list) {
  Cell* curr = list;
  Cell* next;
  while (curr != NULL) {
    next = curr->next;
    deleteFileList(curr->files);
    free(curr);
    curr = next;
  }
}


void deleteTable(HashTable* table) {
  for (int i = 0; i < table->size; ++i) {
    deleteList(table->buckets[i]);
  }
  free(table);
}


void printFileList(FileList list) {
  File* curr = list;
  while (curr != NULL) {
    printf("%s ", curr->filename);
    curr = curr->next;
  }
  printf("\n");
}


int normalize(ino_t hash, int tableSize) {
  return (int)hash % tableSize;
}


int main() {
  HashTable* table = (HashTable*)malloc(sizeof(HashTable));
  if (table == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return 1;
  }
  table->size = 16;
  table->buckets = (List*)calloc(table->size, sizeof(List));
  Cell* anchor;

  DIR *dirp = opendir("tmp");
  if (dirp == NULL) {
    fprintf(stderr, "Directory `tmp` not found\n");
    return 1;
  }

  struct dirent *dp;
  struct stat *st;
  char *newFilename, *fullPath;
  while ((dp = readdir(dirp)) != NULL) {
    st = malloc(sizeof(struct stat));
    fullPath = calloc(FILENAME_LEN + 4, sizeof(char));
    strcpy(fullPath, "tmp/");
    strcpy(fullPath + 4, dp->d_name);
    if (stat(fullPath, st) == -1) {
      fprintf(stderr, "Failed to stat the file %s\n", fullPath);
      return 1;
    }
    free(fullPath);
    int tableIndex = normalize(st->st_ino, table->size);
    anchor = find(st->st_ino, table->buckets[tableIndex]);
    if (anchor == NULL) {
      if (table->buckets[tableIndex] == NULL) {
        table->buckets[tableIndex] = createCell(st->st_ino);
      } else {
        table->buckets[tableIndex] = addFirst(createCell(st->st_ino),
                                              table->buckets[tableIndex]);
      }
      anchor = table->buckets[tableIndex];
    } else {
      anchor->nbr++;
    }
    newFilename = calloc(FILENAME_LEN, sizeof(char));

    strcpy(newFilename, dp->d_name);
    anchor->files = addFile(newFilename, anchor->files);
    free(st);
  }

  closedir(dirp);

  for (int i = 0; i < table->size; ++i) {
    Cell* curr = table->buckets[i];
    while (curr != NULL) {
      if (curr->nbr >= 2) {
        printf("%d: ", (int)curr->inode);
        printFileList(curr->files);
      }
      curr = curr->next;
    }
  }

  deleteTable(table);
  return 0;
}
