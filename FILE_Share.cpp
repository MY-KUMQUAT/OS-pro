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
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (data_block[a].fcb[i].filename == filename
			&& checkID(inodes[data_block[a].fcb[i].inode].inode_userID))//�ļ�����ͬ  ����Ϊ�ļ�  ���ڿɲ����û�
		{
			//����û��ظ�
			for (int j = 0; j < 8; j++)
			{
				if (inodes[data_block[a].fcb[i].inode].inode_userID[j] == user)
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
					if (inodes[data_block[a].fcb[i].inode].inode_userID[k] < 0)
					{
						inodes[data_block[a].fcb[i].inode].inode_userID[k] = user;
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
	if (user == userID)
	{
		cout << "����" << endl;
		return;
	}
	//���Ҵ治����
	if (user == -1)
	{
		cout << usr << "�û�������" << endl;
		return;
	}
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (data_block[a].fcb[i].filename == filename)//�ҵ��ļ�
		{
			if (inodes[data_block[a].fcb[i].inode].inode_userID[0] == userID)//�Ǵ�����
			{
				for (int j = 0; j < 8; j++)
				{
					if (inodes[data_block[a].fcb[i].inode].inode_userID[j] == user)
					{
						inodes[data_block[a].fcb[i].inode].inode_userID[j] = -1;
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