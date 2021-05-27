#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void create_directory(char directoryname[], int length, int userID, int limit, struct PathNode* head)
{
	int a = Locate(head);
	if (d_or_f[a].countcount != 32) 
	{
		for (int i = 0; i < d_or_f[a].countcount; i++)
		{
			if (strcmp(directoryname, d_or_f[a].dir_list[i].filename) == 0)  //如果已有重名的文件
			{
				cout << "There is a directory or file with the same name.File creation failed." << endl;
				return;
			}
		}

		for (int i = 1; i < num_OF_inode; i++)
		{
			if (d_or_f[i].df_inum == -1)
			{
				d_or_f[i].df_inum = i;
				strcpy(d_or_f[i].dir_directoryname, directoryname);
				inodes[i].inode_inum = i;
				inodes[i].inode_filetype = 0;  //文件类型，0为目录文件，1为普通文件
				inodes[i].inode_filelength = length;
				inodes[i].inode_limit = limit;
				inodes[i].inode_userID = userID;
				allocation(length);
				for (int j = 0; j < length; j++)
				{
					inodes[i].inode_fileaddress[j] = ADDRbuffer[j];
				}
				for (int j = 0; j < size_OF_fileADDRbuffer; j++)
				{
					ADDRbuffer[j] = -1;
				}
				int temp = Locate(head);
				strcpy(d_or_f[temp].dir_list[d_or_f[temp].countcount].filename, directoryname);
				d_or_f[temp].dir_list[d_or_f[temp].countcount].inode = i;
				d_or_f[temp].countcount++;
				break;
			}
		}
	}
	else {
		cout << "full!!!" << endl;
	}
}
