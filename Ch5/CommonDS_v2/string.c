#include "string.h"

StringData *__StrData(String Str)
{ return (StringData *)Str->Element; }

unsigned int __StrPartLen(String Str)
{ return CharArrayLen(__StrData(Str)->Data + __StrData(Str)->Head); }

void __StrTerminateStringAt(String Str, unsigned int Index)
{
	if (Str == NULL || Index < 0 || Index > StringPartSize)
		return;
	
	Index += __StrData(Str)->Head;
	if (Index > StringPartSize)
		return;
	
	__StrData(Str)->Data[Index] = '\0';
}

void __StrShiftToBack(String Str)
{
	if (Str == NULL)
		return;
	
	unsigned int Len = __StrPartLen(Str);
	if (Len + __StrData(Str)->Head != StringPartSize)
	{
		unsigned int Start = StringPartSize - Len;
		memcpy(__StrData(Str)->Data + Start, __StrData(Str)->Data + __StrData(Str)->Head, Len * sizeof(CharType));
		__StrData(Str)->Head = Start;
	}
}

void __StrWhichPartHasIndex(String Str, unsigned int Index, String *Part, unsigned int *Offset)
{
	if (Str == NULL || Index < 1 || Part == NULL || Offset == NULL)
		return;
	
	// Original implementation is based on full strings: all parts are fully used with all head pointed to 0
	/*
	unsigned int LinkedItemCount = Index / StringPartSize;
	if (!(Index % StringPartSize))
		LinkedItemCount -= 1;
	
	fmt::print("[STRING] Part No. {} has index {}, with offset {}.\n", LinkedItemCount, Index, Index % StringPartSize);
	
	for (; LinkedItemCount > 0; LinkedItemCount--)
		if (Str != NULL)
			Str = Str->Next;
		else break;
	
	fmt::print("[STRING] Split occurres in part {} with offset pointed to {}.\n", __StrData(Str)->Data, __StrData(Str)->Data[Index % StringPartSize]);
	
	*Part = Str;
	*Offset = Index % StringPartSize;
	*/
	
	unsigned int Tmp = 0;
	
	for (; Str != NULL && Index > 0;)
	{
		Tmp = __StrPartLen(Str);
		if (Index > Tmp)
			Str = Str->Next;
		else
			Tmp = __StrData(Str)->Head + Index;
		Index -= Min(Tmp, Index);
	}
	
	*Offset = Tmp;
	*Part = Str;
	
	//fmt::print("[STRING] Part No. {} has index {}, with offset {}.\n", i, Index, *Offset);
	//fmt::print("[STRING] Split occurres in part {} with offset pointed to {}.\n", __StrData(*Part)->Data, __StrData(*Part)->Data[*Offset]);
}

void __StrSplitStringIntoTwoParts(String Str, unsigned int Index)
{
	if (Str == NULL || Index < 0)
		return;
	
	String Tmp;
	unsigned int Split;
	__StrWhichPartHasIndex(Str, Index, &Tmp, &Split);
	
	if (Tmp == NULL)
		return;
	
	String Copy = CreateString();
	memcpy(Copy->Element, Tmp->Element, sizeof(StringData));
	
	Copy->Next = Tmp->Next;
	Tmp->Next = Copy;
	
	__StrData(Tmp)->Data[Split] = '\0';
	__StrData(Copy)->Head = Split;
	
	__StrShiftToBack(Tmp);
}

String CreateString()
{
	String Tmp = (String)CreateList();
	PStringData Data = (PStringData)malloc(sizeof(StringData));
	memset(Data, 0, sizeof(StringData));
	Tmp->Element = (void *)Data;
	return Tmp;
}

String CloneString(String Str)
{
	CharType *Buffer = GetCharArray(Str);
	String Tmp = CreateStringFromCharArray(Buffer);
	free(Buffer);
	return Tmp;
}

String CreateStringFromCharArray(const CharType *Str)
{
	if (Str == NULL)
		return NULL;
	
	int TargetLength = CharArrayLen(Str);
	if (TargetLength == 1)
		return NULL;
	
	unsigned int LinkedItemCount = TargetLength / StringPartSize;
	if (TargetLength % StringPartSize)
		LinkedItemCount += 1;
	
	unsigned int Start = (LinkedItemCount - 1) * StringPartSize;
	
	String Tmp = NULL;
	unsigned int CopyLen = TargetLength - Start;
	
	//fmt::print("[STRING] Spliting C-string \"{}\" into {} parts. The last part has {} characters.\n", Str, LinkedItemCount, CopyLen);
	
	for (; LinkedItemCount > 0; LinkedItemCount--)
	{
		String LatestPart = CreateString();
		//fmt::print("Copying the {}th part. String splited from {} to {}, length {}.\n", LinkedItemCount, Start, Start + CopyLen * sizeof(CharType) - 1, CopyLen * sizeof(CharType));
		memcpy(__StrData(LatestPart)->Data, Str + Start, CopyLen * sizeof(CharType));
		LatestPart->Next = Tmp;
		Tmp = LatestPart;
		Start -= StringPartSize;
		CopyLen = StringPartSize;
	}
	
	return Tmp;
}

