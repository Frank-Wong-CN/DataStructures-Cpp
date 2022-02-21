#include "common.h"

#define CommonDS_v2_List_ElementType CommonDS_v2_PointerSize

// If list node needs to be modified, expand the adjacency list version, not the basic version.
// Otherwise the graph implementation would break!

//#include "node_impl_basic.h"
#include "node_impl_adjacency_list.h"
#include "list.h"
#include "stack.h"
#include "queue.h"

#include "tnode_impl_basic.h"
#include "tree.h"
#include "bintree.h"
#include "btree.h"

#include "string.h"
#include "adjacency_list.h"
#include "graph.h"

#include "hash.h"

#include "list.c"
#include "stack.c"
#include "queue.c"

#include "tree.c"
#include "bintree.c"
#include "btree.c"

#include "string.c"
#include "adjacency_list.c"
#include "graph.c"

#include "hash.c"

#define __DSVER(X) 				CommonDS_v2_ ## X

#define __LIST(X) 				CommonDS_v2_List_ ## X
#define __STACK(X) 				CommonDS_v2_Stack_ ## X
#define __QUEUE(X) 				CommonDS_v2_Queue_ ## X
#define __TREE(X) 				CommonDS_v2_Tree_ ## X
#define __BINTREE(X) 			CommonDS_v2_BinaryTree_ ## X
#define __BST(X) 				CommonDS_v2_BST_ ## X
#define __AVL(X) 				CommonDS_v2_AVL_ ## X
#define __GNS_STRING(X) 		CommonDS_v2_String_ ## X
#define __GRAPH(X) 				CommonDS_v2_Graph_ ## X
#define __ADJLIST(X) 			CommonDS_v2_AdjacencyList_ ## X
#define __HASHMAP(X) 			CommonDS_v2_HashMap_ ## X
#define __HASHFUNC(X) 			CommonDS_v2_Hash_ ## X ##Hash

// Basic Types
#define DSSizeT 				__DSVER(SizeType)
#define DSPtr 					__DSVER(Pointer) // void *
#define DSPtrInt 				__DSVER(PointerSize) // unsigned long long
#define DSPtrIntS 				__DSVER(PointerSize_Signed) // long long
#define DSHash 					__DSVER(HashType)

// Element Types
// They are all PtrInt if not futher modified
#define ElemType 				__LIST(ElementType)
#define PayloadType 			__TREE(PayloadType)
#define ExtraDataType 			__ADJLIST(ExtraDataType)
#define WeightType 				__ADJLIST(WeightType)

// Lists
#define List					__DSVER(List)
#define Node					__LIST(Node)
#define Position				__LIST(Position)
#define Stack					__DSVER(Stack)
#define Queue					__DSVER(Queue)
#define String					__DSVER(String)

// Trees
#define Tree					__DSVER(Tree)
#define Child					__TREE(Child)
#define Sibling					__TREE(Sibling)
#define BinaryTree				__DSVER(BinaryTree)
#define BSTTree					__DSVER(BSTTree)
#define AVLTree					__DSVER(AVLTree)
#define BTree					__DSVER(BTree)

// Graphs
#define AdjacencyList			__DSVER(AdjacencyList)
#define Vertex					__DSVER(Vertex)
#define Edge					__DSVER(Edge)
#define Graph					__DSVER(Graph)

// Hash Map
#define HashMap					__DSVER(HashMap)

// List Interfaces
#define ListCreate				__LIST(CreateList)
#define ListClone				__LIST(CloneList)
#define ListIsEmpty				__LIST(IsEmpty)
#define ListIsLast				__LIST(IsLast)
#define ListFind				__LIST(Find)
#define ListFindPrev			__LIST(FindPrevious)
#define ListHeader				__LIST(Header)
#define ListFirst				__LIST(First)
#define ListLast				__LIST(Last)
#define ListAdvance				__LIST(Advance)
#define ListAt					__LIST(At)
#define ListRetrieve			__LIST(Retrieve)
#define ListSize				__LIST(Size)
#define ListRemove				__LIST(Delete)
#define ListInsert				__LIST(Insert)
#define ListSwap				__LIST(Swap)
#define ListClear				__LIST(MakeEmpty)
#define ListDestroy				__LIST(DeleteList)

// Stack Interfaces
#define StackCreate				__STACK(CreateStack)
#define StackDispose			__STACK(Dispose)
#define StackPush				__STACK(Push)
#define StackPeak				__STACK(Top)
#define StackPop				__STACK(Pop)

