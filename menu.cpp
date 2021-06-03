#include "OS_pro.h"
#include <conio.h>
#include <windows.h>

void help()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//字体颜色
	SetConsoleTextAttribute(h, 2);
	cout << "——————————————命令菜单——————————————" << endl;
	SetConsoleTextAttribute(h, 7);
	cout << "  1.mkdir         [目录名]               ——创建目录" << endl;
	cout << "  2.rm-rf         [目录名]               ——删除目录" << endl;
	cout << "  3.rename-d      [目录名] [目录名]      ——目录重命名" << endl;
	cout << "  4.cd            [目录名]               ——切换目录（相对路径）" << endl;
	cout << "  5.cd           ./[目录名]              ——切换目录（相对路径）" << endl;
	cout << "  6.cd            /[目录名]              ——切换目录（绝对路径）" << endl;
	cout << "  7.cd            ..                     ——切换目录（返回上一级）" << endl;
	cout << "  8.pwd                                  ——显示当前目录" << endl;
	cout << "  9.dir                                  ——显示当前目录下内容" << endl;
	cout << "  10.create       [文件名]               ——创建文件" << endl;
	cout << "  11.rm-f         [文件名]               ——删除文件" << endl;
	cout << "  12.rename-f     [文件名] [文件名]      ——目录重命名" << endl;
	cout << "  13.open         [文件名]               ——打开文件" << endl;
	cout << "  14.read         [文件名]               ——读文件" << endl;
	cout << "  15.write        [文件名]               ——写文件" << endl;
	cout << "  16.close        [文件名]               ——关闭文件" << endl;
	cout << "  17.cp           [文件名][目录名]       ——复制文件" << endl;
	cout << "  18.mv           [文件名][目录名]       ——移动文件" << endl;
	cout << "  19.find         [搜索深度] [文件名]/[目录名]（正则表达式）" << endl;
	cout << "                                         ——模糊搜索文件/目录" << endl;
	cout << "  20.logout                              ——登出" << endl;
	cout << "  21.chuser       [用户名]               ——切换用户" << endl;
	cout << "  22.chmod-a      [文件名]/[目录名] [用户名]" << endl;
	cout << "                                         ——文件共享" << endl;
	cout << "  23.chmod-r      [文件名]/[目录名] [用户名]" << endl;
	cout << "                                         ——回收权限" << endl;
	cout << "  24.format                              ——系统格式化" << endl;
	cout << "  25.save                                ——系统保存" << endl;
	cout << "  26.exit                                ——系统保存并退出" << endl;
	cout << "  27.restore                             ——系统从备份中恢复" << endl;
	cout << "  28.help                                ——帮助" << endl;
	cout << "  29.cls                                 ——清屏" << endl;
}


bool menu(struct PathNode* head, int index)
{
	char a = getchar();//接
	//index为用户在用户数组中的位置
	userID = index;
	string command;//命令
	string arg;//参数
	string path = "/root";//路径
	char* argCh;
	string input;
	cout << "欢迎进入文件管理系统!" << user[index].username << endl;
	help();
	while (1)
	{
		path = DisplayFullPath(head);
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//字体颜色
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
				cout << command << ": 缺少操作数" << endl;
			else
				create_directory(argCh, 1, index, 1, head);
		}
		else if (command == "create")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				createfile(argCh, 1, index, 1, head);
		}
		else if (command == "rm-rf")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				delete_dirctory(argCh, head);
		}
		else if (command == "cd")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
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
				cout << command << ": 缺少操作数" << endl;
			else
				deletefile(argCh, head);
		}
		else if (command == "read")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				readfile(argCh, head);
		}
		else if (command == "write")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
			{
				char* newcontent = gettext();
				writefile(argCh, newcontent, head);
			}
		}
		else if (command == "open")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				openfile(argCh, head);
		}
		else if (command == "close")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
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
				cout << "登出，返回到登录程序？(Y/N)" << endl;
				cin >> a;
				if (a == "y" || a == "Y")
				{
					return true;//返回true表示继续运行login函数
				}
				else if (a == "N" || a == "n")
				{
					return false;//表示退出登录程序
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
				cout << "退出程序(Y/N)?" << endl;
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
				cout << "转换用户失败" << endl;
			}
			else
			{
				index = j;//现用户id赋给index
				userID = j;
				ReturnRoot(head);
				cout << "切换用户成功。" << endl;
			}
		}
		else if (command == "cp")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				mv(head, argCh, 'c');
		}
		else if (command == "mv")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				mv(head, argCh, 'm');
		}
		else if (command.substr(0, 4) == "find")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
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
				cout << "缺少操作数" << endl;
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
				cout << "缺少操作数" << endl;
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
				cout << "缺少操作数" << endl;
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
				cout << "缺少操作数" << endl;
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
				cout << "暂无备份" << endl;
			}
			else
			{
				char bak[] = "filesystem.bak";
				read_system(fbak, bak);
			}
		}
		else
			cout << "请输入正确的命令。" << endl;
	}
}