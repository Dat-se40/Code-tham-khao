#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Lớp trừu tượng đại diện cho một yếu tố thời tiết
class YeuToThoiTiet
{
protected:
    float soLieu;
public:
    YeuToThoiTiet(float sl = 0) : soLieu(sl) {}
    virtual ~YeuToThoiTiet() {}
    void nhap() { cin >> soLieu; }
    float laySoLieu() const { return soLieu; }
    void datSoLieu(float sl) { soLieu = sl; }
    virtual void thayDoi(float giaTriT1, float doCao, float doChePhu) = 0;
    virtual string tenYeuTo() const = 0;
};

// Các lớp con tương ứng từng yếu tố thời tiết
class NhietDo : public YeuToThoiTiet
{
public:
    using YeuToThoiTiet::YeuToThoiTiet;
    void thayDoi(float t1, float doCao, float chePhu) override
    {
        float delta = (soLieu - t1) * (1 - doCao / 10000) * (1 - chePhu);
        soLieu = t1 + delta;
    }
    string tenYeuTo() const override { return "Nhiet do"; }
};

class DoAm : public YeuToThoiTiet
{
public:
    using YeuToThoiTiet::YeuToThoiTiet;
    void thayDoi(float t1, float, float chePhu) override
    {
        soLieu = t1 + (soLieu - t1) * chePhu;
    }
    string tenYeuTo() const override { return "Do am"; }
};

class TocDoGio : public YeuToThoiTiet
{
public:
    using YeuToThoiTiet::YeuToThoiTiet;
    void thayDoi(float, float, float chePhu) override
    {
        soLieu = soLieu * (1 - chePhu);
    }
    string tenYeuTo() const override { return "Toc do gio"; }
};

class BucXa : public YeuToThoiTiet
{
public:
    using YeuToThoiTiet::YeuToThoiTiet;
    void thayDoi(float, float, float chePhu) override
    {
        soLieu = soLieu * (1 - chePhu / 2);
    }
    string tenYeuTo() const override { return "Buc xa"; }
};

class LuongMua : public YeuToThoiTiet
{
public:
    using YeuToThoiTiet::YeuToThoiTiet;
    void thayDoi(float, float, float chePhu) override
    {
        soLieu = soLieu * chePhu;
    }
    string tenYeuTo() const override { return "Luong mua"; }
};

// Tập hợp 5 yếu tố khí tượng tại 1 thời điểm
class TapHopBienSo
{
private:
    vector<YeuToThoiTiet *> bienSo;

public:
    TapHopBienSo()
    {
        bienSo.resize(5);
        bienSo[0] = new NhietDo;
        bienSo[1] = new DoAm;
        bienSo[2] = new TocDoGio;
        bienSo[3] = new BucXa;
        bienSo[4] = new LuongMua;
    }

    ~TapHopBienSo()
    {
        for (auto y : bienSo)
            delete y;
    }


    void nhap(){
        for (auto y : bienSo)
        {
            cout << "Nhap " << y->tenYeuTo() << ": ";
            y->nhap();
        }
    }

    void operator=(const TapHopBienSo &b)
    {
        for (int i = 0; i < 5; i++)
        {
            bienSo[i]->datSoLieu(b.bienSo[i]->laySoLieu());
        }
    }
    YeuToThoiTiet *operator[](int index) const
    {
        if (index < 0 || index >= bienSo.size())
        {
            return NULL;
        }
        return bienSo[index];
    }
};

// Lớp mô tả một vùng địa lý
class VungDiaLy
{
    string ten;
    float doCao;
    float doChePhu;
    vector<TapHopBienSo> thoiDiem; // thoiDiem[0] = t1, thoiDiem[1] = t2
public:
    VungDiaLy() : ten(""), doCao(0), doChePhu(0)
    {
        thoiDiem.resize(2);
    }

