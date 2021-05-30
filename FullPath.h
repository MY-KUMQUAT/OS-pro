#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>

using namespace std;

struct PathNode
{
	char* NodeName;
	int Node_Inode;
	struct PathNode* next;
};

struct PathNode* InitPathNode();
void InsertNode(struct PathNode* head, struct PathNode* New);
string DisplayFullPath(struct PathNode* head);
int Locate(struct PathNode* head);
int Enter(PathNode* head, char* filename);
int FromPos(PathNode* head, char c);
void ReturnLastLevel(struct PathNode* head);
void ReturnRoot(PathNode* head);
//FullPath part end;
void dir(struct PathNode* head);
struct PathNode* Copy_LinkedLisk(struct PathNode* COPY);
