#include "test.h"
#include "FullPath.h"

void create_directory(char directoryname[],int length,int userID,int limit,struct PathNode *head)
{
    int a = Locate(head);
    if(d_or_f[a].countcount!=32){
    for(int i=0;i<d_or_f[a].countcount;i++)
    {
        if(strcmp(directoryname,d_or_f[a].dir_list[i].filename)==0)  //��������������ļ�
        {
            cout<<"There is a directory or file with the same name.File creation failed."<<endl;
            return;
        }
    }


    for(int i=1;i<num_OF_inode;i++)
    {
        if(d_or_f[i].df_inum==-1)
        {
            d_or_f[i].df_inum=i;
            strcpy(d_or_f[i].dir_directoryname,directoryname);
            //d_or_f[i].dir_list[32][2]="";
            inode[i].inode_inum=i;
            inode[i].inode_filetype=0;  //�ļ����ͣ�0ΪĿ¼�ļ���1Ϊ��ͨ�ļ�
            inode[i].inode_filelength=length;
            inode[i].inode_limit=limit;
            inode[i].inode_userID=userID;
            allocation(length);
            for(int j=0;j<length;j++)
            {
                inode[i].inode_fileaddress[j]=ADDRbuffer[j];
            }
            for(int j=0;j<size_OF_fileADDRbuffer;j++)
            {
                ADDRbuffer[j]=-1;
            }
            int temp=Locate(head);
            strcpy(d_or_f[temp].dir_list[d_or_f[temp].countcount].filename,directoryname);
            //d_or_f[temp].dir_list[d_or_f[temp].countcount].filename=directoryname;
            d_or_f[temp].dir_list[d_or_f[temp].countcount].inode=i;
            d_or_f[temp].countcount++;
            break;
        }
    }
    }else{
    cout<<"full!!!"<<endl;
    }
}