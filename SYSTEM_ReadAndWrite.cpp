#include "test.h"

void write_system(FILE *fp)   //��������Ϣͳͳд��ϵͳ�ļ��У��Զ������ļ�����ʽ��
{
    fp=fopen("filesystem","wb");
    for(int i=0;i<num_OF_storage;i++)
    {
        fwrite(&storage[i],sizeof(struct block),1,fp);
    }

    fwrite(&super_block,sizeof(struct super_block),1,fp);

    for(int i=0;i<num_OF_inode;i++)
    {
        fwrite(&inode[i],sizeof(struct inode),1,fp);
    }

    for(int i=0;i<num_OF_datablock;i++)
    {
        fwrite(&d_or_f[i],sizeof(struct dir_file_block),1,fp);
    }

    for(int i=0;i<num_OF_storage;i++)
    {
        fwrite(&storage[i],sizeof(struct block),1,fp);
    }

    fclose(fp);
}

void read_system(FILE *fp)  //��������Ϣ��ϵͳ�ļ�filesystem�ж�ȡ����
{
    fp=fopen("filesystem","rb");
    for(int i=0;i<num_OF_storage;i++)
    {
        fread(&storage[i],sizeof(struct block),1,fp);
    }

    fread(&super_block,sizeof(struct super_block),1,fp);

    for(int i=0;i<num_OF_inode;i++)
    {
        fread(&inode[i],sizeof(struct inode),1,fp);
    }



    for(int i=0;i<num_OF_datablock;i++)
    {
        fread(&d_or_f[i],sizeof(struct dir_file_block),1,fp);
    }

    for(int i=0;i<num_OF_storage;i++)
    {
        fread(&storage[i],sizeof(struct block),1,fp);
    }
    fclose(fp);
}
