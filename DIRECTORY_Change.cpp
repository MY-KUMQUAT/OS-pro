#include "OS_pro.h"
#include "login.h"
#include <stdio.h>
#include <malloc.h>

string DisplayFullPath(struct PathNode* head)
{
	struct PathNode* p1 = head;
	string path = "";
	while (p1 != NULL)
	{
		path = path + "/" + p1->NodeName;
		p1 = p1->next;
	}
	return path;
}

int Locate(struct PathNode* head)//��λ��·�������һ��Ŀ¼������/root/abc�Ļ����Ͷ�λ��abc���Ŀ¼�ļ���i�ڵ㡣
{
	struct dir_list dir_list[32];//Ŀ¼�б�
	struct PathNode* p1 = head;
	DisplayFullPath(head);
	while (p1->next != NULL)
	{
		int flag = 0;
		for (int i = 0; i < 32; i++) {
			dir_list[i] = d_or_f[p1->Node_Inode].dir_list[i];//��Ŀ¼��i�ڵ��ҳ���Ŀ¼�ļ��������¼Ŀ¼�Ŀ�
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
			printf("ʧ�ܣ�\n");
			return -1;
		}
		p1 = p1->next;
	}
	return p1->Node_Inode;
}

int Enter(struct PathNode* head, char* filename)
{
	int a = Locate(head);
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))
		{
			struct PathNode* p1 = InitPathNode();
			p1->NodeName = filename;
			p1->Node_Inode = d_or_f[a].dir_list[i].inode;
			InsertNode(head, p1);
			return 1;
		}
	}
	printf("��ʽ������ļ������ڣ�\n");
	return 0;
}

int FromPos(struct PathNode* head, char c)
{
	int from_pos = 0;
	if (c == '.')
	{
		from_pos = 2;
	}
	else if (c == '/')
	{
		from_pos = 1;
		ReturnRoot(head);
	}
	else
	{
		from_pos = 0;
	}
	return from_pos;
}

void chdir(struct PathNode* head, string name)
{
	int n = 0;
	int from_pos = FromPos(head, name[0]);
	name += '/';
	string dir = "";
	for (int i = from_pos; i < name.length(); i++)
	{
		if (name[i] != '/')
		{
			dir += name[i];
		}
		else
		{
			if (!Enter(head, ChangeStrToChar(dir)))
			{
				while (n)
				{
					ReturnLastLevel(head);
					n--;
				}
				break;
			}
			else
			{
				dir = "";
				n++;
			}
		}
	}

}

void ReturnLastLevel(struct PathNode* head)
{
	struct PathNode* p1 = head;
	if (p1->next == NULL)
	{
		return;
	}
	while (p1->next->next != NULL)
	{
		p1 = p1->next;
	}
	p1->next = NULL;
	return;

}

void ReturnRoot(struct PathNode* head)
{
	head->next = NULL;
	return;
}

void Dir(struct PathNode* head)
{
	int a = Locate(head);
	struct dir_list dirlist[32];
	for (int m = 0; m < 32; m++)
	{
		dirlist[m] = d_or_f[a].dir_list[m];
	}
	cout << endl << "��������Ŀ¼��������" << endl;
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (inodes[dirlist[i].inode].inode_filetype == 0 && checkID(inodes[dirlist[i].inode].inode_userID))
		{
			cout << dirlist[i].filename << " ";
		}
	}
	cout << endl << "���������ļ���������" << endl;
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (inodes[dirlist[i].inode].inode_filetype == 1 && checkID(inodes[dirlist[i].inode].inode_userID))
		{
			cout << dirlist[i].filename << " ";
		}
	}
}