    void nhapThongTin()
    {
        cout << "Nhap ten vung: ";
        cin >> ten;
        cout << "Nhap do cao (m) va do che phu (0-1): ";
        cin >> doCao >> doChePhu;
    }

    void nhapBienSo(int chiSo)
    {
        if (chiSo < 0 || chiSo > 1)
            return;
        cout << "Nhap cac bien so tai thoi diem t" << chiSo + 1 << ":\n";
        thoiDiem[chiSo].nhap();
    }

    void capNhatBienSo()
    {
        for (int i = 0; i < 5; ++i)
        {
            thoiDiem[1][i]->thayDoi(
                thoiDiem[0][i]->laySoLieu(),
                doCao, doChePhu);
        }
    }

    void ganThoiDiemT2(const TapHopBienSo &tapBienSo)
    {
        thoiDiem[1] = tapBienSo;
    }

    float mucThayDoiNhietDo() const
    {// theta2_adj = theta1 + delta ; 
        return thoiDiem[1][0]->laySoLieu() - thoiDiem[0][0]->laySoLieu();
    }

    string duBaoKieuThoiTiet() const
    {
        float T = thoiDiem[1][0]->laySoLieu();
        float H = thoiDiem[1][1]->laySoLieu();
        float W = thoiDiem[1][2]->laySoLieu();
        float S = thoiDiem[1][3]->laySoLieu();
        float P = thoiDiem[1][4]->laySoLieu();

        if (P >= 15 && W >= 12 && T < 25)
            return "Giong bao";
        if (P > 5 && H >= 70)
            return "Mua nhieu";
        if (T >= 30 && H <= 50 && S > 800)
            return "Nong kho";
        if (H >= 80 && W >= 8)
            return "Gio am";
        return "On hoa";
    }

    string layTenVung() const
    {
        return ten;
    }
};

// === CHƯƠNG TRÌNH CHÍNH ===
int main()
{
    {
        // cout << "=== YEU CAU 2.1 ===\n";
        // VungDiaLy motVung;
        // motVung.nhapThongTin();
        // motVung.nhapBienSo(0); // t1
        // motVung.nhapBienSo(1); // t2
        // motVung.capNhatBienSo();
        // cout << "=> Du bao thoi tiet: " << motVung.duBaoKieuThoiTiet() << "\n";
    }

    {
        cout << "\n=== YEU CAU 2.2 ===\n";
        TapHopBienSo bienSoChung;
        bienSoChung.nhap();

        int soLuongVung;
        cout << "Nhap so luong vung: ";
        cin >> soLuongVung;
        vector<VungDiaLy> danhSachVung(soLuongVung);
        VungDiaLy vungNhietDoTangCaoNhat;

        for (int i = 0; i < soLuongVung; ++i) {
            cout << "\n-- Vung thu " << i + 1 << " --\n";
            danhSachVung[i].nhapThongTin();
            danhSachVung[i].nhapBienSo(0); // t1
            danhSachVung[i].ganThoiDiemT2(bienSoChung);
            danhSachVung[i].capNhatBienSo();
            if (danhSachVung[i].mucThayDoiNhietDo() > vungNhietDoTangCaoNhat.mucThayDoiNhietDo()) {
                vungNhietDoTangCaoNhat = danhSachVung[i];
            }
        }

        cout << "\nVung co muc thay doi nhiet do lon nhat: " << vungNhietDoTangCaoNhat.layTenVung() << "\n";

        cout << "Danh sach cac vung co kieu thoi tiet 'Nong kho':\n";
        for (const auto& vung : danhSachVung) {
            // cout << "- " << vung.layTenVung() <<"- delta T: "<<
            //     vung.mucThayDoiNhietDo()<<"- thoi tiet: "<<vung.duBaoKieuThoiTiet()<<endl;
            if (vung.duBaoKieuThoiTiet() == "Nong kho") {
                cout << "- " << vung.layTenVung() << "\n";
            }
        }
    }

    system("pause");
    return 0;
}