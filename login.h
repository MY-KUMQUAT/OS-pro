#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<cassert>
#include<stdlib.h>

using namespace std;

char* ChangeStrToChar(string InputString);
string ChangeCharToStr(char* InputChar);
char* gettext();
bool file_access(char* filename, PathNode* head);
void help();

void regist(int index);
int dengLu();
bool menu(struct PathNode* head, int index);
int changeUsr(string usrname);
int checkName(string a);
int checkUsrNum();
void login(struct PathNode* head);

bool checkID(int* usrID);

extern struct userlog user[size_OF_user];

extern int userID;
