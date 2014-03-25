
#ifndef __GAME__TOOL__
#define __GAME__TOOL__

#include "cocos2d.h"

namespace TOOL
{
	///////////////////////////////////////////////////////////////////////////////
	//////////////		�ֽڲ�������		//////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////

	//��num���ض��ֽڽ��и���
	//num	Ԫ����
	//index	��Ҫ��ȡ��λ��
	inline int GetBinNum(int num, int index)
	{
		return (num >> (index - 1)) & 1;
	}

	//��ȡnum���ض��ֽڵ�����
	//num	Ԫ����
	//index ��Ҫ���ĵ��ֽ�λ��
	//flag	���ĵ�����
	inline void SetBinNum(int& num, int index, int flag)
	{
		--index;
		num = (num&~(1 << index)) | (flag << index);
	}

	
	//��ȡ8λ�ֽ�����
	//num	Ԫ����
	//index	��Ҫ��ȡ���������ڵ���
	//num��8λΪһ��,��һ��Ϊһ��0x000000FF
	inline int GetHexNum(int num, int index)
	{
		return (num >> (8 * (index - 1))) & 0x000000FF;
	}

	//����8λ�ֽ�����
	//num	Ԫ����
	//index ��Ҫ��ȡ���������ڵ���
	//flag	���ĵ�����
	//num��8λΪһ��,��һ��Ϊһ��0x000000FF
	inline void SetHexNum(int& num, int index, int flag)
	{
		--index;
		num = (num&~(0x000000FF << index)) | (flag << 8 * index);
	}


	//��ȡ��16λ����
	inline int GetHigData(int num)
	{
		return num >> 16;
	}

	//num	��Ҫ���ĵ�����
	//data	�޸ĵ�����
	//���ø�16λ����
	inline void SetHigData(int& num, int data)
	{
		num = (num & 0x0000FFFF) | (data << 16);
	}

	//num	��Ҫ���ĵ�����
	//data	�޸ĵ�����
	//���õ�16λ����
	inline void SetLowData(int& num, int data)
	{
		num = (num & 0xFFFF0000) | (data & 0x0000FFFF);
	}

	//��ȡ��16λ����
	inline int GetLowData(int num)
	{
		return num & 0x0000FFFF;
	}

	//��ȡ����λ���ֽ�����
	inline unsigned int GetDataFromSize(unsigned int sor, int size, int begin = 0)
	{
		unsigned int mask = 0xFFFFFFFF;
		mask = ~(mask << size);
		mask = mask << begin;
		return (sor&mask) >> begin;
	}


	//��������λ���ֽ�����
	inline void SetDataFromSize(unsigned int& sor, unsigned int data, int size, int begin = 0)
	{
		unsigned int mask = 0xFFFFFFFF;
		mask = ~(mask << size);
		mask = ~(mask << begin);
		sor = sor&mask | ((data << begin)&mask);
	}





	template <class T>
	inline T* GetDataFromFile(char* fileName, int *size)
	{
		return (T*)(cocos2d::FileUtils::getInstance()->getFileData(fileName, "rb", size));
	}

	template <class T>
	inline void GetDataFromFile(char* fileName, T* data, int size)
	{
		unsigned char* ch = (unsigned char*)data;
		FILE *f = fopen(fileName, "wb");
		if (!fp)
			break;
		fwrite(ch, sizeof(T), size / sizeof(T), fp);
	}


	//����˵Ŀ�ƽ���㷨
	inline float kamake_sqr(float number)
	{
		long i;
		float x, y;
		const float f = 1.5F;
		x = number * 0.5F;
		y = number;
		i = *(long *)&y;
		i = 0x5f3759df - (i >> 1);
		y = *(float *)&i;
		y = y * (f - (x * y * y));
		y = y * (f - (x * y * y));
		return number * y;
	}

	//��������
	inline float PointToPoint(cocos2d::Point p1, cocos2d::Point p2)
	{
		float dx = p1.x - p2.x;
		float dy = p1.y - p2.y;
		return kamake_sqr(dx*dx + dy*dy);
	}

	//��������
	inline float PointToPoint(float x1, float y1, float x2, float y2)
	{
		float dx = x1 - x2;
		float dy = y1 - y2;
		return kamake_sqr(dx*dx + dy*dy);
	}


	//����
	template<class T>
	T Lock(T data)
	{
		return data;
	}

	//����
	template<class T>
	T Unlock(T data)
	{
		return data;
	}

	

};


#endif