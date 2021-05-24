#include "test.h"
#include "FullPath.h"
#include "login.h"

void delete_dirctory(char directory[],struct PathNode *head)
{

    //�ж��Ƿ��ڵ�ǰĿ¼��
    int a=Locate(head);
    int flag=0;
    if(d_or_f[a].countcount>0)
    {
        for(int i=0; i<d_or_f[a].countcount; i++)
        {
            if( strcmp(directory,d_or_f[a].dir_list[i].filename)==0 && inode[d_or_f[a].dir_list[i].inode].inode_userID==userID)
            {
                //printf("���뵱ǰĿ¼");
                //Enter(head,directory[]);
                recycledelete(head,directory);
                flag=1;
                break;
            }
            /*else
            {
                cout<<"û���ҵ���ӦĿ¼��ɾ��ʧ��1"<<endl;
                //cout<<d_or_f[a].dir_list[i].filename<<inode[d_or_f[a].dir_list[i].inode].inode_filetype<<endl;
                return;
            }*/
        }
        if(flag==0)
        {
            cout<<"û���ҵ���ӦĿ¼��ɾ��ʧ��1"<<endl;
            return;
        }
    }
    else
    {
        cout<<"û���ҵ���ӦĿ¼��ɾ��ʧ��2"<<endl;
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
        if(inode[nowstytle].inode_filetype==1) //0Ŀ¼ 1�ļ�
        {
            //cout<<"filename is="<<d_or_f[temp].dir_list[i].filename<<endl;
            deletefile(d_or_f[temp].dir_list[i].filename,head);//ɾ���ļ�
            cout<<"ɾ���ɹ�: "<<d_or_f[temp].dir_list[i].filename<<endl;
        }
        else
        {
            recycledelete(head,d_or_f[temp].dir_list[i].filename);//�ݹ�ɾ��Ŀ¼�ļ�
        }
    }
    ReturnLastLevel(head);//��ǰĿ¼�б���ɾ���꣬��������ɾ���ýڵ�
    temp=Locate(head);
    for(int i=0; i<d_or_f[temp].countcount; i++)
    {
        if( strcmp(directory,d_or_f[temp].dir_list[i].filename)==0)
        {
            printf("ɾ���ɹ�!%s",directory);
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

