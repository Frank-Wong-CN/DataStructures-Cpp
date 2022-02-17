#ifndef DSV2_CHARTYPE_H
#define DSV2_CHARTYPE_H

typedef char CommonDS_v2_CharType;

CommonDS_v2_SizeType CommonDS_v2_CharArrayLen(const CommonDS_v2_CharType *Arr)
{
	if (Arr == NULL)
		return -1;
	
	CommonDS_v2_SizeType CommonDS_v2_List_Size = 0;
	while (*Arr++)
		CommonDS_v2_List_Size += 1;
	
	return CommonDS_v2_List_Size;
}

int CommonDS_v2_CharArrayCmp(const CommonDS_v2_CharType *A, const CommonDS_v2_CharType *B)
{
	while (*A && (*A == *B))
		A++, B++;
	
	return (*A > *B) - (*A < *B);
}

#endif