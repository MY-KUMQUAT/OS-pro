#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"
#include <conio.h>
#include <windows.h>
#pragma warning(disable : 4996)

int tempLength = 1;
int tempLimit = 1;

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
	user[index].username = usrname;
	user[index].password = password;
	user[index].uid = index;
	cout << "ע��ɹ������¼��" << endl;
}

int dengLu()//��½
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
		if (user[index].password != password)//���벻һ��
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
	else cout << "��¼�ɹ���" << endl;
	return index;
}

void login(struct PathNode* head)
{
	int usrNum = checkUsrNum();
	while (1)
	{
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
				logState = dengLu();
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
				if (answer != 1 && answer != 2)
				{
					cout << "������1��2:";
				}
				else break;
			}
			if (answer == 1)
			{
				logState = dengLu();//��¼
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
				logState = dengLu();
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
			logState = dengLu();
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

bool menu(struct PathNode* head, int index)
{
	char a = getchar();//��
	//indexΪ�û����û������е�λ��
	userID = index;
	string command;//����
	string arg;//����
	string path = "/root";//·��
	char* argCh;
	string input;
	cout << "��ӭ�����ļ�����ϵͳ!" << user[index].username << endl;
	help();
	while (1)
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//������ɫ
		SetConsoleTextAttribute(h, 10);
		cout << endl << user[index].username;
		SetConsoleTextAttribute(h, 13);
		cout << "@OS_pro:" << path << "$ ";
		SetConsoleTextAttribute(h, 7);
		getline(cin, input);
		int l;
		l = input.find(" ");
		command = input.substr(0, l);//ȡ����
		arg = input.substr(input.find_first_of(" ") + 1, input.length());//ȡ����
		argCh = ChangeStrToChar(arg);
		if (command == "mkdir")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				create_directory(argCh, tempLength, index, tempLimit, head);
		}
		else if (command == "create")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				createfile(argCh, tempLength, index, tempLimit, head);
		}
		else if (command == "rm-rf")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				delete_dirctory(argCh, head);
		}
		else if (command == "cd")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else if (arg == "..")
			{
				ReturnLastLevel(head);
				path = DisplayFullPath(head);
			}
			else
			{
				chdir(head, argCh);
				path = DisplayFullPath(head);
			}
		}
		else if (command == "pwd")
		{
			if (arg == "")
			{
				path = DisplayFullPath(head);
				cout << path << endl;
			}
			else
				cout << "��ʽ����" << endl;
		}
		else if (command == "dir")
		{
			dir(head);
		}
		else if (command == "rm-f")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				deletefile(argCh, head);
		}
		else if (command == "read")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				readfile(argCh, head);
		}
		else if (command == "write")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
			{
				char* newcontent = gettext();
				writefile(argCh, newcontent, head);
			}
		}
		else if (command == "open")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				openfile(argCh, head);
		}
		else if (command == "close")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				closefile(argCh, head);
		}
		else if (command == "format")
		{
			format();
		}
		else if (command == "logout")
		{
			string a;
			while (1)
			{
				cout << "�ǳ������ص���¼����(Y/N)" << endl;
				cin >> a;
				if (a == "y" || a == "Y")
				{
					return true;//����true��ʾ��������login����
				}
				else if (a == "N" || a == "n")
				{
					return false;//��ʾ�˳���¼����
				}
				else
					continue;
			}

		}
		else if (command == "exit")
		{
			int p = 0;
			while (1)
			{
				string a;
				cout << "�˳�����(Y/N)?" << endl;
				cin >> a;
				if (a == "y" || a == "Y")
				{
					p++;
					break;
				}
				else if (a == "N" || a == "n")
				{
					break;
				}
				else
					continue;
			}
			if (p) { return false; }
		}
		else if (command == "changeuser")
		{
			int j = changeUsr(arg);
			if (j == -1)
			{
				cout << "ת���û�ʧ��" << endl;
			}
			else
			{
				index = j;//���û�id����index
				userID = j;
				cout << "�л��û��ɹ���" << endl;
			}
		}
		else if (command == "cp")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				copyfile(head, argCh);
		}
		else if (command == "mv")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				mv(head, argCh);
		}
		else if (command.substr(0, 4) == "find")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
			{
				if (command.length() == 4)searchfile(arg, head, 10);
				else
				{
					searchfile(arg, head, command.substr(4, 1)[0] - '0');
				}
			}
		}
		else if (command == "help")
		{
			help();
		}
		else if (command == "cls")
		{
			system("cls");
			path = DisplayFullPath(head);
		}
		else if (command == "share")
		{
			//arg="abc 123"
			string filename;
			string usr;
			filename = arg.substr(0, arg.find(" "));
			usr = arg.substr(arg.find_last_of(" ") + 1, arg.length());
			if (filename == "" || usr == "")
				cout << "ȱ�ٲ�����" << endl;
			else {
				ShareFile(filename, checkName(usr), head);
			}
		}
		else
			cout << "��������ȷ�����" << endl;
	}
}

void help()
{
	cout << "-----------��������˵�------------" << endl;
	cout << "           1.mkdir                  " << endl;
	cout << "           2.create                    " << endl;
	cout << "           3.rm-rf                    " << endl;
	cout << "           4.enter                   " << endl;
	cout << "           5.cd                   " << endl;
	cout << "           6.dir                  " << endl;
	cout << "           7.rm-f                   " << endl;
	cout << "           8.read                     " << endl;
	cout << "           9.write                  " << endl;
	cout << "           10.open                  " << endl;
	cout << "           11.close                 " << endl;
	cout << "           12.format                 " << endl;
	cout << "           12.logout                 " << endl;
	cout << "           13.exit                   " << endl;
	cout << "           14.changeuser             " << endl;
	cout << "           15.copy                   " << endl;
	cout << "           16.cut                    " << endl;
	cout << "           17.paste                  " << endl;
	cout << "           18.help                   " << endl;
	cout << "           19.cls                    " << endl;
	cout << "           20.share                    " << endl;
	cout << "ģ��dos���ʽ" << endl;
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
	if (user[a].password != pw)
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
		if (user[i].username == a)
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
		if (user[i].password == "")//δ��,����0�����û�Ϊ0
			return i;
	}
	return -1;
}

char* ChangeStrToChar(string InputString)
{
	char* InputChar = new char[InputString.length()];
	int i;
	for (i = 0; i <= InputString.length(); i++)
		InputChar[i] = InputString[i];
	InputChar[i] = '\0'; //�����һ���ַ������Ԫ���ÿգ�������ܳ�����ֵĴ���
	return InputChar;
}

string ChangeCharToStr(char* InputChar)
{
	string InputString;
	for (int k = 0; InputChar[k] != '\0'; k++)
	{
		InputString += InputChar[k];
	}
	return InputString;
}

char* gettext()
{
	char c = ' ';
	char* newcontent = new(char);
	/*cin.get(newcontent, 10);
	a = getchar();*/
	string newcontent_s = "";
	//getline(cin, newcontent_s);
	while (c = _getch())
	{
		if (c == 27)
			break;
		else if (c == 13)
		{
			cout << endl;
			newcontent_s += '\n';
		}
		else
		{
			cout << c;
			newcontent_s += c;
		}
	}
	newcontent = ChangeStrToChar(newcontent_s);
	return newcontent;
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
