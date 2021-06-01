#include "OS_pro.h"
#include "login.h"

void ShareFile(string filename, string usr, struct PathNode* head)//分享当前目录的文件
{
	int a = Locate(head);//定位到最后的目录
	int flag = 0;
	int user = checkName(usr);
	//先找存不存在
	if (user == -1)
	{
		cout << usr << "用户不存在" << endl;
		return;
	}
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (d_or_f[a].dir_list[i].filename == filename && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1
			&& checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))//文件名相同  类型为文件  属于可操作用户
		{
			//检查用户重复
			for (int j = 0; j < 8; j++)
			{
				if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] == user)
				{
					cout << "该用户已有权限" << endl;
					flag = 1;
					break;
				}
			}
			if (flag == 0)//usr用户无权限，将其添加
			{
				for (int k = 0; k < 8; k++)
				{
					if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[k] < 0)
					{
						inodes[d_or_f[a].dir_list[i].inode].inode_userID[k] = user;
						cout << "把文件" << filename << "授权给" << usr << "成功！" << endl;
						break;
					}
				}
			}
			return;
		}
	}
	cout << "文件不存在" << endl;
}

void Recovery(string filename, string usr, struct PathNode* head)
{
	int a = Locate(head);
	int flag = 0;
	int user = checkName(usr);
	//先找存不存在
	if (user == -1)
	{
		cout << usr << "用户不存在" << endl;
		return;
	}
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (d_or_f[a].dir_list[i].filename == filename && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1)//找到文件
		{
			if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[0] == userID)//是创建者
			{
				for (int j = 0; j < 8; j++)
				{
					if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] == user)
					{
						inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] = -1;
						cout << "成功收回" << usr << "对文件" << filename << "的权限" << endl;
						return;
					}
				}
				cout << usr << "本来无对文件" << filename << "的权限";
				return;
			}
			else {
				cout << usr << "不是该文件的创建者"; return;
			}
		}
	}
	cout << "文件不存在" << endl;
}