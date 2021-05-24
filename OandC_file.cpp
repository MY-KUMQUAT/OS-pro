#include "test.h"
/*
int open(char filename[])
{
    int i;
    for(i=0;i<num_OF_datablock;i++)
    {
        if( (strcmp(root[i].dir_filename,filename)==0) && inode[root[i].dir_inum].inode_filetype==1 /*&& inode[root[i].dir_inum].inode_userID==login_userID)
        {
            if(openfile_array_head<maxnum_OF_openfile)
            {
                openfile_array[openfile_array_head]=root[i].dir_inum;
                openfile_array_head++;
            }
            else
            {
                cout<<"Fail to open file due to the upper limit."<<endl;
            }
            return root[i].dir_inum;
        }
    }
    if(i==num_OF_directory)
    {
        cout<<"The file does not exist or does not belong to the user."<<endl;
    }
    return 0;
}

void close(char filename[])
{
    int i;
    for(i=0;i<num_OF_directory;i++)
    {
        if(strcmp(root[i].dir_filename,filename) && inode[root[i].dir_inum].inode_filetype==1 && inode[root[i].dir_inum].inode_userID==login_userID)
        {
            int j;
            for(j=0;j<openfile_array_head;j++)
            {
                if(root[i].dir_inum==openfile_array[j])
                {
                    for(int k=j;k<openfile_array_head;k++)
                    {
                        openfile_array[k]=openfile_array[k+1];
                    }
                    openfile_array_head--;
                    return;
                }
            }
            if(j==openfile_array_head)
            {
                cout<<"The file to be closed has not been opened."<<endl;
            }
            return;
        }
    }
    if(i==num_OF_directory)
    {
        cout<<"The file does not exist or does not belong to the user."<<endl;
    }
    return;
}
*/
