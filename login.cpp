#include "OS_pro.h"
#include "login.h"
#include <conio.h>
#include <windows.h>
#pragma warning(disable : 4996)

void regist(int index)//ע��
{
	string usrname;
	string password;
	while (1)
	{
		cout << "�û���(���Ȳ�����12���ַ�)��" << endl;
		cin >> usrname;
		if (usrname.length() > 12)
		{
			cout << "������Ҫ������������" << endl;
		}
		else if (checkName(usrname) != -1)//����
		{
			cout << "�������û�������,����������" << endl;
		}
		else break;
	}
	while (1)
	{
		cout << "����(���Ȳ�����20���ַ�)��" << endl;
		cin >> password;
		if (password.length() > 20)
		{
			cout << "������Ҫ������������" << endl;
		}
		else break;
	}
	
	strcpy(user[index].username, ChangeStrToChar(usrname));
	strcpy(user[index].password, ChangeStrToChar(password));
	user[index].uid = index;
	cout << "ע��ɹ������¼��" << endl;
}

int dengLu(struct PathNode* head)//��½
{
	string usrname;
	string password;
	int index;
	int count = 5;//����ɴ������
	while (1)
	{
		cout << "�û�����" << endl;
		cin >> usrname;
		index = checkName(usrname);
		if (index == -1)//������
		{
			cout << "�û��������ڣ�����������" << endl;
		}
		else break;
	}
	while (count > 0)
	{
		cout << "���룺" << endl;
		cin >> password;
		string upwd = ChangeCharToStr(user[index].password);
		if (upwd != password)//���벻һ��
		{
			cout << "�����������������" << endl;
			count--;
		}
		else break;
	}
	if (count == 0)
	{
		cout << "������������5�Σ��˳���¼����" << endl;
		return -1;
	}
	else
	{
		cout << "��¼�ɹ���" << endl;
		ReturnRoot(head);
	}
	return index;
}

void login(struct PathNode* head)
{
	while (1)
	{
		int usrNum = checkUsrNum();
		int logState = 0;//��¼״̬,û����ȥ����-1
		cout << ">>�ļ�����ϵͳ" << endl;
		if (usrNum == 0)//�û�����Ϊ0,ע��
		{
			int flag = 0;
			string answer;
			cout << "���û��ڴ�ϵͳ�У��Ƿ�ע�᣿(Y/N):";
			while (1)
			{
				cin >> answer;
				if (answer == "Y" || answer == "y")
				{
					regist(usrNum);//ע��
					break;
				}
				else if (answer == "N" || answer == "n")
				{
					flag++;
					break;
				}
				else
					cout << "�����롮Y������y������N������n����:";
			}
			if (flag == 1) {//��ע�ᣬ�˳�����
				break;
			}
			else {//ע��ɹ�
				logState = dengLu(head);
				if (logState != -1)//��¼�ɹ�
				{
					if (!menu(head, logState))//����˵�
					{
						break;
					}//����˵�menu(head,logState)
				}
				else continue;
			}
		}
		else if (usrNum != -1)//�û�����δ��
		{
			int answer;
			cout << "��¼/ע�ᣨ1/2��:";
			while (1)
			{
				cin >> answer;
				cin.clear();
				cin.ignore(1024, '\n');
				if (answer != 1 && answer != 2)
				{
					cout << "������1��2:";
				}
				else break;
			}
			if (answer == 1)
			{
				logState = dengLu(head);//��¼
				if (logState != -1)
				{
					if (!menu(head, logState))//����˵�
					{
						break;
					}
				}
				else continue;
			}
			else if (answer == 2)
			{
				regist(usrNum);//ע��
				logState = dengLu(head);
				if (logState != -1)//��¼�ɹ�
				{
					if (!menu(head, logState))//����˵�
					{
						break;
					}
				}
				else continue;
			}
		}
		else//����
		{
			logState = dengLu(head);
			if (logState != -1)//��¼�ɹ�
			{
				if (!menu(head, logState))//����˵�
				{
					break;
				}
			}
			else continue;
		}
	}
}

int changeUsr(string usrname)
{
	char n;
	string pw;
	int a = checkName(usrname);
	if (a == -1)
	{
		cout << "�û�������" << endl;
		return -1;
	}
	cout << "���룺";
	cin >> pw;
	n = getchar();
	string upwd = ChangeCharToStr(user[a].password);
	if (upwd != pw)
	{
		cout << "�������" << endl;
		return -1;
	}
	return a;
}

int checkName(string a)//����û��Ƿ����,-1Ϊ�����ڣ�����Ϊ�����ҷ���index
{
	for (int i = 0; i < size_OF_user; i++)
	{
		string uname = ChangeCharToStr(user[i].username);
		if (uname == a)
		{
			return user[i].uid;
		}
	}
	return -1;
}

int checkUsrNum()//���ע����û��Ƿ��Ѿ��ﵽ8��
{
	for (int i = 0; i < size_OF_user; i++)
	{
		if (strcmp(user[i].password,"") == 0)//δ��,����0�����û�Ϊ0
			return i;
	}
	return -1;
}

bool checkID(int* usrID)//����û�id�Ƿ��ڿɶ��ļ�������������
{
	for (int i = 0; i < 8; i++)
	{
		if (usrID[i] == userID)
			return true;
	}
	return false;
}


