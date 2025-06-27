#include <iostream>
#include <iomanip>
#include <string>
#include <limits>   // Untuk numeric_limits
#include <ctime>    // Untuk waktu
#include <cstdlib>  // Untuk system("cls") atau system("clear")
#include <fstream>  // Untuk operasi file (ifstream, ofstream)
#include <sstream>  // Untuk stringstream
#include <vector>   // Hanya untuk membantu dalam beberapa konversi atau logika, tidak menggantikan array global
#include <algorithm> // Untuk fungsi transform dan tolower

using namespace std;

// --- GLOBAL CONSTANTS ---
const int MAX_TRANSAKSI = 1000; // Maximum transaction limit, increased for simulation

// --- GLOBAL ARRAYS FOR TRANSACTION DATA ---
string namaPembeli[MAX_TRANSAKSI];
string namaBaju[MAX_TRANSAKSI];
int jumlahBeli[MAX_TRANSAKSI];
double hargaSatuan[MAX_TRANSAKSI];
double totalBayar[MAX_TRANSAKSI];
string waktuTransaksi[MAX_TRANSAKSI]; // Format: YYYY-MM-DD HH:MM:SS

// --- OTHER GLOBAL VARIABLES ---
int jumlahTransaksi = 0; // Number of transactions currently stored

// --- FUNCTION PROTOTYPES ---
void tampilkanHeader();
void tampilkanMenuUtama();
void tampilkanMenuAdmin();
void inputDataPembeli();
void tampilkanTabelTransaksi();
void hitungTotalPemasukan();
void cariTransaksi(); // Modified to include search choices
void tampilkanStatistik();
void hapusTransaksi();
void editTransaksi();
void simpanKeFile();
void muatDataDariFile(); // Function: Load data from file
void tampilkanTransaksiTertinggi();
void tampilkanTransaksiTerendah();
void selectionSortByTotalBayar();
void sortTransactionsByDate(); // Function: Sort by date (newest to oldest)
void selectionSortByNamaPembeli(); // NEW: Sort by customer name for binary search
int binarySearchByName(const string& key); // NEW: Binary search by customer name
void filterTransaksiByTanggal(); // Function: Filter by date range
void filterTransaksiByTotal();   // Function: Filter by total amount range
void exportToCSV();              // Function: Export data to CSV
bool loginUser(string& username, string& role); // Function: Login simulation
string getCurrentTime();
void clearScreen();
void pauseScreen();
void tampilkanGaris(int panjang);
bool isLeapYear(int year); // Helper function for date
int daysInMonth(int year, int month); // Helper function for date
bool isValidDate(int year, int month, int day); // Helper function for date

