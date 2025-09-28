#include <bits/stdc++.h>
using namespace std;

struct Buku {
    string judul;
    string pengarang;
    int harga;
};

struct NodeBuku {
    Buku data;
    NodeBuku* next;
};

struct Peminjam {
    string nama;
    string judulBuku;
    string tanggalAmbil;
    int lamaPinjam;
    int totalPembayaran;
};

void tambahBuku(NodeBuku*& head, const Buku& bukuBaru) {
    NodeBuku* nodeBaru = new NodeBuku{bukuBaru, NULL};
    if (!head) {
        head = nodeBaru;
    } else {
        nodeBaru->next = head;
        head = nodeBaru;
    }
}

Buku* cariBuku(NodeBuku* head, int nomor) {
    NodeBuku* current = head;
    int counter = 1;

    while (current) {
        if (counter == nomor) {
            return &current->data;
        }
        current = current->next;
        counter++;
    }
    return NULL;
}

void tampilkanBuku(NodeBuku* head) {
    NodeBuku* current = head;
    int nomor = 1;

    while (current) {
        cout << "Nomor: " << nomor << ", Judul: " << current->data.judul << ", Pengarang: " << current->data.pengarang
             << ", Harga per Hari: " << current->data.harga << endl;
        current = current->next;
        nomor++;
    }
}

void bubbleSort(NodeBuku* head) {
    if (!head || !head->next) {
        return;
    }

    bool swapped;
    NodeBuku* temp;
    NodeBuku* end = NULL;

    do {
        swapped = false;
        temp = head;

        while (temp->next != end) {
            if (temp->data.judul > temp->next->data.judul) {
                Buku tempData = temp->data;
                temp->data = temp->next->data;
                temp->next->data = tempData;

                swapped = true;
            }
            temp = temp->next;
        }

        end = temp;

    } while (swapped);
}

void simpanPeminjamKeFile(const Peminjam& peminjam) {
    ofstream file("peminjam.txt", ios::app);
    if (file.is_open()) {
        file << " Nama: " << peminjam.nama << endl
             << " Judul: " << peminjam.judulBuku << endl
             << " Tanggal Ambil: " << peminjam.tanggalAmbil << endl
             << " Lama peminjam: " << peminjam.lamaPinjam << " hari" << endl
             << " Total pembayaran: " << peminjam.totalPembayaran << endl
             << endl;
        file.close();
    } else {
        cout << "Tidak dapat membuka file untuk menyimpan data peminjam." << endl;
    }
}

void tampilkanDaftarPeminjam() {
    ifstream file("peminjam.txt");
    string line;

    if (file.is_open()) {
        cout << "\nDaftar Peminjam:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Tidak dapat membuka file peminjam.txt." << endl;
    }
}

int hitungTotalPembayaran(const Buku& buku, int lamaPinjam) {
    return buku.harga * lamaPinjam;
}

