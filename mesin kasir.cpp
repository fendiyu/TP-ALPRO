#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <ctime>
#include <cstdlib>

using namespace std;

// Konstanta untuk maksimal transaksi
const int MAX_TRANSAKSI = 100;

// Array 1 dimensi untuk menyimpan data
string namaPembeli[MAX_TRANSAKSI];
string namaBaju[MAX_TRANSAKSI];
int jumlahBeli[MAX_TRANSAKSI];
double hargaSatuan[MAX_TRANSAKSI];
double totalBayar[MAX_TRANSAKSI];
string waktuTransaksi[MAX_TRANSAKSI];

// Variable global untuk jumlah transaksi
int jumlahTransaksi = 0;

// Deklarasi fungsi-fungsi
void tampilkanHeader();
void tampilkanMenu();
void inputDataPembeli();
void tampilkanTabelTransaksi();
void hitungTotalPemasukan();
void cariTransaksi();
void tampilkanStatistik();
void hapusTransaksi();
void editTransaksi();
void simpanKeFile();
void tampilkanTransaksiTertinggi();
void tampilkanTransaksiTerendah();
string getCurrentTime();
void clearScreen();
void pauseScreen();
void tampilkanGaris(int panjang);

int main() {
    int pilihan;
    
    // Inisialisasi random seed
    srand(time(0));
    
    do {
        clearScreen();
        tampilkanHeader();
        tampilkanMenu();
        
        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;
        
        // Validasi input menu
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid! Silakan masukkan angka.\n";
            pauseScreen();
            continue;
        }
        
        cin.ignore(); // Membersihkan buffer
        
        switch (pilihan) {
            case 1:
                inputDataPembeli();
                break;
            case 2:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    tampilkanTabelTransaksi();
                }
                pauseScreen();
                break;
            case 3:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    hitungTotalPemasukan();
                }
                pauseScreen();
                break;
            case 4:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    cariTransaksi();
                }
                pauseScreen();
                break;
            case 5:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    tampilkanStatistik();
                }
                pauseScreen();
                break;
            case 6:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    editTransaksi();
                }
                pauseScreen();
                break;
            case 7:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    hapusTransaksi();
                }
                pauseScreen();
                break;
            case 8:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    simpanKeFile();
                }
                pauseScreen();
                break;
            case 9:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    tampilkanTransaksiTertinggi();
                }
                pauseScreen();
                break;
            case 10:
                if (jumlahTransaksi == 0) {
                    cout << "\nBelum ada data transaksi!\n";
                } else {
                    tampilkanTransaksiTerendah();
                }
                pauseScreen();
                break;
            case 0:
                cout << "\nTerima kasih telah menggunakan program kasir!\n";
                cout << "Program dibuat untuk simulasi transaksi penjualan baju.\n";
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan pilih menu yang tersedia.\n";
                pauseScreen();
                break;
        }
    } while (pilihan != 0);
    
    return 0;
}

// Fungsi untuk menampilkan header program
void tampilkanHeader() {
    tampilkanGaris(60);
    cout << "|" << setw(58) << "PROGRAM MESIN KASIR TOKO BAJU" << setw(2) << "|" << endl;
    cout << "|" << setw(58) << "Sistem Transaksi Penjualan" << setw(2) << "|" << endl;
    tampilkanGaris(60);
    cout << "Tanggal: " << getCurrentTime() << endl;
    tampilkanGaris(60);
    cout << endl;
}

// Fungsi untuk menampilkan menu utama
void tampilkanMenu() {
    cout << "MENU UTAMA:" << endl;
    cout << "1. Input Data Pembeli" << endl;
    cout << "2. Tampilkan Tabel Transaksi" << endl;
    cout << "3. Hitung Total Pemasukan" << endl;
    cout << "4. Cari Transaksi" << endl;
    cout << "5. Tampilkan Statistik" << endl;
    cout << "6. Edit Transaksi" << endl;
    cout << "7. Hapus Transaksi" << endl;
    cout << "8. Simpan Data ke File" << endl;
    cout << "9. Transaksi Tertinggi" << endl;
    cout << "10. Transaksi Terendah" << endl;
    cout << "0. Keluar Program" << endl;
    tampilkanGaris(30);
}

