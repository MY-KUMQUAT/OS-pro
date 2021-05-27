#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void searchfile(char* reg_name, struct PathNode* head)
{
	string reg_str = ChangeCharToStr(reg_name);
	regex reg(reg_str);

	int a = Locate(head);
	int i, n = 0;

	for (i = 0; i < d_or_f[a].countcount; i++)
	{
		string filename = ChangeCharToStr(d_or_f[a].dir_list[i].filename);
		bool ret = regex_match(filename, reg); //正则匹配
		if (ret == 1 && inodes[d_or_f[a].dir_list[i].inode].inode_userID == userID)
		{
			cout << d_or_f[a].dir_list[i].filename << endl;
			n++;
		}
	}
	if (n == 0)
	{
		cout << "没有那个文件或目录！" << endl;
	}
}
