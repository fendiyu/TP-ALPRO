#include <iostream>
#include <iomanip>
#include <string>
#include <limits>   // Untuk numeric_limits
#include <ctime>    // Untuk waktu
#include <cstdlib>  // Untuk system("cls") atau system("clear")
#include <fstream>  // Untuk operasi file (ifstream, ofstream)
#include <sstream>  // Untuk stringstream
#include <vector>   // Hanya untuk membantu dalam beberapa konversi atau logika, tidak menggantikan array global

using namespace std;

// --- KONSTANTA GLOBAL ---
const int MAX_TRANSAKSI = 1000; // Batas maksimal transaksi, diperbesar untuk simulasi

// --- ARRAY GLOBAL UNTUK DATA TRANSAKSI ---
string namaPembeli[MAX_TRANSAKSI];
string namaBaju[MAX_TRANSAKSI];
int jumlahBeli[MAX_TRANSAKSI];
double hargaSatuan[MAX_TRANSAKSI];
double totalBayar[MAX_TRANSAKSI];
string waktuTransaksi[MAX_TRANSAKSI]; // Format: YYYY-MM-DD HH:MM:SS

// --- VARIABEL GLOBAL LAINNYA ---
int jumlahTransaksi = 0; // Jumlah transaksi yang saat ini tersimpan

// --- PROTOTYPE FUNGSI ---
void tampilkanHeader();
void tampilkanMenuUtama();
void tampilkanMenuAdmin();
void inputDataPembeli();
void tampilkanTabelTransaksi();
void hitungTotalPemasukan();
void cariTransaksi();
void tampilkanStatistik();
void hapusTransaksi();
void editTransaksi();
void simpanKeFile();
void muatDataDariFile(); // Fungsi baru: Memuat data dari file
void tampilkanTransaksiTertinggi();
void tampilkanTransaksiTerendah();
void selectionSortByTotalBayar();
void sortTransactionsByDate(); // Fungsi baru: Mengurutkan berdasarkan tanggal
void filterTransaksiByTanggal(); // Fungsi baru: Filter berdasarkan tanggal
void filterTransaksiByTotal();   // Fungsi baru: Filter berdasarkan rentang total bayar
void exportToCSV();              // Fungsi baru: Export data ke CSV
bool loginUser(string& username, string& role); // Fungsi baru: Simulasi login
string getCurrentTime();
void clearScreen();
void pauseScreen();
void tampilkanGaris(int panjang);
bool isLeapYear(int year); // Fungsi helper untuk tanggal
int daysInMonth(int year, int month); // Fungsi helper untuk tanggal
bool isValidDate(int year, int month, int day); // Fungsi helper untuk tanggal

