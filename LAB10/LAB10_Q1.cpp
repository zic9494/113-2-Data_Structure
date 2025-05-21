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
    int Breadth_first_search(TreeNode* root, int target_layer) {
        if (!root) return 0;// 拒絕空樹
        queue<TreeNode*> q;
        q.push(root);
        int current_layer = 0;

        while (!q.empty()) {
            int level_size = q.size(); //判斷父層有多少兄弟
            int level_sum = 0;
            for (int i=0;i<level_size;i++){
                TreeNode* node = q.front(); q.pop();//依序取出兄弟們
                if (current_layer == target_layer)level_sum+=node ->value;// 目標等級
                if (node ->left) q.push(node->left); // 預處理下一層左兒子
                if (node->right) q.push(node->right);// 預處理下一層右兒子
            }
            if (current_layer==target_layer)return level_sum; //算完目標層跳過後面
            current_layer++;
        }
        return INT_MIN; //找不到
    }
};

int main(){
    BinaryTree tree;
    vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9, EMPTY, EMPTY, 10, 11, EMPTY, EMPTY};
    tree.bulidTree(arr);

    cout << "BFS Result: ";
    tree.BFS(tree.root);
    cout << endl;
    
    cout<<"請輸入要查詢的樹高： ";
    int layer;
    cin>>layer;
    int ans = tree.Breadth_first_search(tree.root, layer);
    if (ans != INT_MIN)cout<<"第"<<layer<<"層的總合為："<< ans<<endl;
    else cout<<"超過樹高";
}