int main() {
    // Initialize random seed (used by other functions if any)
    srand(time(0));

    // Try to load data when the program starts
    muatDataDariFile();

    string usernameLoggedIn;
    string roleLoggedIn;

    // --- LOGIN SIMULATION ---
    clearScreen();
    tampilkanHeader();
    cout << "SELAMAT DATANG DI PROGRAM MESIN KASIR" << endl;
    tampilkanGaris(40);
    if (!loginUser(usernameLoggedIn, roleLoggedIn)) {
        cout << "\nTerlalu banyak percobaan login gagal. Program akan keluar." << endl;
        pauseScreen();
        return 1; // Exit with error code
    }
    cout << "\nLogin Berhasil! Selamat datang, " << usernameLoggedIn << " (" << roleLoggedIn << ")." << endl;
    pauseScreen();


    int pilihan;
    do {
        clearScreen();
        tampilkanHeader();
        tampilkanMenuUtama();

        // Only show admin menu if role is "admin"
        if (roleLoggedIn == "admin") {
            cout << "11. Menu Administrator" << endl;
        }
        cout << "0. Keluar Program" << endl;
        tampilkanGaris(30);

        cout << "Masukkan pilihan Anda: ";
        cin >> pilihan;

        // Validate main menu input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid! Silakan masukkan angka.\n";
            pauseScreen();
            continue;
        }
        cin.ignore(); // Clear buffer

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
                if (roleLoggedIn == "admin") { // Only admin can access this menu
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

// --- FUNCTION DEFINITIONS ---

// Function to display program header
void tampilkanHeader() {
    tampilkanGaris(60);
    cout << "|" << setw(58) << "PROGRAM MESIN KASIR TOKO BAJU" << setw(2) << "|" << endl;
    cout << "|" << setw(58) << "Sistem Transaksi Penjualan" << setw(2) << "|" << endl;
    tampilkanGaris(60);
    cout << "Tanggal: " << getCurrentTime() << endl;
    tampilkanGaris(60);
    cout << endl;
}

// Function to display main menu
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
    // Admin menu option will be added in main() if role is "admin"
}

// Function to display administrator menu
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

// Function to input customer data
void inputDataPembeli() {
    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        cout << "\nDatabase transaksi sudah penuh! Maksimal " << MAX_TRANSAKSI << " transaksi.\n";
        pauseScreen();
        return;
    }

    clearScreen();
    cout << "INPUT DATA PEMBELI" << endl;
    tampilkanGaris(30);

    // Input customer name
    cout << "Nama Pembeli: ";
    getline(cin, namaPembeli[jumlahTransaksi]);
    while (namaPembeli[jumlahTransaksi].empty()) {
        cout << "Nama pembeli tidak boleh kosong! Masukkan nama: ";
        getline(cin, namaPembeli[jumlahTransaksi]);
    }

    // Input shirt name
    cout << "Nama Baju: ";
    getline(cin, namaBaju[jumlahTransaksi]);
    while (namaBaju[jumlahTransaksi].empty()) {
        cout << "Nama baju tidak boleh kosong! Masukkan nama: ";
        getline(cin, namaBaju[jumlahTransaksi]);
    }

    // Input quantity with validation
    do {
        cout << "Jumlah Beli: ";
        cin >> jumlahBeli[jumlahTransaksi];
        if (cin.fail() || jumlahBeli[jumlahTransaksi] <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Jumlah beli harus berupa angka positif!\n";
        }
    } while (cin.fail() || jumlahBeli[jumlahTransaksi] <= 0);

    // Input unit price with validation
    do {
        cout << "Harga Satuan (Rp): ";
        cin >> hargaSatuan[jumlahTransaksi];
        if (cin.fail() || hargaSatuan[jumlahTransaksi] <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Harga satuan harus berupa angka positif!\n";
        }
    } while (cin.fail() || hargaSatuan[jumlahTransaksi] <= 0);
    cin.ignore(); // Clear buffer after double/int input

    // Calculate total payment
    totalBayar[jumlahTransaksi] = jumlahBeli[jumlahTransaksi] * hargaSatuan[jumlahTransaksi];

    // Set transaction time
    waktuTransaksi[jumlahTransaksi] = getCurrentTime();

    // Display transaction summary
    cout << "\nRINGKASAN TRANSAKSI:" << endl;
    tampilkanGaris(40);
    cout << "Nama Pembeli: " << namaPembeli[jumlahTransaksi] << endl;
    cout << "Nama Baju: " << namaBaju[jumlahTransaksi] << endl;
    cout << "Jumlah Beli: " << jumlahBeli[jumlahTransaksi] << " pcs" << endl;
    cout << "Harga Satuan: Rp " << fixed << setprecision(2) << hargaSatuan[jumlahTransaksi] << endl;
    cout << "Total Bayar: Rp " << fixed << setprecision(2) << totalBayar[jumlahTransaksi] << endl;
    cout << "Waktu: " << waktuTransaksi[jumlahTransaksi] << endl;
    tampilkanGaris(40);

    // Confirmation for saving
    char konfirmasi;
    cout << "\nSimpan transaksi ini? (y/n): ";
    cin >> konfirmasi;
    cin.ignore(); // Clear buffer after char input

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        jumlahTransaksi++;
        cout << "\nTransaksi berhasil disimpan! ID Transaksi: " << jumlahTransaksi << endl;
    } else {
        cout << "\nTransaksi dibatalkan!" << endl;
    }

    pauseScreen();
}