int main() {
    system("color 9E");
	
	cout << "\t\t\t==================================================================\n" << endl;
    cout << "\t\t\t         Selamat Datang Di Program Rental Buku sederhana          \n" << endl;
    cout << "\t\t\t==================================================================\n" << endl;
	
    int menu;

    NodeBuku* daftarBuku = NULL;
    tambahBuku(daftarBuku, {"Algorithms and Programming", "I.I. Septian", 5000});
    tambahBuku(daftarBuku, {"Intro To Business Intel", "Harper Lee", 6000});
    tambahBuku(daftarBuku, {"Database Systems", "George Orwell", 7000});
    tambahBuku(daftarBuku, {"Tutorial Hidup", "Virgilius Owen", 4500});
    tambahBuku(daftarBuku, {"Belajar Jadi Wanita Idaman", "D.A. Dwiantoko", 5500});
    tambahBuku(daftarBuku, {"Jangan Takut Jadi Wibu", "L.K. Wijaya", 8000});

    bubbleSort(daftarBuku);

    stack<Peminjam> stackPeminjam;

    do {
        cout << "\n\t\t\t\t Pilihan Menu: \n"<< endl;
        cout << "\t\t\t\t1. Syarat dan ketentuan peminjaman" << endl;
        cout << "\t\t\t\t2. Daftar Buku" << endl;
        cout << "\t\t\t\t3. Peminjaman" << endl;
        cout << "\t\t\t\t4. Pembayaran" << endl;
        cout << "\t\t\t\t5. Daftar peminjam" << endl;
        cout << "\t\t\t\t0. Keluar\n" << endl;

        cout << "Pilih menu (0-5): ";
        cin >> menu;
        system("clear || cls");
        
		system("color F9");
        switch (menu) {
	
            case 1:
                cout << "\n\n\t Syarat Dan Ketentuan Peminjaman Buku: "<< endl;
                cout << "\n\t 1. Mengisi data peminjam buku.";
                cout << "\n\t 2. Memberikan identitas berupa KTP/KTM.";
                cout << "\n\t 3. Membayar buku sesuai dengan harga yang ditentukan.";
                cout << "\n\t 4. Harap menjaga buku dengan baik.\n\n";
                break;
            case 2:
                cout << "\nDaftar Buku Tersedia:" << endl;
                tampilkanBuku(daftarBuku);
                break;
            case 3: {
                int jumlahPeminjam;
                Peminjam peminjam;

                cout << "\nMasukkan nama Anda: ";
                cin >> peminjam.nama;
                

                cout << "\nMasukkan jumlah buku yang mau dipinjam: ";
                cin >> jumlahPeminjam;
                cin.ignore();

                for (int i = 0; i < jumlahPeminjam; ++i) {
                    cout << "\nData Peminjam ke-" << i + 1 << ":" << endl;

                    int nomorBuku;

                    cout << "Masukkan nomor buku yang ingin dipinjam: ";
                    cin >> nomorBuku;

                    Buku* bukuDitemukan = cariBuku(daftarBuku, nomorBuku);

                    if (bukuDitemukan) {
                        cout << "Buku ditemukan: " << bukuDitemukan->judul << " oleh " << bukuDitemukan->pengarang
                             << ", Harga per Hari: " << bukuDitemukan->harga << endl;

                        cout << "Masukkan tanggal pengambilan buku (yyyy-mm-dd): ";
                        cin >> peminjam.tanggalAmbil;
                        cin.ignore();

                        cout << "Masukkan jumlah hari meminjam: ";
                        cin >> peminjam.lamaPinjam;
                        cin.ignore();

                        peminjam.judulBuku = bukuDitemukan->judul;
                        peminjam.totalPembayaran = hitungTotalPembayaran(*bukuDitemukan, peminjam.lamaPinjam);

                        cout << "Total Pembayaran: " << peminjam.totalPembayaran << endl;

                        // Simpan informasi peminjam ke dalam file
                        simpanPeminjamKeFile(peminjam);

                        // Tampilkan informasi buku yang dipinjam
                        cout << "\nInformasi Peminjaman:" << endl;
                        cout << "Nama: " << peminjam.nama << endl;
                        cout << "Judul Buku: " << peminjam.judulBuku << endl;
                        cout << "Tanggal Ambil: " << peminjam.tanggalAmbil << endl;
                        cout << "Lama Pinjam: " << peminjam.lamaPinjam << " hari" << endl;
                        cout << "Total Pembayaran: " << peminjam.totalPembayaran << endl;

                        cout << "\nSilahkan lakukan pembayaran untuk melanjutkan peminjaman!" << endl;

                        stackPeminjam.push(peminjam);
                    } else {
                        cout << "Buku tidak ditemukan." << endl;
                        i--;
                    }
                }
                break;
            }
            case 4: {
                int totalPendapatan = 0;

                cout << "\nPeminjam dari Stack:" << endl;
                while (!stackPeminjam.empty()) {
                    Peminjam topPeminjam = stackPeminjam.top();
                    stackPeminjam.pop();
                    totalPendapatan += topPeminjam.totalPembayaran;
                    cout << "Nama: " << topPeminjam.nama << ", Judul Buku: " << topPeminjam.judulBuku
                         << ", Tanggal Ambil: " << topPeminjam.tanggalAmbil
                         << ", Lama Pinjam: " << topPeminjam.lamaPinjam << " hari"
                         << ", Total Pembayaran: " << topPeminjam.totalPembayaran << endl;
                }

                cout << "\nTotal Pembayaran: " << totalPendapatan << endl;

                int uangDibayarkan;
                cout << "Masukkan jumlah uang yang dibayarkan oleh pengunjung: ";
                cin >> uangDibayarkan;

                while (uangDibayarkan < totalPendapatan) {
                    cout << "Uang yang dimasukkan kurang dari total pembayaran. Masukkan kembali jumlah uang: ";
                    cin >> uangDibayarkan;
                }

                int kembalian = uangDibayarkan - totalPendapatan;
                if (kembalian > 0) {
                    cout << "Kembalian: " << kembalian << endl;
                } else {
                    cout << "Terima kasih. Uang pas, tidak ada kembalian." << endl;
                }
                break;
            }
            case 5:
                tampilkanDaftarPeminjam();
                break;
            case 0:
                cout << "Terima kasih! Program Selesai" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan pilih lagi." << endl;
        }

    } while (menu != 0);

    return 0;
}

