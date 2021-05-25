#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"
void copyfile(struct PathNode* head, char filename[])
{
	Copy_LinkedLisk(head);
	//cout<<"after copy";
	//DisplayFullPath(paste_head);

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
			//cout<<endl;
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
		//cout<<"delete source file"<<endl;
		//DisplayFullPath(head);
		//DisplayFullPath(paste_head);
		deletefile(new_filename, paste_head);
	}
	return;
}
void cutfile(struct PathNode* head, char filename[])
{
	copyfile(head, new_filename);
	paste_flag = 1;
}
