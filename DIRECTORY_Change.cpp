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

int Locate(struct PathNode* head)//定位到路径的最后一个目录，比如/root/abc的话，就定位到abc这个目录文件的i节点。
{
	struct fcb fcb[32];//目录列表
	struct PathNode* p1 = head;
	DisplayFullPath(head);
	while (p1->next != NULL)
	{
		int flag = 0;
		for (int i = 0; i < 32; i++) {
			fcb[i] = data_block[p1->Node_Inode].fcb[i];//根目录的i节点找出根目录文件在物理记录目录的块
		}
		for (int i = 0; i < 32; i++)
		{

			if (strcmp(p1->next->NodeName, fcb[i].filename) == 0)
			{
				flag = 1;
				break;
			}
		}
		if (flag != 1) {
			printf("失败！\n");
			return -1;
		}
		p1 = p1->next;
	}
	return p1->Node_Inode;
}

int Enter(struct PathNode* head, char* filename)
{
	int a = Locate(head);
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 0 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			struct PathNode* p1 = InitPathNode();
			p1->NodeName = filename;
			p1->Node_Inode = data_block[a].fcb[i].inode;
			InsertNode(head, p1);
			return 1;
		}
	}
	printf("格式错误或文件不存在！\n");
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
	if (name == "/" || name == "./" || name == "/root")
	{
		ReturnRoot(head); return;
	}
	if (name[0] == '.' || name[0] != '/')
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
	else if (name[0] == '/')
	{
		string path = DisplayFullPath(head);
		string dir;
		name += '/';
		ReturnRoot(head);
		for (int i = 1; i < name.length(); i++)
		{
			if (name[i] != '/')
			{
				dir += name[i];
			}
			else {

				if (dir != "root" && !Enter(head, ChangeStrToChar(dir)))//进入失败
				{
					//回到源路径
					chdir(head, path);
				}
				else {
					dir = "";
				}

			}
		}
	}
}

void Dir(struct PathNode* head)//
{
	int a = Locate(head);
	struct fcb dirlist[32];
	for (int m = 0; m < 32; m++)
	{
		dirlist[m] = data_block[a].fcb[m];
	}
	cout << "  TYPE\t\tSIZE\t\tNAME\t\tOWNER" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (inodes[dirlist[i].inode].inode_filetype == 1 && checkID(inodes[dirlist[i].inode].inode_userID))
		{
			cout << "FILE" << "\t\t";
			cout << inodes[dirlist[i].inode].inode_filelength * 0.5 << "KB\t\t";
			cout << dirlist[i].filename << "\t\t";
			for (int q = 0; q < size_OF_user; q++)
			{
				if (inodes[dirlist[i].inode].inode_userID[q] == -1)
				{
					continue;
				}
				else
					cout << user[inodes[dirlist[i].inode].inode_userID[q]].username << "|";
			}
			cout << endl;
		}
		
		if (inodes[dirlist[i].inode].inode_filetype == 0 && checkID(inodes[dirlist[i].inode].inode_userID))
		{
			int count = CountSize(head, dirlist[i].filename);
			cout << "FOLDER\t\t";
			cout << count * 0.5 << "KB\t\t";
			cout << dirlist[i].filename << "\t\t";
			for (int q = 0; q < size_OF_user; q++)
			{
				if (inodes[dirlist[i].inode].inode_userID[q] == -1)
				{
					continue;
				}
				else
					cout << user[inodes[dirlist[i].inode].inode_userID[q]].username << "|";
			}
			cout << endl;
		}
		
	}

}

int CountSize(struct PathNode* head, char* dir)
{
	int n = 0;
	Enter(head, dir);
	int a = Locate(head);
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (inodes[data_block[a].fcb[i].inode].inode_filetype == 1)//文件
		{
			n += inodes[data_block[a].fcb[i].inode].inode_filelength;
		}
		else if (inodes[data_block[a].fcb[i].inode].inode_filetype == 0)//目录
		{
			n += CountSize(head, data_block[a].fcb[i].filename);
		}
	}
	ReturnLastLevel(head);
	return n;
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