// Fungsi untuk input data pembeli
void inputDataPembeli() {
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        cout << "\nDatabase transaksi sudah penuh! Maksimal " << MAX_TRANSAKSI << " transaksi.\n";
        pauseScreen();
        return;
    }
    
    clearScreen();
    cout << "INPUT DATA PEMBELI" << endl;
    tampilkanGaris(30);
    
    // Input nama pembeli
    cout << "Nama Pembeli: ";
    getline(cin, namaPembeli[jumlahTransaksi]);
    
    // Validasi nama pembeli tidak kosong
    while (namaPembeli[jumlahTransaksi].empty()) {
        cout << "Nama pembeli tidak boleh kosong! Masukkan nama: ";
        getline(cin, namaPembeli[jumlahTransaksi]);
    }
    
    // Input nama baju
    cout << "Nama Baju: ";
    getline(cin, namaBaju[jumlahTransaksi]);
    
    // Validasi nama baju tidak kosong
    while (namaBaju[jumlahTransaksi].empty()) {
        cout << "Nama baju tidak boleh kosong! Masukkan nama: ";
        getline(cin, namaBaju[jumlahTransaksi]);
    }
    
    // Input jumlah beli dengan validasi
    do {
        cout << "Jumlah Beli: ";
        cin >> jumlahBeli[jumlahTransaksi];
        
        if (cin.fail() || jumlahBeli[jumlahTransaksi] <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Jumlah beli harus berupa angka positif!\n";
        }
    } while (cin.fail() || jumlahBeli[jumlahTransaksi] <= 0);
    
    // Input harga satuan dengan validasi
    do {
        cout << "Harga Satuan (Rp): ";
        cin >> hargaSatuan[jumlahTransaksi];
        
        if (cin.fail() || hargaSatuan[jumlahTransaksi] <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harga satuan harus berupa angka positif!\n";
        }
    } while (cin.fail() || hargaSatuan[jumlahTransaksi] <= 0);
    
    // Hitung total bayar
    totalBayar[jumlahTransaksi] = jumlahBeli[jumlahTransaksi] * hargaSatuan[jumlahTransaksi];
    
    // Set waktu transaksi
    waktuTransaksi[jumlahTransaksi] = getCurrentTime();
    
    // Tampilkan ringkasan transaksi
    cout << "\nRINGKASAN TRANSAKSI:" << endl;
    tampilkanGaris(40);
    cout << "Nama Pembeli: " << namaPembeli[jumlahTransaksi] << endl;
    cout << "Nama Baju: " << namaBaju[jumlahTransaksi] << endl;
    cout << "Jumlah Beli: " << jumlahBeli[jumlahTransaksi] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[jumlahTransaksi] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[jumlahTransaksi] << endl;
    cout << "Waktu: " << waktuTransaksi[jumlahTransaksi] << endl;
    tampilkanGaris(40);
    
    // Konfirmasi penyimpanan
    char konfirmasi;
    cout << "\nSimpan transaksi ini? (y/n): ";
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        jumlahTransaksi++;
        cout << "\nTransaksi berhasil disimpan! ID Transaksi: " << jumlahTransaksi << endl;
    } else {
        cout << "\nTransaksi dibatalkan!" << endl;
    }
    
    pauseScreen();
}

// Fungsi untuk menampilkan tabel transaksi
void tampilkanTabelTransaksi() {
    clearScreen();
    cout << "TABEL TRANSAKSI PENJUALAN BAJU" << endl;
    tampilkanGaris(120);
    
    // Header tabel
    cout << "| " << setw(3) << "No" 
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;
    
    tampilkanGaris(120);
    
    // Data transaksi
    for (int i = 0; i < jumlahTransaksi; i++) {
        cout << "| " << setw(3) << (i + 1)
             << " | " << setw(20) << namaPembeli[i].substr(0, 20)
             << " | " << setw(15) << namaBaju[i].substr(0, 15)
             << " | " << setw(8) << jumlahBeli[i]
             << " | " << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
             << " | " << setw(15) << fixed << setprecision(0) << totalBayar[i]
             << " | " << setw(19) << waktuTransaksi[i]
             << " |" << endl;
    }
    
    tampilkanGaris(120);
    cout << "Total Transaksi: " << jumlahTransaksi << " transaksi" << endl;
}

// Fungsi untuk menghitung total pemasukan
void hitungTotalPemasukan() {
    double totalPemasukan = 0;
    int totalBarang = 0;
    
    for (int i = 0; i < jumlahTransaksi; i++) {
        totalPemasukan += totalBayar[i];
        totalBarang += jumlahBeli[i];
    }
    
    clearScreen();
    cout << "LAPORAN TOTAL PEMASUKAN TOKO" << endl;
    tampilkanGaris(50);
    cout << "Jumlah Transaksi: " << jumlahTransaksi << " transaksi" << endl;
    cout << "Total Barang Terjual: " << totalBarang << " pcs" << endl;
    cout << "Total Pemasukan: Rp " << fixed << setprecision(2) << totalPemasukan << endl;
    
    if (jumlahTransaksi > 0) {
        double rataRata = totalPemasukan / jumlahTransaksi;
        cout << "Rata-rata per Transaksi: Rp " << fixed << setprecision(2) << rataRata << endl;
    }
    
    tampilkanGaris(50);
}

