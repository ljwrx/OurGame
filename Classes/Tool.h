
#pragma once
#ifndef __GAME__TOOL__
#define __GAME__TOOL__

namespace TOOL
{
	//对num中特定字节进行更改
	//num	元数据
	//index	需要获取的位置
	inline int GetBinNum(int num, int index);

	//获取num中特定字节的数据
	//num	元数据
	//index 需要更改的字节位置
	//flag	更改的数据
	inline int SetBinNum(int& num, int index, int flag);

	//num	元数据
	//index	需要获取的数据所在的组
	//num以16位为一组,即一组为一个0x000000FF
	inline int GetHexNum(int num, int index);

	//num	元数据
	//index 需要获取的数据所在的组
	//flag	更改的数据
	//num以16位为一组,即一组为一个0x000000FF
	inline int SetHexNum(int& num, int index, int flag);
};
#endif