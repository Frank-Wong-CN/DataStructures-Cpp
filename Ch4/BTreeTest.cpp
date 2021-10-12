void Post(BTree T)
{
	for (BTree Y = PostOrderYield(T); Y != NULL; Y = PostOrderYield(NULL))
	{
		List L = (List)Y->Element;
		for (Position i = First(L); i != NULL; i = Advance(i))
			std::cout << i->Element << " ";
		std::cout << std::endl;
	}
}

void Pre(BTree T)
{
	for (BTree Y = PreOrderYield(T); Y != NULL; Y = PreOrderYield(NULL))
	{
		List L = (List)Y->Element;
		for (Position i = First(L); i != NULL; i = Advance(i))
			std::cout << i->Element << " ";
		std::cout << std::endl;
	}
}

class TestCase
{
public:
	int N;
	int *Arr;
	
	BTree T;
	
	TestCase(int n, int max)
	{
		N = n;
		Arr = RdGen::ArrGen<int>(n, 0, max);
		
		T = BTreeCreateTree();
		RecordTime(N)
		for (int i = 0; i < n; i++)
			BTreeAdd(Arr[i], T);
		Timer::Lap();
	}
};