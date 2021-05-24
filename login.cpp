#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

int tempLength=1;
int tempLimit=1;

int login(struct PathNode *head)
{
    string a;
    string b;

    int codecorrect=0;
    int returntomenu=0;
    cout<<">>文件管理系统"<<endl;

    while(returntomenu==0||returntomenu==1)
    {
        cout<<">>username:";
        cin>>a;
        userID=checkname(a);//权哥要的用户id（该用户在用户文本中的顺序）
        if(userID==-1)           //没找到用户进入注册操作
        {
            cout<<">>请注册"<<endl;
            signin();
        }
        else//找到用户输入密码登录
        {
            int m=0;
            while(codecorrect==0&&m<3)
            {
                cout<<">>password:";
                cin>>b;
                codecorrect=checkpassword(b,userID);//密码不正确重新输入
                m++;
            }
            codecorrect=0;//每次成功登陆以后将codecorrect归0，重新登陆的时候才能正常输入密码
            if(m<3)
            {
                cout<<"userid="<<userID<<endl;
                returntomenu=menu(head);
            }
            else
                cout<<">>密码三次不正确,强制退出"<<endl;
        }
    }
    return 0;
}

void help()
{
    cout<<"-----------可用命令菜单：------------"<<endl;
    cout<<"           1.createdir                  "<<endl;
    cout<<"           2.createfile                    "<<endl;
    cout<<"           3.deletedir                    "<<endl;
    cout<<"           4.enter                   "<<endl;
    cout<<"           5.cd                   "<<endl;
    cout<<"           6.dir                  "<<endl;
    cout<<"           7.deletefile                   "<<endl;
    cout<<"           8.read                     "<<endl;
    cout<<"           9.write                  "<<endl;
    cout<<"           10.openfile                  "<<endl;
    cout<<"           11.closefile                 "<<endl;
    cout<<"           12.format                 "<<endl;
    cout<<"           12.logout                 "<<endl;
    cout<<"           13.exit                   "<<endl;
    cout<<"           14.changeuser             "<<endl;
    cout<<"           15.copy                   "<<endl;
    cout<<"           16.cut                    "<<endl;
    cout<<"           17.paste                  "<<endl;
    cout<<"           18.help                   "<<endl;
    cout<<"           19.cls                    "<<endl;
    cout<<"模仿dos命令方式"<<endl;
}

int menu(struct PathNode *head)
{

    char a;

    cout<<">>welcome!"<<endl;

    help();

    a=getchar();//防止bug，把之前输入密码是时候的回车接住。

    int flag=0;

    int codenum;
    int n;

        string order("");
        string name("");
    while(flag==0)
    {

        order="";
        name="";

        cout<<endl<<">>";

        string str("");
        char c;

        while((c=cin.get())!='\n')
        {
            str=str+c;
        }
        n=str.find(' ');
        if(n==-1)
        {
            order=str;

            name="";
        }
        else
        {
            order=str.substr(0,n);
            name=str.substr(n+1,str.length());
        }
        //cout<<order<<" "<<name<<" "<<n<<" "<<str.length()<<endl;

       char *inputname;
       inputname=ChangeStrToChar(name);

        //cout<<"测试："<<inputname<<endl;

        if(order=="createdir")
        {
            codenum=0;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                create_directory(inputname,tempLength,userID,tempLimit,head);
                //cout<<">>成功创建目录"<<name<<endl;
        }
        else if(order=="createfile")
        {
            codenum=1;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                createfile(inputname,tempLength,userID,tempLimit,head);
                //cout<<">>成功创建文件"<<name<<endl;
        }
        else if(order=="deletedir")
        {
            codenum=2;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                delete_dirctory(inputname,head);
                //cout<<">>成功删除目录"<<name<<endl;
        }
        else if(order=="enter")
        {
            codenum=3;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                Enter(head,inputname);
                //cout<<">>成功进入目录"<<name<<endl;
        }
        else if(order=="cd"&&name=="..")
        {
            codenum=4;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                ReturnLastLevel(head);
                //cout<<">>成功退出目录到上一级"<<endl;
        }
        else if(order=="dir")
        {
            codenum=5;
            dir(head);
            //cout<<">>成功展示目录"<<endl;
        }
        else if(order=="deletefile")
        {
            codenum=6;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                deletefile(inputname,head);
                //cout<<">>成功删除文件"<<name<<endl;
        }
        else if(order=="read")
        {
            codenum=7;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                readfile(inputname,head);
                //cout<<">>成功读取文件"<<name<<endl;
        }
        else if(order=="write")
        {
            codenum=8;
            if(name=="")
                cout<<"指令不全"<<endl;
            else
            {
                //char *newcontent = "";
                char* newcontent = new(char);
                cin.get(newcontent, 10);
                //cin>>newcontent;
                a=getchar();
                writefile(inputname,newcontent,head);
            }
                //cout<<">>成功写入文件"<<name<<endl;
        }
       else if(order=="openfile")
       {
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                openfile(inputname,head);
                //cout<<">>成功打开文件"<<name<<endl;
       }
       else if(order=="closefile")
       {
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                closefile(inputname,head);
                //cout<<">>暂时无法关闭，请见谅"<<name<<endl;
       }
       else if(order=="format")
       {
            format();
            //cout<<"成功格式化"<<name<<endl;
       }
        else if(order=="logout"&&name=="")
        {
            codenum=13;
            int q=0;

            while(q==0)
            {
                cout<<">>logout and back to login(y/n)?"<<endl;
                string n;
                cin>>n;
                if(n=="y")
                {
                    flag=1;
                    q=1;
                    return 1;     //返回到登录username处
                }
                else if (n=="n")
                {
                   q=1;
                   a=getchar();
                }
                else
                {
                    q=0;
                    cout<<"请用y/n"<<endl;
                }
            }
        }
        else if(order=="exit"&&name=="")//退出系统
        {
            codenum=15;
            int p=0;
            while(p==0)
            {
                cout<<">>退出程序(y/n)?"<<endl;
                string m;
                cin>>m;
                if(m=="y")//退出程序
                {
                    flag=1;
                    return 2;
                }
                else if (m=="n")
                {
                    p=1;
                    a=getchar();
                }
                else
                {
                    p=0;
                    cout<<"请用y/n"<<endl;
                }
            }
        }
        else if(order=="cls")
        {
            system("cls");
            DisplayFullPath(head);
        }
        else if(order=="changeuser")
        {
            int j=0;
            int old;
            old=userID;//保存旧的id，防止切换失败
            j=changeuser(name);
            if(j==997755)
            {
                cout<<">>用户切换失败"<<endl;
                userID=old;//切换失败还原现有的userid;p
            }
            else
            {
                cout<<">>成功切换用户"<<endl;
            }
        }
        else if(order=="help")
        {
            help();
        }
        else if(order=="copy")
       {
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                copyfile(head,inputname);
                //cout<<">>暂时无法关闭，请见谅"<<name<<endl;
       }
       else if(order=="cut")
       {
            if(name=="")
                cout<<"指令不全"<<endl;
            else
                cutfile(head,inputname);
                //cout<<">>暂时无法关闭，请见谅"<<name<<endl;
       }
       else if(order=="paste")
        {
            pastefile(head);
        }
        else
            cout<<">>指令不存在,请重新输入"<<endl;
    }
}