// Queue Interfaces
#define QueueCreate				__QUEUE(CreateQueue)
#define QueueDispose			__QUEUE(Dispose)
#define QueueIn					__QUEUE(Enqueue)
#define QueuePeak				__QUEUE(Front)
#define QueueOut				__QUEUE(Dequeue)

// Tree Interfaces
#define TreeCreate				__TREE(CreateTree)
#define TreeHasChild			__TREE(HasChild)
#define TreeHasSibling			__TREE(HasSibling)
#define TreeIsChild				__TREE(IsChild)
#define TreeIsSibling			__TREE(IsSibling)
#define TreeIsAncestor			__TREE(IsProperAncestor)
#define TreeIsDescendant		__TREE(IsProperDescendant)
#define TreeInSameTree			__TREE(IsInSameTree)
#define TreePreOrderYield		__TREE(PreOrderYield)
#define TreePostOrderYield		__TREE(PostOrderYield)
#define TreeBtmUpLevelYield		__TREE(BottomUpLevelYield)
#define TreeTopDwLevelYield		__TREE(TopDownLevelYield)
#define TreeCurYieldParent		__TREE(CurrentYieldParent)
#define TreeSaveYieldInfo		__TREE(PushYieldState)
#define TreeLoadYieldInfo		__TREE(PopYieldState)
#define TreeTraverse			__TREE(Traverse)
#define TreeGetClosestConn		__TREE(GetClosestConnection)
#define TreeGetChild			__TREE(FirstChild)
#define TreeGetSibling			__TREE(NextSibling)
#define TreeRetrieve			__TREE(Retrieve)
#define TreeRemove				__TREE(Delete)
#define TreeAddChild			__TREE(AddChild)
#define TreeAddSibling			__TREE(AddSibling)
#define TreeAppend				__TREE(AppendTree)
#define TreeSwap				__TREE(Swap)
#define TreeClear				__TREE(MakeEmpty)
#define TreeDestroy				__TREE(DeleteTree)

// Binary Tree Interfaces
#define BinTreePreOrdYield		__BINTREE(PreOrderYield)
#define BinTreeInOrdYield		__BINTREE(InOrderYield)
#define BinTreePostOrdYield		__BINTREE(PostOrderYield)
#define BinTreeHasLeft			__BINTREE(HasLeft)
#define BinTreeHasRight			__BINTREE(HasRight)
#define BinTreeGetLeft			__BINTREE(RetrieveLeft)
#define BinTreeGetRight			__BINTREE(RetrieveRight)
#define BinTreeTreeDepth		__BINTREE(Depth)
#define BinTreeAddLeft			__BINTREE(AddLeft)
#define BinTreeAddRight			__BINTREE(AddRight)
#define BinTreeDelLeft			__BINTREE(RemoveLeft)
#define BinTreeDelRight			__BINTREE(RemoveRight)
#define BinTreeToForest			__BINTREE(ConvertToForest)
#define BinTreeCreate			TreeCreate
#define BinTreeClear			__BINTREE(MakeEmpty)
#define BinTreeDestroy			__BINTREE(DeleteBinTree)

// Binary Search Tree Interfaces
#define BSTAdd					__BST(Add)
#define BSTFind					__BST(Find)
#define BSTFindMax				__BST(FindMax)
#define BSTFindMin				__BST(FindMin)
#define BSTRemove				__BST(RemoveValue)
#define BSTDepth				BinTreeDepth
#define BSTCreate				TreeCreate
#define BSTClear				TreeClear
#define BSTDestroy				TreeDestroy

// AVL Tree Interfaces
#define AVLAdd					__AVL(Add)
#define AVLRemove				__AVL(RemoveValue)
#define AVLFind					BSTFind
#define AVLFindMax				BSTFindMax
#define AVLFindMin				BSTFindMin
#define AVLDepth				BinTreeDepth
#define AVLCreate				TreeCreate
#define AVLClear				TreeClear
#define AVLDestroy				TreeDestroy

// B-Tree Interfaces
#define BTreeCreate				__BTREE(CreateTree)
#define BTreeAdd				__BTREE(Add)
#define BTreeRemove				__BTREE(RemoveValue)
#define BTreeFind				__BTREE(Find)

