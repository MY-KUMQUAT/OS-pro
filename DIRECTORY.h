#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>

using namespace std;

string DisplayFullPath(struct PathNode* head);
int Locate(struct PathNode* head);
int Enter(PathNode* head, char* filename);
int FromPos(PathNode* head, char c);
void chdir(struct PathNode* head, string name);
void ReturnLastLevel(struct PathNode* head);
void ReturnRoot(PathNode* head);
void Dir(struct PathNode* head);

struct PathNode* InitPathNode();
void create_directory(char directoryname[], int length, int userID, int limit, struct PathNode* head);
void InsertNode(struct PathNode* head, struct PathNode* New);

void delete_dirctory(char directory[], struct PathNode* head);
void recycledelete(struct PathNode* head, char directory[]);
void release(int iNode);
