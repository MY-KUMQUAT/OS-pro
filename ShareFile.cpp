#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void ShareFile(string filename,int usr,struct PathNode* head)//分享当前目录的文件
{
	int a = Locate(head);
	int flag=0;
	//先找存不存在
	if (usr == -1)
	{
		cout << "被共享的用户不存在" << endl;
		return ;
	}
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (d_or_f[a].dir_list[i].filename == filename && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1
			&& checkID(inodes[d_or_f[a].dir_list[i].inode].inode_userID))//文件名相同  类型为文件  属于可操作用户
		{
			//检查用户重复
			for (int j = 0; j < 8; j++)
			{
				if (inodes[d_or_f[a].dir_list[i].inode].inode_userID[j] == usr)
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
						inodes[d_or_f[a].dir_list[i].inode].inode_userID[k] = usr;
						break;
					}
				}
			}
			break;
		}
	}
}