int main() {
    // Inisialisasi random seed (digunakan oleh fungsi-fungsi lain jika ada)
    srand(time(0));

    // Coba muat data saat program dimulai
    muatDataDariFile();

    string usernameLoggedIn;
    string roleLoggedIn;

    // --- SIMULASI LOGIN ---
    clearScreen();
    tampilkanHeader();
    cout << "SELAMAT DATANG DI PROGRAM MESIN KASIR" << endl;
    tampilkanGaris(40);
    if (!loginUser(usernameLoggedIn, roleLoggedIn)) {
        cout << "\nTerlalu banyak percobaan login gagal. Program akan keluar." << endl;
        pauseScreen();
        return 1; // Keluar dengan kode error
    }
    cout << "\nLogin Berhasil! Selamat datang, " << usernameLoggedIn << " (" << roleLoggedIn << ")." << endl;
    pauseScreen();


    int pilihan;
    do {
        clearScreen();
        tampilkanHeader();
        tampilkanMenuUtama();

        // Hanya tampilkan menu admin jika role adalah "admin"
        if (roleLoggedIn == "admin") {
            cout << "11. Menu Administrator" << endl;
        }
        cout << "0. Keluar Program" << endl;
        tampilkanGaris(30);

        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        // Validasi input menu utama
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid! Silakan masukkan angka.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(); // Membersihkan buffer

        switch (pilihan) {
            case 1: inputDataPembeli(); break;
            case 2:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { tampilkanTabelTransaksi(); }
                pauseScreen();
                break;
            case 3:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { hitungTotalPemasukan(); }
                pauseScreen();
                break;
            case 4:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { cariTransaksi(); }
                pauseScreen();
                break;
            case 5:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { tampilkanStatistik(); }
                pauseScreen();
                break;
            case 6:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { editTransaksi(); }
                pauseScreen();
                break;
            case 7:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { hapusTransaksi(); }
                pauseScreen();
                break;
            case 8:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { simpanKeFile(); }
                pauseScreen();
                break;
            case 9:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { tampilkanTransaksiTertinggi(); }
                pauseScreen();
                break;
            case 10:
                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                else { tampilkanTransaksiTerendah(); }
                pauseScreen();
                break;
            case 11:
                if (roleLoggedIn == "admin") { // Hanya admin yang bisa mengakses menu ini
                    int adminPilihan;
                    do {
                        clearScreen();
                        tampilkanHeader();
                        tampilkanMenuAdmin();
                        cout << "Masukkan pilihan Admin: ";
                        cin >> adminPilihan;

                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\nInput tidak valid! Silakan masukkan angka.\n";
                            pauseScreen();
                            continue;
                        }
                        cin.ignore();

                        switch (adminPilihan) {
                            case 1:
                                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                                else { selectionSortByTotalBayar(); cout << "\nTransaksi berhasil diurutkan berdasarkan Total Bayar (terendah ke tertinggi).\n"; tampilkanTabelTransaksi(); }
                                pauseScreen();
                                break;
                            case 2:
                                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                                else { sortTransactionsByDate(); cout << "\nTransaksi berhasil diurutkan berdasarkan Waktu (terbaru ke terlama).\n"; tampilkanTabelTransaksi(); }
                                pauseScreen();
                                break;
                            case 3:
                                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                                else { filterTransaksiByTanggal(); }
                                pauseScreen();
                                break;
                            case 4:
                                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                                else { filterTransaksiByTotal(); }
                                pauseScreen();
                                break;
                            case 5:
                                if (jumlahTransaksi == 0) { cout << "\nBelum ada data transaksi!\n"; }
                                else { exportToCSV(); }
                                pauseScreen();
                                break;
                            case 0:
                                cout << "\nKeluar dari Menu Administrator.\n";
                                break;
                            default:
                                cout << "\nPilihan tidak valid untuk Administrator! Silakan pilih menu yang tersedia.\n";
                                pauseScreen();
                                break;
                        }
                    } while (adminPilihan != 0);
                } else {
                    cout << "\nAnda tidak memiliki izin untuk mengakses menu ini! Hanya untuk Administrator.\n";
                    pauseScreen();
                }
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

// --- DEFINISI FUNGSI ---

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
void tampilkanMenuUtama() {
    cout << "MENU UTAMA:" << endl;
    cout << "1. Input Data Pembeli" << endl;
    cout << "2. Tampilkan Tabel Transaksi" << endl;
    cout << "3. Hitung Total Pemasukan" << endl;
    cout << "4. Cari Transaksi (Berdasarkan Nama Pembeli)" << endl;
    cout << "5. Tampilkan Statistik Penjualan" << endl;
    cout << "6. Edit Transaksi" << endl;
    cout << "7. Hapus Transaksi" << endl;
    cout << "8. Simpan Data ke File" << endl;
    cout << "9. Tampilkan Transaksi dengan Nilai Tertinggi" << endl;
    cout << "10. Tampilkan Transaksi dengan Nilai Terendah" << endl;
    // Opsi menu admin akan ditambahkan di main() jika role sesuai
}

// Fungsi untuk menampilkan menu administrator
void tampilkanMenuAdmin() {
    cout << "MENU ADMINISTRATOR:" << endl;
    cout << "1. Urutkan Transaksi (Total Bayar Ascending)" << endl;
    cout << "2. Urutkan Transaksi (Waktu Transaksi Terbaru)" << endl;
    cout << "3. Filter Transaksi (Berdasarkan Tanggal)" << endl;
    cout << "4. Filter Transaksi (Berdasarkan Rentang Total Bayar)" << endl;
    cout << "5. Export Data Transaksi ke CSV" << endl;
    cout << "0. Kembali ke Menu Utama" << endl;
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
    while (namaPembeli[jumlahTransaksi].empty()) {
        cout << "Nama pembeli tidak boleh kosong! Masukkan nama: ";
        getline(cin, namaPembeli[jumlahTransaksi]);
    }

    // Input nama baju
    cout << "Nama Baju: ";
    getline(cin, namaBaju[jumlahTransaksi]);
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
    cin.ignore(); // Membersihkan buffer setelah input double/int

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
    cin.ignore(); // Membersihkan buffer setelah input char

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
    cout << "| " << left << setw(3) << "No"
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
        cout << "| " << left << setw(3) << (i + 1)
             << " | " << setw(20) << namaPembeli[i].substr(0, 20)
             << " | " << setw(15) << namaBaju[i].substr(0, 15)
             << " | " << right << setw(8) << jumlahBeli[i]
             << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
             << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[i]
             << " | " << left << setw(19) << waktuTransaksi[i]
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
    cout << "Jumlah Transaksi Terdaftar: " << jumlahTransaksi << " transaksi" << endl;
    cout << "Total Barang Terjual: " << totalBarang << " pcs" << endl;
    cout << "Total Pemasukan Bruto: Rp " << fixed << setprecision(2) << totalPemasukan << endl;

    if (jumlahTransaksi > 0) {
        double rataRata = totalPemasukan / jumlahTransaksi;
        cout << "Rata-rata Pemasukan per Transaksi: Rp " << fixed << setprecision(2) << rataRata << endl;
    } else {
        cout << "Tidak ada data transaksi untuk dihitung pemasukan." << endl;
    }

    tampilkanGaris(50);
}

// Fungsi untuk mencari transaksi berdasarkan nama pembeli
void cariTransaksi() {
    clearScreen();
    cout << "PENCARIAN TRANSAKSI BERDASARKAN NAMA PEMBELI" << endl;
    tampilkanGaris(50);

    string keyword;
    cout << "Masukkan nama pembeli yang dicari: ";
    getline(cin, keyword);

    bool ditemukan = false;
    cout << "\nHASIL PENCARIAN UNTUK '" << keyword << "':" << endl;
    tampilkanGaris(120);

    // Header tabel hasil pencarian
    cout << "| " << left << setw(3) << "No"
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;
    tampilkanGaris(120);

    for (int i = 0; i < jumlahTransaksi; i++) {
        // Menggunakan find() untuk mencari substring (bisa diubah ke case-insensitive jika perlu)
        if (namaPembeli[i].find(keyword) != string::npos) {
            cout << "| " << left << setw(3) << (i + 1)
                 << " | " << setw(20) << namaPembeli[i].substr(0, 20)
                 << " | " << setw(15) << namaBaju[i].substr(0, 15)
                 << " | " << right << setw(8) << jumlahBeli[i]
                 << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
                 << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[i]
                 << " | " << left << setw(19) << waktuTransaksi[i]
                 << " |" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada transaksi yang cocok dengan nama pembeli: '" << keyword << "'.\n";
    } else {
        tampilkanGaris(120);
    }
}

// Fungsi untuk menampilkan statistik penjualan
void tampilkanStatistik() {
    clearScreen();
    cout << "STATISTIK PENJUALAN TOKO BAJU" << endl;
    tampilkanGaris(50);

    if (jumlahTransaksi == 0) {
        cout << "Tidak ada data transaksi untuk menampilkan statistik." << endl;
        tampilkanGaris(50);
        return;
    }

    double totalPemasukan = 0;
    double transaksiTertinggi = totalBayar[0];
    double transaksiTerendah = totalBayar[0];
    int totalBarang = 0;
    int indeksTertinggi = 0;
    int indeksTerendah = 0;

    for (int i = 0; i < jumlahTransaksi; i++) {
        totalPemasukan += totalBayar[i];
        totalBarang += jumlahBeli[i];

        if (totalBayar[i] > transaksiTertinggi) {
            transaksiTertinggi = totalBayar[i];
            indeksTertinggi = i;
        }

        if (totalBayar[i] < transaksiTerendah) {
            transaksiTerendah = totalBayar[i];
            indeksTerendah = i;
        }
    }

    cout << "Jumlah Total Transaksi: " << jumlahTransaksi << endl;
    cout << "Total Pemasukan Bersih: Rp " << fixed << setprecision(2) << totalPemasukan << endl;
    cout << "Total Barang Terjual: " << totalBarang << " pcs" << endl;
    cout << "---------------------------------------" << endl;
    cout << "Transaksi Dengan Nilai Tertinggi:" << endl;
    cout << "  - Pembeli: " << namaPembeli[indeksTertinggi] << endl;
    cout << "  - Barang: " << namaBaju[indeksTertinggi] << endl;
    cout << "  - Total: Rp " << fixed << setprecision(2) << totalBayar[indeksTertinggi] << endl;
    cout << "---------------------------------------" << endl;
    cout << "Transaksi Dengan Nilai Terendah:" << endl;
    cout << "  - Pembeli: " << namaPembeli[indeksTerendah] << endl;
    cout << "  - Barang: " << namaBaju[indeksTerendah] << endl;
    cout << "  - Total: Rp " << fixed << setprecision(2) << totalBayar[indeksTerendah] << endl;
    cout << "---------------------------------------" << endl;

    if (jumlahTransaksi > 0) {
        double rataRata = totalPemasukan / jumlahTransaksi;
        cout << "Rata-rata Nilai Transaksi: Rp " << fixed << setprecision(2) << rataRata << endl;
    }

    tampilkanGaris(50);
}

// Fungsi untuk mengedit transaksi
void editTransaksi() {
    clearScreen();
    cout << "EDIT TRANSAKSI" << endl;
    tampilkanGaris(20);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi untuk diedit!" << endl;
        return;
    }

    int nomor;
    cout << "Masukkan nomor transaksi yang akan diedit (1-" << jumlahTransaksi << "): ";
    cin >> nomor;

    if (cin.fail() || nomor < 1 || nomor > jumlahTransaksi) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nomor transaksi tidak valid!\n";
        return;
    }

    int index = nomor - 1;
    cin.ignore(); // Membersihkan buffer setelah cin >> nomor

    cout << "\n--- Data Transaksi No. " << nomor << " Saat Ini ---" << endl;
    cout << "Nama Pembeli: " << namaPembeli[index] << endl;
    cout << "Nama Baju: " << namaBaju[index] << endl;
    cout << "Jumlah: " << jumlahBeli[index] << endl;
    cout << "Harga Satuan: " << hargaSatuan[index] << endl;
    cout << "Total Bayar: " << totalBayar[index] << endl;
    cout << "Waktu Transaksi: " << waktuTransaksi[index] << endl;
    tampilkanGaris(30);

    cout << "\nMasukkan data baru (kosongkan/masukkan 0 untuk mempertahankan nilai lama):" << endl;
    string tempNamaPembeli, tempNamaBaju;
    int tempJumlahBeli;
    double tempHargaSatuan;

    cout << "Nama Pembeli [" << namaPembeli[index] << "]: ";
    getline(cin, tempNamaPembeli);
    if (!tempNamaPembeli.empty()) {
        namaPembeli[index] = tempNamaPembeli;
    }

    cout << "Nama Baju [" << namaBaju[index] << "]: ";
    getline(cin, tempNamaBaju);
    if (!tempNamaBaju.empty()) {
        namaBaju[index] = tempNamaBaju;
    }

    cout << "Jumlah [" << jumlahBeli[index] << "]: ";
    cin >> tempJumlahBeli;
    if (!cin.fail() && tempJumlahBeli > 0) {
        jumlahBeli[index] = tempJumlahBeli;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input jumlah beli tidak valid atau 0, menggunakan nilai lama (" << jumlahBeli[index] << ").\n";
    }

    cout << "Harga Satuan [" << fixed << setprecision(2) << hargaSatuan[index] << "]: ";
    cin >> tempHargaSatuan;
    if (!cin.fail() && tempHargaSatuan > 0) {
        hargaSatuan[index] = tempHargaSatuan;
    } else {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input harga satuan tidak valid atau 0, menggunakan nilai lama (" << fixed << setprecision(2) << hargaSatuan[index] << ").\n";
    }
    cin.ignore(); // Membersihkan buffer setelah cin untuk harga satuan

    // Hitung ulang total bayar
    totalBayar[index] = jumlahBeli[index] * hargaSatuan[index];
    waktuTransaksi[index] = getCurrentTime(); // Update waktu transaksi saat diedit

    cout << "\nTransaksi No. " << nomor << " berhasil diperbarui!" << endl;
}

// Fungsi untuk menghapus transaksi
void hapusTransaksi() {
    clearScreen();
    cout << "HAPUS TRANSAKSI" << endl;
    tampilkanGaris(20);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi untuk dihapus!" << endl;
        return;
    }

    int nomor;
    cout << "Masukkan nomor transaksi yang akan dihapus (1-" << jumlahTransaksi << "): ";
    cin >> nomor;

    if (cin.fail() || nomor < 1 || nomor > jumlahTransaksi) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nomor transaksi tidak valid!\n";
        return;
    }

    int index = nomor - 1;

    cout << "\n--- Data yang akan dihapus (No. " << nomor << ") ---" << endl;
    cout << "Nama Pembeli: " << namaPembeli[index] << endl;
    cout << "Nama Baju: " << namaBaju[index] << endl;
    cout << "Jumlah: " << jumlahBeli[index] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[index] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[index] << endl;
    cout << "Waktu Transaksi: " << waktuTransaksi[index] << endl;
    tampilkanGaris(30);

    char konfirmasi;
    cout << "\nYakin ingin menghapus transaksi ini? (y/n): ";
    cin >> konfirmasi;
    cin.ignore(); // Membersihkan buffer

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

