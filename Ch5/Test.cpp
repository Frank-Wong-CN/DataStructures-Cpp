#include "Load"

int main(int argc, char *argv[])
{
	String a = CreateStringFromCharArray("Hello World");
	auto c = GetCharArray(a);
	printf("%s\n", c);
	free(c);
	return 0;
}
