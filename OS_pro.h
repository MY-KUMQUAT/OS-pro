#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>
#include <regex>
#include <conio.h>

#include "DIRECTORY.h"
#include "DATA_STRUCT.h"
#include "FILE_.h"
#include "SYSTEM_.h"
#include "MENU.h"
#include "LOGIN.h"
#include "OTHER.h"


using namespace std;

extern int openfile_array[maxnum_OF_openfile];  //可同时打开文件的数组
extern int openfile_array_head;
extern int ADDRbuffer[size_OF_fileADDRbuffer];  //文件地址缓冲区

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

extern struct block storage[num_OF_storage];
extern struct userlog user[size_OF_user];
extern struct super_block super_block;
extern struct dir_file_block data_block[num_OF_datablock];
extern struct inode inodes[num_OF_inode];

extern struct userlog user[size_OF_user];
extern int userID;
