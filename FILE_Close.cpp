#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void closefile(char filename[],struct PathNode *head)
{
    int a =Locate(head);
    int i;
    for(i=0;i<d_or_f[a].countcount;i++)
    {
        if( strcmp(filename,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_filetype==1 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID )
        {
            int flag=0;
            for(int j=0;j<openfile_array_head;j++)
            {
                if(d_or_f[a].dir_list[i].inode==openfile_array[j])
                {
                    for(int k=j;k<openfile_array_head;k++)
                    {
                        openfile_array[k]=openfile_array[k+1];
                    }
                    openfile_array_head--;
                    flag=1;
                    return;
                }
            }
            if(flag==0)
            {
                cout<<"The file to be closed has not been opened."<<endl;
            }
            return;
        }
    }
    if(i==d_or_f[a].countcount)
    {
        cout<<"The file does not exist or does not belong to the user."<<endl;
    }
    return;
}
