#include <iostream>
#include <queue>
#include <vector>
using namespace std;
const int EMPTY=INT_MIN;
class TreeNode{
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val):value(val), left(nullptr), right(nullptr){}
};

class BinaryTree{
public:
    TreeNode* root;
    BinaryTree():root(nullptr){}
    TreeNode* bulidTree(const vector<int>& arr){
        if(arr.empty() || arr[0]==EMPTY)return nullptr;
        queue<TreeNode**> q;
        root = new TreeNode(arr[0]);
        q.push(&root);// 刻意塞入，彌補之後每一次要pop

        size_t i =1;
        while (!q.empty() && i< arr.size()){
            TreeNode** nodePtr = q.front();
            q.pop();

            if(i<arr.size()){
                if (arr[i] != EMPTY){
                    (*nodePtr)->left = new TreeNode(arr[i]);
                    q.push(&((*nodePtr)->left));
                }
                i++;
            }
            if(i<arr.size()){
                if (arr[i] != EMPTY){
                    (*nodePtr)->right = new TreeNode(arr[i]);
                    q.push(&((*nodePtr)->right));
                }
                i++;
            }
        }
        return root;
    }
    void BFS(TreeNode* root) {
        if (root == nullptr) return;
        queue<TreeNode*> q;//建立queue儲存待處理的節點指標
        q.push(root); // 將根節點的指標加入queue

        while (!q.empty()) {
            TreeNode* current = q.front();// 取出queue的第一個節點指標
            q.pop();// 將該節點從queue中刪除
            cout << current->value << " ";
            if (current->left) q.push(current->left);  // 將左子節點的指標加入queue
            if (current->right) q.push(current->right);// 將左子節點的指標加入queue
        }
    }
    TreeNode* Depth_frist_sreach(TreeNode* node ,int target_value){
        if (node == nullptr) return nullptr;// 走到底了或本身就是空指標
        if (node->value == target_value)return node;// 找到目標數字

        TreeNode* LeftNode = Depth_frist_sreach(node->left, target_value);// 從左邊開始找，沒找到回傳nullptr
        if (LeftNode!= nullptr)return LeftNode;// 在左邊找到了

        TreeNode* RightNode = Depth_frist_sreach(node->right, target_value);// 從右邊找
        return RightNode;// 在右邊找到回傳指標，沒找到就回傳空指標
    }
    
    int Tree_Sum(TreeNode* node){
        if (node == nullptr)return 0;
        int left = Tree_Sum(node->left);//左邊的總和
        int right = Tree_Sum(node->right);//右邊得總和
        return left + right + node->value;//左邊+右邊+自己
    }
    
};

int main(){
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, EMPTY, EMPTY, 10, 11, EMPTY, EMPTY};
    tree.bulidTree(arr);

    cout << "BFS Result: ";
    tree.BFS(tree.root);
    cout << endl;
    
    cout<<"請輸入要查詢的數值： ";
    int target_number;
    cin>>target_number;
    TreeNode* target_tree = tree.Depth_frist_sreach(tree.root, target_number);//找到目標節點的位址
    if (target_tree != nullptr){
        int left_sum = tree.Tree_Sum(target_tree->left);//算左子樹
        
        int right_sum = tree.Tree_Sum(target_tree->right);//算右子樹
        
        if (left_sum==right_sum && right_sum==0)cout<<"沒有子樹"<<endl;
        else{
            cout<<"左子樹總和： "<< left_sum<<endl;
            cout<<"右子樹總和： "<< right_sum<<endl;
            if (left_sum==right_sum && right_sum==0)cout<<"一樣大"<<endl;
            else{
                if (left_sum>right_sum)cout<<"左";
                else cout<<"右";
                cout<<"子樹比較大";
            }
        }
    }else cout<<"數字不存在"<<endl;

}