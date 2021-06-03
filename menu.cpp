#include "OS_pro.h"
#include <conio.h>
#include <windows.h>

void help()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//������ɫ
	SetConsoleTextAttribute(h, 2);
	cout << "��������������������������������˵�����������������������������" << endl;
	SetConsoleTextAttribute(h, 7);
	cout << "  1.mkdir         [Ŀ¼��]               ��������Ŀ¼" << endl;
	cout << "  2.rm-rf         [Ŀ¼��]               ����ɾ��Ŀ¼" << endl;
	cout << "  3.rename-d      [Ŀ¼��] [Ŀ¼��]      ����Ŀ¼������" << endl;
	cout << "  4.cd            [Ŀ¼��]               �����л�Ŀ¼�����·����" << endl;
	cout << "  5.cd           ./[Ŀ¼��]              �����л�Ŀ¼�����·����" << endl;
	cout << "  6.cd            /[Ŀ¼��]              �����л�Ŀ¼������·����" << endl;
	cout << "  7.cd            ..                     �����л�Ŀ¼��������һ����" << endl;
	cout << "  8.pwd                                  ������ʾ��ǰĿ¼" << endl;
	cout << "  9.dir                                  ������ʾ��ǰĿ¼������" << endl;
	cout << "  10.create       [�ļ���]               ���������ļ�" << endl;
	cout << "  11.rm-f         [�ļ���]               ����ɾ���ļ�" << endl;
	cout << "  12.rename-f     [�ļ���] [�ļ���]      ����Ŀ¼������" << endl;
	cout << "  13.open         [�ļ���]               �������ļ�" << endl;
	cout << "  14.read         [�ļ���]               �������ļ�" << endl;
	cout << "  15.write        [�ļ���]               ����д�ļ�" << endl;
	cout << "  16.close        [�ļ���]               �����ر��ļ�" << endl;
	cout << "  17.cp           [�ļ���][Ŀ¼��]       ���������ļ�" << endl;
	cout << "  18.mv           [�ļ���][Ŀ¼��]       �����ƶ��ļ�" << endl;
	cout << "  19.find         [�������] [�ļ���]/[Ŀ¼��]��������ʽ��" << endl;
	cout << "                                         ����ģ�������ļ�/Ŀ¼" << endl;
	cout << "  20.logout                              �����ǳ�" << endl;
	cout << "  21.chuser       [�û���]               �����л��û�" << endl;
	cout << "  22.chmod-a      [�ļ���]/[Ŀ¼��] [�û���]" << endl;
	cout << "                                         �����ļ�����" << endl;
	cout << "  23.chmod-r      [�ļ���]/[Ŀ¼��] [�û���]" << endl;
	cout << "                                         ��������Ȩ��" << endl;
	cout << "  24.format                              ����ϵͳ��ʽ��" << endl;
	cout << "  25.save                                ����ϵͳ����" << endl;
	cout << "  26.exit                                ����ϵͳ���沢�˳�" << endl;
	cout << "  27.restore                             ����ϵͳ�ӱ����лָ�" << endl;
	cout << "  28.help                                ��������" << endl;
	cout << "  29.cls                                 ��������" << endl;
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
		else if (command == "chuser")
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
				ReturnRoot(head);
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
			file_found = 0;
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
		else if (command == "rename-d")
		{
			string filename;
			string new_name;
			filename = arg.substr(0, arg.find(" "));
			new_name = arg.substr(arg.find_last_of(" ") + 1, arg.length());
			if (filename == "" || new_name == "")
				cout << "ȱ�ٲ�����" << endl;
			else {
				DirRename(head, filename, new_name);
			}
		}
		else if (command == "rename-f")
		{
			string filename;
			string new_name;
			filename = arg.substr(0, arg.find(" "));
			new_name = arg.substr(arg.find_last_of(" ") + 1, arg.length());
			if (filename == "" || new_name == "")
				cout << "ȱ�ٲ�����" << endl;
			else {
				FileRename(head, filename, new_name);
			}
		}
		else if (command == "save")
		{
			FILE* fp = fopen("filesystem", "rb");
			write_system(fp, "filesystem");
		}
		else if (command == "restore")
		{
			FILE* fbak = fopen("filesystem.bak", "rb");
			if (fbak == NULL)
			{
				cout << "���ޱ���" << endl;
			}
			else
			{
				char bak[] = "filesystem.bak";
				read_system(fbak, bak);
			}
		}
		else
			cout << "��������ȷ�����" << endl;
	}
}