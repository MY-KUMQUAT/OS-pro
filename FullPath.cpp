#include "FullPath.h"
#include "OS_pro.h"
#include "login.h"
#include <stdio.h>
#include <malloc.h>

struct PathNode* InitPathNode()
{
	struct PathNode* p1;
	p1 = (struct PathNode*)malloc(sizeof(struct PathNode));
	p1->next = NULL;
	return p1;
}
void InsertNode(struct PathNode* head, struct PathNode* New)
{
	struct PathNode* p1 = head;
	while (head->next != NULL)
	{
		head = head->next;
	}
	head->next = New;
	New->next = NULL;

}
void DisplayFullPath(struct PathNode* head)
{
	struct PathNode* p1 = head;
	printf("Path is :%s", p1->NodeName);
	p1 = p1->next;
	while (p1 != NULL)
	{
		printf("\\%s", p1->NodeName);
		p1 = p1->next;
	}
	printf("\n");
}
int Locate(struct PathNode* head)
{

	struct dir_list dir_list[32];
	struct PathNode* p1 = head;
	DisplayFullPath(head);
	while (p1->next != NULL)
	{
		int flag = 0;
		for (int i = 0; i < 32; i++) {
			dir_list[i] = d_or_f[p1->Node_Inode].dir_list[i];
		}
		for (int i = 0; i < 32; i++)
		{

			if (strcmp(p1->next->NodeName, dir_list[i].filename) == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1) {
			printf("fail\n");
			return -1;
		}
		p1 = p1->next;
	}
	return p1->Node_Inode;
}
void Enter(struct PathNode* head, char* FILENAME)
{
	int a = Locate(head);
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(FILENAME, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_userID == userID)
		{
			struct PathNode* p1 = InitPathNode();
			p1->NodeName = FILENAME;
			p1->Node_Inode = d_or_f[a].dir_list[i].inode;
			InsertNode(head, p1);
			return;
		}
	}
	printf("error\n");
}
void ReturnLastLevel(struct PathNode* head)
{
	struct PathNode* p1 = head;
	if (p1->next == NULL)
	{
		printf("now is root\n");
		return;
	}
	while (p1->next->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = NULL;
	printf("\nreturn finished!\n");
	return;

}

void dir(struct PathNode* head)
{
	int a = Locate(head);
	struct dir_list dirlist[32];
	for (int m = 0; m < 32; m++)
	{
		dirlist[m] = d_or_f[a].dir_list[m];
	}
	cout << endl << "Directory:" << endl;
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (inodes[dirlist[i].inode].inode_filetype == 0 && inodes[dirlist[i].inode].inode_userID == userID)
		{
			cout << dirlist[i].filename << " ";
		}
	}
	cout << endl << "File:" << endl;
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (inodes[dirlist[i].inode].inode_filetype == 1 && inodes[dirlist[i].inode].inode_userID == userID)
		{
			cout << dirlist[i].filename << " ";
		}
	}
}
struct PathNode* Copy_LinkedLisk(struct PathNode* COPY)
{
	//cout<<"COPY is";
	//DisplayFullPath(COPY);
	struct PathNode* p1 = COPY, * p2, * p3 = paste_head; //= paste_head;
	//p2 = InitPathNode();
	p1 = p1->next;//p2 = p2->next;
	while (p1 != NULL)
	{
		p2 = InitPathNode();
		p2->NodeName = p1->NodeName;
		p2->Node_Inode = p1->Node_Inode;
		p1 = p1->next;
		p3->next = p2;
		p3 = p3->next;
	}
	//cout<<"in copy";
	//DisplayFullPath(paste_head);
	return 0;
}
