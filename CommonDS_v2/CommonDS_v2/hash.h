#ifndef HASH_H
#define HASH_H

#include "ds.h"

#define CommonDS_v2_HashType DSPtrInt

typedef CommonDS_v2_HashType (*CommonDS_v2_HashFunction)(DSPtr Data, DSSizeT Size);

typedef struct _HashMap
{
	AVLTree Index;
	CommonDS_v2_HashFunction Hash;
	
} HashMapSize, *HashMap;

typedef struct _KeyValue
{
	DSPtr Key;
	DSSizeT KeySize;
	DSPtr Value;
	DSSizeT ValueSize;
} KeyValueSize, *KeyValue;

CommonDS_v2_HashType Hash_DJBHash(DSPtr Data, DSSizeT Size);

HashMap HashMapCreate(CommonDS_v2_HashFunction Hash);
HashMap HashMapInsert(HashMap H, DSPtr Key, DSSizeT KeySize, DSPtr Value, DSSizeT ValSize, DSPtr *OldVal, DSSizeT *OldValSize);
KeyValue HashMapGet(HashMap H, DSPtr Key, DSSizeT KeySize);
HashMap HashMapRemove(HashMap H, DSPtr Key, DSSizeT KeySize, DSPtr *OldVal, DSSizeT *OldValSize);
void HashMapClear(HashMap H);
void HashMapDestroy(HashMap *H);

#endif