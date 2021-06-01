#include "OS_pro.h"
#include "login.h"

void ShareFile(string filename, string usr, struct PathNode* head)//����ǰĿ¼���ļ�
{
	int a = Locate(head);//��λ������Ŀ¼
	int flag = 0;
	int user = checkName(usr);
	//���Ҵ治����
	if (user == -1)
	{
		cout << usr << "�û�������" << endl;
		return;
	}
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (d_or_f[a].dir_list[i].filename == filename && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1
			&& checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))//�ļ�����ͬ  ����Ϊ�ļ�  ���ڿɲ����û�
		{
			//����û��ظ�
			for (int j = 0; j < 8; j++)
			{
				if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] == user)
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
						inodes[d_or_f[a].dir_list[i].inode].inode_userID[k] = user;
						cout << "���ļ�" << filename << "��Ȩ��" << usr << "�ɹ���" << endl;
						break;
					}
				}
			}
			return;
		}
	}
	cout << "�ļ�������" << endl;
}

void Recovery(string filename, string usr, struct PathNode* head)
{
	int a = Locate(head);
	int flag = 0;
	int user = checkName(usr);
	//���Ҵ治����
	if (user == -1)
	{
		cout << usr << "�û�������" << endl;
		return;
	}
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (d_or_f[a].dir_list[i].filename == filename && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1)//�ҵ��ļ�
		{
			if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[0] == userID)//�Ǵ�����
			{
				for (int j = 0; j < 8; j++)
				{
					if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] == user)
					{
						inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] = -1;
						cout << "�ɹ��ջ�" << usr << "���ļ�" << filename << "��Ȩ��" << endl;
						return;
					}
				}
				cout << usr << "�����޶��ļ�" << filename << "��Ȩ��";
				return;
			}
			else {
				cout << usr << "���Ǹ��ļ��Ĵ�����"; return;
			}
		}
	}
	cout << "�ļ�������" << endl;
}