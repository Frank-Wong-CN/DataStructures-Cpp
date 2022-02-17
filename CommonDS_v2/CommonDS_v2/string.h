#ifndef DSV2_STRING_H
#define DSV2_STRING_H

#ifndef CommonDS_v2_List_ElementType
#define CommonDS_v2_List_ElementType unsigned long long
#endif

#ifndef DSV2_NODE_IMPL_
#include "node_impl_basic.h"
#endif

#include "list.h"
#include "stack.h"
#include "queue.h"

#ifndef CommonDS_v2_String_StringPart_Size
#define CommonDS_v2_String_StringPart_Size 31 // Should be smaller than uint_max
#endif

#include "chartype.h"

typedef CommonDS_v2_List CommonDS_v2_String;
typedef CommonDS_v2_CharType CommonDS_v2_String_StringPart[CommonDS_v2_String_StringPart_Size + 1];

typedef struct CommonDS_v2_String__StringData
{
	CommonDS_v2_String_StringPart Data;
	CommonDS_v2_PointerSize Head;
} CommonDS_v2_String_StringData, *CommonDS_v2_String_PStringData;

CommonDS_v2_String CommonDS_v2_String_CreateString();
CommonDS_v2_String CommonDS_v2_String_CloneString(CommonDS_v2_String Str);
CommonDS_v2_String CommonDS_v2_String_CreateStringFromCharArray(const CommonDS_v2_CharType *Str);
CommonDS_v2_CharType *CommonDS_v2_String_GetCharArray(const CommonDS_v2_String Str); // Free after use
CommonDS_v2_SizeType CommonDS_v2_String_GetStringLength(const CommonDS_v2_String Str);

void CommonDS_v2_String_ClearString(CommonDS_v2_String Str);
void CommonDS_v2_String_DeleteString(CommonDS_v2_String *Str);
void CommonDS_v2_String_CopyString(CommonDS_v2_String Dest, const CommonDS_v2_String Src, CommonDS_v2_SizeType Size, int TerminateString);
void CommonDS_v2_String_ConcatString(CommonDS_v2_String First, const CommonDS_v2_String Second);
void CommonDS_v2_String_InsertString(CommonDS_v2_String Main, const CommonDS_v2_SizeType Index, const CommonDS_v2_String Insert);
int CommonDS_v2_String_CompareString(CommonDS_v2_String First, CommonDS_v2_String Second);
CommonDS_v2_String CommonDS_v2_String_BruteForcePatternMatch(CommonDS_v2_String Main, const CommonDS_v2_String Pattern);
CommonDS_v2_String CommonDS_v2_String_KMPPatternMatch(CommonDS_v2_String Main, const CommonDS_v2_String Pattern);

void CommonDS_v2_String_CopyCharArray(CommonDS_v2_String Dest, const CommonDS_v2_CharType *Src, int Size, int TerminateString);
void CommonDS_v2_String_ConcatCharArray(CommonDS_v2_String First, const CommonDS_v2_CharType *Second);
void CommonDS_v2_String_InsertCharArray(CommonDS_v2_String Main, const int Index, const CommonDS_v2_CharType *Insert);
int CommonDS_v2_String_CompareCharArray(CommonDS_v2_String First, const CommonDS_v2_CharType *Second);
CommonDS_v2_String CommonDS_v2_String_BruteForcePatternMatchWithCharArray(CommonDS_v2_String Main, const CommonDS_v2_CharType *Pattern);
CommonDS_v2_String CommonDS_v2_String_KMPPatternMatchWithCharArray(CommonDS_v2_String Main, const CommonDS_v2_CharType *Pattern);

#endif
