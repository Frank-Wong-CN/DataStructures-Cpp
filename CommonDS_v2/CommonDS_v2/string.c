#include "string.h"
#include "common.h"

#include <limits.h>

CommonDS_v2_String_StringData *__CommonDS_v2_String_StrData(CommonDS_v2_String Str)
{ return (CommonDS_v2_String_StringData *)Str->Element; }

CommonDS_v2_SizeType __CommonDS_v2_String_StrPartLen(CommonDS_v2_String Str)
{ return CommonDS_v2_CharArrayLen(__CommonDS_v2_String_StrData(Str)->Data + __CommonDS_v2_String_StrData(Str)->Head); }

void __CommonDS_v2_String_StrTerminateStringAt(CommonDS_v2_String Str, CommonDS_v2_SizeType Index)
{
	if (Str == NULL || Index > CommonDS_v2_String_StringPart_Size)
		return;
	
	Index += __CommonDS_v2_String_StrData(Str)->Head;
	if (Index > CommonDS_v2_String_StringPart_Size)
		return;
	
	__CommonDS_v2_String_StrData(Str)->Data[Index] = '\0';
}

void __CommonDS_v2_String_StrShiftToBack(CommonDS_v2_String Str)
{
	if (Str == NULL)
		return;
	
	CommonDS_v2_SizeType Len = __CommonDS_v2_String_StrPartLen(Str);
	CommonDS_v2_SizeType Start = CommonDS_v2_String_StringPart_Size - Len;
	if (Len + __CommonDS_v2_String_StrData(Str)->Head != CommonDS_v2_String_StringPart_Size)
	{
		memcpy(__CommonDS_v2_String_StrData(Str)->Data + Start, __CommonDS_v2_String_StrData(Str)->Data + __CommonDS_v2_String_StrData(Str)->Head, Len * sizeof(CommonDS_v2_CharType));
		__CommonDS_v2_String_StrData(Str)->Head = Start;
	}
	
	memset(__CommonDS_v2_String_StrData(Str)->Data, 48, Start);
}

CommonDS_v2_String __CommonDS_v2_String_StrWhichPartHasIndex(CommonDS_v2_String Str, CommonDS_v2_SizeType Index, CommonDS_v2_String *Part, CommonDS_v2_SizeType *Offset)
{
	if (Str == NULL)
		return NULL;
	
	CommonDS_v2_SizeType CurLen = 0;
	CommonDS_v2_SizeType TotalLen = 0;
	CommonDS_v2_String CurPart;
	
	for (CurPart = Str; CurPart != NULL; CurPart = CurPart->Next)
	{
		CurLen = __CommonDS_v2_String_StrPartLen(CurPart);
		TotalLen += CurLen;
		if (TotalLen > Index)
		{
			if (Offset != NULL)
				*Offset = __CommonDS_v2_String_StrData(CurPart)->Head + CurLen - (TotalLen - Index);
			if (Part != NULL)
				*Part = CurPart;
			return CurPart;
		}
	}
	
	return NULL;
}

CommonDS_v2_String __CommonDS_v2_String_StrSplitStringIntoTwoParts(CommonDS_v2_String Str, CommonDS_v2_SizeType Index)
{
	if (Str == NULL)
		return NULL;
	
	CommonDS_v2_String Tmp = NULL;
	CommonDS_v2_SizeType Split;
	__CommonDS_v2_String_StrWhichPartHasIndex(Str, Index, &Tmp, &Split);
	
	if (Tmp == NULL)
		return NULL;
	
	CommonDS_v2_String Copy = CommonDS_v2_String_CreateString();
	memcpy((void *)Copy->Element, (void *)Tmp->Element, sizeof(CommonDS_v2_String_StringData));
	
	Copy->Next = Tmp->Next;
	Tmp->Next = Copy;
	
	__CommonDS_v2_String_StrData(Tmp)->Data[Split] = '\0';
	__CommonDS_v2_String_StrData(Copy)->Head = Split;
	
	__CommonDS_v2_String_StrShiftToBack(Tmp);
	
	return Tmp;
}

