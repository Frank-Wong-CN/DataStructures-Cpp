static Tree tree;

bool IsPrime(unsigned long long n)
{
	bool isPrime = true;
	int i;
	if (n == 0 || n == 1)
	{
		isPrime = false;
	}
	else
	{
		for (i = 2; i <= n / 2; ++i)
		{
			if (n % i == 0)
			{
				isPrime = false;
				break;
			}
		}
	}
	
	return isPrime;
}

void BuildTree()
{
	tree = CreateTree();
	
	for (int i = 2; i < 100; i++)
	{
		Tree node = AddChild(i, tree);
		for (int j = 2; j < 100; j++)
		{
			Tree inner = AddChild(j, node);
			AddChild(i + j, inner);
			AddChild(i * j, inner);
		}
	}
}

void Walk(Tree T)
{
	bool FirstPrime = false;
	bool SecondPrime = false;
	bool FirstOdd = false;
	bool SecondOdd = false;
	Tree node = T->FirstChild;
	while (node != NULL)
	{
		FirstPrime = IsPrime(node->Element);
		FirstOdd = node->Element % 2;
		Tree nodeInner = node->FirstChild;
		while (nodeInner != NULL)
		{
			SecondPrime = IsPrime(nodeInner->Element);
			SecondOdd = nodeInner->Element % 2;
			
			Tree leaf = nodeInner->FirstChild;
			unsigned long long sum = leaf->Element;
			unsigned long long prd = leaf->NextSibling->Element;
			
			if ((sum % 2) && !(FirstPrime && SecondPrime) /* Same condition after */ && !(prd % 2) && (FirstOdd ^ SecondOdd))
				fmt::print("{}, {}:\t{}, {}\n", node->Element, nodeInner->Element, sum, prd);
			
			nodeInner = nodeInner->NextSibling;
		}
		node = node->NextSibling;
	}
}

#define Run \
BuildTree(); \
Walk(tree);