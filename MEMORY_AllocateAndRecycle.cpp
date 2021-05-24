#include "test.h"

void recycling(int length)  //���մ��̿�
{
    for (int i = length;i > 0;i--) {
           // cout<<"recycle "<<super_block.sbk_num<<endl;
		storage[ADDRbuffer[i]].blk_flag = 0;//����Ӧ���̿���Ϊ����
		if (super_block.sbk_num == 50) {//����������װ��50�����д��̿�
		   // cout<<"if"<<super_block.sbk_num<<endl;
			for (int j = 0;j < 50;j++) {
				storage[ADDRbuffer[i]].blk_free[j] = super_block.sbk_free[49-j];
				super_block.sbk_free[49-j] = -1;
			}
			storage[ADDRbuffer[i]].blk_num = 50;
			super_block.sbk_num = 1;
			super_block.sbk_free[0] = ADDRbuffer[i];
		}
		else {
              //  cout<<"else"<<endl;
			super_block.sbk_free[super_block.sbk_num] = ADDRbuffer[i];
			super_block.sbk_num++;
		}
    //cout<<"endrecycle "<<super_block.sbk_num<<endl;
	}
	clearADDRbuffer();//������ϣ���ջ�����
}
void clearADDRbuffer() {
	for (int i = 0;i < size_OF_fileADDRbuffer;i++) {
		ADDRbuffer[i] = -1;
	}
}


void allocation(int length)
{
int temp;
	for (int i = 0;i < length;i++) {
		temp = super_block.sbk_num - 1;
		if (super_block.sbk_free[0] == -1) {//�Ѿ�û�п��д��̿�
			cout << "���̿ռ䲻�㣬����ʧ�ܣ�����" << endl;
			recycling(i - 1);//��֮ǰ�����i-1�����
		}
		else {//���̿ռ��㹻
			if (super_block.sbk_num == 1) {//���ռ�õĴ��̿�Ϊջ�н�ʣ��һ������ռ�õĴ��̿��д������һ����д��̿�ĵ�ַ��
				storage[super_block.sbk_free[0]].blk_flag = 1;//ռ�õ�ǰ���̿�
				ADDRbuffer[i] = super_block.sbk_free[0];//����ռ�õĴ��̿�Ŵ��뻺����
				super_block.sbk_num--;
				loadNewFreeGroup(super_block.sbk_free[0]);
			}
			else {
				storage[super_block.sbk_free[temp]].blk_flag = 1;//ռ�õ�ǰ���̿�
				ADDRbuffer[i] = super_block.sbk_free[temp];//����ռ�õĴ��̿�Ŵ��뻺����
				super_block.sbk_free[temp] = -1;
				super_block.sbk_num--;
			}
		}
	}
}
void loadNewFreeGroup(int address) {
	int temp = storage[address].blk_num - 1;
	for (int i = 0;i < storage[address].blk_num;i++) {
		super_block.sbk_free[temp--] = storage[address].blk_free[i];
	}
	super_block.sbk_num = storage[address].blk_num;
}
