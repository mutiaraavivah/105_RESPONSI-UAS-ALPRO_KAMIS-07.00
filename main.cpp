#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

class FileReader {
private:
    const int bufferSize;
    char* buffer;
    string filename;
    ifstream file;

public:
    FileReader(const string& fname, int size = 100)
        : bufferSize(size), filename(fname), file() {
        buffer = new char[bufferSize];
    }

    bool openFile() {
        file.open(filename.c_str());
        return file.is_open();
    }

    void readFile() {
        if (!file) {
            cout << "Gagal membuka file!" << endl;
            return;
        }

        cout << "Isi file " << filename << ":\n";
        while (file.getline(buffer, bufferSize)) {
            cout << buffer << endl;
        }
    }

    ~FileReader() {
        if (file.is_open()) {
            file.close();
        }
        delete[] buffer;
        buffer = NULL;
    }
};

struct Mahasiswa {
    string nim;
    string nama;
    float uts, uas;
    float nilaiAkhir;
    string status;
};

void hitungNilai(Mahasiswa &m) {
    m.nilaiAkhir = (m.uts + m.uas) / 2;
    m.status = (m.nilaiAkhir >= 75) ? "Lulus" : "Tidak Lulus";
}

void tampilkanData(const vector<Mahasiswa>& mhs) {
    cout << left << setw(12) << "NIM" << setw(15) << "Nama" << setw(6) << "UTS"
         << setw(6) << "UAS" << setw(15) << "Nilai Akhir" << setw(15) << "Status" << endl;
    for (int i = 0; i < mhs.size(); ++i) {
        cout << left << setw(12) << mhs[i].nim << setw(15) << mhs[i].nama
             << setw(6) << mhs[i].uts << setw(6) << mhs[i].uas
             << setw(15) << mhs[i].nilaiAkhir << setw(15) << mhs[i].status << endl;
    }
}

void cariNama(vector<Mahasiswa> &mhs, const string &key) {
    bool ditemukan = false;
    for (int i = 0; i < mhs.size(); i++) {
        if (mhs[i].nama == key) {
            cout << "Ditemukan: " << mhs[i].nama
                 << " | Nilai Akhir: " << mhs[i].nilaiAkhir
                 << " | Status: " << mhs[i].status << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan)
        cout << "Nama tidak ditemukan." << endl;
}

void cariTertentu(vector<Mahasiswa> &mhs, float nilai) {
    bool ditemukan = false;
    for (int i = 0; i < mhs.size(); i++) {
        if (mhs[i].nilaiAkhir == nilai) {
            cout << "Mahasiswa dengan nilai " << nilai << ": "
                 << mhs[i].nama << " (" << mhs[i].nim << ")" << endl;
            ditemukan = true;
        }
    }
    if (!ditemukan)
        cout << "Tidak ada mahasiswa dengan nilai tersebut." << endl;
}

void urutkan(vector<Mahasiswa> &mhs, bool naik) {
    for (int i = 0; i < mhs.size() - 1; ++i) {
        for (int j = i + 1; j < mhs.size(); ++j) {
            if ((naik && mhs[i].nilaiAkhir > mhs[j].nilaiAkhir) ||
                (!naik && mhs[i].nilaiAkhir < mhs[j].nilaiAkhir)) {
                swap(mhs[i], mhs[j]);
            }
        }
    }
}

void simpanNilaiAkhir(vector<Mahasiswa> &mhs) {
    ofstream out("nilai_akhir.txt");
    for (int i = 0; i < mhs.size(); i++) {
        out << mhs[i].nim << " "
            << mhs[i].nama << " "
            << mhs[i].nilaiAkhir << endl;
    }
    out.close();
}

//void simpanStatus(vector<Mahasiswa> &mhs) {
//    ofstream out("status_lulus.txt");
//    for (int i = 0; i < mhs.size(); i++) {
//        out << mha[i].nim << " "
//            << mhs[i].nama << " "
//            <, mhs[i].status << endl;
//    }
//    out.close();
//}


int main() {
    vector<Mahasiswa> mhs;
    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "File data.txt tidak ditemukan!\n";
        return 1;
    }

    int n;
    file >> n;
    Mahasiswa m;
    for (int i = 0; i < n; ++i) {
        file >> m.nim >> m.nama >> m.uts >> m.uas;
        hitungNilai(m);
        mhs.push_back(m);
    }
    file.close();

    int pilih;
    do {
        cout << "\nMENU PROGRAM:\n";
        cout << "1. Tampilkan data\n";
        cout << "2. Cari berdasarkan nama\n";
        cout << "3. Cari mahasiswa dengan nilai tertentu\n";
        cout << "4. Urutkan nilai dari besar ke kecil\n";
        cout << "5. Urutkan nilai dari kecil ke besar\n";
        cout << "6. Simpan nilai akhir ke file\n";
        cout << "7. Simpan status lulus ke file\n";
        cout << "0. Keluar\n";
        cout << "\nPilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilkanData(mhs); 
				break;
            case 2: {
                string nama;
                cout << "Masukkan nama yang ingin dicari: "; cin >> nama;
                cariNama(mhs, nama); 
				break;
            }
            case 3: {
                float nilai;
                cout << "Masukkan nilai yang ingin dicari: "; cin >> nilai;
                cariTertentu(mhs, nilai); break;
            }
            case 4: urutkan(mhs, false); cout << "Data berhasil diurutkan dari besar ke kecil.\n"; break;
            case 5: urutkan(mhs, true); cout << "Data berhasil diurutkan dari kecil ke besar.\n"; break;
            case 6: simpanNilaiAkhir(mhs); cout << "Disimpan ke nilai_akhir.txt\n"; break;
            //case 7: simpanStatus(mhs); cout << "Disimpan ke status_lulus.txt\n"; break;
        }
    } while (pilih != 0);

    return 0;
}
