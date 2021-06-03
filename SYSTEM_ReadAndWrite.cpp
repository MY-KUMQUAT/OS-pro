#include "OS_pro.h"

void write_system(FILE* fp,char* filename)   //��������Ϣͳͳд��ϵͳ�ļ��У��Զ������ļ�����ʽ��
{
	fp = fopen(filename, "wb");
	for (int i = 0; i < num_OF_storage; i++)
	{
		fwrite(&storage[i], sizeof(struct block), 1, fp);
	}

	for (int i = 0; i < size_OF_user; i++)
	{
		fwrite(&user[i], sizeof(struct userlog), 1, fp);
	}

	fwrite(&super_block, sizeof(struct super_block), 1, fp);

	for (int i = 0; i < num_OF_inode; i++)
	{
		fwrite(&inodes[i], sizeof(struct inode), 1, fp);
	}

	for (int i = 0; i < num_OF_datablock; i++)
	{
		fwrite(&data_block[i], sizeof(struct dir_file_block), 1, fp);
	}

	for (int i = 0; i < num_OF_storage; i++)
	{
		fwrite(&storage[i], sizeof(struct block), 1, fp);
	}

	fclose(fp);
}

void read_system(FILE* fp, char* filename)  //��������Ϣ��ϵͳ�ļ�filesystem�ж�ȡ����
{
	fp = fopen(filename, "rb");
	for (int i = 0; i < num_OF_storage; i++)
	{
		fread(&storage[i], sizeof(struct block), 1, fp);
	}

	for (int i = 0; i < size_OF_user; i++)
	{
		fread(&user[i], sizeof(struct userlog), 1, fp);
	}

	fread(&super_block, sizeof(struct super_block), 1, fp);

	for (int i = 0; i < num_OF_inode; i++)
	{
		fread(&inodes[i], sizeof(struct inode), 1, fp);
	}

	for (int i = 0; i < num_OF_datablock; i++)
	{
		fread(&data_block[i], sizeof(struct dir_file_block), 1, fp);
	}

	for (int i = 0; i < num_OF_storage; i++)
	{
		fread(&storage[i], sizeof(struct block), 1, fp);
	}
	fclose(fp);
}
