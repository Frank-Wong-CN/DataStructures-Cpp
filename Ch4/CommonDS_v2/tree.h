#ifndef _TREE_H
#define _TREE_H

#include "tnode.h"

#ifndef _TNODE_IMPL_
#include "tnode_impl_basic.h"
#warning Tree node definition not found, basic implementation included.
#endif

#ifndef Payload
#define Payload void *
#endif

#ifndef _NODE_IMPL_
#include "..\Ch3\CommonDS_v2\node_impl_basic.h"
#endif

#include "..\Ch3\CommonDS_v2\stack.h"
#include "..\Ch3\CommonDS_v2\queue.h"

Stack __CurrentYieldingTree = NULL;
Stack __SavedYieldState = NULL;
List __CurrentLevelingTree = NULL;

Tree CreateTree(ElementType IV);
int HasChild(Tree T);
int HasSibling(Tree T);
int IsChild(Tree T, Child C);
int IsSibling(Sibling A, Sibling B);
int IsProperAncestor(Tree Ancestor, Tree Descendant);
int IsProperDescendant(Tree Descendant, Tree Ancestor);
int IsInSameTree(Tree A, Tree B);
Child PreOrderYield(Tree T);
Child PostOrderYield(Tree T);
Child BottomUpLevelYield(Tree T);
Child TopDownLevelYield(Tree T);
Tree CurrentYieldParent();
void PushYieldState();
void PopYieldState();
void Traverse(Tree T, Child (*Yield)(Tree T), int (*F)(Child CurNode, Sibling PrevNode, Tree Parent, Payload Data), Payload D);
Tree *GetClosestConnection(Child C, Tree T, Tree R, Tree *P, unsigned long long *Offset);
Child FirstChild(Tree T);
Sibling NextSibling(Sibling S);
ElementType TNodeRetrieve(PTNode N);

void Delete(ElementType X, Tree T, Child (*Yield)(Tree T), int DeleteSubTreeAsWell);
Child AddChild(ElementType X, Tree T);
Sibling AddSibling(ElementType X, Tree T);
void AppendTree(Tree Sub, Tree Dst);
void DeleteTree(Tree *T, Tree P);
void MakeEmpty(Tree T);
void TNodeSwap(PTNode A, PTNode B);

#endif
