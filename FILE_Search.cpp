#include "OS_pro.h"
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
	for (i = 0; i < data_block[a].countcount; i++)
	{
		string filename = ChangeCharToStr(data_block[a].fcb[i].filename);
		bool ret = regex_match(filename, reg); //����ƥ��
		if (checkID(inodes[data_block[a].fcb[i].inode].inode_userID))
		{
			if (ret == 1)  //��ӡĿ¼���ļ�
			{
				struct PathNode* p1 = head;
				cout << "/" << p1->NodeName;
				p1 = p1->next;
				while (p1 != NULL)
				{
					cout << "/" << p1->NodeName;
					p1 = p1->next;
				}
				cout << "/" << data_block[a].fcb[i].filename << endl;
				file_found++;
			}
			else if (inodes[data_block[a].fcb[i].inode].inode_filetype == 0)
			{
				recursion_flag++;  //�����ݹ����
				Enter(head, data_block[a].fcb[i].filename);  //������һ��
				searchfile(reg_name, head, depth);  //�ݹ����
				ReturnLastLevel(head);
				recursion_flag--;
			}
		}
	}
	if (file_found == 0 && recursion_flag == 0)
	{
		cout << "û���Ǹ��ļ���Ŀ¼��" << endl;
	}
	return;
}
