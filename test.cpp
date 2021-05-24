//#include "test.h"
//#include "FullPath.h"
//#include "login.h"
//using namespace std;
//struct block storage[num_OF_storage];
//struct super_block super_block;
//struct dir_file_block d_or_f[num_OF_datablock];
//struct inode inode[num_OF_inode];
//struct command cmd[17];
//struct PathNode *paste_head;
//int main()
//{
//    int a,b;
//    struct PathNode *head = InitPathNode();
//    head->NodeName = d_or_f[0].dir_directoryname;
//    head->Node_Inode = 0;
//    //struct PathNode *paste_head;
//    paste_head = InitPathNode();
//    paste_head->NodeName = d_or_f[0].dir_directoryname;
//    paste_head->Node_Inode = 0;
//    //构建文件系统或者导入文件系统
//    FILE *fp;
//    if((fp=fopen("filesystem","rb"))==NULL)
//    {
//        cout<<"cannot open file"<<endl;
//        cout<<"format the disk"<<endl;
//        Sleep(500);
//        format();
//    }
//    else
//    {
//        read_system(fp);
//        DisplayFullPath(head);
//    }
//
//    login(head);
//
//    write_system(fp);
//    //cout<<"an"<<endl;
//}
