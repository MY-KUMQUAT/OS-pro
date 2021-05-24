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
    cout<<">>�ļ�����ϵͳ"<<endl;

    while(returntomenu==0||returntomenu==1)
    {
        cout<<">>username:";
        cin>>a;
        userID=checkname(a);//Ȩ��Ҫ���û�id�����û����û��ı��е�˳��
        if(userID==-1)           //û�ҵ��û�����ע�����
        {
            cout<<">>��ע��"<<endl;
            signin();
        }
        else//�ҵ��û����������¼
        {
            int m=0;
            while(codecorrect==0&&m<3)
            {
                cout<<">>password:";
                cin>>b;
                codecorrect=checkpassword(b,userID);//���벻��ȷ��������
                m++;
            }
            codecorrect=0;//ÿ�γɹ���½�Ժ�codecorrect��0�����µ�½��ʱ�����������������
            if(m<3)
            {
                cout<<"userid="<<userID<<endl;
                returntomenu=menu(head);
            }
            else
                cout<<">>�������β���ȷ,ǿ���˳�"<<endl;
        }
    }
    return 0;
}

void help()
{
    cout<<"-----------��������˵���------------"<<endl;
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
    cout<<"ģ��dos���ʽ"<<endl;
}

int menu(struct PathNode *head)
{

    char a;

    cout<<">>welcome!"<<endl;

    help();

    a=getchar();//��ֹbug����֮ǰ����������ʱ��Ļس���ס��

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

        //cout<<"���ԣ�"<<inputname<<endl;

        if(order=="createdir")
        {
            codenum=0;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                create_directory(inputname,tempLength,userID,tempLimit,head);
                //cout<<">>�ɹ�����Ŀ¼"<<name<<endl;
        }
        else if(order=="createfile")
        {
            codenum=1;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                createfile(inputname,tempLength,userID,tempLimit,head);
                //cout<<">>�ɹ������ļ�"<<name<<endl;
        }
        else if(order=="deletedir")
        {
            codenum=2;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                delete_dirctory(inputname,head);
                //cout<<">>�ɹ�ɾ��Ŀ¼"<<name<<endl;
        }
        else if(order=="enter")
        {
            codenum=3;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                Enter(head,inputname);
                //cout<<">>�ɹ�����Ŀ¼"<<name<<endl;
        }
        else if(order=="cd"&&name=="..")
        {
            codenum=4;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                ReturnLastLevel(head);
                //cout<<">>�ɹ��˳�Ŀ¼����һ��"<<endl;
        }
        else if(order=="dir")
        {
            codenum=5;
            dir(head);
            //cout<<">>�ɹ�չʾĿ¼"<<endl;
        }
        else if(order=="deletefile")
        {
            codenum=6;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                deletefile(inputname,head);
                //cout<<">>�ɹ�ɾ���ļ�"<<name<<endl;
        }
        else if(order=="read")
        {
            codenum=7;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                readfile(inputname,head);
                //cout<<">>�ɹ���ȡ�ļ�"<<name<<endl;
        }
        else if(order=="write")
        {
            codenum=8;
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
            {
                //char *newcontent = "";
                char* newcontent = new(char);
                cin.get(newcontent, 10);
                //cin>>newcontent;
                a=getchar();
                writefile(inputname,newcontent,head);
            }
                //cout<<">>�ɹ�д���ļ�"<<name<<endl;
        }
       else if(order=="openfile")
       {
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                openfile(inputname,head);
                //cout<<">>�ɹ����ļ�"<<name<<endl;
       }
       else if(order=="closefile")
       {
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                closefile(inputname,head);
                //cout<<">>��ʱ�޷��رգ������"<<name<<endl;
       }
       else if(order=="format")
       {
            format();
            //cout<<"�ɹ���ʽ��"<<name<<endl;
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
                    return 1;     //���ص���¼username��
                }
                else if (n=="n")
                {
                   q=1;
                   a=getchar();
                }
                else
                {
                    q=0;
                    cout<<"����y/n"<<endl;
                }
            }
        }
        else if(order=="exit"&&name=="")//�˳�ϵͳ
        {
            codenum=15;
            int p=0;
            while(p==0)
            {
                cout<<">>�˳�����(y/n)?"<<endl;
                string m;
                cin>>m;
                if(m=="y")//�˳�����
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
                    cout<<"����y/n"<<endl;
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
            old=userID;//����ɵ�id����ֹ�л�ʧ��
            j=changeuser(name);
            if(j==997755)
            {
                cout<<">>�û��л�ʧ��"<<endl;
                userID=old;//�л�ʧ�ܻ�ԭ���е�userid;p
            }
            else
            {
                cout<<">>�ɹ��л��û�"<<endl;
            }
        }
        else if(order=="help")
        {
            help();
        }
        else if(order=="copy")
       {
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                copyfile(head,inputname);
                //cout<<">>��ʱ�޷��رգ������"<<name<<endl;
       }
       else if(order=="cut")
       {
            if(name=="")
                cout<<"ָ�ȫ"<<endl;
            else
                cutfile(head,inputname);
                //cout<<">>��ʱ�޷��رգ������"<<name<<endl;
       }
       else if(order=="paste")
        {
            pastefile(head);
        }
        else
            cout<<">>ָ�����,����������"<<endl;
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
                  cout<<">>ָ���ʽ����"<<endl;
                  return 997755;            //����һ�������ܳ��ֵ�����
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
int checkname(string a)//����û��Ƿ����
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

     return id;//�����û���user.txt���ڵ�������Ϊuserid
   }
}
int checkpassword(string b,int n)//���û����ڣ���������Ƿ���ȷ
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


    for(i=0; i<n,getline(test,str);i++ )//code��username�������Ӧ��Ҫ�ҵ��û�����Ӧ�������һ�У�������Ѱ��
    {


        if(str==b)
        {
            if(i+1==n)//���ı����ҵ������봮������Ҫ��֤��username��user.txt��������λ�õ���һ�У�������ǣ�˵���������
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
          cout<<"�������!"<<endl;

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
    int flag=0;//�ܹ���������,���û��������ظ������

    while(flag==0)
   {


    cout<<"your username:"<<endl;
    cin>>a;

        n=checkname(a);
        if(n==-1)//�û���û�ظ�������£���ע��
    {
            const char* filename="user.txt";
            const char* filename1="password.txt";


        cout<<"your password:"<<endl;
        cin>>b;
        cout<<"ȷ��ע��(y/n)��"<<endl;
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
    else//�û����ظ�������ע�ᣬ��������
    {

    }
   }
}
void endwriting(const char* yourfile,string a)//�ļ�βд��
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
    InputChar[i] = '\0';//�����һ���ַ������Ԫ���ÿգ�������ܳ�����ֵĴ���
     return InputChar;
}
