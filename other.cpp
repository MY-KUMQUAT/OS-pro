#include "OS_pro.h"

char* ChangeStrToChar(string InputString)
{
	char* InputChar = new char[InputString.length()];
	int i;
	for (i = 0; i <= InputString.length(); i++)
		InputChar[i] = InputString[i];
	InputChar[i] = '\0'; //将最后一个字符后面的元素置空，否则可能出现奇怪的错误
	return InputChar;
}

string ChangeCharToStr(char* InputChar)
{
	string InputString;
	for (int k = 0; InputChar[k] != '\0'; k++)
	{
		InputString += InputChar[k];
	}
	return InputString;
}

char* gettext()
{
	char c = ' ';
	char* newcontent = new(char);
	/*cin.get(newcontent, 10);
	a = getchar();*/
	string newcontent_s = "";
	//getline(cin, newcontent_s);
	while (c = _getch())
	{
		if (c == 27)
			break;
		else if (c == 13)
		{
			cout << endl;
			newcontent_s += '\n';
		}
		else
		{
			cout << c;
			newcontent_s += c;
		}
	}
	newcontent = ChangeStrToChar(newcontent_s);
	return newcontent;
}

void fragment(string& com, string& arg, string input)//输入分词,假设com前无空格
{
	string arg1;
	string arg2;
	int l = input.find(" ");
	com = input.substr(0, l);
	if (l == -1)
	{
		arg = "";
		return;
	}
	int index = 0;
	input = input.substr(l + 1, input.length());
	index = input.find_first_not_of(" ");
	if (index == -1)
	{
		arg = "";
		return;
	}
	input = input.substr(index, input.length());
	int n = input.find(" ");
	arg1 = input.substr(0, n);
	if (n == -1)
	{
		arg = arg1;
		return;
	}
	input = input.substr(n + 1, input.length());
	int m = input.find_first_not_of(" ");
	arg2 = input.substr(m, input.length());
	arg = arg1 + " " + arg2;
}