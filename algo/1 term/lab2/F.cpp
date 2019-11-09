#include <stack>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

const string in = "push";
const string out = "pop";

int main() {
	int n;
	cin >> n;
	vector<int> stack;
	vector<string> ans;
	int next, last = 0;
	for (int i = 0; i < n; i++)
	{
		ans.push_back(in);
		cin >> next;
		if (next == last + 1)
		{
			ans.push_back(out);
			last++;
			while (stack.size() > 0 && stack[stack.size() - 1] == last + 1)
			{
				ans.push_back(out);
				stack.pop_back();
				last++;
			}
			continue;
		}
		if (stack.size() == 0 || stack[stack.size() - 1] > next)
		{
			stack.push_back(next);
			continue;
		}
		cout << "impossible";
		//system("pause");
		return 0;
	}

	while (stack.size() > 0)
	{
		stack.pop_back();
		ans.push_back(out);
	}

	for (int i = 0; i < ans.size(); i++)
		cout << ans[i] << endl;

	//system("pause");
	return 0;
}