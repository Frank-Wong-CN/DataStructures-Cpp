#ifndef DSV2_HASH_H
#define DSV2_HASH_H

#include "node_impl_adjacency_list.h"
#include "tnode_impl_basic.h"

#include "common.h"
#include "list.h"
#include "bintree.h"

#define CommonDS_v2_HashType CommonDS_v2_PointerSize

typedef CommonDS_v2_HashType (*CommonDS_v2_HashFunction)(CommonDS_v2_Pointer Data, CommonDS_v2_SizeType Size);

typedef struct CommonDS_v2__HashMap
{
	CommonDS_v2_Tree Index;
	CommonDS_v2_HashFunction Hash;
	
} CommonDS_v2_HashMapSize, *CommonDS_v2_HashMap;

typedef struct CommonDS_v2__KeyValue
{
	CommonDS_v2_Pointer Key;
	CommonDS_v2_SizeType KeySize;
	CommonDS_v2_Pointer Value;
	CommonDS_v2_SizeType ValueSize;
} CommonDS_v2_KeyValueSize, *CommonDS_v2_KeyValue;

CommonDS_v2_HashType CommonDS_v2_Hash_DJBHash(CommonDS_v2_Pointer Data, CommonDS_v2_SizeType Size);

CommonDS_v2_HashMap CommonDS_v2_HashMap_Create(CommonDS_v2_HashFunction Hash);
CommonDS_v2_HashMap CommonDS_v2_HashMap_Insert(CommonDS_v2_HashMap H, CommonDS_v2_Pointer Key, CommonDS_v2_SizeType KeySize, CommonDS_v2_Pointer Value, CommonDS_v2_SizeType ValSize, CommonDS_v2_Pointer *OldVal, CommonDS_v2_SizeType *OldValSize);
CommonDS_v2_KeyValue CommonDS_v2_HashMap_Get(CommonDS_v2_HashMap H, CommonDS_v2_Pointer Key, CommonDS_v2_SizeType KeySize);
CommonDS_v2_HashMap CommonDS_v2_HashMap_Remove(CommonDS_v2_HashMap H, CommonDS_v2_Pointer Key, CommonDS_v2_SizeType KeySize, CommonDS_v2_Pointer *OldVal, CommonDS_v2_SizeType *OldValSize);
void CommonDS_v2_HashMap_Clear(CommonDS_v2_HashMap H);
void CommonDS_v2_HashMap_Destroy(CommonDS_v2_HashMap *H);

#endif