CommonDS_v2_SizeType *__CommonDS_v2_String_CharArrayBuildKMPNextTable(const CommonDS_v2_CharType *Str, CommonDS_v2_SizeType *Length)
{
	if (Str == NULL)
		return NULL;
	
	CommonDS_v2_SizeType Pos = 1, Cnd = 0;
	CommonDS_v2_SizeType Len = CommonDS_v2_CharArrayLen(Str);
	
	if (Len < 1)
		return NULL;
	
	CommonDS_v2_SizeType *T = (CommonDS_v2_SizeType *)malloc(Len * sizeof(CommonDS_v2_SizeType));
	memset(T, 0, Len * sizeof(T));
	
	while (Pos < Len)
		if (Str[Pos] == Str[Cnd])
			T[Pos++] = ++Cnd;
		else if (Cnd == 0)
			T[Pos++] = 0;
		else Cnd = T[Cnd - 1];
	
	if (Length != NULL)
		*Length = Len;
	
	return T;
}

CommonDS_v2_String CommonDS_v2_String_CreateString()
{
	CommonDS_v2_String Tmp = (CommonDS_v2_String)CommonDS_v2_List_CreateList();
	CommonDS_v2_String_PStringData Data = (CommonDS_v2_String_PStringData)malloc(sizeof(CommonDS_v2_String_StringData));
	memset(Data, 0, sizeof(CommonDS_v2_String_StringData));
	Tmp->Element = (CommonDS_v2_PointerSize)Data;
	return Tmp;
}

CommonDS_v2_String CommonDS_v2_String_CloneString(CommonDS_v2_String Str)
{
	CommonDS_v2_CharType *Buffer = CommonDS_v2_String_GetCharArray(Str);
	CommonDS_v2_String Tmp = CommonDS_v2_String_CreateStringFromCharArray(Buffer);
	free(Buffer);
	return Tmp;
}

CommonDS_v2_String CommonDS_v2_String_CreateStringFromCharArray(const CommonDS_v2_CharType *Str)
{
	if (Str == NULL)
		return NULL;
	
	CommonDS_v2_SizeType TargetLength = CommonDS_v2_CharArrayLen(Str);
	if (TargetLength == 1)
		return NULL;
	
	CommonDS_v2_SizeType LinkedItemCount = TargetLength / CommonDS_v2_String_StringPart_Size;
	if (TargetLength % CommonDS_v2_String_StringPart_Size)
		LinkedItemCount += 1;
	
	CommonDS_v2_SizeType Start = (LinkedItemCount - 1) * CommonDS_v2_String_StringPart_Size;
	
	CommonDS_v2_String Tmp = NULL;
	CommonDS_v2_SizeType CopyLen = TargetLength - Start;
	
	for (; LinkedItemCount > 0; LinkedItemCount--)
	{
		CommonDS_v2_String LatestPart = CommonDS_v2_String_CreateString();
		memcpy(__CommonDS_v2_String_StrData(LatestPart)->Data, Str + Start, CopyLen * sizeof(CommonDS_v2_CharType));
		LatestPart->Next = Tmp;
		Tmp = LatestPart;
		Start -= CommonDS_v2_String_StringPart_Size;
		CopyLen = CommonDS_v2_String_StringPart_Size;
	}
	
	return Tmp;
}