// Fungsi untuk mencari transaksi
void cariTransaksi() {
    clearScreen();
    cout << "PENCARIAN TRANSAKSI" << endl;
    tampilkanGaris(30);
    
    string keyword;
    cout << "Masukkan nama pembeli yang dicari: ";
    getline(cin, keyword);
    
    bool ditemukan = false;
    cout << "\nHASIL PENCARIAN:" << endl;
    tampilkanGaris(80);
    
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (namaPembeli[i].find(keyword) != string::npos) {
            if (!ditemukan) {
                cout << "| " << setw(3) << "No" 
                     << " | " << setw(20) << "Nama Pembeli"
                     << " | " << setw(15) << "Nama Baju"
                     << " | " << setw(8) << "Jumlah"
                     << " | " << setw(15) << "Total Bayar" << " |" << endl;
                tampilkanGaris(80);
            }
            
            cout << "| " << setw(3) << (i + 1)
                 << " | " << setw(20) << namaPembeli[i]
                 << " | " << setw(15) << namaBaju[i]
                 << " | " << setw(8) << jumlahBeli[i]
                 << " | " << setw(15) << fixed << setprecision(0) << totalBayar[i]
                 << " |" << endl;
            ditemukan = true;
        }
    }
    
    if (!ditemukan) {
        cout << "Tidak ada transaksi dengan nama pembeli: " << keyword << endl;
    } else {
        tampilkanGaris(80);
    }
}

// Fungsi untuk menampilkan statistik
void tampilkanStatistik() {
    clearScreen();
    cout << "STATISTIK PENJUALAN" << endl;
    tampilkanGaris(40);
    
    double totalPemasukan = 0;
    double transaksiTertinggi = 0;
    double transaksiTerendah = totalBayar[0];
    int totalBarang = 0;
    
    for (int i = 0; i < jumlahTransaksi; i++) {
        totalPemasukan += totalBayar[i];
        totalBarang += jumlahBeli[i];
        
        if (totalBayar[i] > transaksiTertinggi) {
            transaksiTertinggi = totalBayar[i];
        }
        
        if (totalBayar[i] < transaksiTerendah) {
            transaksiTerendah = totalBayar[i];
        }
    }
    
    cout << "Total Transaksi: " << jumlahTransaksi << endl;
    cout << "Total Pemasukan: Rp " << fixed << setprecision(2) << totalPemasukan << endl;
    cout << "Total Barang Terjual: " << totalBarang << " pcs" << endl;
    cout << "Transaksi Tertinggi: Rp " << fixed << setprecision(2) << transaksiTertinggi << endl;
    cout << "Transaksi Terendah: Rp " << fixed << setprecision(2) << transaksiTerendah << endl;
    
    if (jumlahTransaksi > 0) {
        double rataRata = totalPemasukan / jumlahTransaksi;
        cout << "Rata-rata Transaksi: Rp " << fixed << setprecision(2) << rataRata << endl;
    }
    
    tampilkanGaris(40);
}

// Fungsi untuk mengedit transaksi
void editTransaksi() {
    clearScreen();
    cout << "EDIT TRANSAKSI" << endl;
    tampilkanGaris(20);
    
    int nomor;
    cout << "Masukkan nomor transaksi yang akan diedit (1-" << jumlahTransaksi << "): ";
    cin >> nomor;
    
    if (nomor < 1 || nomor > jumlahTransaksi) {
        cout << "Nomor transaksi tidak valid!" << endl;
        return;
    }
    
    int index = nomor - 1;
    cin.ignore();
    
    cout << "\nData saat ini:" << endl;
    cout << "Nama Pembeli: " << namaPembeli[index] << endl;
    cout << "Nama Baju: " << namaBaju[index] << endl;
    cout << "Jumlah: " << jumlahBeli[index] << endl;
    cout << "Harga Satuan: " << hargaSatuan[index] << endl;
    
    cout << "\nMasukkan data baru:" << endl;
    cout << "Nama Pembeli: ";
    getline(cin, namaPembeli[index]);
    cout << "Nama Baju: ";
    getline(cin, namaBaju[index]);
    cout << "Jumlah: ";
    cin >> jumlahBeli[index];
    cout << "Harga Satuan: ";
    cin >> hargaSatuan[index];
    
    totalBayar[index] = jumlahBeli[index] * hargaSatuan[index];
    
    cout << "\nTransaksi berhasil diperbarui!" << endl;
}

