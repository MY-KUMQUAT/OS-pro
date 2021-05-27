#include "OS_pro.h"

void allocation(int length)
{
	int temp;
	for (int i = 0; i < length; i++) 
	{
		temp = super_block.sbk_num - 1;
		if (super_block.sbk_free[0] == -1) //�Ѿ�û�п��д��̿�
		{
			cout << "���̿ռ䲻�㣬����ʧ�ܣ�" << endl;
			recycling(i - 1); //��֮ǰ�����i-1�����
		}
		else //���̿ռ��㹻
		{
			if (super_block.sbk_num == 1) //���ռ�õĴ��̿�Ϊջ�н�ʣ��һ������ռ�õĴ��̿��д������һ����д��̿�ĵ�ַ��
			{
				storage[super_block.sbk_free[0]].blk_flag = 1; //ռ�õ�ǰ���̿�
				ADDRbuffer[i] = super_block.sbk_free[0]; //����ռ�õĴ��̿�Ŵ��뻺����
				super_block.sbk_num--;

				int temp_add = storage[super_block.sbk_free[0]].blk_num - 1;
				for (int i = 0; i < storage[super_block.sbk_free[0]].blk_num; i++)
				{
					super_block.sbk_free[temp--] = storage[super_block.sbk_free[0]].blk_free[i];
				}
				super_block.sbk_num = storage[super_block.sbk_free[0]].blk_num;
			}
			else 
			{
				storage[super_block.sbk_free[temp]].blk_flag = 1; //ռ�õ�ǰ���̿�
				//cout << "super_block.sbk_num - 1:" << temp << endl;
				//cout << "super_block.sbk_free:" << super_block.sbk_free[temp] << endl;
				ADDRbuffer[i] = super_block.sbk_free[temp]; //����ռ�õĴ��̿�Ŵ��뻺����
				super_block.sbk_free[temp] = -1;
				super_block.sbk_num--;
			}
		}
	}
}

void recycling(int length)  //���մ��̿�
{
	for (int i = 0; i < length; i++) 
	{
		storage[ADDRbuffer[i]].blk_flag = 0;//����Ӧ���̿���Ϊ����
		if (super_block.sbk_num == 50) //����������װ��50�����д��̿�
		{
			for (int j = 0; j < 50; j++) 
			{
				storage[ADDRbuffer[i]].blk_free[j] = super_block.sbk_free[49 - j];
				super_block.sbk_free[49 - j] = -1;
			}
			storage[ADDRbuffer[i]].blk_num = 50;
			super_block.sbk_num = 1;
			super_block.sbk_free[0] = ADDRbuffer[i];
		}
		else {
			super_block.sbk_free[super_block.sbk_num] = ADDRbuffer[i];
			super_block.sbk_num++;
			//cout << "super_block.sbk_num" << super_block.sbk_num << endl;
			//cout << "super_block.sbk_free" << ADDRbuffer[i] << endl;
		}
	}
	clearADDRbuffer();//������ϣ���ջ�����
}

void clearADDRbuffer() //��ջ�����
{
	for (int i = 0; i < size_OF_fileADDRbuffer; i++) 
	{
		ADDRbuffer[i] = -1;
	}
}

