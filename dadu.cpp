#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;


struct pemain {
    string nama;
    int angka_acak = 0;
    int total = 0;
    int selisih = 0;
    int skor_tiebreak = 0;
};

class maindadu{
private:
    vector <pemain> datapemain;
    vector <pemain> peserta_tie_break;
    mt19937 gen;
    uniform_int_distribution<> dadu;

public:
    maindadu() : gen(time(0)), dadu(1,6) {}

    void tambahpemain(const pemain& p){
        datapemain.push_back(p);
    }



    void urutkanPemain() {
    sort(datapemain.begin(), datapemain.end(), [](const pemain& a, const pemain& b) {
        if (a.selisih != b.selisih)
            return a.selisih < b.selisih;

        return a.skor_tiebreak > b.skor_tiebreak;
    });
}


    void lempardadu(int jlh_pemain){
        for (int i = 0;i<3;i++){
            cout <<"Putaran ke-" <<i+1 << "\n\n";
            for(int j = 0;j<jlh_pemain;j++){
                datapemain[j].angka_acak = dadu(gen);
                cout <<"Pemain ke-" << j+1 <<" atau " << datapemain[j].nama <<endl;
                cout <<"Dadu anda bernilai: " << datapemain[j].angka_acak <<endl;
                datapemain[j].total += datapemain[j].angka_acak;
                cout <<"Skor anda saat ini: " << datapemain[j].total <<"\n\n";
            }
            cout <<endl;
        }
    }

    void tampilkanhasil(int target){
        for (auto& p : datapemain) {
            p.selisih = abs(target - p.total);
        }
        urutkanPemain();
        cout << left << setw(10) << "Ranking"
         << "| " << setw(10) << "Nama"
         << "| " << setw(6) << "Skor"
         << "| " << setw(13) << "Selisih Skor" << endl;
        cout << string(50, '=') << endl;

        for (int i = 0; i < datapemain.size(); i++) {
            datapemain[i].selisih = abs(target - datapemain[i].total);
            cout << left << setw(10) << (i + 1)
                << "| " << setw(10) << datapemain[i].nama
                << "| " << setw(6) << datapemain[i].total
                << "| " << setw(13) << datapemain[i].selisih << endl;
        }
        cout <<"Tekan enter untuk lanjut...";
        cin.get();

    }

    void tiebreak(int jlh_pemain,int target){
        int min_selisih = datapemain[0].selisih;
        for (auto& p : datapemain) {
            p.selisih = abs(target - p.total);
        }
        for (int i = 1; i < jlh_pemain; i++) {
            if (datapemain[i].selisih < min_selisih) {
                min_selisih = datapemain[i].selisih;
            }
        }
        for (int i = 0; i < jlh_pemain; i++) {
            if (datapemain[i].selisih == min_selisih) {
                peserta_tie_break.push_back(datapemain[i]);
            }
        }
        if (peserta_tie_break.size() <= 1) return;

        cout << string(50, '=') << endl;
        cout <<"Selamat Datang di Game Tie Breaker\n";
        cout << string(50, '=') << endl;
        cout <<"Peserta Tie Breaker: \n";
        for (int i =0;i<peserta_tie_break.size();i++){
            cout << i+1 <<". " << peserta_tie_break[i].nama <<endl;
        }
        cout <<"Tekan enter untuk lanjut bermain...";
        cin.get();

        int player_num = 1;
        for (auto& p : peserta_tie_break) {
            cout <<"Pemain ke-" << player_num << " atau " << p.nama << endl;
            player_num++;
            p.angka_acak = dadu(gen);
            cout <<"Dadu anda bernilai: " << p.angka_acak <<"\n\n";
            for (auto& dp : datapemain) {
                if (dp.nama == p.nama) {
                    dp.skor_tiebreak = p.angka_acak;
                    dp.selisih = abs(target - dp.total);
                    break;
                }
            }
        }
        urutkanPemain();
        cout << left << setw(10) << "Ranking"
        << "| " << setw(10) << "Nama"
        << "| " << setw(6) << "Skor"
        << "| " << setw(13) << "Selisih Skor"
        << "| " << setw(14) << "Skor Tie Break" << endl;
        cout << string(70, '=') << endl;

        for (int i = 0; i < datapemain.size(); i++) {
            cout << left << setw(10) << (i + 1)
                << "| " << setw(10) << datapemain[i].nama
                << "| " << setw(6) << datapemain[i].total
                << "| " << setw(13) << datapemain[i].selisih
                << "| " << setw(14) << datapemain[i].skor_tiebreak << endl;
        }

    }

    void bersihkandata(){
        datapemain.clear();
        peserta_tie_break.clear();
    }
};

int main(){
    pemain p;
    maindadu play;
    int jlh_pemain,target;
    char ulang;
do {
    play.bersihkandata();
    cout << string(50, '=') << endl;
    cout <<"Selamat Datang di Game Dadu Kelompok ONOJ\n";
    cout << string(50, '=') << endl;
    cout <<"NOTE: Pemain maksimal berjumlah 5 orang\n\n";
    loop: cout <<"Masukan jumlah pemain: ";
    cin >> jlh_pemain;
    if (jlh_pemain >5){
        cout <<"jumlah pemain lebih dari 5 orang!!\n";
        cout <<"silahkan input jumlah pemain lagi\n";
        goto loop;
    }
    loop2: cout <<"Masukan skor target: ";
    cin >> target;
    if (target >18){
        cout <<"skor target melebihi 18!!\n";
        cout <<"silahkan input skor target lagi lagi\n";
        goto loop2;
    }

    cin.ignore();
    for (int i = 0;i<jlh_pemain;i++){
        cout <<"Nama Pemain ke-" << i+1 <<": ";
        getline(cin,p.nama);
        play.tambahpemain(p);
    }
    cout <<endl;
    play.lempardadu(jlh_pemain);

    cout<<"Skor target: " << target <<endl;
    play.tampilkanhasil(target);
    play.tiebreak(jlh_pemain,target);
    
    
    cout << "Apakah ingin lanjut bermain (Y/T): ";
    cin >> ulang;
} while (ulang == 'Y' || ulang == 'y');
cout << "TERIMA KASIH SUDAH MENCOBA GAME KAMI!!!" << endl;
return 0;
}