// Fungsi untuk menyimpan data ke file
void simpanKeFile() {
    clearScreen();
    cout << "SIMPAN DATA TRANSAKSI KE FILE" << endl;
    tampilkanGaris(40);

    ofstream fileTransaksi("transaksi_toko.txt"); // Membuat atau membuka file

    if (fileTransaksi.is_open()) {
        fileTransaksi << jumlahTransaksi << "\n"; // Baris pertama: jumlah transaksi
        for (int i = 0; i < jumlahTransaksi; i++) {
            fileTransaksi << namaPembeli[i] << "\n";
            fileTransaksi << namaBaju[i] << "\n";
            fileTransaksi << jumlahBeli[i] << "\n";
            fileTransaksi << hargaSatuan[i] << "\n";
            fileTransaksi << totalBayar[i] << "\n";
            fileTransaksi << waktuTransaksi[i] << "\n";
        }
        fileTransaksi.close();
        cout << "Data transaksi berhasil disimpan ke file 'transaksi_toko.txt'!\n";
        cout << jumlahTransaksi << " record transaksi disimpan." << endl;
    } else {
        cout << "Gagal membuka file 'transaksi_toko.txt' untuk penyimpanan.\n";
    }
}

// Fungsi baru: Memuat data dari file
void muatDataDariFile() {
    ifstream fileTransaksi("transaksi_toko.txt");

    if (fileTransaksi.is_open()) {
        fileTransaksi >> jumlahTransaksi;
        fileTransaksi.ignore(numeric_limits<streamsize>::max(), '\n'); // Konsumsi newline setelah membaca int

        for (int i = 0; i < jumlahTransaksi; i++) {
            getline(fileTransaksi, namaPembeli[i]);
            getline(fileTransaksi, namaBaju[i]);
            fileTransaksi >> jumlahBeli[i];
            fileTransaksi >> hargaSatuan[i];
            fileTransaksi >> totalBayar[i];
            fileTransaksi.ignore(numeric_limits<streamsize>::max(), '\n'); // Konsumsi newline setelah membaca double
            getline(fileTransaksi, waktuTransaksi[i]);
        }
        fileTransaksi.close();
        cout << "\n" << jumlahTransaksi << " data transaksi berhasil dimuat dari 'transaksi_toko.txt'.\n";
    } else {
        cout << "\nFile 'transaksi_toko.txt' tidak ditemukan atau gagal dibuka. Memulai dengan data kosong.\n";
    }
    pauseScreen();
}

