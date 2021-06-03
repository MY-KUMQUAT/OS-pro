#include "OS_pro.h"
#include "login.h"

int main()
{
	struct PathNode* head = InitPathNode();
	head->NodeName = data_block[0].directoryname;
	head->Node_Inode = 0;

	paste_head = InitPathNode();
	paste_head->NodeName = data_block[0].directoryname;
	paste_head->Node_Inode = 0;

	FILE* fp;
	FILE* fbak = NULL;

	char sys[] = "filesystem";
	char bak[] = "filesystem.bak";

	if ((fp = fopen("filesystem", "rb")) == NULL)
	{
		cout << "磁盘首次格式化——请稍等。。。" << endl;
		Sleep(1000);
		format();
	}
	else
	{
		read_system(fp,sys);
		DisplayFullPath(head);
	}

	login(head);
	write_system(fp, sys);
	write_system(fp, bak);
}
