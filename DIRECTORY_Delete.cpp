#include "OS_pro.h"
#include "login.h"

void delete_dirctory(char directory[], struct PathNode* head)
{

	//判断是否在当前目录下
	int a = Locate(head);
	int flag = 0;
	if (data_block[a].countcount > 0)
	{
		for (int i = 0; i < data_block[a].countcount; i++)
		{
			if (strcmp(directory, data_block[a].fcb[i].filename) == 0 &&inodes[data_block[a].fcb[i].inode].inode_filetype == 0 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
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
	for (int i = 0; i < data_block[temp].countcount;)
	{
		int nowstytle = data_block[temp].fcb[i].inode;
		if (inodes[nowstytle].inode_filetype == 1) //0目录 1文件
		{
			deletefile(data_block[temp].fcb[i].filename, head);//删除文件
			cout << "删除成功: " << data_block[temp].fcb[i].filename << endl;
		}
		else
		{
			recycledelete(head, data_block[temp].fcb[i].filename);//递归删除目录文件
		}
	}
	ReturnLastLevel(head);//当前目录列表已删除完，从链表中删除该节点
	temp = Locate(head);
	for (int i = 0; i < data_block[temp].countcount; i++)
	{
		if (strcmp(directory, data_block[temp].fcb[i].filename) == 0)
		{
			printf("删除成功!%s", directory);
			release(data_block[temp].fcb[i].inode);
			for (int j = i; j < data_block[temp].countcount - 1; j++)
			{
				data_block[temp].fcb[j] = data_block[temp].fcb[j + 1];
			}
			data_block[temp].countcount--;
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


