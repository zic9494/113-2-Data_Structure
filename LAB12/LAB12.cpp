class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int p1 = m - 1;              // nums1 指標（有效元素）
        int p2 = n - 1;              // nums2 指標
        int p = m + n - 1;           // nums1 最末端指標

        while (p1 >= 0 && p2 >= 0) {
            if (nums1[p1] > nums2[p2]) {
                nums1[p--] = nums1[p1--];
            } else {
                nums1[p--] = nums2[p2--];
            }
        }

        // 如果 nums2 還有剩，補上去（nums1 剩下的不用補，已在原位）
        while (p2 >= 0) {
            nums1[p--] = nums2[p2--];
        }
    }
};
