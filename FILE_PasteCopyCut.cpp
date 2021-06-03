#include "OS_pro.h"
#include "login.h"

void mv(struct PathNode* head, string name, char com)
{
	string from_name, to_name;
	string file_from_name;
	string dir_from_name;
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
	chdir(head, dir_from_name);
	if(com == 'm')
		cutfile(head, ChangeStrToChar(file_from_name));
	else if(com == 'c')
		copyfile(head, ChangeStrToChar(file_from_name));
	//chdir(head, dir_to_name);
	chdir(head, to_name);
	pastefile(head);
	
	//cout << from_name << endl;
	//cout << to_name << endl;
}

void copyfile(struct PathNode* head, char filename[])
{
	Copy_LinkedLisk(head);

	int a = Locate(head);
	for (int i = 0; i < data_block[a].countcount; i++)
	{
		if (strcmp(filename, data_block[a].fcb[i].filename) == 0 && inodes[data_block[a].fcb[i].inode].inode_filetype == 1 && checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			new_inode_filetype = inodes[data_block[a].fcb[i].inode].inode_filetype;  //文件类型
			new_inode_filelength = inodes[data_block[a].fcb[i].inode].inode_filelength;  //文件长度
			new_inode_limit = inodes[data_block[a].fcb[i].inode].inode_limit;  //文件读写权限
			new_inode_userID = userID;

			strcpy(new_filename, filename);

			for (int j = 0; j < inodes[data_block[a].fcb[i].inode].inode_filelength; j++)  //读取文件内容
			{
				for (int k = 0; storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k] != '\0'; k++)
				{
					new_content[k] = storage[inodes[data_block[a].fcb[i].inode].inode_fileaddress[j]].txt_content[k];
				}
			}
			break;
		}
	}
	paste_flag = 0;
}

void pastefile(struct PathNode* head)
{
	createfile(new_filename, new_inode_filelength, userID, new_inode_limit, head);
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
	copyfile(head, filename);
	paste_flag = 1;
}

struct PathNode* Copy_LinkedLisk(struct PathNode* COPY)
{
	struct PathNode* p1 = COPY, * p2, * p3 = paste_head;
	p1 = p1->next;
	while (p1 != NULL)
	{
		p2 = InitPathNode();
		p2->NodeName = p1->NodeName;
		p2->Node_Inode = p1->Node_Inode;
		p1 = p1->next;
		p3->next = p2;
		p3 = p3->next;
	}
	return 0;
}