// Function to display transaction table
void tampilkanTabelTransaksi() {
    clearScreen();
    cout << "TABEL TRANSAKSI PENJUALAN BAJU" << endl;
    tampilkanGaris(120);

    // Table header
    cout << "| " << left << setw(3) << "No"
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;

    tampilkanGaris(120);

    // Transaction data
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

// Function to calculate total income
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

// Function to search for transactions
void cariTransaksi() {
    clearScreen();
    cout << "PENCARIAN TRANSAKSI" << endl;
    tampilkanGaris(50);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada data transaksi untuk dicari!\n";
        return;
    }

    int searchChoice;
    cout << "Pilih metode pencarian:" << endl;
    cout << "1. Pencarian Linier (Substring Nama Pembeli)" << endl;
    cout << "2. Pencarian Biner (Nama Pembeli Tepat Sama - Membutuhkan Pengurutan)" << endl;
    cout << "Masukkan pilihan (1/2): ";
    cin >> searchChoice;

    if (cin.fail() || (searchChoice != 1 && searchChoice != 2)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPilihan tidak valid! Membatalkan pencarian.\n";
        return;
    }
    cin.ignore(); // Consume the newline character

    string keyword;
    cout << "Masukkan nama pembeli yang dicari: ";
    getline(cin, keyword);

    clearScreen();
    cout << "HASIL PENCARIAN UNTUK '" << keyword << "':" << endl;
    tampilkanGaris(120);

    // Table header for search results
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
    if (searchChoice == 1) { // Linear Search (substring match, case-insensitive)
        for (int i = 0; i < jumlahTransaksi; i++) {
            // Convert both strings to lowercase for case-insensitive search
            string namaPembeliLower = namaPembeli[i];
            string keywordLower = keyword;
            transform(namaPembeliLower.begin(), namaPembeliLower.end(), namaPembeliLower.begin(), ::tolower);
            transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

            if (namaPembeliLower.find(keywordLower) != string::npos) {
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
    } else { // Binary Search (exact match, case-sensitive)
        cout << "\nMelakukan pengurutan data berdasarkan Nama Pembeli untuk pencarian biner...\n";
        selectionSortByNamaPembeli(); // Sort data by name
        // After sorting, the original indices are lost. We display based on the new sorted order.

        int found_idx = binarySearchByName(keyword);

        if (found_idx != -1) {
            // Found at least one match, now find all exact matches around it
            ditemukan = true;
            int current_idx = found_idx;

            // Move left to find the first occurrence (if duplicates exist)
            while (current_idx >= 0 && namaPembeli[current_idx] == keyword) {
                current_idx--;
            }
            current_idx++; // Move back to the first exact match

            // Iterate right to display all exact matches
            while (current_idx < jumlahTransaksi && namaPembeli[current_idx] == keyword) {
                cout << "| " << left << setw(3) << (current_idx + 1) // Display index in sorted list
                     << " | " << setw(20) << namaPembeli[current_idx].substr(0, 20)
                     << " | " << setw(15) << namaBaju[current_idx].substr(0, 15)
                     << " | " << right << setw(8) << jumlahBeli[current_idx]
                     << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[current_idx]
                     << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[current_idx]
                     << " | " << left << setw(19) << waktuTransaksi[current_idx]
                     << " |" << endl;
                current_idx++;
            }
            cout << "\nCatatan: Untuk pencarian biner, data diurutkan berdasarkan nama pembeli. Nomor transaksi (No) mencerminkan posisi dalam daftar yang sudah diurutkan." << endl;

        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada transaksi yang cocok dengan kriteria pencarian Anda.\n";
    } else {
        tampilkanGaris(120);
    }
}

// Function to display sales statistics
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
    cout << "  - Pembeli: " << namaPembeli[indeksTertinggi] << endl;
    cout << "  - Barang: " << namaBaju[indeksTertinggi] << endl;
    cout << "  - Total: Rp " << fixed << setprecision(2) << totalBayar[indeksTertinggi] << endl;
    cout << "---------------------------------------" << endl;
    cout << "Transaksi Dengan Nilai Terendah:" << endl;
    cout << "  - Pembeli: " << namaPembeli[indeksTerendah] << endl;
    cout << "  - Barang: " << namaBaju[indeksTerendah] << endl;
    cout << "  - Total: Rp " << fixed << setprecision(2) << totalBayar[indeksTerendah] << endl;
    cout << "---------------------------------------" << endl;

    if (jumlahTransaksi > 0) {
        double rataRata = totalPemasukan / jumlahTransaksi;
        cout << "Rata-rata Nilai Transaksi: Rp " << fixed << setprecision(2) << rataRata << endl;
    }

    tampilkanGaris(50);
}

// Function to edit a transaction
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
    cin.ignore(); // Clear buffer after cin >> nomor

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
    cin.ignore(); // Clear buffer after cin for unit price

    // Recalculate total payment
    totalBayar[index] = jumlahBeli[index] * hargaSatuan[index];
    waktuTransaksi[index] = getCurrentTime(); // Update transaction time when edited

    cout << "\nTransaksi No. " << nomor << " berhasil diperbarui!" << endl;
}

// Function to delete a transaction
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
    cin.ignore(); // Clear buffer

    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Shift all data after the deleted index
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

// Function to save data to file
void simpanKeFile() {
    clearScreen();
    cout << "SIMPAN DATA TRANSAKSI KE FILE" << endl;
    tampilkanGaris(40);

    ofstream fileTransaksi("transaksi_toko.txt"); // Create or open file

    if (fileTransaksi.is_open()) {
        fileTransaksi << jumlahTransaksi << "\n"; // First line: number of transactions
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

// Function: Load data from file
void muatDataDariFile() {
    ifstream fileTransaksi("transaksi_toko.txt");

    if (fileTransaksi.is_open()) {
        fileTransaksi >> jumlahTransaksi;
        fileTransaksi.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline after reading int

        for (int i = 0; i < jumlahTransaksi; i++) {
            getline(fileTransaksi, namaPembeli[i]);
            getline(fileTransaksi, namaBaju[i]);
            fileTransaksi >> jumlahBeli[i];
            fileTransaksi >> hargaSatuan[i];
            fileTransaksi >> totalBayar[i];
            fileTransaksi.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume newline after reading double
            getline(fileTransaksi, waktuTransaksi[i]);
        }
        fileTransaksi.close();
        cout << "\n" << jumlahTransaksi << " data transaksi berhasil dimuat dari 'transaksi_toko.txt'.\n";
    } else {
        cout << "\nFile 'transaksi_toko.txt' tidak ditemukan atau gagal dibuka. Memulai dengan data kosong.\n";
    }
    pauseScreen();
}

// Function to display highest transaction
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

// Function to display lowest transaction
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

// Selection Sort function to sort transactions by Total Pay (ascending)
void selectionSortByTotalBayar() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < jumlahTransaksi; j++) {
            if (totalBayar[j] < totalBayar[min_idx]) {
                min_idx = j;
            }
        }

        // Swap all transaction data elements in parallel
        swap(namaPembeli[min_idx], namaPembeli[i]);
        swap(namaBaju[min_idx], namaBaju[i]);
        swap(jumlahBeli[min_idx], jumlahBeli[i]);
        swap(hargaSatuan[min_idx], hargaSatuan[i]);
        swap(totalBayar[min_idx], totalBayar[i]);
        swap(waktuTransaksi[min_idx], waktuTransaksi[i]);
    }
}

