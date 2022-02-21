#include "hash.h"

CommonDS_v2_HashType CommonDS_v2_Hash_DJBHash(CommonDS_v2_Pointer Data, CommonDS_v2_SizeType Size)
{
   CommonDS_v2_HashType hash = 5381;
   CommonDS_v2_HashType i    = 0;
   
   CommonDS_v2_PointerSize str  = (CommonDS_v2_PointerSize)Data;

   for (i = 0; i < Size; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*(const char *)str);
   }

   return hash;
}

CommonDS_v2_HashMap CommonDS_v2_HashMap_Create(CommonDS_v2_HashFunction HashFunc)
{
	CommonDS_v2_HashMap H;
	
	H = (CommonDS_v2_HashMap)malloc(sizeof(CommonDS_v2_HashMapSize));
	memset(H, 0, sizeof(CommonDS_v2_HashMapSize));
	
	H->Hash = HashFunc;
	H->Index = CommonDS_v2_Tree_CreateTree(0);
	
	return H;
}

CommonDS_v2_HashMap CommonDS_v2_HashMap_Insert(CommonDS_v2_HashMap H, CommonDS_v2_Pointer Key, CommonDS_v2_SizeType KeySize, CommonDS_v2_Pointer Value, CommonDS_v2_SizeType ValSize, CommonDS_v2_Pointer *OldVal, CommonDS_v2_SizeType *OldValSize)
{
	if (!H) return NULL;
	
	CommonDS_v2_HashType HashVal = H->Hash(Key, KeySize);
	
	CommonDS_v2_Tree_Child DataNode;
	CommonDS_v2_List L;
	
	if (!H->Index->Param) // First entry of the map, root node has no list
	{
		L = CommonDS_v2_List_CreateList();
		DataNode = H->Index;
		DataNode->Element = (CommonDS_v2_PointerSize)HashVal;
		DataNode->Param = (CommonDS_v2_PointerSize)L;
	}
	
	// Get the corresponding hash node, add node if necessary
	DataNode = (CommonDS_v2_Tree_Child)CommonDS_v2_BST_Find(HashVal, H->Index);
	if (!DataNode)
	{
		L = CommonDS_v2_List_CreateList();
		DataNode = CommonDS_v2_AVL_Add(HashVal, H->Index);
		DataNode->Param = (CommonDS_v2_PointerSize)L;
	}
	else L = (CommonDS_v2_List)DataNode->Param;
	
	// Check if the key already exists
	for (CommonDS_v2_List_Position P = CommonDS_v2_List_First(L); P != NULL; P = CommonDS_v2_List_Advance(P))
	{
		CommonDS_v2_KeyValue Cur = (CommonDS_v2_KeyValue)CommonDS_v2_List_Retrieve(P);
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
	CommonDS_v2_KeyValue KVPair = (CommonDS_v2_KeyValue)malloc(sizeof(CommonDS_v2_KeyValueSize));
	*KVPair = { Key, KeySize, Value, ValSize };
	
	CommonDS_v2_List_Insert((CommonDS_v2_PointerSize)KVPair, L, L);
	
	return H;
}

CommonDS_v2_KeyValue CommonDS_v2_HashMap_Get(CommonDS_v2_HashMap H, CommonDS_v2_Pointer Key, CommonDS_v2_SizeType KeySize)
{
	if (!H) return NULL;
	
	CommonDS_v2_HashType HashVal = H->Hash(Key, KeySize);
	
	// Get the hash node
	CommonDS_v2_Tree_Child DataNode = (CommonDS_v2_Tree_Child)CommonDS_v2_BST_Find(HashVal, H->Index);
	if (!DataNode)
		return NULL;
	
	CommonDS_v2_List L = (CommonDS_v2_List)DataNode->Param;
	
	// Find the key
	for (CommonDS_v2_List_Position P = CommonDS_v2_List_First(L); P != NULL; P = CommonDS_v2_List_Advance(P))
	{
		CommonDS_v2_KeyValue Cur = (CommonDS_v2_KeyValue)CommonDS_v2_List_Retrieve(P);
		if (Cur->KeySize == KeySize && !memcmp(Cur->Key, Key, KeySize))
			return Cur;
	}
	
	// Key not found
	return NULL;
}

CommonDS_v2_HashMap CommonDS_v2_HashMap_Remove(CommonDS_v2_HashMap H, CommonDS_v2_Pointer Key, CommonDS_v2_SizeType KeySize, CommonDS_v2_Pointer *OldVal, CommonDS_v2_SizeType *OldValSize)
{
	if (!H) return NULL;
	
	CommonDS_v2_HashType HashVal = H->Hash(Key, KeySize);
	
	// Get the hash node
	CommonDS_v2_Tree_Child DataNode = (CommonDS_v2_Tree_Child)CommonDS_v2_BST_Find(HashVal, H->Index);
	if (!DataNode)
		return NULL;
	
	CommonDS_v2_List L = (CommonDS_v2_List)DataNode->Param;
	
	// Find the key
	for (CommonDS_v2_List_Position P = CommonDS_v2_List_First(L); P != NULL; P = CommonDS_v2_List_Advance(P))
	{
		CommonDS_v2_KeyValue Cur = (CommonDS_v2_KeyValue)CommonDS_v2_List_Retrieve(P);
		if (Cur->KeySize == KeySize && !memcmp(Cur->Key, Key, KeySize))
		{
			CommonDS_v2_List_Delete((CommonDS_v2_PointerSize)Cur, L);
			if (OldVal) *OldVal = Cur->Value;
			if (OldValSize) *OldValSize = Cur->ValueSize;
			free(Cur);
			return H; // No need to enumerate the remaining stuff
		}
	}
	
	return H;
}

void CommonDS_v2_HashMap_Clear(CommonDS_v2_HashMap H)
{
	if (!H) return;
	
	for (CommonDS_v2_Tree_Child C = CommonDS_v2_BinaryTree_PreOrderYield(H->Index); C != NULL; C = CommonDS_v2_BinaryTree_PreOrderYield(NULL))
	{
		CommonDS_v2_List L = (CommonDS_v2_List)C->Param;
		for (CommonDS_v2_List_Position P = CommonDS_v2_List_First(L); P != NULL; P = CommonDS_v2_List_Advance(P))
			free((CommonDS_v2_Pointer)P->Element); // Free all KeyValue pairs
		CommonDS_v2_List_DeleteList((CommonDS_v2_List *)&(C->Param)); // Free all lists
	}
	CommonDS_v2_BinaryTree_MakeEmpty(H->Index); // Empty the AVL tree
}

void CommonDS_v2_HashMap_Destroy(CommonDS_v2_HashMap *H)
{
	if (!H || !(*H)) return;
	
	for (CommonDS_v2_Tree_Child C = CommonDS_v2_BinaryTree_PreOrderYield((*H)->Index); C != NULL; C = CommonDS_v2_BinaryTree_PreOrderYield(NULL))
	{
		CommonDS_v2_List L = (CommonDS_v2_List)C->Param;
		for (CommonDS_v2_List_Position P = CommonDS_v2_List_First(L); P != NULL; P = CommonDS_v2_List_Advance(P))
			free((CommonDS_v2_Pointer)P->Element); // Free all KeyValue pairs
		CommonDS_v2_List_DeleteList((CommonDS_v2_List *)&(C->Param)); // Free all lists
	}
	CommonDS_v2_BinaryTree_DeleteBinTree(&((*H)->Index)); // Free the AVL tree
	
	free(*H);
	*H = NULL;
}
