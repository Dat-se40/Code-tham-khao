#include <iostream>
#include<vector>

using namespace std ; 
class Vector
{
private:
    vector<int> container;
    int size;

public:
    Vector(int n = 0 ) : size(n) { container.resize(n); }

    friend istream &operator>>(istream &in, Vector &v)
    {   
        if ( v.size == 0 ){
            in>>v.size;
            v.container.resize(v.size);
        } 
        for (int &x : v.container)
            cin >> x;
        return in;
    }

    friend ostream &operator<<(ostream &out, const Vector &v)
    {
        for (int x : v.container)
            cout << x << " ";
        return out;
    }

    Vector operator+(const Vector &v)
    {
        if (v.size != size)
            exit(1);

        Vector ans(size);
        for (int i = 0; i < size; i++)
            ans.container[i] = container[i] + v.container[i];
        return ans;
    }

    int &operator()(int i)
    {
        if (i < 0 || i >= size)
            exit(1);
        return container[i];
    }
};
  int main()
{
    Vector A(3), B(3), C(3) ;  // Tạo vector có kích thước bằng 3
    cout<< A << endl; // 0 0 0
    cin >> B >> A; 
    C = A + B;
    cout << " c = a + b = " << C<<endl;
    cout << "B(1) = " << B(1) << endl; // gia tri thu 2
    return 0;
}