// Fungsi untuk menghapus transaksi
void hapusTransaksi() {
    clearScreen();
    cout << "HAPUS TRANSAKSI" << endl;
    tampilkanGaris(20);
    
    int nomor;
    cout << "Masukkan nomor transaksi yang akan dihapus (1-" << jumlahTransaksi << "): ";
    cin >> nomor;
    
    if (nomor < 1 || nomor > jumlahTransaksi) {
        cout << "Nomor transaksi tidak valid!" << endl;
        return;
    }
    
    int index = nomor - 1;
    
    cout << "\nData yang akan dihapus:" << endl;
    cout << "Nama Pembeli: " << namaPembeli[index] << endl;
    cout << "Nama Baju: " << namaBaju[index] << endl;
    cout << "Total Bayar: Rp " << totalBayar[index] << endl;
    
    char konfirmasi;
    cout << "\nYakin ingin menghapus? (y/n): ";
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Geser semua data setelah index yang dihapus
        for (int i = index; i < jumlahTransaksi - 1; i++) {
            namaPembeli[i] = namaPembeli[i + 1];
            namaBaju[i] = namaBaju[i + 1];
            jumlahBeli[i] = jumlahBeli[i + 1];
            hargaSatuan[i] = hargaSatuan[i + 1];
            totalBayar[i] = totalBayar[i + 1];
            waktuTransaksi[i] = waktuTransaksi[i + 1];
        }
        jumlahTransaksi--;
        cout << "Transaksi berhasil dihapus!" << endl;
    } else {
        cout << "Penghapusan dibatalkan!" << endl;
    }
}

// Fungsi untuk menyimpan data ke file (simulasi)
void simpanKeFile() {
    clearScreen();
    cout << "SIMPAN DATA KE FILE" << endl;
    tampilkanGaris(30);
    
    cout << "Menyimpan " << jumlahTransaksi << " transaksi..." << endl;
    
    // Simulasi proses penyimpanan
    for (int i = 0; i < 5; i++) {
        cout << "." << flush;
        // Simulasi delay
        for (int j = 0; j < 100000000; j++);
    }
    
    cout << "\n\nData berhasil disimpan ke file 'transaksi_toko.txt'" << endl;
    cout << "File berisi " << jumlahTransaksi << " record transaksi" << endl;
}

// Fungsi untuk menampilkan transaksi tertinggi
void tampilkanTransaksiTertinggi() {
    double maksimal = totalBayar[0];
    int indeksMaks = 0;
    
    for (int i = 1; i < jumlahTransaksi; i++) {
        if (totalBayar[i] > maksimal) {
            maksimal = totalBayar[i];
            indeksMaks = i;
        }
    }
    
    clearScreen();
    cout << "TRANSAKSI TERTINGGI" << endl;
    tampilkanGaris(30);
    cout << "Nama Pembeli: " << namaPembeli[indeksMaks] << endl;
    cout << "Nama Baju: " << namaBaju[indeksMaks] << endl;
    cout << "Jumlah: " << jumlahBeli[indeksMaks] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[indeksMaks] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[indeksMaks] << endl;
    cout << "Waktu: " << waktuTransaksi[indeksMaks] << endl;
    tampilkanGaris(30);
}

// Fungsi untuk menampilkan transaksi terendah
void tampilkanTransaksiTerendah() {
    double minimal = totalBayar[0];
    int indeksMin = 0;
    
    for (int i = 1; i < jumlahTransaksi; i++) {
        if (totalBayar[i] < minimal) {
            minimal = totalBayar[i];
            indeksMin = i;
        }
    }
    
    clearScreen();
    cout << "TRANSAKSI TERENDAH" << endl;
    tampilkanGaris(30);
    cout << "Nama Pembeli: " << namaPembeli[indeksMin] << endl;
    cout << "Nama Baju: " << namaBaju[indeksMin] << endl;
    cout << "Jumlah: " << jumlahBeli[indeksMin] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[indeksMin] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[indeksMin] << endl;
    cout << "Waktu: " << waktuTransaksi[indeksMin] << endl;
    tampilkanGaris(30);
}

// Fungsi untuk mendapatkan waktu saat ini
string getCurrentTime() {
    time_t now = time(0);
    char* timeStr = ctime(&now);
    string result(timeStr);
    
    // Menghapus newline character di akhir string
    if (!result.empty() && result[result.length()-1] == '\n') {
        result.erase(result.length()-1);
    }
    
    return result;
}

// Fungsi untuk membersihkan layar
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi untuk pause/menunggu input
void pauseScreen() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// Fungsi untuk menampilkan garis
void tampilkanGaris(int panjang) {
    for (int i = 0; i < panjang; i++) {
        cout << "-";
    }
    cout << endl;
}
