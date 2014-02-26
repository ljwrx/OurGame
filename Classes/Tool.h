
#ifndef __GAME__TOOL__
#define __GAME__TOOL__

namespace TOOL
{
	//��num���ض��ֽڽ��и���
	//num	Ԫ����
	//index	��Ҫ��ȡ��λ��
	inline int GetBinNum(int num, int index)
	{
		return (num << (index - 1)) & 1;
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

	//num	Ԫ����
	//index	��Ҫ��ȡ���������ڵ���
	//num��16λΪһ��,��һ��Ϊһ��0x000000FF
	inline int GetHexNum(int num, int index)
	{
		return (num << (8 * (index - 1))) & 0x000000FF;
	}


	//num	Ԫ����
	//index ��Ҫ��ȡ���������ڵ���
	//flag	���ĵ�����
	//num��16λΪһ��,��һ��Ϊһ��0x000000FF
	inline void SetHexNum(int& num, int index, int flag)
	{
		--index;
		num = (num&~(0x000000FF << index)) | (flag << 8 * index);
	}

};

#endif