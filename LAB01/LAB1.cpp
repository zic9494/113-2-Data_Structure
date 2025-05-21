class Solution {
    public:
        bool isMonotonic(vector<int>& nums) {
            int count = 0;
            
            count++;
            // 排除只有一個值的情況
            if (nums.size() == 1){
                count++;
                return true;
            }
            
            count += 2 ;
            //判斷數列上升或下降，排除相同值的情況
            int in_decrease = 1;
            int p = 1;

            //第一次while判斷
            count += 3;
            while (nums[0] == nums[p]){
                
                //if判斷
                count+=2;
                if ( p == (nums.size()-1) ){
                    count++;
                    return true;
                }

                //p遞增
                count++;
                p++;
                //追加while判斷
                count += 3;
            }

            //if判斷
            count+=3;
            if (nums[p]-nums[0]<0){
                count++;
                in_decrease = -1;
            }
            
            count++;//for初始化
            //判斷是否為單調數列
            for(int i = 0; i < nums.size()-1; i++){
                //for判斷
                count+=2;
                
                //if判斷
                count+=6;
                if ( (in_decrease * ( nums[i+1] - nums[i])) < 0 ){
                    count++;
                    return false;
                }
                
                //for遞增
                count++;
            }
    
            return true;
        }
};