// Fungsi untuk menampilkan transaksi tertinggi
void tampilkanTransaksiTertinggi() {
    clearScreen();
    cout << "DETAIL TRANSAKSI DENGAN NILAI TERTINGGI" << endl;
    tampilkanGaris(45);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi untuk menentukan yang tertinggi." << endl;
        tampilkanGaris(45);
        return;
    }

    double maksimal = totalBayar[0];
    int indeksMaks = 0;

    for (int i = 1; i < jumlahTransaksi; i++) {
        if (totalBayar[i] > maksimal) {
            maksimal = totalBayar[i];
            indeksMaks = i;
        }
    }

    cout << "Nama Pembeli: " << namaPembeli[indeksMaks] << endl;
    cout << "Nama Baju: " << namaBaju[indeksMaks] << endl;
    cout << "Jumlah Beli: " << jumlahBeli[indeksMaks] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[indeksMaks] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[indeksMaks] << endl;
    cout << "Waktu Transaksi: " << waktuTransaksi[indeksMaks] << endl;
    tampilkanGaris(45);
}

// Fungsi untuk menampilkan transaksi terendah
void tampilkanTransaksiTerendah() {
    clearScreen();
    cout << "DETAIL TRANSAKSI DENGAN NILAI TERENDAH" << endl;
    tampilkanGaris(45);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada transaksi untuk menentukan yang terendah." << endl;
        tampilkanGaris(45);
        return;
    }

    double minimal = totalBayar[0];
    int indeksMin = 0;

    for (int i = 1; i < jumlahTransaksi; i++) {
        if (totalBayar[i] < minimal) {
            minimal = totalBayar[i];
            indeksMin = i;
        }
    }

    cout << "Nama Pembeli: " << namaPembeli[indeksMin] << endl;
    cout << "Nama Baju: " << namaBaju[indeksMin] << endl;
    cout << "Jumlah Beli: " << jumlahBeli[indeksMin] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[indeksMin] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[indeksMin] << endl;
    cout << "Waktu Transaksi: " << waktuTransaksi[indeksMin] << endl;
    tampilkanGaris(45);
}

