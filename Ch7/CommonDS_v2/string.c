#include "string.h"
#include "../Ch3/CommonDS_v2/common.h"

#include <limits.h>

StringData *__StrData(String Str)
{ return (StringData *)Str->Element; }

unsigned int __StrPartLen(String Str)
{ return CharArrayLen(__StrData(Str)->Data + __StrData(Str)->Head); }

void __StrTerminateStringAt(String Str, unsigned int Index)
{
	if (Str == NULL || Index > StringPartSize)
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
	unsigned int Start = StringPartSize - Len;
	if (Len + __StrData(Str)->Head != StringPartSize)
	{
		memcpy(__StrData(Str)->Data + Start, __StrData(Str)->Data + __StrData(Str)->Head, Len * sizeof(CharType));
		__StrData(Str)->Head = Start;
	}
	
	memset(__StrData(Str)->Data, 48, Start);
}

String __StrWhichPartHasIndex(String Str, unsigned int Index, String *Part, unsigned int *Offset)
{
	if (Str == NULL)
		return NULL;
	
	unsigned int CurLen = 0;
	unsigned int TotalLen = 0;
	String CurPart;
	
	for (CurPart = Str; CurPart != NULL; CurPart = CurPart->Next)
	{
		CurLen = __StrPartLen(CurPart);
		TotalLen += CurLen;
		if (TotalLen > Index)
		{
			if (Offset != NULL)
				*Offset = __StrData(CurPart)->Head + CurLen - (TotalLen - Index);
			if (Part != NULL)
				*Part = CurPart;
			return CurPart;
		}
	}
	
	return NULL;
}

String __StrSplitStringIntoTwoParts(String Str, unsigned int Index)
{
	if (Str == NULL)
		return NULL;
	
	String Tmp = NULL;
	unsigned int Split;
	__StrWhichPartHasIndex(Str, Index, &Tmp, &Split);
	
	if (Tmp == NULL)
		return NULL;
	
	D("[{}] Spliting string \"{}\" at index {}.\n", __FUNCTION__, __StrData(Tmp)->Data, Index);
	
	String Copy = CreateString();
	memcpy((void *)Copy->Element, (void *)Tmp->Element, sizeof(StringData));
	
	Copy->Next = Tmp->Next;
	Tmp->Next = Copy;
	
	__StrData(Tmp)->Data[Split] = '\0';
	__StrData(Copy)->Head = Split;
	
	__StrShiftToBack(Tmp);
	
	return Tmp;
}

void __StrPrint(String Str)
{
	String Cur = Str;
	int i = 0;
	for (; Cur != NULL; Cur = Cur->Next, i++)
		__StrClingOutput("%s", "{}", __StrData(Cur)->Data + __StrData(Cur)->Head);
	__StrClingOutput("%c", " ", '\n');
}

void __StrPrintPart(String Str)
{
	String Cur = Str;
	int i = 0;
	int j = 0;
	for (; Cur != NULL; Cur = Cur->Next, i++)
	{
		__StrClingOutput("Part %02d: %s#%03d#\n", "Part {:02d}: {}#{:03d}#\n", i + 1, __StrData(Cur)->Data, StringPartSize);
		for (j = 0; j < __StrData(Cur)->Head + 9; j++)
			__StrClingOutput("%c", "{}", ' ');
		__StrClingOutput("^ (%d)\n", "^ ({})\n", __StrData(Cur)->Head);
	}
}

