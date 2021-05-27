#include "OS_pro.h"

void format()  //��ʽ������ʼ��
{
	int m;
	super_block.sbk_num = num_OF_superblock;
	for (int i = 0; i < num_OF_superblock; i++)  //��ʼ��������
	{
		super_block.sbk_free[i] = num_OF_superblock - 1 - i;  //����ջ�еĿ��п�
	}

	for (int i = 0; i < num_OF_inode; i++)  //i�ڵ������ʼ��
	{
		for (int j = 0; j < length_OF_fileaddress; j++)
		{
			inodes[i].inode_fileaddress[j] = -1;
		}
		inodes[i].inode_inum = i;
		inodes[i].inode_filelength = -1;
		inodes[i].inode_filetype = -1;
		inodes[i].inode_limit = -1;
		inodes[i].inode_userID = -1;
	}

	for (int i = 1; i < num_OF_datablock; i++)  //Ŀ¼���ļ������ʼ��
	{
		d_or_f[i].df_inum = -1;
		d_or_f[i].countcount = 0;
		strcpy(d_or_f[i].dir_directoryname, "");
	}

	//��ʼ����Ŀ¼
	d_or_f[0].df_inum = -1;
	d_or_f[0].countcount = 0;
	strcpy(d_or_f[0].dir_directoryname, "root");

	for (int i = 0; i < num_OF_storage; i++)
	{
		storage[i].blk_num = 0;
		storage[i].blk_flag = 0;
		for (int j = 0; j < 50; j++)
		{
			storage[i].blk_free[j] = -1;
		}
		for (int j = 1; j < size_OF_block; j++)
		{
			storage[j].txt_content[j] = '\0';
		}
	}

	for (int i = 0; i < num_OF_datablock; i++)  //�������ӷ���֯���п�
	{
		if ((i + 1) % 50 == 0)
		{
			m = i + 1;
			for (int j = 0; j < num_OF_superblock; j++)
			{
				if (m < (num_OF_storage + 1))
				{
					storage[i].blk_free[j] = m;  //��һ��Ŀ��е�ַ
					storage[i].blk_num++;  //��һ��Ŀ��п�ĸ���
					m++;
				}
				else
				{
					storage[i].blk_free[j] = -1;
				}
			}
			storage[i].blk_flag = 0;  //���Ϊδʹ��
			continue;  //�����������ڴ洢��һ���̿���Ϣ�Ĵ��̿����������ѭ��
		}
		for (int j = 0; j < num_OF_superblock; j++)
		{
			storage[i].blk_free[j] = -1;
		}
		storage[i].blk_num = 0;
	}

	for (int n = 0; n < maxnum_OF_openfile; n++)  //��ʼ�����ļ�����
	{
		openfile_array[n] = -1;
	}
	openfile_array_head = 0;

	for (int n = 0; n < size_OF_fileADDRbuffer; n++)  //��ʼ���ļ���ַ������
	{
		ADDRbuffer[n] = -1;
	}

	cout << "��ʽ����ɣ�" << endl;
	cout << "OS-pro�ļ�ϵͳ" << endl;
}