// Fungsi Selection Sort untuk mengurutkan transaksi berdasarkan Total Bayar (ascending)
void selectionSortByTotalBayar() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < jumlahTransaksi; j++) {
            if (totalBayar[j] < totalBayar[min_idx]) {
                min_idx = j;
            }
        }

        // Tukar semua elemen data transaksi secara paralel
        swap(namaPembeli[min_idx], namaPembeli[i]);
        swap(namaBaju[min_idx], namaBaju[i]);
        swap(jumlahBeli[min_idx], jumlahBeli[i]);
        swap(hargaSatuan[min_idx], hargaSatuan[i]);
        swap(totalBayar[min_idx], totalBayar[i]);
        swap(waktuTransaksi[min_idx], waktuTransaksi[i]);
    }
}

// Fungsi pengurutan berdasarkan Waktu Transaksi (terbaru ke terlama) - Menggunakan Selection Sort
void sortTransactionsByDate() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        int max_idx = i; // Cari yang terbaru (terbesar)
        for (int j = i + 1; j < jumlahTransaksi; j++) {
            // Membandingkan string waktu secara leksikografis
            // String waktu dalam format YYYY-MM-DD HH:MM:SS dapat langsung dibandingkan
            if (waktuTransaksi[j] > waktuTransaksi[max_idx]) {
                max_idx = j;
            }
        }

        // Tukar semua elemen data transaksi secara paralel
        swap(namaPembeli[max_idx], namaPembeli[i]);
        swap(namaBaju[max_idx], namaBaju[i]);
        swap(jumlahBeli[max_idx], jumlahBeli[i]);
        swap(hargaSatuan[max_idx], hargaSatuan[i]);
        swap(totalBayar[max_idx], totalBayar[i]);
        swap(waktuTransaksi[max_idx], waktuTransaksi[i]);
    }
}

