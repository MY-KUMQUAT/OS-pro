#include "OS_pro.h"
#include "login.h"

void delete_dirctory(char directory[], struct PathNode* head)
{

	//�ж��Ƿ��ڵ�ǰĿ¼��
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
	for (int i = 0; i < d_or_f[temp].countcount;)
	{
		int nowstytle = d_or_f[temp].dir_list[i].inode;
		if (inodes[nowstytle].inode_filetype == 1) //0Ŀ¼ 1�ļ�
		{
			deletefile(d_or_f[temp].dir_list[i].filename, head);//ɾ���ļ�
			cout << "ɾ���ɹ�: " << d_or_f[temp].dir_list[i].filename << endl;
		}
		else
		{
			recycledelete(head, d_or_f[temp].dir_list[i].filename);//�ݹ�ɾ��Ŀ¼�ļ�
		}
	}
	ReturnLastLevel(head);//��ǰĿ¼�б���ɾ���꣬��������ɾ���ýڵ�
	temp = Locate(head);
	for (int i = 0; i < d_or_f[temp].countcount; i++)
	{
		if (strcmp(directory, d_or_f[temp].dir_list[i].filename) == 0)
		{
			printf("ɾ���ɹ�!%s", directory);
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


