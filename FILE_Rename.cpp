#include "OS_pro.h"
#include "LOGIN.h"
#include "OTHER.h"

void FileRename(struct PathNode* head, string file1, string file2)
{
	int a = Locate(head);
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (data_block[a].fcb[i].filename == file1 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1)//�ҵ�Ŀ¼�ļ�
		{
			if (checkID(inodes[data_block[a].fcb[i].inode].inode_userID))//�û��Ƿ���Ȩ�޴˲���
			{
				char* temp = new char;
				temp = ChangeStrToChar(file2);
				strcpy(data_block[a].fcb[i].filename, temp);
				cout << "�ļ��Ѿ�����:" << data_block[a].fcb[i].filename;
				return;
			}
			else
			{
				cout << "���޸���Ȩ��" << endl;
				return;
			}
		}
	}
	cout << "δ�ҵ���ӦĿ¼" << endl;
	return;
}