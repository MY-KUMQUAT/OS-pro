#include "test.h"
#include "FullPath.h"
#include "login.h"

void writefile(char *filename,char *newcontent,struct PathNode *head)
{
    int a = Locate(head);
    int i,j,k,m;
    for(i=0;i<d_or_f[a].countcount;i++)
    {
        if( strcmp(filename,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_filetype==1 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID )
        {
            for(m=0;m<openfile_array_head;m++)//�Ƿ���openfilearray��
            {
                if(openfile_array[m]==d_or_f[a].dir_list[i].inode)
                {
                    break;
                }
            }
            if(m==openfile_array_head)
            {
                cout<<"���ļ�δ�򿪣��޷���ȡ"<<endl;
                return;
            }

            for(int n=0;n<inode[d_or_f[a].dir_list[i].inode].inode_filelength;n++)  //������ļ�����
            {
                for(int k=0;storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[n]].txt_content[k]!='\0';k++)
                {
                    storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[n]].txt_content[k]='\0';
                }
            }

            for(j=0;j<inode[d_or_f[a].dir_list[i].inode].inode_filelength;j++)  //��д���ļ�����
            {
                for(k=0;newcontent[k+j*size_OF_block]!='\0'&&k<(size_OF_block-1);k++)
                {
                    storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k]=newcontent[k+j*size_OF_block];
                }
                if(newcontent[k+j*size_OF_block]=='\0')
                {
                    storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k]='\0';
                    break;
                }
                else if(k==size_OF_block-1)
                {
                    storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k]='\0';
                }
            }
            break;
        }
    }
    if(i==d_or_f[a].countcount)
    {
        cout<<"The file does not exist or does not belong to the user."<<endl;
    }
}