int changeuser(string str)
{
    string user;
    string pass;
    int n;

    int flag;
    n=str.find(' ');

            if(n==-1)
              {
                  cout<<">>指令格式错误"<<endl;
                  return 997755;            //反馈一个不可能出现的数字
              }
            else
            {
                user=str.substr(0,n);
                pass=str.substr(n+1,str.length());
            }
    userID=checkname(user);
    if(userID==-1)
    {
        return 997755;
    }
    else
    {
        flag=checkpassword(pass,userID);
        if(flag==0)
            return 997755;
        return userID;
    }
}

//logincheck
int checkname(string a)//检查用户是否存在
{
    int n=0;
    int id=0;
    int flag=0;
    ifstream test("user.txt",ios::in);

    string str;
    string str2;
    if(!test)
    {
        cout<<"open fail"<<endl;
        id=-2;
    }
    else
   {
    while( getline(test,str) )
    {

        id++;
        if(str==a)
        {
            cout<<"user exists"<<endl;
            flag=1;
            break;

        }
    }

    if(flag==0)
    {
        cout<<"user not exists"<<endl;
        id=-1;
    }

     return id;//返回用户在user.txt所在的行数作为userid
   }
}
int checkpassword(string b,int n)//该用户存在，检查密码是否正确
{   int i=0;
    int flag1=0;
    int codecorrect=0;
    ifstream test("password.txt",ios::in);

    string str;
    string str2;

    if(!test)
    {
        cout<<"open fail"<<endl;
    }
    else
    {


    for(i=0; i<n,getline(test,str);i++ )//code和username行数相对应，要找到用户名对应密码的那一行，先逐行寻找
    {


        if(str==b)
        {
            if(i+1==n)//在文本中找到了密码串，但是要保证是username在user.txt中所排列位置的那一行，如果不是，说明密码错误
            {


            flag1=1;

            cout<<"password correct!"<<endl;

            codecorrect=1;
            break;
            }
        }

      }

      if(flag1==0)
      {
          cout<<"密码错误!"<<endl;

      }
    }
       return codecorrect;
}
void signin()
{
    string a;
    string b;
    string ans;
    int n=0;
    int flag=0;//能够反复输入,如用户名输入重复的情况

    while(flag==0)
   {


    cout<<"your username:"<<endl;
    cin>>a;

        n=checkname(a);
        if(n==-1)//用户名没重复的情况下，可注册
    {
            const char* filename="user.txt";
            const char* filename1="password.txt";


        cout<<"your password:"<<endl;
        cin>>b;
        cout<<"确认注册(y/n)？"<<endl;
        cin>>ans;
        if(ans=="y")
        {
            endwriting(filename,a);
            endwriting(filename1,b);
            flag=1;
        }
        else
            flag=0;
    }
    else//用户名重复，不能注册，重新输入
    {

    }
   }
}
void endwriting(const char* yourfile,string a)//文件尾写入
{
     ofstream out(yourfile,ios::app);
     out<<a<<endl;
}

char* ChangeStrToChar(string InputString)
{
    char *InputChar = new char[InputString.length()];
    int i;
    for(i=0;i <=InputString.length();i++)
        InputChar[i]=InputString[i];
    InputChar[i] = '\0';//将最后一个字符后面的元素置空，否则可能出现奇怪的错误
     return InputChar;
}
