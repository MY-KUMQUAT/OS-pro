#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void mv(struct PathNode* head, string name)
{
	string from_name, to_name;
	string file_from_name, file_to_name;
	string dir_from_name, dir_to_name;
	int n, flag, from_name_pos, to_name_pos;
	n = name.find(' ');
	if (n == -1)
	{
		cout << ">>指令格式错误" << endl;
		return;
	}
	else
	{
		from_name = name.substr(0, n);
		to_name = name.substr(n + 1, name.length());
		from_name_pos = from_name.find_last_of('/');
		//to_name_pos = to_name.find_last_of('/');
	}
	if (from_name_pos == -1)
	{
		file_from_name = from_name;
		dir_from_name = '.';
	}
	else
	{
		file_from_name = from_name.substr(from_name_pos + 1, name.length());
		dir_from_name = from_name.substr(0, from_name_pos);
	}
	/*if (to_name_pos == -1)
	{
		file_to_name = to_name;
		dir_to_name = '.';
	}
	else
	{
		file_to_name = to_name.substr(to_name_pos + 1, name.length());
		dir_to_name = to_name.substr(0, to_name_pos);
	}*/
	chdir(head, dir_from_name);
	cutfile(head, ChangeStrToChar(file_from_name));
	//chdir(head, dir_to_name);
	chdir(head, dir_to_name);
	pastefile(head);
	
	cout << from_name << endl;
	cout << to_name << endl;
}

void cp(struct PathNode* head, char name[])
{

}

void copyfile(struct PathNode* head, char filename[])
{
	Copy_LinkedLisk(head);

	int a = Locate(head);
	for (int i = 0; i < d_or_f[a].countcount; i++)
	{
		if (strcmp(filename, d_or_f[a].dir_list[i].filename) == 0 && inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 1 && inodes[d_or_f[a].dir_list[i].inode].inode_userID == userID)
		{
			new_inode_filetype = inodes[d_or_f[a].dir_list[i].inode].inode_filetype;  //文件类型
			new_inode_filelength = inodes[d_or_f[a].dir_list[i].inode].inode_filelength;  //文件长度
			new_inode_limit = inodes[d_or_f[a].dir_list[i].inode].inode_limit;  //文件读写权限
			new_inode_userID = inodes[d_or_f[a].dir_list[i].inode].inode_userID;  //用户标识符

			strcpy(new_filename, filename);

			for (int j = 0; j < inodes[d_or_f[a].dir_list[i].inode].inode_filelength; j++)  //读取文件内容
			{
				for (int k = 0; storage[inodes[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k] != '\0'; k++)
				{
					new_content[k] = storage[inodes[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k];
				}
			}
			break;
		}
	}
	paste_flag = 0;
}

void pastefile(struct PathNode* head)
{
	createfile(new_filename, new_inode_filelength, new_inode_userID, new_inode_limit, head);
	openfile(new_filename, head);
	writefile(new_filename, new_content, head);
	if (paste_flag == 1)
	{
		deletefile(new_filename, paste_head);
	}
	return;
}

void cutfile(struct PathNode* head, char filename[])
{
	copyfile(head, new_filename);
	paste_flag = 1;
}
