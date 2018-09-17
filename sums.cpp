// My summary on Two Sums, Three Sums problems, and different variants


# include <iostream>
# include <vector>
# include <unordered_set>
# include <unordered_map>
#include <algorithm>

using namespace std;


// Case 2: two sum, find all unique indices
// Solution 1: We can use one pass hash table, along with a multimap to maintain all indices of an element's complement

vector<vector<int>> twoSum1(vector<int>& nums, int target)
{
	vector<vector<int>> res;
	unordered_map<int, vector<int>> nums_seen;
	// quick look up from value to indices

	for (int i = 0; i < nums.size(); ++i)
	{
		int comp = target - nums[i];
		if (nums_seen.count(comp))
		{
			vector<int> comp_arr = nums_seen[comp];
			for (int j = 0; j < comp_arr.size(); ++j)
			{
				vector<int> pairs;
				pairs.push_back(comp_arr[j]);
				pairs.push_back(i);
				res.push_back(pairs);
			}
		}
		nums_seen[nums[i]].push_back(i);
	}
	
	return res;
}


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

// case 5: two sum closest, three sum closest 
// Solution 1: one pass hash table, and maintain a min difference 
// Solution 2: sort + bidirectional (constant space, cheap if the input array is presorted)

int twoSumClosest(vector<int>& nums, int target, int pos = 0)
{
	// sort the input array
	// sort(nums.begin(), nums.end());

	int n = nums.size();
	int l = pos, r = n - 1;
	int sum_closest;
	int min_diff = INT32_MAX;
	while (l < r)
	{
		int sum = nums[l] + nums[r];
		int diff = sum > target ? (sum - target) : (target - sum);
		if (diff < min_diff)
		{
			min_diff = diff;
			sum_closest = sum;
		}
		if (sum < target) ++l;
		else if (sum > target) --r;
		else break; // if sum == target
	}
	return sum_closest;
}

int threeSumClosest(vector<int>& nums, int target)
{
	vector<int> nums_sorted = nums;
	sort(nums_sorted.begin(), nums_sorted.end());


	int i = 0, n = nums_sorted.size();
	int sum_closest;
	int min_diff = INT32_MAX;
	while (i < n - 2)
	{
		int first = nums_sorted[i];
		int comp = target - first;
		int sum = first + twoSumClosest(nums_sorted, comp, i + 1);
		int diff = (sum > target) ? sum - target : target - sum;
		if (diff == 0) 
			return target;
		else if (diff < min_diff)
		{
			min_diff = diff;
			sum_closest = sum;
		}
		
		while (nums_sorted[i] == first)
			++i;
	}

	return sum_closest;
}





int main()
{
	vector<int> array = {1, -1, 3, 2, -1, 5, -4, -1};
	vector<int> array2 = { 1, 6, 3, 5, 5, 6, 7, 4, 9, 5 };
	/*
	vector<vector<int>> three = threeSum(array, 0);
	for (int i = 0; i < three.size(); ++i)
	{
		cout << "The pair is: ";
		for (int j = 0; j < three[0].size(); ++j)
				cout << three[i][j] << ' ';
		cout << endl;
	}
	*/

	vector<vector<int>> pairs = twoSum1(array2, 12);
	for (int i = 0; i < pairs.size(); ++i)
	{
		cout << "The pair is: ";
		for (int j = 0; j < pairs[0].size(); ++j)
			cout << pairs[i][j] << ' ';
		cout << endl;
	}

}