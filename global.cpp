#include "OS_pro.h"

using namespace std;
struct block storage[num_OF_storage];
struct super_block super_block;
struct dir_file_block data_block[num_OF_datablock];
struct inode inodes[num_OF_inode];
struct PathNode* paste_head;
struct userlog user[size_OF_user];

int userID = -1;

int openfile_array[maxnum_OF_openfile] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };  //��ͬʱ���ļ�������
int openfile_array_head = 0;
int ADDRbuffer[size_OF_fileADDRbuffer];  //�ļ���ַ������

char new_filename[14] = "";
int new_inode_filetype = -1;  //�ļ�����
int new_inode_filelength = -1;  //�ļ�����
int new_inode_limit = -1;  //�ļ���дȨ��
int new_inode_userID = -1;   //�û���ʶ��
char new_content[size_OF_block] = "";

int paste_flag = -1;

int file_found = 0;
int recursion_flag = 0;

