#include "test.h"
#include "FullPath.h"
#include "login.h"

void readfile(char *filename,struct PathNode *head)
{
    int a = Locate(head);
    int i,k;
    for(i=0;i<d_or_f[a].countcount;i++)
    {
        if( strcmp(filename,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_filetype==1 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID )
        {
            int k = 0;
            for(int k=0;k<openfile_array_head;k++)//�Ƿ���openfilearray��
            {
                cout<<k<<endl;
                if(openfile_array[k]==d_or_f[a].dir_list[i].inode)
                {
                    break;
                }
            }
            if(k==openfile_array_head)
            {
                cout<<"���ļ�δ�򿪣��޷���ȡ"<<endl;
                return;
            }

            cout<<endl;
            for(int j=0;j<inode[d_or_f[a].dir_list[i].inode].inode_filelength;j++)  //��ȡ�ļ�����
            {
                for(int k=0;storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k]!='\0';k++)
                {
                    cout<<storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k];
                }
            }
            cout<<endl;
            break;
        }
    }
    if(i==d_or_f[a].countcount)
    {
        cout<<"��ǰĿ¼��û�д��ļ���"<<endl;
    }
}
