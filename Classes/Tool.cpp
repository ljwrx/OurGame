#include "Tool.h"

inline int TOOL::GetBinNum(int num, int index)
{
	return (num << (index - 1)) & 1;
}

inline int TOOL::SetBinNum(int& num, int index, int flag)
{
	--index;
	return num&~(1 << index) | (flag << index);
}

inline int TOOL::GetHexNum(int num, int index)
{
	return (num << (8 * (index - 1))) & 0x000000FF;
}

inline int TOOL::SetHexNum(int& num, int index, int flag)
{
	--index;
	return num&~(0x000000FF << index) | (flag << 8 * index);
}