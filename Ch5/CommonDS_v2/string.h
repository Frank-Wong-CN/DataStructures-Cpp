#ifndef _STRING_H
#define _STRING_H

#ifndef ElementType
#define ElementType unsigned long long
#endif

#ifndef _NODE_IMPL_
#include "../Ch3/CommonDS_v2/node_impl_basic.h"
#endif

#include "../Ch3/CommonDS_v2/list.h"
#include "../Ch3/CommonDS_v2/stack.h"
#include "../Ch3/CommonDS_v2/queue.h"

#ifndef StringPartSize
#define StringPartSize 31 // Should be smaller than uint_max
#endif

#include "chartype.h"

typedef PNode String;
typedef CharType StringPart[StringPartSize + 1];

struct _StringData
{
	StringPart Data;
	unsigned int Head;
};

typedef _StringData StringData, *PStringData;

String CreateString();
String CloneString(String Str);
String CreateStringFromCharArray(const CharType *Str);
CharType *GetCharArray(const String Str); // Free after use
unsigned int GetStringLength(const String Str);

void ClearString(String Str);
void DestroyString(String *Str);
void CopyString(String Dest, const String Src, int Size, int TerminateString);
void ConcatString(String First, const String Second);
void InsertString(String Main, const int Index, const String Insert);
int CompareString(String First, String Second);
String BruteForcePatternMatch(String Main, const String Pattern);
String KMPPatternMatch(String Main, const String Pattern);

void CopyCharArray(String Dest, const CharType *Src, int Size, int TerminateString);
void ConcatCharArray(String First, const CharType *Second);
void InsertCharArray(String Main, const int Index, const CharType *Insert);
int CompareCharArray(String First, const CharType *Second);
String BruteForcePatternMatchWithCharArray(String Main, const CharType *Pattern);
String KMPPatternMatchWithCharArray(String Main, const CharType *Pattern);

#endif