// String Interfaces
#define StringCreate			__GNS_STRING(CreateString)
#define StringLength			__GNS_STRING(GetStringLength)
#define StringCStrGet			__GNS_STRING(GetCharArray)
#define StringClone				__GNS_STRING(CloneString)
#define StringClear				__GNS_STRING(ClearString)
#define StringDestroy			__GNS_STRING(DeleteString)

#define StringCopy				__GNS_STRING(CopyString)
#define StringConcat			__GNS_STRING(ConcatString)
#define StringInsert			__GNS_STRING(InsertString)
#define StringCompare			__GNS_STRING(CompareString)
#define StringSubstr			__GNS_STRING(KMPPatternMatch)

#define StringCStrCreate		__GNS_STRING(CreateStringFromCharArray)
#define StringCStrCopy			__GNS_STRING(CopyCharArray)
#define StringCStrConcat		__GNS_STRING(ConcatCharArray)
#define StringCStrInsert		__GNS_STRING(InsertCharArray)
#define StringCStrCompare		__GNS_STRING(CompareCharArray)
#define StringCStrSubstr		__GNS_STRING(KMPPatternMatchWithCharArray)

// Adjacency List Interfaces
#define GraphCreate				__GRAPH(CreateGraph)
#define GraphClear				__GRAPH(MakeEmpty)
#define GraphDestroy			__GRAPH(DeleteGraph)
#define GraphAddVertex			__GRAPH(AddVertex)
#define GraphRemoveVertex		__GRAPH(RemoveVertex)
#define GraphFindVertex			__GRAPH(FindVertex)
#define GraphCountVertex		__GRAPH(CountVertex)
#define GraphConnect			__GRAPH(ConnectVertex)
#define GraphDisconnect			__GRAPH(DisconnectVertex)
#define GraphFindEdge			__GRAPH(FindEdge)
#define GraphFindNeighborTo		__GRAPH(FindNeighborTo)
#define GraphFindNeighborFrom	__GRAPH(FindNeighborFrom)
#define GraphCountEdge			__GRAPH(CountEdge)
#define GraphGetInDegree		__GRAPH(InDegree)
#define GraphGetOutDegree		__GRAPH(OutDegree)
#define GraphAddDataToVert		__GRAPH(AttachDataToVertex)
#define GraphAddDataToEdge		__GRAPH(AttachDataToEdge)

// Graph Interfaces
#define GraphDFYield			__GRAPH(DepthFirstYield)
#define GraphBFYield			__GRAPH(BreadthFirstYield)
#define GraphSaveYieldInfo		__GRAPH(PushYieldState)
#define GraphLoadYieldInfo		__GRAPH(PopYieldState)
#define GraphDFTraverse			__GRAPH(DepthFirstTraverse)
#define GraphBFTraverse			__GRAPH(BreadthFirstTraverse)
#define GraphSpanningForest		__GRAPH(SpanningForestFromGraph)
#define GraphPrim				__GRAPH(MST_Prim)
#define GraphKruskal			__GRAPH(MST_Kruskal)
#define GraphDijkstra			__GRAPH(PathFinding_Dijkstra)
#define GraphFloyd				__GRAPH(PathFinding_Floyd)
#define GraphIsSimple			__GRAPH(IsSimpleGraph)
#define GraphIsDirected			__GRAPH(IsDirectedGraph)
#define GraphIsCyclic			__GRAPH(IsCyclicGraph)
#define GraphIsComplete			__GRAPH(IsCompleteGraph)
#define GraphIsPathSimple		__GRAPH(IsPathSimple)
#define GraphIsPathCircuit		__GRAPH(IsPathCircuit)
#define GraphIsConnected		__GRAPH(IsConnectedGraph)
#define GraphGetComponents		__GRAPH(GetAllConnectedComponents)
#define GraphIsStrongConn		__GRAPH(IsStronglyConnectedGraph)
#define GraphGetStrongComp		__GRAPH(GetAllStronglyConnectedComponents)

// Hash Functions
#define DJBHash					__HASHFUNC(DJB)

// Hash Map Interfaces
#define HashMapCreate			__HASHMAP(Create)
#define HashMapInsert			__HASHMAP(Insert)
#define HashMapGet				__HASHMAP(Get)
#define HashMapRemove			__HASHMAP(Remove)
#define HashMapClear			__HASHMAP(Clear)
#define HashMapDestroy			__HASHMAP(Destroy)