// Sorting function by Transaction Time (newest to oldest) - Uses Selection Sort
void sortTransactionsByDate() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        int max_idx = i; // Find the newest (largest)
        for (int j = i + 1; j < jumlahTransaksi; j++) {
            // Comparing time strings lexicographically
            // Time strings in YYYY-MM-DD HH:MM:SS format can be directly compared
            if (waktuTransaksi[j] > waktuTransaksi[max_idx]) {
                max_idx = j;
            }
        }

        // Swap all transaction data elements in parallel
        swap(namaPembeli[max_idx], namaPembeli[i]);
        swap(namaBaju[max_idx], namaBaju[i]);
        swap(jumlahBeli[max_idx], jumlahBeli[i]);
        swap(hargaSatuan[max_idx], hargaSatuan[i]);
        swap(totalBayar[max_idx], totalBayar[i]);
        swap(waktuTransaksi[max_idx], waktuTransaksi[i]);
    }
}

// NEW: Selection Sort function to sort transactions by Customer Name (ascending)
void selectionSortByNamaPembeli() {
    for (int i = 0; i < jumlahTransaksi - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < jumlahTransaksi; j++) {
            // Compare name strings lexicographically
            if (namaPembeli[j] < namaPembeli[min_idx]) {
                min_idx = j;
            }
        }

        // Swap all transaction data elements in parallel
        swap(namaPembeli[min_idx], namaPembeli[i]);
        swap(namaBaju[min_idx], namaBaju[i]);
        swap(jumlahBeli[min_idx], jumlahBeli[i]);
        swap(hargaSatuan[min_idx], hargaSatuan[i]);
        swap(totalBayar[min_idx], totalBayar[i]);
        swap(waktuTransaksi[min_idx], waktuTransaksi[i]);
    }
}