CommonDS_v2_CharType *CommonDS_v2_String_GetCharArray(const CommonDS_v2_String Str)
{
	if (Str == NULL)
		return NULL;
	
	CommonDS_v2_SizeType Length = CommonDS_v2_String_GetStringLength(Str);
	CommonDS_v2_SizeType CopyLen = 0;
	CommonDS_v2_SizeType Start = 0;
	CommonDS_v2_String P;
	
	CommonDS_v2_CharType *CharArray = (CommonDS_v2_CharType *)malloc((Length + 1) * sizeof(CommonDS_v2_CharType));
	memset(CharArray, 0, (Length + 1) * sizeof(CommonDS_v2_CharType));
	
	for (P = Str; P != NULL; P = P->Next)
		if (__CommonDS_v2_String_StrData(P)->Head < CommonDS_v2_String_StringPart_Size)
		{
			CopyLen = __CommonDS_v2_String_StrPartLen(P);
			memcpy(CharArray + Start, __CommonDS_v2_String_StrData(P)->Data + __CommonDS_v2_String_StrData(P)->Head, CopyLen * sizeof(CommonDS_v2_CharType));
			Start += CopyLen;
		}
	
	return CharArray;
}

CommonDS_v2_SizeType CommonDS_v2_String_GetStringLength(const CommonDS_v2_String Str)
{
	if (Str == NULL)
		return 0;
	
	CommonDS_v2_SizeType Length = 0;
	CommonDS_v2_String P;
	
	for (P = Str; P != NULL; P = P->Next)
		if (__CommonDS_v2_String_StrData(P)->Head < CommonDS_v2_String_StringPart_Size)
			Length += __CommonDS_v2_String_StrPartLen(P);
	
	return Length;
}

void CommonDS_v2_String_ClearString(CommonDS_v2_String Str)
{
	if (Str == NULL)
		return;
	
	CommonDS_v2_String P;
	
	for (P = Str; P != NULL; P = P->Next)
		memset((void *)P->Element, 0, sizeof(CommonDS_v2_String_StringData));
}

void CommonDS_v2_String_DeleteString(CommonDS_v2_String *Str)
{
	if (Str == NULL || *Str == NULL)
		return;
	
	CommonDS_v2_String P;
	
	for (P = *Str; P != NULL; P = P->Next)
		free((void *)P->Element);
	
	CommonDS_v2_List_DeleteList((CommonDS_v2_List *)Str);
}

void CommonDS_v2_String_CopyString(CommonDS_v2_String Dest, const CommonDS_v2_String Src, CommonDS_v2_SizeType Size, int TerminateString)
{
	if (Dest == NULL || Src == NULL)
		return;
	
	CommonDS_v2_String DestCur = Dest, SrcCur = Src, DestPrev = NULL;
	CommonDS_v2_SizeType CopyLen;
	
	if (Size <= 0)
		Size = ULONG_MAX;
	
	while (SrcCur != NULL)
	{
		if (DestCur == NULL)
			DestPrev->Next = DestCur = CommonDS_v2_String_CreateString();
		
		CopyLen = Min(Size, __CommonDS_v2_String_StrPartLen(SrcCur));
		memcpy(__CommonDS_v2_String_StrData(DestCur)->Data, __CommonDS_v2_String_StrData(SrcCur)->Data + __CommonDS_v2_String_StrData(SrcCur)->Head, CopyLen * sizeof(CommonDS_v2_CharType));
		__CommonDS_v2_String_StrData(DestCur)->Head = 0;
		
		Size -= CopyLen;
		DestPrev = DestCur;
		DestCur = DestCur->Next;
		SrcCur = SrcCur->Next;
	}
	
	if (TerminateString)
	{
		__CommonDS_v2_String_StrData(DestPrev)->Data[CopyLen] = '\0';
		CommonDS_v2_String_DeleteString(&(DestPrev->Next));
	}
}

