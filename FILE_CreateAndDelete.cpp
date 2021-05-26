#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void createfile(char filename[], int length, int userID, int limit, struct PathNode* head)
{
	int a = Locate(head);
	if (d_or_f[a].countcount != 32) {
		for (int i = 0; i < d_or_f[a].countcount; i++)
		{
			if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_userID == userID)  //如果已有重名的文件
			{
				cout << "There is a directory or file with the same name.File creation failed." << endl;
				return;
			}
		}
		for (int i = 0; i < num_OF_inode; i++)
		{
			if (d_or_f[i].df_inum == -1)
			{
				d_or_f[i].df_inum = i;
				strcpy(d_or_f[i].txt_filename, filename);
				inodes[i].inode_inum = i;
				inodes[i].inode_filetype = 1;  //文件类型，0为目录文件，1为普通文件
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
				strcpy(d_or_f[temp].dir_list[d_or_f[temp].countcount].filename, filename);
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


void deletefile(char* filename, struct PathNode* head)
{

	int a = Locate(head);
	int temp, i;
	int tempcount = d_or_f[a].countcount;


	for (i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1 && inodes[d_or_f[a].dir_list[i].inode].inode_userID == userID)
		{
			for (int j = 0; j < inodes[d_or_f[a].dir_list[i].inode].inode_filelength; j++)  //清空文件内容
			{
				for (int k = 0; storage[inodes[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k] != '\0'; k++)
				{
					storage[inodes[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k] = '\0';
				}
			}

			temp = d_or_f[a].dir_list[i].inode;
			inodes[temp].inode_userID = -1;
			inodes[temp].inode_limit = -1;
			for (int j = 0; j < inodes[temp].inode_filelength; j++)
			{
				ADDRbuffer[j] = inodes[temp].inode_fileaddress[j];
			}
			recycling(inodes[temp].inode_filelength);  //回收被删除文件所占的空间
			for (int j = 0; j < size_OF_fileADDRbuffer; j++)
			{
				ADDRbuffer[j] = -1;  //清空文件地址缓冲区
			}

			for (int j = 0; j < length_OF_fileaddress; j++)  //回收物理地址
			{
				inodes[temp].inode_fileaddress[j] = -1;
			}
			strcpy(d_or_f[a].txt_filename, "");

			strcpy(d_or_f[a].dir_list[i].filename, "");  //初始化目录列表中的所在位置
			d_or_f[a].dir_list[i].inode = -1;

			d_or_f[a].dir_list[i].inode = -1;  //文件i节点恢复初值
			inodes[temp].inode_filelength = -1;
			inodes[temp].inode_filetype = -1;

			for (int m = i; m < d_or_f[a].countcount; m++)
			{
				strcpy(d_or_f[a].dir_list[m].filename, d_or_f[a].dir_list[m + 1].filename);
				d_or_f[a].dir_list[m].inode = d_or_f[a].dir_list[m + 1].inode;
			}
			d_or_f[a].countcount--;


			break;
		}
	}
	if (i == tempcount)
	{
		cout << "This file does not exist in the user's current directory." << endl;
	}
}