// NEW: Binary Search function to find transactions by Customer Name (exact match)
// Customer names must be sorted in ascending order before calling this function
int binarySearchByName(const string& key) {
    int low = 0;
    int high = jumlahTransaksi - 1;
    int result_idx = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (namaPembeli[mid] == key) {
            result_idx = mid;
            // Important: Continue searching in the left part to find the first occurrence (if duplicates)
            high = mid - 1;
        } else if (namaPembeli[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return result_idx;
}


// Function: Filter transactions by date range
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
    cin.ignore(); // Consume the newline character

    cout << "Masukkan Tanggal Akhir (YYYY MM DD): ";
    cin >> endYear >> endMonth >> endDay;
    while (cin.fail() || !isValidDate(endYear, endMonth, endDay)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Format tanggal tidak valid atau tanggal tidak ada! Masukkan Tanggal Akhir (YYYY MM DD): ";
        cin >> endYear >> endMonth >> endDay;
    }
    cin.ignore(); // Consume the newline character

    // Convert input dates to string for comparison (YYYY-MM-DD format)
    stringstream ssStart, ssEnd;
    ssStart << setfill('0') << setw(4) << startYear << "-"
            << setfill('0') << setw(2) << startMonth << "-"
            << setfill('0') << setw(2) << startDay;
    string startDateStr = ssStart.str();

    ssEnd << setfill('0') << setw(4) << endYear << "-"
          << setfill('0') << setw(2) << endMonth << "-"
          << setfill('0') << setw(2) << endDay;
    string endDateStr = ssEnd.str();

    bool ditemukan = false;
    cout << "\nHASIL FILTER TRANSAKSI DARI " << startDateStr << " HINGGA " << endDateStr << ":" << endl;
    tampilkanGaris(120);

    // Table header for filtered results
    cout << "| " << left << setw(3) << "No"
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;
    tampilkanGaris(120);

    int count = 0;
    for (int i = 0; i < jumlahTransaksi; i++) {
        // Extract only the date part (YYYY-MM-DD) from waktuTransaksi
        string transactionDateStr = waktuTransaksi[i].substr(0, 10); // "YYYY-MM-DD"

        // Compare string dates
        if (transactionDateStr >= startDateStr && transactionDateStr <= endDateStr) {
            cout << "| " << left << setw(3) << (i + 1) // Using original index for now
                 << " | " << setw(20) << namaPembeli[i].substr(0, 20)
                 << " | " << setw(15) << namaBaju[i].substr(0, 15)
                 << " | " << right << setw(8) << jumlahBeli[i]
                 << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
                 << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[i]
                 << " | " << left << setw(19) << waktuTransaksi[i]
                 << " |" << endl;
            ditemukan = true;
            count++;
        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada transaksi dalam rentang tanggal tersebut.\n";
    } else {
        tampilkanGaris(120);
        cout << "Total Transaksi Filtered: " << count << " transaksi" << endl;
    }
}

// Function to filter transactions by total amount range
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
        cout << "Input tidak valid! Masukkan angka yang lebih besar dari atau sama dengan Total Minimum: ";
        cin >> maxTotal;
    }
    cin.ignore(); // Consume the newline character

    bool ditemukan = false;
    cout << "\nHASIL FILTER TRANSAKSI DENGAN TOTAL BAYAR ANTARA Rp " << fixed << setprecision(2) << minTotal
         << " DAN Rp " << fixed << setprecision(2) << maxTotal << ":" << endl;
    tampilkanGaris(120);

    // Table header for filtered results
    cout << "| " << left << setw(3) << "No"
         << " | " << setw(20) << "Nama Pembeli"
         << " | " << setw(15) << "Nama Baju"
         << " | " << setw(8) << "Jumlah"
         << " | " << setw(12) << "Harga Satuan"
         << " | " << setw(15) << "Total Bayar"
         << " | " << setw(19) << "Waktu Transaksi"
         << " |" << endl;
    tampilkanGaris(120);

    int count = 0;
    for (int i = 0; i < jumlahTransaksi; i++) {
        if (totalBayar[i] >= minTotal && totalBayar[i] <= maxTotal) {
            cout << "| " << left << setw(3) << (i + 1)
                 << " | " << setw(20) << namaPembeli[i].substr(0, 20)
                 << " | " << setw(15) << namaBaju[i].substr(0, 15)
                 << " | " << right << setw(8) << jumlahBeli[i]
                 << " | " << right << setw(12) << fixed << setprecision(0) << hargaSatuan[i]
                 << " | " << right << setw(15) << fixed << setprecision(0) << totalBayar[i]
                 << " | " << left << setw(19) << waktuTransaksi[i]
                 << " |" << endl;
            ditemukan = true;
            count++;
        }
    }

    if (!ditemukan) {
        cout << "\nTidak ada transaksi dalam rentang total bayar tersebut.\n";
    } else {
        tampilkanGaris(120);
        cout << "Total Transaksi Filtered: " << count << " transaksi" << endl;
    }
}

