#include "OS_pro.h"

void write_system(FILE* fp,char* filename)   //将磁盘信息统统写入系统文件中（以二进制文件的形式）
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

void read_system(FILE* fp, char* filename)  //将磁盘信息从系统文件filesystem中读取出来
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
