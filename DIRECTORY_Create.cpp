#include "OS_pro.h"
#include "login.h"

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

void create_directory(char directoryname[], int length, int userID, int limit, struct PathNode* head)
{
	int a = Locate(head);
	if (data_block[a].countcount != 32) 
	{
		for (int i = 0; i < data_block[a].countcount; i++)
		{
			if (strcmp(directoryname, data_block[a].fcb[i].filename) == 0)  //如果已有重名的文件
			{
				cout << "文件已存在！"  << endl;
				return;
			}
		}

		for (int i = 1; i < num_OF_inode; i++)
		{
			if (data_block[i].df_inode == -1)
			{
				data_block[i].df_inode = i;
				strcpy(data_block[i].directoryname, directoryname);
				inodes[i].inode_inum = i;
				inodes[i].inode_filetype = 0;  //文件类型，0为目录文件，1为普通文件
				inodes[i].inode_filelength = length;
				inodes[i].inode_limit = limit;
				//inodes[i].inode_userID = userID;
				for (int k = 0; k < 8; k++)
				{
					if (inodes[i].inode_userID[k] < 0)
					{
						inodes[i].inode_userID[k] = userID;
						break;
					}
				}
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
				strcpy(data_block[temp].fcb[data_block[temp].countcount].filename, directoryname);
				data_block[temp].fcb[data_block[temp].countcount].inode = i;
				data_block[temp].countcount++;
				break;
			}
		}
	}
	else {
		cout << "文件已满！" << endl;
	}
}
