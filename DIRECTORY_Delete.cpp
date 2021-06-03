#include "OS_pro.h"
#include "login.h"

void delete_dirctory(char directory[], struct PathNode* head)
{

	//�ж��Ƿ��ڵ�ǰĿ¼��
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
			cout << "û���ҵ���ӦĿ¼��ɾ��ʧ��" << endl;
			return;
		}
	}
	else
	{
		cout << "û���ҵ���ӦĿ¼��ɾ��ʧ��" << endl;
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
		if (inodes[nowstytle].inode_filetype == 1) //0Ŀ¼ 1�ļ�
		{
			deletefile(data_block[temp].fcb[i].filename, head);//ɾ���ļ�
			cout << "ɾ���ɹ�: " << data_block[temp].fcb[i].filename << endl;
		}
		else
		{
			recycledelete(head, data_block[temp].fcb[i].filename);//�ݹ�ɾ��Ŀ¼�ļ�
		}
	}
	ReturnLastLevel(head);//��ǰĿ¼�б���ɾ���꣬��������ɾ���ýڵ�
	temp = Locate(head);
	for (int i = 0; i < data_block[temp].countcount; i++)
	{
		if (strcmp(directory, data_block[temp].fcb[i].filename) == 0)
		{
			printf("ɾ���ɹ�!%s", directory);
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


