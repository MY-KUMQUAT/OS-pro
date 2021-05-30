#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>
#include <regex>

using namespace std;

#define num_OF_superblock  50  //超级块中的空闲块数
#define num_OF_inode  512  //i节点个数
#define length_OF_fileaddress  100  //文件长度100
#define num_OF_datablock  512  //数据磁盘块共计512块
#define num_OF_storage  550  //系统总大小
#define size_OF_block  512  //每个磁盘块大小512B
#define maxnum_OF_openfile  10  //最大可同时打开10个文件
#define size_OF_fileADDRbuffer  100  //文件缓冲池大小

void format();
void write_system(FILE* fp);
void read_system(FILE* fp);
void allocation(int length);
void recycling(int lenghth);
int open(char filename[]);
void close(char filename[]);
void createfile(char filename[], int length, int userID, int limit, struct PathNode* head);
void deletefile(char filename[], struct PathNode* head);
void login();
void show_directory();
void create_directory(char directoryname[], int length, int userID, int limit, struct PathNode* head);
void delete_dirctory(char directory[], struct PathNode* head);
void recycledelete(struct PathNode* head, char directory[]);
void release(int iNode);
void clearADDRbuffer();
void openfile(char* filename, struct PathNode* head);
void closefile(char filename[], struct PathNode* head);
void writefile(char* filename, char* newcontent, struct PathNode* head);
void readfile(char* filename, struct PathNode* head);
void copyfile(struct PathNode* head, char filename[]);
void pastefile(struct PathNode* head);
void cutfile(struct PathNode* head, char filename[]);
void mv(struct PathNode* head, string name);
void searchfile(char* filename, PathNode* head, int depth);
void chdir(struct PathNode* head, string name);


extern int openfile_array[maxnum_OF_openfile];  //可同时打开文件的数组
extern int openfile_array_head;
extern int filetype;  //文件类型，0为目录，1为文件
extern int ADDRbuffer[size_OF_fileADDRbuffer];  //文件地址缓冲区
extern char current_directory[20];  //根目录

extern char new_filename[14];
extern int new_inode_filetype;  //文件类型
extern int new_inode_filelength;  //文件长度

extern int new_inode_limit;  //文件读写权限
extern int new_inode_userID;  //用户标识符
extern char new_content[size_OF_block];
extern int paste_flag;
extern struct PathNode* paste_head;

extern int file_found;  //找到文件数
extern int recursion_flag;  //搜索深度，递归标记

struct block  //每块
{
	int blk_num;  //空闲块个数
	int blk_free[50];  //空闲盘块的地址
	int blk_flag;  //块占用标志
	char txt_content[size_OF_block];  //块上每个字节存放的内容
};

extern struct block storage[num_OF_storage];

struct super_block  //超级块
{
	int sbk_num;  //空闲的盘块数
	int sbk_free[num_OF_superblock];  //放入栈中的空闲块
};

extern struct super_block super_block;

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

extern struct dir_file_block d_or_f[num_OF_datablock];

struct inode  //i节点
{
	int inode_inum;  //i节点号
	int inode_filetype;  //文件类型
	int inode_filelength;  //文件长度
	int inode_fileaddress[length_OF_fileaddress];  //文件的物理块号
	int inode_limit;  //文件读写权限
	int inode_userID;  //用户标识符
};

extern struct inode inodes[num_OF_inode];