// Fungsi baru: Filter transaksi berdasarkan rentang tanggal
void filterTransaksiByTanggal() {
    clearScreen();
    cout << "FILTER TRANSAKSI BERDASARKAN TANGGAL" << endl;
    tampilkanGaris(40);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada data transaksi untuk difilter." << endl;
        return;
    }

    int startYear, startMonth, startDay;
    int endYear, endMonth, endDay;

    cout << "Masukkan Tanggal Mulai (YYYY MM DD): ";
    cin >> startYear >> startMonth >> startDay;
    while (cin.fail() || !isValidDate(startYear, startMonth, startDay)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Format tanggal tidak valid atau tanggal tidak ada! Masukkan Tanggal Mulai (YYYY MM DD): ";
        cin >> startYear >> startMonth >> startDay;
    }

    cout << "Masukkan Tanggal Akhir (YYYY MM DD): ";
    cin >> endYear >> endMonth >> endDay;
    while (cin.fail() || !isValidDate(endYear, endMonth, endDay)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Format tanggal tidak valid atau tanggal tidak ada! Masukkan Tanggal Akhir (YYYY MM DD): ";
        cin >> endYear >> endMonth >> endDay;
    }
    cin.ignore(); // Membersihkan buffer

    // Konversi tanggal input menjadi string YYYY-MM-DD untuk perbandingan
    stringstream ssStart, ssEnd;
    ssStart << setfill('0') << setw(4) << startYear << "-"
            << setfill('0') << setw(2) << startMonth << "-"
            << setfill('0') << setw(2) << startDay;
    string tanggalMulaiStr = ssStart.str();

    ssEnd << setfill('0') << setw(4) << endYear << "-"
          << setfill('0') << setw(2) << endMonth << "-"
          << setfill('0') << setw(2) << endDay;
    string tanggalAkhirStr = ssEnd.str();


    cout << "\nHASIL FILTER TRANSAKSI DARI " << tanggalMulaiStr << " HINGGA " << tanggalAkhirStr << ":" << endl;
    tampilkanGaris(120);

    // Header tabel hasil filter
    cout << "| " << left << setw(3) << "No"
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;
    tampilkanGaris(120);

    bool ditemukan = false;
    int noUrut = 1;
    for (int i = 0; i < jumlahTransaksi; i++) {
        string tanggalTransaksi = waktuTransaksi[i].substr(0, 10); // Ambil bagian tanggal saja

        if (tanggalTransaksi >= tanggalMulaiStr && tanggalTransaksi <= tanggalAkhirStr) {
            cout << "| " << left << setw(3) << noUrut++
                 << " | " << setw(20) << namaPembeli[i].substr(0, 20)
                 << " | " << setw(15) << namaBaju[i].substr(0, 15)
                 << " | " << right << setw(8) << jumlahBeli[i]
                 << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
                 << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[i]
                 << " | " << left << setw(19) << waktuTransaksi[i]
                 << " |" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada transaksi dalam rentang tanggal tersebut.\n";
    } else {
        tampilkanGaris(120);
    }
}

