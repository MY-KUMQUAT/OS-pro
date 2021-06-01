#include "OS_pro.h"
#include "login.h"

void openfile(char* filename, struct PathNode* head)
{
	int a = Locate(head);
	int i;
	for (i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1 && checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))
		{
			if (openfile_array_head < maxnum_OF_openfile)
			{
				openfile_array[openfile_array_head] = d_or_f[a].dir_list[i].inode;
				openfile_array_head++;
			}
			else
			{
				cout << "系统打开文件过多！无法继续打开" << endl;
			}
			break;
		}
	}
	if (i == d_or_f[a].countcount)
	{
		cout << "文件不存在或无访问权限!" << endl;
	}
}

void closefile(char filename[], struct PathNode* head)
{
	int a = Locate(head);
	int i;
	for (i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1 && checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))
		{
			int flag = 0;
			for (int j = 0; j < openfile_array_head; j++)
			{
				if (d_or_f[a].dir_list[i].inode == openfile_array[j])
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
	if (i == d_or_f[a].countcount)
	{
		cout << "文件不存在或无访问权限!" << endl;
	}
	return;
}

bool file_access(char* filename, struct PathNode* head)
{
	int a = Locate(head);
	int i, m;
	for (i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1 && checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))
		{
			for (m = 0; m < openfile_array_head; m++) //是否在打开文件链表里
			{
				if (openfile_array[m] == d_or_f[a].dir_list[i].inode)
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
	if (i == d_or_f[a].countcount)
	{
		cout << "文件不存在或无访问权限!" << endl;
		return false;
	}
	else return true;
}