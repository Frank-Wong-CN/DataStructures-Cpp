#include "hash.h"

/**
 * An algorithm produced by Professor Daniel J. Bernstein and shown first
 * to the world on the usenet newsgroup comp.lang.c. It is one of the most
 * efficient hash functions ever published.
 * 
 * Taken from: http://www.partow.net/programming/hashfunctions/index.html
 */
CommonDS_v2_HashType Hash_DJBHash(DSPtr Data, DSSizeT Size)
{
   CommonDS_v2_HashType hash = 5381;
   CommonDS_v2_HashType i    = 0;
   
   DSPtrInt str  = (DSPtrInt)Data;

   for (i = 0; i < Size; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*(const char *)str);
   }

   return hash;
}

HashMap HashMapCreate(CommonDS_v2_HashFunction HashFunc)
{
	HashMap H;
	
	H = (HashMap)malloc(sizeof(HashMapSize));
	memset(H, 0, sizeof(HashMapSize));
	
	H->Hash = HashFunc;
	H->Index = (AVLTree)TreeCreate(0);
	
	return H;
}

HashMap HashMapInsert(HashMap H, DSPtr Key, DSSizeT KeySize, DSPtr Value, DSSizeT ValSize, DSPtr *OldVal, DSSizeT *OldValSize)
{
	if (!H) return NULL;
	
	CommonDS_v2_HashType HashVal = H->Hash(Key, KeySize);
	
	Child DataNode;
	List L;
	
	if (!H->Index->Param) // First entry of the map, root node has no list
	{
		L = ListCreate();
		DataNode = H->Index;
		DataNode->Element = (DSPtrInt)HashVal;
		DataNode->Param = (DSPtrInt)L;
	}
	
	// Get the corresponding hash node, add node if necessary
	DataNode = (Child)AVLFind(HashVal, H->Index);
	if (!DataNode)
	{
		L = ListCreate();
		DataNode = AVLAdd(HashVal, H->Index);
		DataNode->Param = (DSPtrInt)L;
	}
	else L = (List)DataNode->Param;
	
	// Check if the key already exists
	for (Position P = ListFirst(L); P != NULL; P = ListAdvance(P))
	{
		KeyValue Cur = (KeyValue)ListRetrieve(P);
		if (Cur->KeySize == KeySize && !memcmp(Cur->Key, Key, KeySize))
		{
			// Key already exists
			// Current implementation replaces the existing value
			if (OldVal)
				*OldVal = Cur->Value;
			//else FatalError("Key already exists!");
			if (OldValSize) *OldValSize = Cur->ValueSize; // Size can be discarded if OldVal is only to be used for free() or has size included
			Cur->Value = Value;
			Cur->ValueSize = ValSize;
			return H;
		}
	}
	
	// Key does not exist
	KeyValue KVPair = (KeyValue)malloc(sizeof(KeyValueSize));
	*KVPair = { Key, KeySize, Value, ValSize };
	
	ListInsert((DSPtrInt)KVPair, L, L);
	
	return H;
}

KeyValue HashMapGet(HashMap H, DSPtr Key, DSSizeT KeySize)
{
	if (!H) return NULL;
	
	CommonDS_v2_HashType HashVal = H->Hash(Key, KeySize);
	
	// Get the hash node
	Child DataNode = (Child)AVLFind(HashVal, H->Index);
	if (!DataNode)
		return NULL;
	
	List L = (List)DataNode->Param;
	
	// Find the key
	for (Position P = ListFirst(L); P != NULL; P = ListAdvance(P))
	{
		KeyValue Cur = (KeyValue)ListRetrieve(P);
		if (Cur->KeySize == KeySize && !memcmp(Cur->Key, Key, KeySize))
			return Cur;
	}
	
	// Key not found
	return NULL;
}

HashMap HashMapRemove(HashMap H, DSPtr Key, DSSizeT KeySize, DSPtr *OldVal, DSSizeT *OldValSize)
{
	if (!H) return NULL;
	
	CommonDS_v2_HashType HashVal = H->Hash(Key, KeySize);
	
	// Get the hash node
	Child DataNode = (Child)AVLFind(HashVal, H->Index);
	if (!DataNode)
		return NULL;
	
	List L = (List)DataNode->Param;
	
	// Find the key
	for (Position P = ListFirst(L); P != NULL; P = ListAdvance(P))
	{
		KeyValue Cur = (KeyValue)ListRetrieve(P);
		if (Cur->KeySize == KeySize && !memcmp(Cur->Key, Key, KeySize))
		{
			ListRemove((DSPtrInt)Cur, L);
			if (OldVal) *OldVal = Cur->Value;
			if (OldValSize) *OldValSize = Cur->ValueSize;
			free(Cur);
			return H; // No need to enumerate the remaining stuff
		}
	}
	
	return H;
}

void HashMapClear(HashMap H)
{
	if (!H) return;
	
	for (Child C = CommonDS_v2_BinaryTree_PreOrderYield(H->Index); C != NULL; C = CommonDS_v2_BinaryTree_PreOrderYield(NULL))
	{
		List L = (List)C->Param;
		for (Position P = ListFirst(L); P != NULL; P = ListAdvance(P))
			free((DSPtr)P->Element); // Free all KeyValue pairs
		ListDestroy((List *)&(C->Param)); // Free all lists
	}
	BinTreeClear(H->Index); // Empty the AVL tree
}

void HashMapDestroy(HashMap *H)
{
	if (!H || !(*H)) return;
	
	for (Child C = CommonDS_v2_BinaryTree_PreOrderYield((*H)->Index); C != NULL; C = CommonDS_v2_BinaryTree_PreOrderYield(NULL))
	{
		List L = (List)C->Param;
		for (Position P = ListFirst(L); P != NULL; P = ListAdvance(P))
			free((DSPtr)P->Element); // Free all KeyValue pairs
		ListDestroy((List *)&(C->Param)); // Free all lists
	}
	BinTreeDestroy(&((*H)->Index)); // Free the AVL tree
	
	free(*H);
	*H = NULL;
}
