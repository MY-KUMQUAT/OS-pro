#include<iostream>
#include<string>
#include<stdio.h>
#include<string.h>
#include<fstream>
#include<cassert>
#include<stdlib.h>

using namespace std;

int checkname(string a);
int checkpassword(string b, int n);
void signin();
void endwriting(const char* yourfile, string a);
int  menu(struct PathNode* head);
int changeuser(string str);
int login(struct PathNode* head);
char* ChangeStrToChar(string InputString);
char* gettext();
void help();

extern int userID;
