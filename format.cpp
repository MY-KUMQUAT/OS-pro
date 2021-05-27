#include "OS_pro.h"

void format()  //格式化，初始化
{
	int m;
	super_block.sbk_num = num_OF_superblock;
	for (int i = 0; i < num_OF_superblock; i++)  //初始化超级块
	{
		super_block.sbk_free[i] = num_OF_superblock - 1 - i;  //放入栈中的空闲块
	}

	for (int i = 0; i < num_OF_inode; i++)  //i节点区域初始化
	{
		for (int j = 0; j < length_OF_fileaddress; j++)
		{
			inodes[i].inode_fileaddress[j] = -1;
		}
		inodes[i].inode_inum = i;
		inodes[i].inode_filelength = -1;
		inodes[i].inode_filetype = -1;
		inodes[i].inode_limit = -1;
		inodes[i].inode_userID = -1;
	}

	for (int i = 1; i < num_OF_datablock; i++)  //目录及文件区域初始化
	{
		d_or_f[i].df_inum = -1;
		d_or_f[i].countcount = 0;
		strcpy(d_or_f[i].dir_directoryname, "");
	}

	//初始化根目录
	d_or_f[0].df_inum = -1;
	d_or_f[0].countcount = 0;
	strcpy(d_or_f[0].dir_directoryname, "root");

	for (int i = 0; i < num_OF_storage; i++)
	{
		storage[i].blk_num = 0;
		storage[i].blk_flag = 0;
		for (int j = 0; j < 50; j++)
		{
			storage[i].blk_free[j] = -1;
		}
		for (int j = 1; j < size_OF_block; j++)
		{
			storage[j].txt_content[j] = '\0';
		}
	}

	for (int i = 0; i < num_OF_datablock; i++)  //成组链接法组织空闲块
	{
		if ((i + 1) % 50 == 0)
		{
			m = i + 1;
			for (int j = 0; j < num_OF_superblock; j++)
			{
				if (m < (num_OF_storage + 1))
				{
					storage[i].blk_free[j] = m;  //下一组的空闲地址
					storage[i].blk_num++;  //下一组的空闲块的个数
					m++;
				}
				else
				{
					storage[i].blk_free[j] = -1;
				}
			}
			storage[i].blk_flag = 0;  //标记为未使用
			continue;  //当处理完用于存储下一组盘块信息的磁盘块后，跳过本次循环
		}
		for (int j = 0; j < num_OF_superblock; j++)
		{
			storage[i].blk_free[j] = -1;
		}
		storage[i].blk_num = 0;
	}

	for (int n = 0; n < maxnum_OF_openfile; n++)  //初始化打开文件队列
	{
		openfile_array[n] = -1;
	}
	openfile_array_head = 0;

	for (int n = 0; n < size_OF_fileADDRbuffer; n++)  //初始化文件地址缓冲区
	{
		ADDRbuffer[n] = -1;
	}

	cout << "格式化完成！" << endl;
	cout << "OS-pro文件系统" << endl;
}
