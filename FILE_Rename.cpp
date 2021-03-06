#include "OS_pro.h"
#include "LOGIN.h"
#include "OTHER.h"

void FileRename(struct PathNode* head, string file1, string file2)
{
	int a = Locate(head);
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (data_block[a].fcb[i].filename == file1 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1)//找到目录文件
		{
			if (checkID(inodes[data_block[a].fcb[i].inode].inode_userID))//用户是否有权限此操作
			{
				char* temp = new char;
				temp = ChangeStrToChar(file2);
				strcpy(data_block[a].fcb[i].filename, temp);
				cout << "文件已经改名:" << data_block[a].fcb[i].filename;
				return;
			}
			else
			{
				cout << "您无更名权限" << endl;
				return;
			}
		}
	}
	cout << "未找到相应目录" << endl;
	return;
}