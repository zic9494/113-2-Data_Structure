#include <vector>
using namespace std;
// Method 1
class Solution1 {
    public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int counter = 0;//複雜度計算
    
        int count[101]={0};//計數陣列,範圍 0-100
        int n= nums.size();//陣列長度
        vector<int> result(n);//vector<int>是動態陣列,在執行分配記憶體時,可以根據 num.size()自動調整大小
        counter += 2;//宣告與指派*2 +2

        //計算每個數字的出現次數,此迴圈遍歷 nums,並統計每個數字 num 出現的次數
        for(int num:nums){
            counter++; //歷遍所有的數字 +n
            count[num]++;
        }
        
        //計算比當前數字小的數量
        for(int i=1; i<101; i++){
            count[i]+=count[i-1];
        }
        counter += 101; //統計所有數字 +101
        
        //計算 result 陣列
        for(int i=0; i<n; i++){
            counter += 8; // 進入result*1，進入nums*2，進入count*1，三元運算式*1，指派*1，迴圈判斷*1、i遞增*1 = +8n
            result[i]=(nums[i]==0)?0:count[nums[i]-1];
            //count[nums[i]-1]代表比 nums[i]小的數的數量,nums[i]==0 時則直接返回 0
        }
        counter++; //返回結果 +1
        return result;
        //f(n) = 2 + n + 101 + 8n + 1 = 9n + 104 => O(n)
    }
    
};

class Solution2 {
    public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        int counter = 0;//複雜度計算
        vector<int> result; // 存結果
        int count; // 計數器
        
        // 外層迴圈遍歷 nums 陣列中的每個元素
        for (int i = 0; i < nums.size(); i++) {
            counter += 2; // 迴圈判斷*1、i遞增*1 = +2n
            count = 0; // 每次重新計算當前元素的較小數量
            counter += 1; // count指派 +n
        
            // 內層迴圈再次遍歷 nums 陣列,統計比 nums[i] 小的元素數量
            for (int j = 0; j < nums.size(); j++) {
                counter += 6; // 迴圈判斷*1、j遞增*1、進入nums*2，count遞增＊１ = +6n^2
                if (nums[j] < nums[i]) { count++; } // 如果 nums[j] 比nums[i] 小,則計數器 +1
            }
            
            //
            counter += 1; // 推入result*1 +n
            result.push_back(count); // 將計算出的數量存入 result
        }
        // 返回結果 +1
        counter += 1;
        return result;
        // f(n)  = 2n + n + 6n^2 + n + 1 = 6n^2 + 4n + 1 => O(n^2)
    }
};