// Fungsi baru: Filter transaksi berdasarkan rentang total bayar
void filterTransaksiByTotal() {
    clearScreen();
    cout << "FILTER TRANSAKSI BERDASARKAN RENTANG TOTAL BAYAR" << endl;
    tampilkanGaris(50);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada data transaksi untuk difilter." << endl;
        return;
    }

    double minTotal, maxTotal;
    cout << "Masukkan Total Bayar Minimum (Rp): ";
    cin >> minTotal;
    while (cin.fail() || minTotal < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid! Masukkan angka positif untuk Total Bayar Minimum: ";
        cin >> minTotal;
    }

    cout << "Masukkan Total Bayar Maksimum (Rp): ";
    cin >> maxTotal;
    while (cin.fail() || maxTotal < minTotal) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid! Maksimum tidak boleh kurang dari Minimum. Masukkan angka positif untuk Total Bayar Maksimum: ";
        cin >> maxTotal;
    }
    cin.ignore(); // Membersihkan buffer

    cout << "\nHASIL FILTER TRANSAKSI DENGAN TOTAL BAYAR ANTARA Rp " << fixed << setprecision(2) << minTotal
         << " DAN Rp " << fixed << setprecision(2) << maxTotal << ":" << endl;
    tampilkanGaris(120);

    // Header tabel hasil filter
    cout << "| " << left << setw(3) << "No"
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;
    tampilkanGaris(120);

    bool ditemukan = false;
    int noUrut = 1;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (totalBayar[i] >= minTotal && totalBayar[i] <= maxTotal) {
            cout << "| " << left << setw(3) << noUrut++
                 << " | " << setw(20) << namaPembeli[i].substr(0, 20)
                 << " | " << setw(15) << namaBaju[i].substr(0, 15)
                 << " | " << right << setw(8) << jumlahBeli[i]
                 << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
                 << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[i]
                 << " | " << left << setw(19) << waktuTransaksi[i]
                 << " |" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada transaksi dalam rentang total bayar tersebut.\n";
    } else {
        tampilkanGaris(120);
    }
}

