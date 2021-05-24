#include "test.h"
#include "FullPath.h"
#include "login.h"

void createfile(char filename[],int length,int userID,int limit,struct PathNode *head)
{
    int a=Locate(head);
    if(d_or_f[a].countcount!=32){
    for(int i=0;i<d_or_f[a].countcount;i++)
    {
        if(strcmp(filename,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID)  //如果已有重名的文件
        {
            cout<<"There is a directory or file with the same name.File creation failed."<<endl;
            return;
        }
    }
    for(int i=0;i<num_OF_inode;i++)
    {
        if(d_or_f[i].df_inum==-1)
        {
            d_or_f[i].df_inum=i;
            strcpy(d_or_f[i].txt_filename,filename);
            //strcpy(d_or_f[i].txt_content,"");
            inode[i].inode_inum=i;
            inode[i].inode_filetype=1;  //文件类型，0为目录文件，1为普通文件
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
            strcpy(d_or_f[temp].dir_list[d_or_f[temp].countcount].filename,filename);
            //d_or_f[temp].dir_list[d_or_f[temp].countcount].filename=filename;
            d_or_f[temp].dir_list[d_or_f[temp].countcount].inode=i;
            d_or_f[temp].countcount++;
            break;
        }
    }
    }else{
    cout<<"full!!!"<<endl;
    }
}


void deletefile(char *filename,struct PathNode *head)
{

    int a=Locate(head);
    int temp,i;
    int tempcount=d_or_f[a].countcount;


    for(i=0;i<d_or_f[a].countcount;i++)
    {
        if( strcmp(filename,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_filetype==1 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID )
        {
            for(int j=0;j<inode[d_or_f[a].dir_list[i].inode].inode_filelength;j++)  //清空文件内容
            {
                for(int k=0;storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k]!='\0';k++)
                {
                    storage[inode[d_or_f[a].dir_list[i].inode].inode_fileaddress[j]].txt_content[k]='\0';
                }
            }

            temp=d_or_f[a].dir_list[i].inode;
            inode[temp].inode_userID=-1;
            inode[temp].inode_limit=-1;
            for(int j=0;j<inode[temp].inode_filelength;j++)
            {
                ADDRbuffer[j]=inode[temp].inode_fileaddress[j];
            }
            recycling(inode[temp].inode_filelength);  //回收被删除文件所占的空间
            for(int j=0;j<size_OF_fileADDRbuffer;j++)
            {
                ADDRbuffer[j]=-1;  //清空文件地址缓冲区
            }

            for(int j=0;j<length_OF_fileaddress;j++)  //回收物理地址
            {
                inode[temp].inode_fileaddress[j]=-1;
            }
            strcpy(d_or_f[a].txt_filename,"");

            strcpy(d_or_f[a].dir_list[i].filename,"");  //初始化目录列表中的所在位置
            //d_or_f[a].dir_list[i].filename="";  //初始化目录列表中的所在位置
            d_or_f[a].dir_list[i].inode=-1;

            d_or_f[a].dir_list[i].inode=-1;  //文件i节点恢复初值
            inode[temp].inode_filelength=-1;
            inode[temp].inode_filetype=-1;

            for(int m=i;m<d_or_f[a].countcount;m++)
            {
                strcpy(d_or_f[a].dir_list[m].filename,d_or_f[a].dir_list[m+1].filename);
               // d_or_f[a].dir_list[m].filename = d_or_f[a].dir_list[m+1].filename;
                d_or_f[a].dir_list[m].inode = d_or_f[a].dir_list[m+1].inode;
            }
            d_or_f[a].countcount--;


            break;
        }
    }
    if(i==tempcount)
    {
        cout<<"This file does not exist in the user's current directory."<<endl;
    }
}








/*
    int temp,i;
    for(i=0;i<num_OF_datablock;i++)
    {
        if( (strcmp(filename,d_or_f[i].txt_filename==0)) && (strcmp(current_directory,root[i].dir_directoryname)==0) && (inode[root[i].dir_inum].inode_userID==login_userID) )
        {
            for(int j=0;j<inode[root[i].dir_inum].inode_filelength;j++)  //清空文件内容
            {
                for(int k=0;storage[inode[root[i].dir_inum].inode_fileaddress[j]].blk_content[k]!='\0';k++)
                {
                    storage[inode[root[i].dir_inum].inode_fileaddress[j]].blk_content[k]='\0';
                }
            }
            temp=root[i].dir_inum;
            inode[temp].inode_userID=-1;
            inode[temp].inode_limit=-1;
            for(int j=0;j<inode[temp].inode_filelength;j++)
            {
                ADDRbuffer[j]=inode[temp].inode_fileaddress[j];
            }
            recycling(inode[temp].inode_filelength);  //回收被删除文件所占的空间
            for(int j=0;j<size_OF_fileADDRbuffer;j++)
            {
                ADDRbuffer[j]=-1;  //清空文件地址缓冲区
            }

            //将删除后的文件属性和目录项的各值恢复到初值
            for(int j=0;j<length_OF_fileaddress;j++)
            {
                inode[temp].inode_fileaddress[j]=-1;
            }
            strcpy(root[i].dir_filename,"");
            root[i].dir_inum=-1;
            strcpy(root[i].dir_directoryname,"");
            inode[temp].inode_filelength=-1;
            inode[temp].inode_filetype=-1;
            break;
        }
    }
    if(i==num_OF_directory)
    {
        cout<<"This file does not exist in the user's current directory."<<endl;
    }
}*/