unsigned int *__CharArrayBuildKMPNextTable(const CharType *Str, unsigned int *Length)
{
	if (Str == NULL)
		return NULL;
	
	unsigned int Pos = 1, Cnd = 0;
	unsigned int Len = CharArrayLen(Str);
	
	if (Len < 1)
		return NULL;
	
	unsigned int *T = (unsigned int *)malloc(Len * sizeof(int));
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

String CreateString()
{
	String Tmp = (String)CreateList();
	PStringData Data = (PStringData)malloc(sizeof(StringData));
	memset(Data, 0, sizeof(StringData));
	Tmp->Element = (unsigned long long)Data;
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
	
	D("[{}] Spliting C-string \"{}\" into {} parts. The last part has {} characters.\n", __FUNCTION__, Str, LinkedItemCount, CopyLen);
	
	for (; LinkedItemCount > 0; LinkedItemCount--)
	{
		D("[{}] Copying the {}th part. String splited from {} to {}, length {}.\n", __FUNCTION__, LinkedItemCount, Start, Start + CopyLen * sizeof(CharType) - 1, CopyLen * sizeof(CharType));
		
		String LatestPart = CreateString();
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
	unsigned int CopyLen = 0;
	unsigned int Start = 0;
	String P;
	
	CharType *CharArray = (CharType *)malloc((Length + 1) * sizeof(CharType));
	memset(CharArray, 0, (Length + 1) * sizeof(CharType));
	
	for (P = Str; P != NULL; P = P->Next)
		if (__StrData(P)->Head < StringPartSize)
		{
			CopyLen = __StrPartLen(P);
			memcpy(CharArray + Start, __StrData(P)->Data + __StrData(P)->Head, CopyLen * sizeof(CharType));
			Start += CopyLen;
		}
	
	return CharArray;
}

unsigned int GetStringLength(const String Str)
{
	if (Str == NULL)
		return 0;
	
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
		memset((void *)P->Element, 0, sizeof(StringData));
}

void DestroyString(String *Str)
{
	if (Str == NULL || *Str == NULL)
		return;
	
	String P;
	
	for (P = *Str; P != NULL; P = P->Next)
		free((void *)P->Element);
	
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
	
	String SecondClone = CloneString(Second);
	
	String FirstCur = First, SecondCur = SecondClone;
	while (FirstCur->Next != NULL)
		FirstCur = FirstCur->Next;
	
	__StrShiftToBack(FirstCur);
	
	while (SecondCur != NULL)
	{
		FirstCur->Next = CreateString();
		FirstCur = FirstCur->Next;
		
		memcpy((void *)FirstCur->Element, (void *)SecondCur->Element, sizeof(StringData));
		
		SecondCur = SecondCur->Next;
	}
	
	DestroyString(&SecondClone);
}

void InsertString(String Main, const int Index, const String Insert)
{
	if (Main == NULL || Index < 0 || Insert == NULL)
		return;
	
	if (Index >= GetStringLength(Main))
	{
		ConcatString(Main, Insert);
		return;
	}
	
	String InsertClone = CloneString(Insert);
	String InsertCur = InsertClone;
	
	Main = __StrSplitStringIntoTwoParts(Main, Index);
	String Concat = Main->Next;
	
	while (InsertCur != NULL)
	{
		Main->Next = CreateString();
		Main = Main->Next;
		
		memcpy((void *)Main->Element, (void *)InsertCur->Element, sizeof(StringData));
		
		InsertCur = InsertCur->Next;
	}
	
	Main->Next = Concat;
	DestroyString(&InsertClone);
}

int CompareString(String First, String Second) /* Throws */
{
	CharType *SecondStr = GetCharArray(Second);
	int Ret = CompareCharArray(First, SecondStr);
	
	free(SecondStr);
	return Ret;
}

String BruteForcePatternMatch(String Main, const String Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	CharType *PatStr = GetCharArray(Pattern);
	String Ret = BruteForcePatternMatchWithCharArray(Main, PatStr);
	
	free(PatStr);
	return Ret;
}

String KMPPatternMatch(String Main, const String Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	CharType *PatStr = GetCharArray(Pattern);
	String Ret = KMPPatternMatchWithCharArray(Main, PatStr);
	
	free(PatStr);
	
	return Ret;
}

void CopyCharArray(String Dest, const CharType *Src, int Size, int TerminateString)
{
	if (Src == NULL)
		return;
	
	String CharArray = CreateStringFromCharArray(Src);
	CopyString(Dest, CharArray, Size, TerminateString);
	DestroyString(&CharArray);
}

void ConcatCharArray(String First, const CharType *Second)
{
	if (Second == NULL)
		return;
	
	String CharArray = CreateStringFromCharArray(Second);
	ConcatString(First, CharArray);
	DestroyString(&CharArray);
}

void InsertCharArray(String Main, const int Index, const CharType *Insert)
{
	if (Insert == NULL)
		return;
	
	String CharArray = CreateStringFromCharArray(Insert);
	InsertString(Main, Index, CharArray);
	DestroyString(&CharArray);
}

int CompareCharArray(String First, const CharType *Second)
{
	CharType *FirstStr = GetCharArray(First);
	
	D("[{}] Comparing {} and {}...\n", __FUNCTION__, FirstStr, Second);
	
	int Ret = CharArrayCmp(FirstStr, Second);
	
	D("[{}] Compare done with result {}.\n", __FUNCTION__, Ret);
	
	free(FirstStr);
	return Ret;
}

String BruteForcePatternMatchWithCharArray(String Main, const CharType *Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	D("[{}] Checking if same length...\n", __FUNCTION__);
	
	unsigned int PatLen = CharArrayLen(Pattern);
	if (PatLen < 1 || PatLen > GetStringLength(Main))
		return NULL;
	
	D("[{}] Checking if same content...\n", __FUNCTION__);
	
	if (!CompareCharArray(Main, Pattern))
		return Main;
	
	D("[{}] Initializing...\n", __FUNCTION__);
		
	CharType *MainStr = GetCharArray(Main);
	unsigned int MainPtr, PatPtr, MainCur;
	
	D("[{}] Starting matching...\n", __FUNCTION__);
	
	for (MainPtr = 0; MainStr[MainPtr] != '\0'; MainPtr++)
	{
		//D("[{}] Matching round {}...\n", __FUNCTION__, i++);
				
		for (MainCur = MainPtr, PatPtr = 0; Pattern[PatPtr] != '\0'; PatPtr++, MainCur++)
			if (Pattern[PatPtr] != MainStr[MainCur])
				break;
		if (Pattern[PatPtr] == '\0')
			break;
	}
	
	D("[{}] End match.\n", __FUNCTION__);
		
	CharType End = MainStr[MainPtr];
	free(MainStr);
	
	D("[{}] MainStr freed.\n", __FUNCTION__);
		
	if (End == '\0')
		return NULL;
	else
	{
		D("[{}] Match found.\n", __FUNCTION__);
				
		unsigned int Offset;
		String Out = __StrWhichPartHasIndex(Main, MainPtr, NULL, &Offset);
		if (__StrData(Out)->Head == Offset)
			return Out;
		else
			return __StrSplitStringIntoTwoParts(Main, MainPtr)->Next;
	}
}

String KMPPatternMatchWithCharArray(String Main, const CharType *Pattern)
{
	if (Main == NULL || Pattern == NULL)
		return NULL;
	
	unsigned int PatLen, *NextTable;
	
	D("[{}] Building table...", __FUNCTION__);
	
	NextTable = __CharArrayBuildKMPNextTable(Pattern, &PatLen);
	if (!NextTable)
		return NULL;
	
	D("Done.\n");
	D("[{}] Table for \"{}\" is as follows:\n", __FUNCTION__, Pattern);
	#ifdef __STR_OUTPUT__
	for (int _i = 0; _i < PatLen; _i++)
		D("[{}]\t{} / {}: {}\n", __FUNCTION__, _i + 1, PatLen, NextTable[_i]);
	#endif

	CharType *MainStr = GetCharArray(Main);
	unsigned int MainLen = GetStringLength(Main);
	
	unsigned int MainPtr = 0, PatPtr = 0;
	
	while (MainPtr != MainLen)
	{
		//D("[{}] Matching round {}...\n", __FUNCTION__, MainPtr);
		if (PatPtr == PatLen)
		{
			D("[{}] Match found.\n", __FUNCTION__);
			MainPtr -= PatLen;
			free(NextTable);
			free(MainStr);
			unsigned int Offset;
			String Out = __StrWhichPartHasIndex(Main, MainPtr, NULL, &Offset);
			if (__StrData(Out)->Head == Offset)
				return Out;
			else
				return __StrSplitStringIntoTwoParts(Main, MainPtr)->Next;
		}
		else if (MainStr[MainPtr] == Pattern[PatPtr])
			MainPtr++, PatPtr++;
		else if (PatPtr != 0)
			PatPtr = NextTable[PatPtr - 1];
		else
			MainPtr++;
	}
	
	D("[{}] End match.\n", __FUNCTION__);
	
	free(NextTable);
	free(MainStr);
	return NULL;
}