CharType *GetCharArray(const String Str)
{
	if (Str == NULL)
		return NULL;
	
	unsigned int Length = GetStringLength(Str);
	if (Length == 0)
		Length = 1;
	
	unsigned int CopyLen = Min(StringPartSize, Length);
	unsigned int Start = 0;
	String P;
	
	CharType *CharArray = (CharType *)malloc((Length + 1) * sizeof(CharType));
	memset(CharArray, 0, (Length + 1) * sizeof(CharType));
	
	for (P = Str; P != NULL; P = P->Next)
		if (__StrData(P)->Head < StringPartSize)
		{
			CopyLen -= __StrData(P)->Head;
			memcpy(CharArray + Start, __StrData(P)->Data + __StrData(P)->Head, CopyLen);
			Start += CopyLen;
			CopyLen = StringPartSize;
		}
	
	return CharArray;
}

unsigned int GetStringLength(const String Str)
{
	if (Str == NULL)
		return -1;
	
	unsigned int Length = 0;
	String P;
	
	for (P = Str; P != NULL; P = P->Next)
		if (__StrData(P)->Head < StringPartSize)
			Length += __StrPartLen(P);
	
	return Length;
}

void ClearString(String Str)
{
	if (Str == NULL)
		return;
	
	String P;
	
	for (P = Str; P != NULL; P = P->Next)
		memset(P->Element, 0, sizeof(StringData));
}

void DestroyString(String *Str)
{
	if (Str == NULL || *Str == NULL)
		return;
	
	String P;
	
	for (P = *Str; P != NULL; P = P->Next)
		free(P->Element);
	
	DeleteList((List *)Str);
}

void CopyString(String Dest, const String Src, int Size, int TerminateString)
{
	if (Dest == NULL || Src == NULL)
		return;
	
	String DestCur = Dest, SrcCur = Src, DestPrev = NULL;
	int CopyLen;
	
	if (Size <= 0)
		Size = INT_MAX;
	
	while (SrcCur != NULL)
	{
		if (DestCur == NULL)
			DestPrev->Next = DestCur = CreateString();
		
		CopyLen = Min(Size, __StrPartLen(SrcCur));
		memcpy(__StrData(DestCur)->Data, __StrData(SrcCur)->Data + __StrData(SrcCur)->Head, CopyLen * sizeof(CharType));
		__StrData(DestCur)->Head = 0;
		
		Size -= CopyLen;
		DestPrev = DestCur;
		DestCur = DestCur->Next;
		SrcCur = SrcCur->Next;
	}
	
	if (TerminateString)
	{
		__StrData(DestPrev)->Data[CopyLen] = '\0';
		DestroyString(&(DestPrev->Next));
	}
}

void ConcatString(String First, const String Second)
{
	if (First == NULL || Second == NULL)
		return;
	
	String FirstCur = First, SecondCur = Second;
	while (FirstCur->Next != NULL)
		FirstCur = FirstCur->Next;
	
	__StrShiftToBack(FirstCur);
	
	while (SecondCur != NULL)
	{
		FirstCur->Next = CreateString();
		FirstCur = FirstCur->Next;
		
		memcpy(FirstCur->Element, SecondCur->Element, sizeof(StringData));
		
		SecondCur = SecondCur->Next;
	}
}

void InsertString(String Main, const int Index, const String Insert)
{
	if (Main == NULL || Index < 0 || Insert == NULL)
		return;
	
	__StrSplitStringIntoTwoParts(Main, Index);
	String Concat = Main->Next;
	String InsertClone = CloneString(Insert);
	String InsertCur = InsertClone;
	
	while (InsertCur != NULL)
	{
		Main->Next = CreateString();
		Main = Main->Next;
		
		memcpy(Main->Element, InsertCur->Element, sizeof(StringData));
		
		InsertCur = InsertCur->Next;
	}
	
	Main->Next = Concat;
	DestroyString(&InsertClone);
}

String BruteForcePatternMatch(String Main, const String Pattern);
String KMPPatternMatch(String Main, const String Pattern);

void CopyStringWithCharArray(String Dest, const CharType *Src, int Size, int TerminateString);
void ConcatStringWithCharArray(String First, const CharType *Second);
void InsertStringWithCharArray(String Main, const int Index, const CharType *Insert);
String BruteForcePatternMatchWithCharArray(String Main, const CharType *Pattern);
String KMPPatternMatchWithCharArray(String Main, const CharType *Pattern);