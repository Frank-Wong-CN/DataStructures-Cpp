int Walker(Child CurNode, Sibling PrevNode, Tree Parent, Payload Data) {
	std::cout << "CurNode: " << CurNode->Element << ", PrevNode: " << (PrevNode == NULL ? "NULL" : std::to_string(PrevNode->Element)) << (IsSibling(PrevNode, CurNode) ? " (Sibling)" : "") << ", Parent: " << (Parent == NULL ? "NULL" : std::to_string(Parent->Element));
	
	std::cout << ", Stack: ";
	for (Position S = First((List)__CurrentYieldingTree); S != NULL; S = Advance(S))
		std::cout << ((Tree)S->Element)->Element << " ";
	
	std::cout << std::endl;
	
	return 1;
}

int SimpleWalker(Child CurNode, Sibling PrevNode, Tree Parent, Payload Data) {
	std::cout << CurNode->Element << " ";
	return 1;
}


#define Post(T) Traverse(T, PostOrderYield, Walker, NULL);
#define Pre(T) Traverse(T, PreOrderYield, Walker, NULL);

#define SimplePre(T) Traverse(T, PreOrderYield, SimpleWalker, NULL);
#define SimplePost(T) Traverse(T, PostOrderYield, SimpleWalker, NULL);

class BSTTestCase
{
public:
	int N;
	int *Arr;
	
	BinaryTree T;
	
	BSTTestCase(int n, int max)
	{
		N = n;
		Arr = RdGen::ArrGen<int>(n, 0, max);
		
		T = CreateTree(Arr[0]);
		RecordTime(N)
		for (int i = 1; i < n; i++)
			//if (!BSTFind(Arr[i], T))
			{
				BSTAdd(Arr[i], T);
				/*
				std::cout << "Pre: ";
				SimplePre(T);
				std::cout << "\nPost: ";
				SimplePost(T);
				std::cout << std::endl;
				*/
			}
		Timer::Lap();
	}
	
	void RemovalTest(int n)
	{
		RecordTime(N)
		for (int i = 0; i < n; i++)
		{
			int j = RdGen::Random(0, n);
			//std::cout << "Removing element index: " << j;
			//std::cout << ", value: " << Arr[j] << std::endl;
			BSTRemoveValue(Arr[j], &T);
		}
		Timer::Lap();
	}
};

class AVLTestCase
{
public:
	int N;
	int *Arr;
	
	BinaryTree T;
	
	AVLTestCase(int n, int max)
	{
		N = n;
		Arr = RdGen::ArrGen<int>(n, 0, max);
		
		T = CreateTree(Arr[0]);
		RecordTime(N)
		for (int i = 1; i < n; i++)
			//if (!BSTFind(Arr[i], T))
			{
				AVLAdd(Arr[i], T);
				/*
				std::cout << "Pre: ";
				SimplePre(T);
				std::cout << "\nPost: ";
				SimplePost(T);
				std::cout << std::endl;
				*/
			}
		Timer::Lap();
	}
	
	void RemovalTest(int n)
	{
		RecordTime(n)
		for (int i = 0; i < n; i++)
		{
			int j = RdGen::Random(0, n);
			//std::cout << "Removing element index: " << j;
			//std::cout << ", value: " << Arr[j] << std::endl;
			AVLRemoveValue(Arr[j], &T);
			//if (AVLBalanceNext(T))
			//{
				//std::cout << "AVLBalanceError\n";
			//}
		}
		Timer::Lap();
	}
};