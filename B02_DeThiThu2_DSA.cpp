#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<float> vaChamThienThach(vector<float> &thienThach)
{
    stack<float> trenDuong; 
    for(float thanh : thienThach){
        bool chuaVaCham = true ; 
        // check va cham 
        while(!trenDuong.empty() && chuaVaCham && trenDuong.top() > 0 && thanh < 0  ){
            if(trenDuong.top() < - thanh) trenDuong.pop() ; 
            else if ( trenDuong.top() > - thanh ){
                chuaVaCham = false;
            }else {
                chuaVaCham = false;
                trenDuong.pop() ; 
            }
        }
        if(chuaVaCham) trenDuong.push(thanh);
    }

    vector<float> ans(trenDuong.size());
    for(int i = ans.size() -1 ; i >= 0 ;i--){
        ans[i] = trenDuong.top() ; 
        trenDuong.pop() ; 
    }
    return ans ; 
}
int main()
{
    int n, m;
    cin >> n;
    vector<vector<float>> test(n);
    vector<vector<float>> ketQua;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        test[0].resize(m);
        for (float &x : test[0])
            cin >> x;
        ketQua.push_back(vaChamThienThach(test[0]));
    }
    for(vector<float> kq : ketQua){
        for(int x : kq) cout<<x<<" ";
        cout<<"\n";
    }
    return 0;
}