void CommonDS_v2_String_ConcatString(CommonDS_v2_String First, const CommonDS_v2_String Second)
{
	if (First == NULL || Second == NULL)
		return;
	
	CommonDS_v2_String SecondClone = CommonDS_v2_String_CloneString(Second);
	
	CommonDS_v2_String FirstCur = First, SecondCur = SecondClone;
	while (FirstCur->Next != NULL)
		FirstCur = FirstCur->Next;
	
	__CommonDS_v2_String_StrShiftToBack(FirstCur);
	
	while (SecondCur != NULL)
	{
		FirstCur->Next = CommonDS_v2_String_CreateString();
		FirstCur = FirstCur->Next;
		
		memcpy((void *)FirstCur->Element, (void *)SecondCur->Element, sizeof(CommonDS_v2_String_StringData));
		
		SecondCur = SecondCur->Next;
	}
	
	CommonDS_v2_String_DeleteString(&SecondClone);
}

void CommonDS_v2_String_InsertString(CommonDS_v2_String Main, const CommonDS_v2_SizeType Index, const CommonDS_v2_String Insert)
{
	if (Main == NULL || Index < 0 || Insert == NULL)
		return;
	
	if (Index >= CommonDS_v2_String_GetStringLength(Main))
	{
		CommonDS_v2_String_ConcatString(Main, Insert);
		return;
	}
	
	CommonDS_v2_String InsertClone = CommonDS_v2_String_CloneString(Insert);
	CommonDS_v2_String InsertCur = InsertClone;
	
	Main = __CommonDS_v2_String_StrSplitStringIntoTwoParts(Main, Index);
	CommonDS_v2_String Concat = Main->Next;
	
	while (InsertCur != NULL)
	{
		Main->Next = CommonDS_v2_String_CreateString();
		Main = Main->Next;
		
		memcpy((void *)Main->Element, (void *)InsertCur->Element, sizeof(CommonDS_v2_String_StringData));
		
		InsertCur = InsertCur->Next;
	}
	
	Main->Next = Concat;
	CommonDS_v2_String_DeleteString(&InsertClone);
}

int CommonDS_v2_String_CompareString(CommonDS_v2_String First, CommonDS_v2_String Second) /* Throws */
{
	CommonDS_v2_CharType *SecondStr = CommonDS_v2_String_GetCharArray(Second);
	int Ret = CommonDS_v2_String_CompareCharArray(First, SecondStr);
	
	free(SecondStr);
	return Ret;
}

CommonDS_v2_String CommonDS_v2_String_BruteForcePatternMatch(CommonDS_v2_String Main, const CommonDS_v2_String Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	CommonDS_v2_CharType *PatStr = CommonDS_v2_String_GetCharArray(Pattern);
	CommonDS_v2_String Ret = CommonDS_v2_String_BruteForcePatternMatchWithCharArray(Main, PatStr);
	
	free(PatStr);
	return Ret;
}

CommonDS_v2_String CommonDS_v2_String_KMPPatternMatch(CommonDS_v2_String Main, const CommonDS_v2_String Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	CommonDS_v2_CharType *PatStr = CommonDS_v2_String_GetCharArray(Pattern);
	CommonDS_v2_String Ret = CommonDS_v2_String_KMPPatternMatchWithCharArray(Main, PatStr);
	
	free(PatStr);
	
	return Ret;
}

void CommonDS_v2_String_CopyCharArray(CommonDS_v2_String Dest, const CommonDS_v2_CharType *Src, int Size, int TerminateString)
{
	if (Src == NULL)
		return;
	
	CommonDS_v2_String CharArray = CommonDS_v2_String_CreateStringFromCharArray(Src);
	CommonDS_v2_String_CopyString(Dest, CharArray, Size, TerminateString);
	CommonDS_v2_String_DeleteString(&CharArray);
}

void CommonDS_v2_String_ConcatCharArray(CommonDS_v2_String First, const CommonDS_v2_CharType *Second)
{
	if (Second == NULL)
		return;
	
	CommonDS_v2_String CharArray = CommonDS_v2_String_CreateStringFromCharArray(Second);
	CommonDS_v2_String_ConcatString(First, CharArray);
	CommonDS_v2_String_DeleteString(&CharArray);
}

