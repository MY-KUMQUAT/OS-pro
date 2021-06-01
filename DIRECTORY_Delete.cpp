#include "OS_pro.h"
#include "login.h"

void delete_dirctory(char directory[], struct PathNode* head)
{

	//判断是否在当前目录下
	int a = Locate(head);
	int flag = 0;
	if (d_or_f[a].countcount > 0)
	{
		for (int i = 0; i < d_or_f[a].countcount; i++)
		{
			if (strcmp(directory, d_or_f[a].dir_list[i].filename) == 0 &&inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 0 && checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))
			{
				recycledelete(head, directory);
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			cout << "没有找到对应目录，删除失败" << endl;
			return;
		}
	}
	else
	{
		cout << "没有找到对应目录，删除失败" << endl;
		return;
	}

}

void recycledelete(struct PathNode* head, char directory[])
{
	Enter(head, directory);
	int temp = Locate(head);
	for (int i = 0; i < d_or_f[temp].countcount;)
	{
		int nowstytle = d_or_f[temp].dir_list[i].inode;
		if (inodes[nowstytle].inode_filetype == 1) //0目录 1文件
		{
			deletefile(d_or_f[temp].dir_list[i].filename, head);//删除文件
			cout << "删除成功: " << d_or_f[temp].dir_list[i].filename << endl;
		}
		else
		{
			recycledelete(head, d_or_f[temp].dir_list[i].filename);//递归删除目录文件
		}
	}
	ReturnLastLevel(head);//当前目录列表已删除完，从链表中删除该节点
	temp = Locate(head);
	for (int i = 0; i < d_or_f[temp].countcount; i++)
	{
		if (strcmp(directory, d_or_f[temp].dir_list[i].filename) == 0)
		{
			printf("删除成功!%s", directory);
			release(d_or_f[temp].dir_list[i].inode);
			for (int j = i; j < d_or_f[temp].countcount - 1; j++)
			{
				d_or_f[temp].dir_list[j] = d_or_f[temp].dir_list[j + 1];
			}
			d_or_f[temp].countcount--;
		}
	}
}

void release(int iNode) {
	for (int i = 0; i < inodes[iNode].inode_filelength; i++) {
		ADDRbuffer[i] = inodes[iNode].inode_fileaddress[i];
	}
	recycling(inodes[iNode].inode_filelength);
	for (int j = 0; j < inodes[iNode].inode_filelength; j++) {
		inodes[iNode].inode_fileaddress[j] = -1;
	}
	inodes[iNode].inode_filelength = -1;
	inodes[iNode].inode_filetype = -1;
	inodes[iNode].inode_inum = -1;
	inodes[iNode].inode_limit = -1;
	for (int i = 0; i < 8; i++)
	{
		inodes[iNode].inode_userID[i] = -1;
	}
}


