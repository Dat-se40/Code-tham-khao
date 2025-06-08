#include <iostream>
#include <vector>
#include <stack>
using namespace std;

vector<int> vaChamThienThach(vector<int> &thienThach)
{
    stack<int> trenDuong;
    for (int thach : thienThach)
    {
        bool chuaBiPha = true;
        while (chuaBiPha && !trenDuong.empty() && thach < 0 && trenDuong.top() > 0)
        {
            if (trenDuong.top() < -thach)
            {
                trenDuong.pop();
            }
            else if (trenDuong.top() == -thach)
            {
                trenDuong.pop();
                chuaBiPha = false;
            }
            else
            {
                chuaBiPha = false;
            }
        }
        if (chuaBiPha)
        {
            trenDuong.push(thach);
        }
    }
    vector<int> ketQua(trenDuong.size());
    for (int i = trenDuong.size() - 1; i >= 0; i--)
    {
        ketQua[i] = trenDuong.top();
        trenDuong.pop();
    }
    return ketQua;
}
int main()
{
    int n, m;
    cin >> n;
    vector<vector<int>> test(n);
    vector<vector<int>> ketQua;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        test[0].resize(m);
        for (int &x : test[0])
            cin >> x;
        ketQua.push_back(vaChamThienThach(test[0]));
    }
    for(vector<int> kq : ketQua){
        for(int x : kq) cout<<x<<" ";
        cout<<"\n";
    }
    return 0;
}