#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

vector<int> twoSum(vector<int>& nums, int target);

int main() {
    vector<int> nums {2, 11, 15, 7};
    int target = 9;

    for (int i : twoSum(nums, target)) {
        cout << i << "\n";
    }
    return 0;
}

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash;

    for (int i = 0; i < nums.size(); i++) {
        int n = target - nums[i];
        if (hash.find(n) != hash.end()) {
            return {hash[n], i};
        }
        hash[nums[i]] = i;
    }
    return {};
}
