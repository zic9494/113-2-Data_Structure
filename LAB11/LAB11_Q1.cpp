#include<iostream>
#include<vector>
#include<fstream>
#include<cstring>
#include<sstream>
using namespace std;

class Product{
public:
    char name[100]; // 商品名稱
    int popularity; // 人氣
    int deadline;   // 期效
};

void Loadfile(const char* filename, vector<Product>* inp){
    ifstream ifs(filename);
    if (!ifs.is_open()){
        cout<<"Failed to open file.\n";
        return ;
    }
    
    string line; //一行一行讀
    getline(ifs, line); // 不需要第一行的數字
    while (getline(ifs, line)){
        istringstream iss(line);
        string part;// 將資料一空格分段處理
        Product p;

        p.name[0]='\0';// 初始化字串
        while(iss >> part){// 讀入各組文字
            if(isdigit(part[0])){
                p.deadline = stoi(part);// 遇到數字代表後面只會有效期與熱門度
                iss >> p.popularity;
                break;
            }else{
                if(strlen(p.name)>0) strcat(p.name, " ");// 文字間的空格
                strcat(p.name, part.c_str());
            }
        }

        inp->push_back(p);
    }
    ifs.close();
}

vector<Product> Sort(vector<Product> inp){
    for (int i=0; i < inp.size();i++){
        for (int j=0;j<inp.size()-1-i;j++){ // 氣泡排序法
            if (inp[j].deadline > inp[j+1].deadline)swap(inp[j], inp[j+1]);// 依照效期大小降序排列
            else if (inp[j].deadline == inp[j+1].deadline){
                if(inp[j].popularity<inp[j+1].popularity)swap(inp[j], inp[j+1]);// 效期相同，依照熱門度升序排列
            }
        }
    }
    return inp;
}

int main(){
    vector<Product> inp;
    Loadfile("input3.txt", &inp);
    vector<Product> ans = Sort(inp);
    cout<<"商品排序："<<endl;
    for (int i=0;i<ans.size();i++){
        cout<<ans[i].name<<endl;
    }
    return 0;
}