#include "test.h"

void recycling(int length)  //回收磁盘块
{
    for (int i = length;i > 0;i--) {
           // cout<<"recycle "<<super_block.sbk_num<<endl;
		storage[ADDRbuffer[i]].blk_flag = 0;//将相应磁盘块标记为空闲
		if (super_block.sbk_num == 50) {//超级块中已装满50个空闲磁盘块
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
	clearADDRbuffer();//回收完毕，清空缓冲区
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
		if (super_block.sbk_free[0] == -1) {//已经没有空闲磁盘块
			cout << "磁盘空间不足，分配失败！！！" << endl;
			recycling(i - 1);//将之前分配的i-1块回收
		}
		else {//磁盘空间足够
			if (super_block.sbk_num == 1) {//如果占用的磁盘块为栈中仅剩的一个（被占用的磁盘块中存放着下一组空闲磁盘块的地址）
				storage[super_block.sbk_free[0]].blk_flag = 1;//占用当前磁盘块
				ADDRbuffer[i] = super_block.sbk_free[0];//将被占用的磁盘块号存入缓冲区
				super_block.sbk_num--;
				loadNewFreeGroup(super_block.sbk_free[0]);
			}
			else {
				storage[super_block.sbk_free[temp]].blk_flag = 1;//占用当前磁盘块
				ADDRbuffer[i] = super_block.sbk_free[temp];//将被占用的磁盘块号存入缓冲区
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
