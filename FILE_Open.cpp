#include "test.h"
#include "FullPath.h"
#include "login.h"

void openfile(char *filename,struct PathNode *head)
{
    int a = Locate(head);
    int i;
    for(i=0;i<d_or_f[a].countcount;i++)
    {
        if( strcmp(filename,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_filetype==1 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID )
        {
            if(openfile_array_head<maxnum_OF_openfile)
            {
                openfile_array[openfile_array_head]=d_or_f[a].dir_list[i].inode;
                openfile_array_head++;
            }
            else
            {
                cout<<"Fail to open file due to the upper limit."<<endl;
            }
            break;
        }
    }
    if(i==d_or_f[a].countcount)
    {
        cout<<"The file does not exist or does not belong to the user."<<endl;
    }
}