// Fungsi baru: Export data ke CSV
void exportToCSV() {
    clearScreen();
    cout << "EXPORT DATA TRANSAKSI KE FILE CSV" << endl;
    tampilkanGaris(40);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada data transaksi untuk diexport." << endl;
        return;
    }

    ofstream fileCSV("transaksi_toko.csv");

    if (fileCSV.is_open()) {
        // Tulis header CSV
        fileCSV << "No,Nama Pembeli,Nama Baju,Jumlah Beli,Harga Satuan,Total Bayar,Waktu Transaksi\n";

        // Tulis data transaksi
        for (int i = 0; i < jumlahTransaksi; i++) {
            fileCSV << (i + 1) << ",";
            fileCSV << "\"" << namaPembeli[i] << "\","; // Gunakan kutip ganda untuk string
            fileCSV << "\"" << namaBaju[i] << "\",";
            fileCSV << jumlahBeli[i] << ",";
            fileCSV << fixed << setprecision(2) << hargaSatuan[i] << ",";
            fileCSV << fixed << setprecision(2) << totalBayar[i] << ",";
            fileCSV << "\"" << waktuTransaksi[i] << "\"\n";
        }
        fileCSV.close();
        cout << "Data transaksi berhasil diexport ke file 'transaksi_toko.csv'!\n";
        cout << jumlahTransaksi << " record diexport." << endl;
    } else {
        cout << "Gagal membuka file 'transaksi_toko.csv' untuk export.\n";
    }
}


// Fungsi simulasi login
bool loginUser(string& username, string& role) {
    const int MAX_LOGIN_ATTEMPTS = 3;
    string user, pass;
    int attempts = 0;

    // Data user dummy (bisa dari file atau database sungguhan)
    // Username: password: role
    // admin: admin123: admin
    // kasir: kasir123: kasir
    string validUsernameAdmin = "admin";
    string validPasswordAdmin = "admin123";
    string validUsernameKasir = "kasir";
    string validPasswordKasir = "kasir123";

    while (attempts < MAX_LOGIN_ATTEMPTS) {
        cout << "\n--- LOGIN ---" << endl;
        cout << "Username: ";
        getline(cin, user);
        cout << "Password: ";
        getline(cin, pass);

        if (user == validUsernameAdmin && pass == validPasswordAdmin) {
            username = validUsernameAdmin;
            role = "admin";
            return true;
        } else if (user == validUsernameKasir && pass == validPasswordKasir) {
            username = validUsernameKasir;
            role = "kasir";
            return true;
        } else {
            cout << "Username atau password salah. Sisa percobaan: " << (MAX_LOGIN_ATTEMPTS - 1 - attempts) << endl;
            attempts++;
        }
    }
    return false; // Login gagal setelah beberapa percobaan
}


// Fungsi untuk mendapatkan waktu saat ini dalam format YYYY-MM-DD HH:MM:SS
string getCurrentTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct); // %X untuk waktu (HH:MM:SS)
    return buf;
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Pastikan buffer bersih
    // cin.get(); // Sudah dibersihkan oleh ignore di atas
}

// Fungsi untuk menampilkan garis
void tampilkanGaris(int panjang) {
    for (int i = 0; i < panjang; i++) {
        cout << "-";
    }
    cout << endl;
}

// --- FUNGSI HELPER UNTUK VALIDASI TANGGAL ---
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int year, int month) {
    if (month < 1 || month > 12) return 0;
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 31;
    }
}

bool isValidDate(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false; // Batasan tahun
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    return true;
}
