#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void BFS(vector<bool> &daTham, const vector<vector<int>> &danhSachKe, int u)
{
    queue<int> q;
    q.push(u);
    daTham[u] = true;

    while (!q.empty())
    {
        int dinh = q.front();
        q.pop();

        for (int v : danhSachKe[dinh])
        {
            if (!daTham[v])
            {
                daTham[v] = true;
                q.push(v);
            }
        }
    }
}


int soThanhPhanLienThong(const vector<vector<int>> &danhSachKe)
{
    int n = danhSachKe.size(), kq = 0;
    vector<bool> daTham(n, false);
    for (int i = 0; i < n; i++)
    {
        if (!daTham[i])
        {
            kq++;
            BFS(daTham, danhSachKe, i);
        }
    }
    return kq;
}

int main()
{
    int n;
    cout << "Nhap so dinh: ";
    cin >> n;

    vector<vector<int>> danhSachKe(n);
    cout << "Nhap danh sach ke (nhap cac dinh ke cho moi dinh, ket thuc bang -1):\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Dinh " << i << ": ";
        int dinhKe;
        while (cin >> dinhKe && dinhKe != -1)
        {
            danhSachKe[i].push_back(dinhKe);
        }
    }

    int kq = soThanhPhanLienThong(danhSachKe);
    cout << "So thanh phan lien thong: " << kq << endl;

    return 0;
}
