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
	char* NodeName; //�ڵ�����
	int Node_Inode; //i�ڵ��
	struct PathNode* next;  //����ָ��
};

struct userlog //�û�
{
	int uid;  //�û�ID
	char password[14]; //�û�����
	char username[14];  //�û���
};

struct super_block  //������
{
	int sbk_num;  //���е��̿���
	int sbk_free[num_OF_superblock];  //����ջ�еĿ��п�
};

struct block  //ÿ��
{
	int blk_num;  //���п����
	int blk_free[num_OF_superblock];  //�����̿�ĵ�ַ
	int blk_flag;  //��ռ�ñ�־
	char txt_content[size_OF_block];  //����ÿ���ֽڴ�ŵ�����
};

struct fcb
{
	char filename[14];  //�ļ���
	int inode;  //i�ڵ��
};

struct dir_file_block
{
	struct fcb fcb[32];  //Ŀ¼�б��ļ�����i�ڵ�
	int countcount;//��¼Ŀ¼����Ԫ������
	char directoryname[10];  //Ŀ¼����
	int df_inode;  //i�ڵ��
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
