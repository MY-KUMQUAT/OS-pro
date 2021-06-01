#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>

#define num_OF_superblock  50  //超级块中的空闲块数
#define num_OF_inode  512  //i节点个数
#define length_OF_fileaddress  100  //文件长度100
#define num_OF_datablock  512  //数据磁盘块共计512块
#define num_OF_storage  550  //系统总大小
#define size_OF_block  512  //每个磁盘块大小512B
#define maxnum_OF_openfile  10  //最大可同时打开10个文件
#define size_OF_fileADDRbuffer  100  //文件缓冲池大小
#define size_OF_user 8

struct PathNode  //目录链表
{
	char* NodeName;
	int Node_Inode;
	struct PathNode* next;
};

struct userlog //用户
{
	int uid;
	char password[14];
	char username[14];
};

struct super_block  //超级块
{
	int sbk_num;  //空闲的盘块数
	int sbk_free[num_OF_superblock];  //放入栈中的空闲块
};

struct block  //每块
{
	int blk_num;  //空闲块个数
	int blk_free[50];  //空闲盘块的地址
	int blk_flag;  //块占用标志
	char txt_content[size_OF_block];  //块上每个字节存放的内容
};

struct dir_list
{
	char filename[14];
	int inode;
};

struct dir_file_block
{
	struct dir_list dir_list[32];  //目录列表，文件名×i节点
	int countcount;//记录目录保存元素数量，初值为0
	char dir_directoryname[10];  //目录名称
	int df_inum;  //目录或文件的i节点号
};

struct inode  //i节点
{
	int inode_inum;  //i节点号
	int inode_filetype;  //文件类型
	int inode_filelength;  //文件长度
	int inode_fileaddress[length_OF_fileaddress];  //文件的物理块号
	int inode_limit;  //文件读写权限
	int inode_userID[size_OF_user];  //用户标识符
};
