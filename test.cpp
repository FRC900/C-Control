#include <iostream>
#include <functional>	
#define WHEELCOUNT 4

using namespace std;
class test
{
	public:
		test(std::function<int(int, int)> _add);
		int suma(int i, int j);
	private:
		std::function<int(int, int)> add;
};


test::test(std::function<int(int, int)> _add)
{
	add = _add;
}
int test::suma(int i, int j)
{
	return add(i, j);
}

int addit(int i, int j)
{
	return i + j;
}
int main()
{

	

	std::function<int(int, int)> addition = addit;
	test tester(addition);
	cout << tester.suma(1, 7) <<endl;
	array<double, WHEELCOUNT> hi = {[0 ... WHEELCOUNT] = 1};
	return 0;

}
