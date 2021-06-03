#include "OS_pro.h"
#include "login.h"

void openfile(char* filename, struct PathNode* head)
{
	int a = Locate(head);
	int i;
	for (i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			if (openfile_array_head < maxnum_OF_openfile)
			{
				openfile_array[openfile_array_head] = data_block[a].fcb[i].inode;
				openfile_array_head++;
			}
			else
			{
				cout << "系统打开文件过多！无法继续打开" << endl;
			}
			break;
		}
	}
	if (i == data_block[a].countcount)
	{
		cout << "文件不存在或无访问权限!" << endl;
	}
}

void closefile(char filename[], struct PathNode* head)
{
	int a = Locate(head);
	int i;
	for (i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			int flag = 0;
			for (int j = 0; j < openfile_array_head; j++)
			{
				if (data_block[a].fcb[i].inode == openfile_array[j])
				{
					for (int k = j; k < openfile_array_head; k++)
					{
						openfile_array[k] = openfile_array[k + 1];
					}
					openfile_array_head--;
					flag = 1;
					return;
				}
			}
			if (flag == 0)
			{
				cout << "文件未打开！" << endl;
			}
			return;
		}
	}
	if (i == data_block[a].countcount)
	{
		cout << "文件不存在或无访问权限!" << endl;
	}
	return;
}

bool file_access(char* filename, struct PathNode* head)
{
	int a = Locate(head);
	int i, m;
	for (i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			for (m = 0; m < openfile_array_head; m++) //是否在打开文件链表里
			{
				if (openfile_array[m] == data_block[a].fcb[i].inode)
				{
					return true;
				}
			}
			if (m == openfile_array_head)
			{
				cout << "该文件未打开，无法读取" << endl;
				return false;
			}
			break;
		}
	}
	if (i == data_block[a].countcount)
	{
		cout << "文件不存在或无访问权限!" << endl;
		return false;
	}
	else return true;
}