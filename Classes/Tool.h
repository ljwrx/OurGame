
#pragma once
#ifndef __GAME__TOOL__
#define __GAME__TOOL__

namespace TOOL
{
	//��num���ض��ֽڽ��и���
	//num	Ԫ����
	//index	��Ҫ��ȡ��λ��
	inline int GetBinNum(int num, int index);

	//��ȡnum���ض��ֽڵ�����
	//num	Ԫ����
	//index ��Ҫ���ĵ��ֽ�λ��
	//flag	���ĵ�����
	inline int SetBinNum(int& num, int index, int flag);

	//num	Ԫ����
	//index	��Ҫ��ȡ���������ڵ���
	//num��16λΪһ��,��һ��Ϊһ��0x000000FF
	inline int GetHexNum(int num, int index);

	//num	Ԫ����
	//index ��Ҫ��ȡ���������ڵ���
	//flag	���ĵ�����
	//num��16λΪһ��,��һ��Ϊһ��0x000000FF
	inline int SetHexNum(int& num, int index, int flag);
};
#endif