// Function to export data to CSV
void exportToCSV() {
    clearScreen();
    cout << "EXPORT DATA TRANSAKSI KE CSV" << endl;
    tampilkanGaris(40);

    if (jumlahTransaksi == 0) {
        cout << "Belum ada data transaksi untuk diekspor." << endl;
        return;
    }

    ofstream csvFile("transaksi_toko.csv");

    if (csvFile.is_open()) {
        // CSV Header
        csvFile << "No,Nama Pembeli,Nama Baju,Jumlah Beli,Harga Satuan,Total Bayar,Waktu Transaksi\n";

        // CSV Data
        for (int i = 0; i < jumlahTransaksi; i++) {
            csvFile << (i + 1) << ","
                    << "\"" << namaPembeli[i] << "\"," // Enclose in quotes to handle commas in names
                    << "\"" << namaBaju[i] << "\","
                    << jumlahBeli[i] << ","
                    << fixed << setprecision(2) << hargaSatuan[i] << ","
                    << fixed << setprecision(2) << totalBayar[i] << ","
                    << waktuTransaksi[i] << "\n";
        }
        csvFile.close();
        cout << "Data transaksi berhasil diekspor ke file 'transaksi_toko.csv'!\n";
        cout << jumlahTransaksi << " record transaksi diekspor." << endl;
    } else {
        cout << "Gagal membuka file 'transaksi_toko.csv' untuk ekspor.\n";
    }
}

// Function: Simulate user login
bool loginUser(string& username, string& role) {
    string inputUsername, inputPassword;
    int loginAttempts = 0;
    const int MAX_ATTEMPTS = 3;

    // Example user data
    // Note: In a real application, this data would be securely stored (e.g., in a database)
    // and passwords would be hashed. This is just a basic simulation.
    const string ADMIN_USER = "admin";
    const string ADMIN_PASS = "admin123";
    const string KASIR_USER = "kasir";
    const string KASIR_PASS = "kasir123";

    do {
        cout << "\nLOGIN SYSTEM" << endl;
        tampilkanGaris(20);
        cout << "Username: ";
        getline(cin, inputUsername);
        cout << "Password: ";
        getline(cin, inputPassword);

        if (inputUsername == ADMIN_USER && inputPassword == ADMIN_PASS) {
            username = ADMIN_USER;
            role = "admin";
            return true;
        } else if (inputUsername == KASIR_USER && inputPassword == KASIR_PASS) {
            username = KASIR_USER;
            role = "kasir";
            return true;
        } else {
            cout << "\nLogin gagal. Username atau password salah. Sisa percobaan: " << (MAX_ATTEMPTS - 1 - loginAttempts) << endl;
            loginAttempts++;
            pauseScreen();
            clearScreen();
            tampilkanHeader();
        }
    } while (loginAttempts < MAX_ATTEMPTS);

    return false; // Login failed after multiple attempts
}

// Function to get current time
string getCurrentTime() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    stringstream ss;
    ss << setfill('0') << setw(4) << (1900 + ltm->tm_year) << "-"
       << setfill('0') << setw(2) << (1 + ltm->tm_mon) << "-"
       << setfill('0') << setw(2) << ltm->tm_mday << " "
       << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    return ss.str();
}

// Function to clear console screen
void clearScreen() {
    // For Windows
    #ifdef _WIN32
        system("cls");
    // For Linux/macOS
    #else
        system("clear");
    #endif
}

// Function to pause console screen
void pauseScreen() {
    cout << "\nTekan ENTER untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Consume remaining input
    // cin.get(); // Wait for enter key
}

// Function to display a separator line
void tampilkanGaris(int panjang) {
    for (int i = 0; i < panjang; i++) {
        cout << "-";
    }
    cout << endl;
}

// Helper function: Check if year is a leap year
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Helper function: Return number of days in a month
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

// Helper function: Check if date is valid
bool isValidDate(int year, int month, int day) {
    if (year < 1900 || year > 2100) return false; // Year limitation
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    return true;
}

