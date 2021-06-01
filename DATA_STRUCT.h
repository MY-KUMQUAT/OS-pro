#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <malloc.h>

#define num_OF_superblock  50  //�������еĿ��п���
#define num_OF_inode  512  //i�ڵ����
#define length_OF_fileaddress  100  //�ļ�����100
#define num_OF_datablock  512  //���ݴ��̿鹲��512��
#define num_OF_storage  550  //ϵͳ�ܴ�С
#define size_OF_block  512  //ÿ�����̿��С512B
#define maxnum_OF_openfile  10  //����ͬʱ��10���ļ�
#define size_OF_fileADDRbuffer  100  //�ļ�����ش�С
#define size_OF_user 8

struct PathNode  //Ŀ¼����
{
	char* NodeName;
	int Node_Inode;
	struct PathNode* next;
};

struct userlog //�û�
{
	int uid;
	char password[14];
	char username[14];
};

struct super_block  //������
{
	int sbk_num;  //���е��̿���
	int sbk_free[num_OF_superblock];  //����ջ�еĿ��п�
};

struct block  //ÿ��
{
	int blk_num;  //���п����
	int blk_free[50];  //�����̿�ĵ�ַ
	int blk_flag;  //��ռ�ñ�־
	char txt_content[size_OF_block];  //����ÿ���ֽڴ�ŵ�����
};

struct dir_list
{
	char filename[14];
	int inode;
};

struct dir_file_block
{
	struct dir_list dir_list[32];  //Ŀ¼�б��ļ�����i�ڵ�
	int countcount;//��¼Ŀ¼����Ԫ����������ֵΪ0
	char dir_directoryname[10];  //Ŀ¼����
	int df_inum;  //Ŀ¼���ļ���i�ڵ��
};

struct inode  //i�ڵ�
{
	int inode_inum;  //i�ڵ��
	int inode_filetype;  //�ļ�����
	int inode_filelength;  //�ļ�����
	int inode_fileaddress[length_OF_fileaddress];  //�ļ���������
	int inode_limit;  //�ļ���дȨ��
	int inode_userID[size_OF_user];  //�û���ʶ��
};
