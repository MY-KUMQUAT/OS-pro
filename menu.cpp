#include "OS_pro.h"
#include <conio.h>
#include <windows.h>

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
		path = DisplayFullPath(head);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//������ɫ
		SetConsoleTextAttribute(h, 10);
		cout << endl << user[index].username;
		SetConsoleTextAttribute(h, 13);
		cout << "@OS_pro:" << path << "$ ";
		SetConsoleTextAttribute(h, 7);
		getline(cin, input);
		fragment(command, arg, input);
		argCh = ChangeStrToChar(arg);
		if (command == "mkdir")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				create_directory(argCh, 1, index, 1, head);
		}
		else if (command == "create")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				createfile(argCh, 1, index, 1, head);
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
			path = DisplayFullPath(head);
			cout << path << endl;
		}
		else if (command == "dir")
		{
			Dir(head);
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
					char ch = getchar();
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
				mv(head, argCh, 'c');
		}
		else if (command == "mv")
		{
			if (arg == "")
				cout << command << ": ȱ�ٲ�����" << endl;
			else
				mv(head, argCh, 'm');
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
		else if (command == "chmod-a")
		{
			string filename;
			string usr;
			filename = arg.substr(0, arg.find(" "));
			usr = arg.substr(arg.find_last_of(" ") + 1, arg.length());
			if (filename == "" || usr == "")
				cout << "ȱ�ٲ�����" << endl;
			else {
				ShareFile(filename, usr, head);
			}
		}
		else if (command == "chmod-r")
		{
			string filename;
			string usr;
			filename = arg.substr(0, arg.find(" "));
			usr = arg.substr(arg.find_last_of(" ") + 1, arg.length());
			if (filename == "" || usr == "")
				cout << "ȱ�ٲ�����" << endl;
			else {
				Recovery(filename, usr, head);
			}
		}
		else if (command == "save")
		{
			FILE* fp = fopen("filesystem", "rb");
			write_system(fp);
		}
		else
			cout << "��������ȷ�����" << endl;
	}
}