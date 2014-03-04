
#ifndef __GAME__TOOL__
#define __GAME__TOOL__

namespace TOOL
{
	//对num中特定字节进行更改
	//num	元数据
	//index	需要获取的位置
	inline int GetBinNum(int num, int index)
	{
		return (num >> (index - 1)) & 1;
	}


	//获取num中特定字节的数据
	//num	元数据
	//index 需要更改的字节位置
	//flag	更改的数据
	inline void SetBinNum(int& num, int index, int flag)
	{
		--index;
		num = (num&~(1 << index)) | (flag << index);
	}

	//num	元数据
	//index	需要获取的数据所在的组
	//num以16位为一组,即一组为一个0x000000FF
	inline int GetHexNum(int num, int index)
	{
		return (num >> (8 * (index - 1))) & 0x000000FF;
	}


	//num	元数据
	//index 需要获取的数据所在的组
	//flag	更改的数据
	//num以16位为一组,即一组为一个0x000000FF
	inline void SetHexNum(int& num, int index, int flag)
	{
		--index;
		num = (num&~(0x000000FF << index)) | (flag << 8 * index);
	}


	//获取高位数据
	inline int GetHigData(int num)
	{
		return num >> 16;
	}

	//获取低位数据
	inline int GetLowData(int num)
	{
		return num & 0x0000FFFF;
	}

	//num	需要更改的数据
	//flag	0为低位 1为高位
	//设置高位数据
	inline void SetHigOrLowData(int& num, int data, int flag)
	{
		num = (num & (0xFFFF0000 >> (16 * flag))) | (flag << (16 * flag));
	}
};


#endif