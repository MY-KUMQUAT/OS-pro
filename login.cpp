#include "OS_pro.h"
#include "login.h"
#include <conio.h>
#include <windows.h>
#pragma warning(disable : 4996)

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
	
	strcpy(user[index].username, ChangeStrToChar(usrname));
	strcpy(user[index].password, ChangeStrToChar(password));
	user[index].uid = index;
	cout << "注册成功！请登录。" << endl;
}

int dengLu(struct PathNode* head)//登陆
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
		string upwd = ChangeCharToStr(user[index].password);
		if (upwd != password)//密码不一致
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
	else
	{
		cout << "登录成功！" << endl;
		ReturnRoot(head);
	}
	return index;
}

void login(struct PathNode* head)
{
	while (1)
	{
		int usrNum = checkUsrNum();
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
				logState = dengLu(head);
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
				cin.clear();
				cin.ignore(1024, '\n');
				if (answer != 1 && answer != 2)
				{
					cout << "请输入1或2:";
				}
				else break;
			}
			if (answer == 1)
			{
				logState = dengLu(head);//登录
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
				logState = dengLu(head);
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
			logState = dengLu(head);
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
	string upwd = ChangeCharToStr(user[a].password);
	if (upwd != pw)
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
		string uname = ChangeCharToStr(user[i].username);
		if (uname == a)
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
		if (strcmp(user[i].password,"") == 0)//未满,返回0就是用户为0
			return i;
	}
	return -1;
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


