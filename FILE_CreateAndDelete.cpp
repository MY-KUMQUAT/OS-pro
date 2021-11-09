#include "OS_pro.h"
#include "login.h"

void createfile(char filename[], int length, int userID, int limit, struct PathNode* head)
{
	int a = Locate(head);
	if (data_block[a].countcount != 32) 
	{
		for (int i = 0; i < data_block[a].countcount; i++)
		{
			if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))  //��������������ļ�
			{
				cout << "�ļ��Ѵ��ڣ�" << endl;
				return;
			}
		}
		for (int i = 0; i < num_OF_inode; i++)
		{
			if (data_block[i].df_inode == -1)
			{
				data_block[i].df_inode = i;
				inodes[i].inode_inum = i;
				inodes[i].inode_filetype = 1;  
				inodes[i].inode_filelength = length;
				inodes[i].inode_limit = limit;
				for (int q = 0; q < 8; q++)
				{
					if (inodes[i].inode_userID[q] < 0)
					{
						inodes[i].inode_userID[q] = userID;
					}
					break;
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
				strcpy(data_block[temp].fcb[data_block[temp].countcount].filename, filename);
				data_block[temp].fcb[data_block[temp].countcount].inode = i;
				data_block[temp].countcount++;
				break;
			}
		}
	}
	else {
		cout << "�ļ�������" << endl;
	}
}

void deletefile(char filename[], struct PathNode* head)
{

	int a = Locate(head);
	int temp, i;
	int tempcount = data_block[a].countcount;


	for (i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			for (int j = 0; j < inodes[data_block[a].fcb[i].inode].inode_filelength; j++)  //����ļ�����
			{
				for (int k = 0; storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] != '\0'; k++)
				{
					storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] = '\0';
				}
			}

			temp = data_block[a].fcb[i].inode;
			for (int i = 0; i < 8; i++)
			{
				inodes[temp].inode_userID[i] = -1;
			}
			inodes[temp].inode_limit = -1;
			for (int j = 0; j < inodes[temp].inode_filelength; j++)
			{
				ADDRbuffer[j] = inodes[temp].inode_fileaddress[j];
			}
			recycling(inodes[temp].inode_filelength);  //���ձ�ɾ���ļ���ռ�Ŀռ�
			for (int j = 0; j < size_OF_fileADDRbuffer; j++)
			{
				ADDRbuffer[j] = -1;  //����ļ���ַ������
			}

			for (int j = 0; j < length_OF_fileaddress; j++)  //���������ַ
			{
				inodes[temp].inode_fileaddress[j] = -1;
			}

			strcpy(data_block[a].fcb[i].filename, "");  //��ʼ��Ŀ¼�б��е�����λ��
			data_block[a].fcb[i].inode = -1;

			data_block[a].fcb[i].inode = -1;  //�ļ�i�ڵ�ָ���ֵ
			inodes[temp].inode_filelength = -1;
			inodes[temp].inode_filetype = -1;

			for (int m = i; m < data_block[a].countcount; m++)
			{
				strcpy(data_block[a].fcb[m].filename, data_block[a].fcb[m + 1].filename);
				data_block[a].fcb[m].inode = data_block[a].fcb[m + 1].inode;
			}
			data_block[a].countcount--;


			break;
		}
	}
	if (i == tempcount)
	{
		cout << "�ļ������ڣ�" << endl;
	}
}



