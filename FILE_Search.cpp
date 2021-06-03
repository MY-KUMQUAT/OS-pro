#include "OS_pro.h"
#include "login.h"

void searchfile(string reg_name, struct PathNode* head, int depth)
{
	if (recursion_flag > depth) return; //当前深度大于搜索深度则返回
	regex reg;
	try
	{
		regex r(reg_name);
		reg = r;
	}
	catch (std::regex_error e)
	{
		cout << "正则语句输入错误，无法解析!" << endl;
		return;
	}

	int i, a = Locate(head);
	for (i = 0; i < data_block[a].countcount; i++)
	{
		string filename = ChangeCharToStr(data_block[a].fcb[i].filename);
		bool ret = regex_match(filename, reg); //正则匹配
		if (checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			if (ret == 1)  //打印目录及文件
			{
				struct PathNode* p1 = head;
				cout << "/" << p1->NodeName;
				p1 = p1->next;
				while (p1 != NULL)
				{
					cout << "/" << p1->NodeName;
					p1 = p1->next;
				}
				cout << "/" << data_block[a].fcb[i].filename << endl;
				file_found++;
			}
			else if (inodes[data_block[a].fcb[i].inode].inode_filetype == 0)
			{
				recursion_flag++;  //搜索递归深度
				Enter(head, data_block[a].fcb[i].filename);  //进入下一层
				searchfile(reg_name, head, depth);  //递归入口
				ReturnLastLevel(head);
				recursion_flag--;
			}
		}
	}
	if (file_found == 0 && recursion_flag == 0)
	{
		cout << "没有那个文件或目录！" << endl;
	}
	return;
}
