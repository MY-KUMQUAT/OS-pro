#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>

struct PathNode
{
	char* NodeName;
	int Node_Inode;
	struct PathNode* next;
};

struct PathNode* InitPathNode();
void InsertNode(struct PathNode* head, struct PathNode* New);
void DisplayFullPath(struct PathNode* head);
int Locate(struct PathNode* head);
void Enter(struct PathNode* head, char FILENAME[]);
void ReturnLastLevel(struct PathNode* head);
//FullPath part end;
void dir(struct PathNode* head);
struct PathNode* Copy_LinkedLisk(struct PathNode* COPY);
