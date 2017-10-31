#include <algorithm>
#include <vector>
#include <iostream>

using std::cout; using std::cin; using std::sort; using std::vector;

int main()
{
	long long n;
	cin >> n;
	
	vector<int> input;
	while(n--)
	{
		int tmp_num;
		cin >> tmp_num;
		input.push_back(tmp_num);
	}
	sort(input.begin(), input.end());
	for(int i = 0; i < input.size(); ++i)
		cout << input[i] << (i + 1 < input.size() ? " " : "\n");
}
