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

// Hàm chuyển từ danh sách cạnh sang danh sách kề
vector<vector<int>> chuyenSangDanhSachKe(int n, const vector<pair<int, int>> &danhSachCanh)
{
    vector<vector<int>> danhSachKe(n);
    for (auto [u, v] : danhSachCanh)
    {
        danhSachKe[u].push_back(v);
        danhSachKe[v].push_back(u); // nếu là đồ thị vô hướng
    }
    return danhSachKe;
}

int main()
{
    int n, m;
    cout << "Nhap so dinh: ";
    cin >> n;
    cout << "Nhap so canh: ";
    cin >> m;

    vector<pair<int, int>> danhSachCanh;
    cout << "Nhap cac canh (u v):\n";
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        danhSachCanh.push_back({u, v});
    }

    vector<vector<int>> danhSachKe = chuyenSangDanhSachKe(n, danhSachCanh);

    int kq = soThanhPhanLienThong(danhSachKe);
    cout << "So thanh phan lien thong: " << kq << endl;

    return 0;
}
/*
8
6
0 1
1 2
3 4
5 6
6 7
5 7
*/