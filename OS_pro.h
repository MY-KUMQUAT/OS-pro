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

extern int openfile_array[maxnum_OF_openfile];  //��ͬʱ���ļ�������
extern int openfile_array_head;
extern int ADDRbuffer[size_OF_fileADDRbuffer];  //�ļ���ַ������

extern char new_filename[14];
extern int new_inode_filetype;  //�ļ�����
extern int new_inode_filelength;  //�ļ�����

extern int new_inode_limit;  //�ļ���дȨ��
extern int new_inode_userID;  //�û���ʶ��
extern char new_content[size_OF_block];
extern int paste_flag;
extern struct PathNode* paste_head;

extern int file_found;  //�ҵ��ļ���
extern int recursion_flag;  //������ȣ��ݹ���

extern struct block storage[num_OF_storage];
extern struct userlog user[size_OF_user];
extern struct super_block super_block;
extern struct dir_file_block data_block[num_OF_datablock];
extern struct inode inodes[num_OF_inode];

extern struct userlog user[size_OF_user];
extern int userID;
