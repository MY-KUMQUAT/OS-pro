//#ifndef  TEST
//#define  TEST


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>
using namespace std;

#define num_OF_superblock  50  //�������еĿ��п���
#define num_OF_inode  512  //i�ڵ����
#define length_OF_fileaddress  100  //�ļ�����100�ֽ�
#define num_OF_datablock  512  //���ݴ��̿鹲��512��
#define num_OF_storage  550  //ϵͳ�ܴ�С
#define size_OF_block  512  //ÿ�����̿��С512B
#define maxnum_OF_openfile  10  //����ͬʱ��10���ļ�
#define size_OF_fileADDRbuffer  100  //�ļ�����ش�С

void format();
void write_system(FILE *fp);
void read_system(FILE *fp);
void allocation(int length);
void recycling(int lenghth);
int open(char filename[]);
void close(char filename[]);
void createfile(char filename[],int length,int userID,int limit,struct PathNode *head);
void deletefile(char filename[],struct PathNode *head);
void login();
void show_directory();
void create_directory(char directoryname[],int length,int userID,int limit,struct PathNode *head);
void delete_dirctory(char directory[],struct PathNode *head);
void recycledelete(struct PathNode *head,char directory[]);
void release(int iNode);
void clearADDRbuffer();
void loadNewFreeGroup(int address);
void openfile(char *filename,struct PathNode *head);
void closefile(char filename[],struct PathNode *head);
void writefile(char *filename,char *newcontent,struct PathNode *head);
void readfile(char *filename,struct PathNode *head);

void copyfile(struct PathNode *head,char filename[]);

void pastefile(struct PathNode *head);

void cutfile(struct PathNode *head,char filename[]);

//ֻ����ʱ���˸�������ʹ��ϵͳ������������
//extern int login_userID;
extern int openfile_array[maxnum_OF_openfile];  //��ͬʱ���ļ�������
extern int openfile_array_head;
extern int filetype;  //�ļ����ͣ�0ΪĿ¼��1Ϊ�ļ�
extern int ADDRbuffer[size_OF_fileADDRbuffer];  //�ļ���ַ������
extern char current_directory[20];  //��Ŀ¼

//extern int inode_inum;  //i�ڵ��
//extern int inode_fileaddress[length_OF_fileaddress];  //�ļ����������
   extern char new_filename[14];
   extern int new_inode_filetype;  //�ļ�����
   extern int new_inode_filelength;  //�ļ�����

   extern int new_inode_limit;  //�ļ���дȨ��
   extern int new_inode_userID;  //�û���ʶ��
    extern char new_content[size_OF_block];
    extern int paste_flag;
    extern struct PathNode *paste_head;
struct block  //ÿ��
{
    int blk_num;  //���п����
    int blk_free[50];  //�����̿�ĵ�ַ
    int blk_flag;  //��ռ�ñ�־
    char txt_content[size_OF_block];  //����ÿ���ֽڴ�ŵ�����
};

extern struct block storage[num_OF_storage];

struct super_block  //������
{
    int sbk_num;  //���е��̿���
    int sbk_free[num_OF_superblock];  //����ջ�еĿ��п�
};

extern struct super_block super_block;

struct dir_list
{
    char filename[14];
    int inode;
};

struct dir_file_block
{
    struct dir_list dir_list[32];  //Ŀ¼�б����ļ�����i�ڵ�
    int countcount;//��¼Ŀ¼����Ԫ����������ֵΪ0
    char dir_directoryname[10];  //Ŀ¼����

    int df_inum;  //Ŀ¼���ļ���i�ڵ��

    char txt_filename[10];  //�ļ�����
};

extern struct dir_file_block d_or_f[num_OF_datablock];

struct inode  //i�ڵ�
{
    int inode_inum;  //i�ڵ��
    int inode_filetype;  //�ļ�����
    int inode_filelength;  //�ļ�����
    int inode_fileaddress[length_OF_fileaddress];  //�ļ����������
    int inode_limit;  //�ļ���дȨ��
    int inode_userID;  //�û���ʶ��
};

extern struct inode inode[num_OF_inode];

struct command  //������
{
    char cmd_cmdname[10];  //��������
};

extern struct command cmd[17];





//#endif