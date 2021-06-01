#include "OS_pro.h"
#include "login.h"

int main()
{
	struct PathNode* head = InitPathNode();
	head->NodeName = d_or_f[0].dir_directoryname;
	head->Node_Inode = 0;

	paste_head = InitPathNode();
	paste_head->NodeName = d_or_f[0].dir_directoryname;
	paste_head->Node_Inode = 0;

	FILE* fp;
	if ((fp = fopen("filesystem", "rb")) == NULL)
	{
		cout << "磁盘首次格式化——请稍等。。。" << endl;
		Sleep(1000);
		format();
	}
	else
	{
		read_system(fp);
		DisplayFullPath(head);
	}

	login(head);
	write_system(fp);
}
