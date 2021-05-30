#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"
#include <conio.h>
#include <windows.h>
#pragma warning(disable : 4996)

int tempLength = 1;
int tempLimit = 1;

void regist(int index)//注册
{
	string usrname;
	string password;
	while (1)
	{
		cout << "用户名(长度不超过12个字符)：" << endl;
		cin >> usrname;
		if (usrname.length() > 12)
		{
			cout << "不符合要求，请重新输入" << endl;
		}
		else if (checkName(usrname) != -1)//重名
		{
			cout << "与现有用户名重名,请重新输入" << endl;
		}
		else break;
	}
	while (1)
	{
		cout << "密码(长度不超过20个字符)：" << endl;
		cin >> password;
		if (password.length() > 20)
		{
			cout << "不符合要求，请重新输入" << endl;
		}
		else break;
	}
	user[index].username = usrname;
	user[index].password = password;
	user[index].uid = index;
	cout << "注册成功！请登录。" << endl;
}

int dengLu()//登陆
{
	string usrname;
	string password;
	int index;
	int count = 5;//密码可错误次数
	while (1)
	{
		cout << "用户名：" << endl;
		cin >> usrname;
		index = checkName(usrname);
		if (index == -1)//不存在
		{
			cout << "用户名不存在，请重新输入" << endl;
		}
		else break;
	}
	while (count > 0)
	{
		cout << "密码：" << endl;
		cin >> password;
		if (user[index].password != password)//密码不一致
		{
			cout << "密码错误，请重新输入" << endl;
			count--;
		}
		else break;
	}
	if (count == 0)
	{
		cout << "密码输入错误达5次，退出登录程序。" << endl;
		return -1;
	}
	else cout << "登录成功！" << endl;
	return index;
}

void login(struct PathNode* head)
{
	int usrNum = checkUsrNum();
	while (1)
	{
		int logState = 0;//登录状态,没登上去就是-1
		cout << ">>文件管理系统" << endl;
		if (usrNum == 0)//用户个数为0,注册
		{
			int flag = 0;
			string answer;
			cout << "无用户在此系统中，是否注册？(Y/N):";
			while (1)
			{
				cin >> answer;
				if (answer == "Y" || answer == "y")
				{
					regist(usrNum);//注册
					break;
				}
				else if (answer == "N" || answer == "n")
				{
					flag++;
					break;
				}
				else
					cout << "请输入‘Y’（‘y’）或‘N’（‘n’）:";
			}
			if (flag == 1) {//不注册，退出程序
				break;
			}
			else {//注册成功
				logState = dengLu();
				if (logState != -1)//登录成功
				{
					if (!menu(head, logState))//进入菜单
					{
						break;
					}//进入菜单menu(head,logState)
				}
				else continue;
			}
		}
		else if (usrNum != -1)//用户个数未满
		{
			int answer;
			cout << "登录/注册（1/2）:";
			while (1)
			{
				cin >> answer;
				if (answer != 1 && answer != 2)
				{
					cout << "请输入1或2:";
				}
				else break;
			}
			if (answer == 1)
			{
				logState = dengLu();//登录
				if (logState != -1)
				{
					if (!menu(head, logState))//进入菜单
					{
						break;
					}
				}
				else continue;
			}
			else if (answer == 2)
			{
				regist(usrNum);//注册
				logState = dengLu();
				if (logState != -1)//登录成功
				{
					if (!menu(head, logState))//进入菜单
					{
						break;
					}
				}
				else continue;
			}
		}
		else//满了
		{
			logState = dengLu();
			if (logState != -1)//登录成功
			{
				if (!menu(head, logState))//进入菜单
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
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);//字体颜色
		SetConsoleTextAttribute(h, 10);
		cout << endl << user[index].username;
		SetConsoleTextAttribute(h, 13);
		cout << "@OS_pro:" << path << "$ ";
		SetConsoleTextAttribute(h, 7);
		getline(cin, input);
		int l;
		l = input.find(" ");
		command = input.substr(0, l);//取命令
		arg = input.substr(input.find_first_of(" ") + 1, input.length());//取参数
		argCh = ChangeStrToChar(arg);
		if (command == "mkdir")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				create_directory(argCh, tempLength, index, tempLimit, head);
		}
		else if (command == "create")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				createfile(argCh, tempLength, index, tempLimit, head);
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
			if (arg == "")
			{
				path = DisplayFullPath(head);
				cout << path << endl;
			}
			else
				cout << "格式错误" << endl;
		}
		else if (command == "dir")
		{
			dir(head);
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
				cout << "转换用户失败" << endl;
			}
			else
			{
				index = j;//现用户id赋给index
				userID = j;
				cout << "切换用户成功。" << endl;
			}
		}
		else if (command == "cp")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				copyfile(head, argCh);
		}
		else if (command == "mv")
		{
			if (arg == "")
				cout << command << ": 缺少操作数" << endl;
			else
				mv(head, argCh);
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
				cout << "缺少操作数" << endl;
			else {
				ShareFile(filename, checkName(usr), head);
			}
		}
		else
			cout << "请输入正确的命令。" << endl;
	}
}

void help()
{
	cout << "-----------可用命令菜单------------" << endl;
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
	cout << "模仿dos命令方式" << endl;
}


int changeUsr(string usrname)
{
	char n;
	string pw;
	int a = checkName(usrname);
	if (a == -1)
	{
		cout << "用户不存在" << endl;
		return -1;
	}
	cout << "密码：";
	cin >> pw;
	n = getchar();
	if (user[a].password != pw)
	{
		cout << "密码错误！" << endl;
		return -1;
	}
	return a;
}


int checkName(string a)//检查用户是否存在,-1为不存在，其他为存在且返回index
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


int checkUsrNum()//检查注册的用户是否已经达到8个
{
	for (int i = 0; i < size_OF_user; i++)
	{
		if (user[i].password == "")//未满,返回0就是用户为0
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
	InputChar[i] = '\0'; //将最后一个字符后面的元素置空，否则可能出现奇怪的错误
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

bool checkID(int* usrID)//检查用户id是否在可对文件操作的数组内
{
	for (int i = 0; i < 8; i++)
	{
		if (usrID[i] == userID)
			return true;
	}
	return false;
}
