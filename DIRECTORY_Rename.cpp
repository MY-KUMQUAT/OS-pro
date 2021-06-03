#include "OS_pro.h"
#include "LOGIN.h"
#include "OTHER.h"

void DirRename(struct PathNode* head,string name_f,string name_s)
{
	int a = Locate(head);
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (data_block[a].fcb[i].filename == name_f && inodes[data_block[a].fcb[i].inode].inode_filetype == 0)//�ҵ�Ŀ¼�ļ�
		{
			if (checkID(inodes[data_block[a].fcb[i].inode].inode_userID))//�û��Ƿ���Ȩ�޴˲���
			{
				char* temp = new char;
				temp = ChangeStrToChar(name_s);
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