void CommonDS_v2_String_InsertCharArray(CommonDS_v2_String Main, const int Index, const CommonDS_v2_CharType *Insert)
{
	if (Insert == NULL)
		return;
	
	CommonDS_v2_String CharArray = CommonDS_v2_String_CreateStringFromCharArray(Insert);
	CommonDS_v2_String_InsertString(Main, Index, CharArray);
	CommonDS_v2_String_DeleteString(&CharArray);
}

int CommonDS_v2_String_CompareCharArray(CommonDS_v2_String First, const CommonDS_v2_CharType *Second)
{
	CommonDS_v2_CharType *FirstStr = CommonDS_v2_String_GetCharArray(First);
	
	int Ret = CommonDS_v2_CharArrayCmp(FirstStr, Second);
	
	free(FirstStr);
	return Ret;
}

CommonDS_v2_String CommonDS_v2_String_BruteForcePatternMatchWithCharArray(CommonDS_v2_String Main, const CommonDS_v2_CharType *Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	CommonDS_v2_SizeType PatLen = CommonDS_v2_CharArrayLen(Pattern);
	if (PatLen < 1 || PatLen > CommonDS_v2_String_GetStringLength(Main))
		return NULL;
	
	if (!CommonDS_v2_String_CompareCharArray(Main, Pattern))
		return Main;
		
	CommonDS_v2_CharType *MainStr = CommonDS_v2_String_GetCharArray(Main);
	unsigned int MainPtr, PatPtr, MainCur;
	
	for (MainPtr = 0; MainStr[MainPtr] != '\0'; MainPtr++)
	{			
		for (MainCur = MainPtr, PatPtr = 0; Pattern[PatPtr] != '\0'; PatPtr++, MainCur++)
			if (Pattern[PatPtr] != MainStr[MainCur])
				break;
		if (Pattern[PatPtr] == '\0')
			break;
	}
		
	CommonDS_v2_CharType End = MainStr[MainPtr];
	free(MainStr);
		
	if (End == '\0')
		return NULL;
	else
	{			
		CommonDS_v2_SizeType Offset;
		CommonDS_v2_String Out = __CommonDS_v2_String_StrWhichPartHasIndex(Main, MainPtr, NULL, &Offset);
		if (__CommonDS_v2_String_StrData(Out)->Head == Offset)
			return Out;
		else
			return __CommonDS_v2_String_StrSplitStringIntoTwoParts(Main, MainPtr)->Next;
	}
}

CommonDS_v2_String CommonDS_v2_String_KMPPatternMatchWithCharArray(CommonDS_v2_String Main, const CommonDS_v2_CharType *Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	CommonDS_v2_SizeType PatLen, *NextTable;
	
	NextTable = __CommonDS_v2_String_CharArrayBuildKMPNextTable(Pattern, &PatLen);
	if (!NextTable)
		return NULL;

	CommonDS_v2_CharType *MainStr = CommonDS_v2_String_GetCharArray(Main);
	CommonDS_v2_SizeType MainLen = CommonDS_v2_String_GetStringLength(Main);
	
	CommonDS_v2_SizeType MainPtr = 0, PatPtr = 0;
	
	while (MainPtr != MainLen)
	{
		if (PatPtr == PatLen)
		{
			MainPtr -= PatLen;
			free(NextTable);
			free(MainStr);
			CommonDS_v2_SizeType Offset;
			CommonDS_v2_String Out = __CommonDS_v2_String_StrWhichPartHasIndex(Main, MainPtr, NULL, &Offset);
			if (__CommonDS_v2_String_StrData(Out)->Head == Offset)
				return Out;
			else
				return __CommonDS_v2_String_StrSplitStringIntoTwoParts(Main, MainPtr)->Next;
		}
		else if (MainStr[MainPtr] == Pattern[PatPtr])
			MainPtr++, PatPtr++;
		else if (PatPtr != 0)
			PatPtr = NextTable[PatPtr - 1];
		else
			MainPtr++;
	}
	
	free(NextTable);
	free(MainStr);
	return NULL;
}