// My summary on Two Sums, Three Sums problems, and different variants


# include <iostream>
# include <vector>
# include <unordered_set>
#include <algorithm>

using namespace std;

// Case 3: find all unique element pairs that sum to target
// Solution 1: We can use a set to maintain all elements pairs found and remove duplicates from it
// Solution 2: We can use one pass hash table, but note the special case that an element's complement is equal to itself, such as (5, 5, 10)

vector<vector<int>> twoSum(vector<int>& nums, int target)
{
	int flag = 0;
	vector<vector<int>> res;
	unordered_set<int> nums_seen;
	for (int i = 0; i < nums.size(); ++i)
	{
		int comp = target - nums[i];
		if (!nums_seen.count(nums[i]))
			// the curr element has not appeared before
		{
			if (nums_seen.count(comp))
			{
				vector<int> temp;
				temp.push_back(comp);
				temp.push_back(nums[i]);
				res.push_back(temp);
			}
			nums_seen.insert(nums[i]);
		}
		else if (comp == nums[i] && (!flag))
			// special case that we detect two or more elements equal to target / 2
		{
			vector<int> temp;
			temp.push_back(nums[i]);
			temp.push_back(nums[i]);
			res.push_back(temp);
			flag = 1;
		}

	}
	return res;
}


// case 4: find all unique element triplets that sum to target
// Solution 1: sort + two sum of element pairs, overall o(n^2) time

vector<vector<int>> twoSum(vector<int>& nums, int target, int pos);

vector<vector<int>> threeSum(vector<int>& nums, int target)
{
	vector<int> nums_sorted = nums;
	sort(nums_sorted.begin(), nums_sorted.end());
	// we sort the input array to handle the special case that an element might appear more than once in the triplet, 
	// such as [-1, 2, 5, -1, 3, -1]
	vector<vector<int>> res;

	int i = 0;
	int n = nums_sorted.size();
	while (i < n - 2)
	{
		int first = nums_sorted[i];
		int comp = target - first;
		vector<vector<int>> pairs = twoSum(nums_sorted, comp, i + 1);
		for (int j = 0; j < pairs.size(); ++j)
		{
			pairs[j].push_back(first);
			res.push_back(pairs[j]);
		}

		while (nums_sorted[i] == first)
			i++;
	}

	return res;
}

vector<vector<int>> twoSum(vector<int>& nums, int target, int pos = 0)
{
	int flag = 0;
	vector<vector<int>> res;
	unordered_set<int> nums_seen;
	for (int i = pos; i < nums.size(); ++i)
	{
		int comp = target - nums[i];
		if (!nums_seen.count(nums[i]))
			// the curr element has not appeared before
		{
			if (nums_seen.count(comp))
			{
				vector<int> temp;
				temp.push_back(comp);
				temp.push_back(nums[i]);
				res.push_back(temp);
			}
			nums_seen.insert(nums[i]);
		}
		else if (comp == nums[i] && (!flag))
			// special case that we detect two or more elements equal to target / 2
		{
			vector<int> temp;
			temp.push_back(nums[i]);
			temp.push_back(nums[i]);
			res.push_back(temp);
			flag = 1;
		}

	}
	return res;
}


int main()
{
	vector<int> array = {1, -1, 3, 2, -1, 5, -4, -1};
	vector<vector<int>> three = threeSum(array, 0);
	for (int i = 0; i < three.size(); ++i)
	{
		cout << "The pair is: ";
			for (int j = 0; j < three[0].size(); ++j)
				cout << three[i][j] << ' ';
		cout << endl;
	}

}