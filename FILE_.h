#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>
#include <regex>

void createfile(char filename[], int length, int userID, int limit, struct PathNode* head);
void deletefile(char filename[], struct PathNode* head);

void openfile(char* filename, struct PathNode* head);
void closefile(char filename[], struct PathNode* head);
bool file_access(char* filename, PathNode* head);

void writefile(char* filename, char* newcontent, struct PathNode* head);
void readfile(char* filename, struct PathNode* head);

void copyfile(struct PathNode* head, char filename[]);
void pastefile(struct PathNode* head);
void cutfile(struct PathNode* head, char filename[]);
void mv(struct PathNode* head, string name, char com);
struct PathNode* Copy_LinkedLisk(struct PathNode* COPY);

void searchfile(string filename, PathNode* head, int depth);

void ShareFile(string filename, string usr, struct PathNode* head);
void Recovery(string filename, string usr, struct PathNode* head);

void FileRename(struct PathNode* head, string file1, string file2);