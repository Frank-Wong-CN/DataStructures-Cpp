#include "Load"

int Walker(Child CurNode, Sibling PrevNode, Tree Parent, Payload Data)
{
	std::cout << "CurNode: " << CurNode->Element << ", PrevNode: " << (PrevNode == NULL ? "NULL" : std::to_string(PrevNode->Element)) << (IsSibling(PrevNode, CurNode) ? " (Sibling)" : "") << ", Parent: " << (Parent == NULL ? "NULL" : std::to_string(Parent->Element));
	
	std::cout << ", Stack: ";
	for (Position S = First((List)__CurrentYieldingTree); S != NULL; S = Advance(S))
		std::cout << ((Tree)S->Element)->Element << " ";
	
	std::cout << std::endl;
	
	return 1;
}

int main(int argc, char *argv[])
{
	Tree t = CreateTree();
	t->Element = 324;
	AVLAdd(427, t);
	AVLAdd(644, t);
	AVLAdd(435, t);
	AVLAdd(5555, t);
	AVLAdd(6665, t);
	AVLAdd(6666, t);
	AVLAdd(6300, t);
	AVLAdd(6500, t);
	AVLAdd(6200, t);
	AVLAdd(6201, t);
	AVLAdd(6202, t);
	
	Traverse(t, PostOrderYield, Walker, NULL);
	
	return 0;
}