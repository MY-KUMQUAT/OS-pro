#include "test.h"
#include "FullPath.h"
#include "login.h"

void delete_dirctory(char directory[],struct PathNode *head)
{

    //判断是否在当前目录下
    int a=Locate(head);
    int flag=0;
    if(d_or_f[a].countcount>0)
    {
        for(int i=0; i<d_or_f[a].countcount; i++)
        {
            if( strcmp(directory,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID)
            {
                //printf("进入当前目录");
                //Enter(head,directory[]);
                recycledelete(head,directory);
                flag=1;
                break;
            }
            /*else
            {
                cout<<"没有找到对应目录，删除失败1"<<endl;
                //cout<<d_or_f[a].dir_list[i].filename<<inode[d_or_f[a].dir_list[i].inode].inode_filetype<<endl;
                return;
            }*/
        }
        if(flag==0)
        {
            cout<<"没有找到对应目录，删除失败1"<<endl;
            return;
        }
    }
    else
    {
        cout<<"没有找到对应目录，删除失败2"<<endl;
        return;
    }

}

void recycledelete(struct PathNode *head,char directory[])
{
    Enter(head,directory);
    int temp=Locate(head);
    //cout<<"count is="<<d_or_f[temp].countcount<<endl;
    for(int i=0; i<d_or_f[temp].countcount;)
    {
        //cout<<"filename is="<<d_or_f[temp].dir_list[i].filename<<endl;
        int nowstytle=d_or_f[temp].dir_list[i].inode;
        if(inode[nowstytle].inode_filetype==1) //0目录 1文件
        {
            //cout<<"filename is="<<d_or_f[temp].dir_list[i].filename<<endl;
            deletefile(d_or_f[temp].dir_list[i].filename,head);//删除文件
            cout<<"删除成功: "<<d_or_f[temp].dir_list[i].filename<<endl;
        }
        else
        {
            recycledelete(head,d_or_f[temp].dir_list[i].filename);//递归删除目录文件
        }
    }
    ReturnLastLevel(head);//当前目录列表已删除完，从链表中删除该节点
    temp=Locate(head);
    for(int i=0; i<d_or_f[temp].countcount; i++)
    {
        if( strcmp(directory,d_or_f[temp].dir_list[i].filename)==0)
        {
            printf("删除成功!%s",directory);
            release(d_or_f[temp].dir_list[i].inode);
            for(int j=i; j<d_or_f[temp].countcount-1; j++)
            {
                d_or_f[temp].dir_list[j]=d_or_f[temp].dir_list[j+1];
            }
            d_or_f[temp].countcount--;
        }
    }
}

void release(int iNode){
    for(int i=0;i<inode[iNode].inode_filelength;i++){
        ADDRbuffer[i]=inode[iNode].inode_fileaddress[i];
    }
    recycling(inode[iNode].inode_filelength);
    for(int j=0;j<inode[iNode].inode_filelength;j++){
        inode[iNode].inode_fileaddress[j]=-1;
    }
    inode[iNode].inode_filelength=-1;
    inode[iNode].inode_filetype=-1;
    inode[iNode].inode_inum=-1;
    inode[iNode].inode_limit=-1;
    inode[iNode].inode_userID=-1;
}


