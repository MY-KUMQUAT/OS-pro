#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void ShareFile(string filename,int usr,struct PathNode* head)//����ǰĿ¼���ļ�
{
	int a = Locate(head);
	int flag=0;
	//���Ҵ治����
	if (usr == -1)
	{
		cout << "��������û�������" << endl;
		return ;
	}
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (d_or_f[a].dir_list[i].filename == filename && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1
			&& checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))//�ļ�����ͬ  ����Ϊ�ļ�  ���ڿɲ����û�
		{
			//����û��ظ�
			for (int j = 0; j < 8; j++)
			{
				if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] == usr)
				{
					cout << "���û�����Ȩ��" << endl;
					flag = 1;
					break;
				}
			}
			if (flag == 0)//usr�û���Ȩ�ޣ��������
			{
				for (int k = 0; k < 8; k++)
				{
					if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[k] < 0)
					{
						inodes[d_or_f[a].dir_list[i].inode].inode_userID[k] = usr;
						break;
					}
				}
			}
			break;
		}
	}
}