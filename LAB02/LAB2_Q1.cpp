#include <vector>
#include <set>
using namespace std;

class Solution {
    public:
        int findLucky(vector<int>& arr) {
            int lucky_num = -1; // 設定初始值 1
            set<int> nums{arr.begin(), arr.end()}; // 將 arr 轉換為 set，一次插入set是logn= +nlogn
            
            for(auto num: nums){ 
                // 指派變數*2 = +2n 
                int i = 0;
                int count =0;
                while(i<arr.size()){
                    // 迴圈判斷*1、i遞增*2 = 3n^2
                    if(arr[i] == num){
                        count++;
                    }
                    i++;
                }

                //判斷*3、指派*1 = +4n
                if (count == num && num > lucky_num){
                    lucky_num = num;
                }
            }
            //返回結果*1 = +1
            return lucky_num;
            //f(n) = nlogn + 2n + 3n^2 + 4n + 1 = 3n^2 + 4n + nlogn + 2 => O(n^2)
        }
};