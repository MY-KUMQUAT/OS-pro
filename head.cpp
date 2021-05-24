#include "OS_pro.h"


//只是暂时给了个常数，使得系统能先正常运行
int userID=-1;

int openfile_array[maxnum_OF_openfile]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};  //可同时打开文件的数组
int openfile_array_head=0;
int filetype=1;  //文件类型，0为目录，1为文件
int ADDRbuffer[size_OF_fileADDRbuffer];  //文件地址缓冲区
char current_directory[20]="filesystem";  //根目录

char new_filename[14]="";
int new_inode_filetype=-1;  //文件类型
int new_inode_filelength=-1;  //文件长度

int new_inode_limit = -1;  //文件读写权限
int new_inode_userID = -1;   //用户标识符
char new_content[size_OF_block]="";
int paste_flag = -1;
//struct PathNode *paste_head;
