#include "OS_pro.h"
#include "FullPath.h"
#include "login.h"

void searchfile(string reg_name, struct PathNode* head, int depth)
{
	if (recursion_flag > depth) return; //��ǰ��ȴ�����������򷵻�
	regex reg;
	try
	{
		regex r(reg_name);
		reg = r;
	}
	catch (std::regex_error e)
	{
		cout << "���������������޷�����!" << endl;
		return;
	}

	int i, a = Locate(head);
	for (i = 0; i < d_or_f[a].countcount; i++)
	{
		string filename = ChangeCharToStr(d_or_f[a].dir_list[i].filename);
		bool ret = regex_match(filename, reg); //����ƥ��
		if (inodes[d_or_f[a].dir_list[i].inode].inode_userID == userID)
		{
			if (ret == 1)
			{
				struct PathNode* p1 = head;
				cout << "/" << p1->NodeName;
				p1 = p1->next;
				while (p1 != NULL)
				{
					cout << "/" << p1->NodeName;
					p1 = p1->next;
				}
				cout << "/" << d_or_f[a].dir_list[i].filename << endl;
				file_found++;
			}
			else if (inodes[d_or_f[a].dir_list[i].inode].inode_filetype == 0)
			{
				recursion_flag++;  //�����ݹ����
				Enter(head, d_or_f[a].dir_list[i].filename);
				searchfile(reg_name, head, depth);
				ReturnLastLevel(head);
				recursion_flag--;
			}
		}
	}
	if (file_found == 0 && recursion_flag == 0)
	{
		cout << "û���Ǹ��ļ���Ŀ¼��" << endl;
	}
	file_found = 0;
	return;
}
