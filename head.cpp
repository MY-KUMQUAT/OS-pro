#include "OS_pro.h"


//ֻ����ʱ���˸�������ʹ��ϵͳ������������
int userID=-1;

int openfile_array[maxnum_OF_openfile]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};  //��ͬʱ���ļ�������
int openfile_array_head=0;
int filetype=1;  //�ļ����ͣ�0ΪĿ¼��1Ϊ�ļ�
int ADDRbuffer[size_OF_fileADDRbuffer];  //�ļ���ַ������
char current_directory[20]="filesystem";  //��Ŀ¼

char new_filename[14]="";
int new_inode_filetype=-1;  //�ļ�����
int new_inode_filelength=-1;  //�ļ�����

int new_inode_limit = -1;  //�ļ���дȨ��
int new_inode_userID = -1;   //�û���ʶ��
char new_content[size_OF_block]="";
int paste_flag = -1;
//struct PathNode *paste_head;
