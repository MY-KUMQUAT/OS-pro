#include "OS_pro.h"
#include "login.h"

void readfile(char* filename, struct PathNode* head)
{
	int a = Locate(head);
	int i, k;
	if (!file_access(filename, head)) return; //�ж��ļ�����Ȩ��
	for (i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			cout << endl;
			for (int j = 0; j < inodes[data_block[a].fcb[i].inode].inode_filelength; j++)  //��ȡ�ļ�����
			{
				for (int k = 0; storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] != '\0'; k++)
				{
					cout << storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k];
				}
			}
			cout << endl;
			break;
		}
	}
}

void writefile(char* filename, char* newcontent, struct PathNode* head)
{
	int a = Locate(head);
	int i, j, k, m;
	int filelength = strlen(newcontent) / size_OF_block + 1; //�ļ�ռ�ô��̿���

	if (!file_access(filename, head)) return; //�ж��ļ�����Ȩ��
	deletefile(filename, head);  //��ɾ��
	createfile(filename, filelength, userID, 1, head);  //�ٴ����µ� 
	openfile(filename, head);

	a = Locate(head);
	for (i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			for (int n = 0; n < inodes[data_block[a].fcb[i].inode].inode_filelength; n++)  //������ļ�����
			{
				for (int k = 0; storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[n]].txt_content[k] != '\0'; k++)
				{
					storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[n]].txt_content[k] = '\0';
				}
			}
			for (j = 0; j < inodes[data_block[a].fcb[i].inode].inode_filelength; j++)  //��д���ļ�����
			{
				for (k = 0; newcontent[k + j * size_OF_block] != '\0' && k < size_OF_block; k++)  // k < size_OF_block(-1)
				{
					storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] = newcontent[k + j * size_OF_block];
				}
				if (newcontent[k + j * size_OF_block] == '\0')
				{
					storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] = '\0';
					break;
				}
				else if (k == size_OF_block - 1)
				{
					storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] = '\0';
				}
			}
			break;
		}
	}
}