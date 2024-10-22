#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>  
#include <vector> 

struct Pesanan {
    int id;
    std::string namaMakanan;
    std::string status; 
    Pesanan* next; 
};

Pesanan* head = nullptr; 
Pesanan* tail = nullptr; 
int jumlahPesanan = 0;

void tambahPesanan() {
    Pesanan* pesananBaru = new Pesanan();
    pesananBaru->id = ++jumlahPesanan; 
    std::cout << "Masukkan nama makanan: ";
    std::cin >> pesananBaru->namaMakanan;
    pesananBaru->status = "Belum Dibeli";
    pesananBaru->next = nullptr;

    if (head == nullptr) {
        head = tail = pesananBaru;
    } else {
        pesananBaru->next = head;
        head = pesananBaru;

        tail->next = pesananBaru;
        tail = pesananBaru;
    }
    std::cout << "Pesanan berhasil ditambahkan!" << std::endl;
}

void tampilkanPesanan() {
    if (head == nullptr) {
        std::cout << "Tidak ada pesanan." << std::endl;
        return;
    }
    
    std::cout << "\nDaftar Pesanan:\n";
    std::cout << std::left << std::setw(5) << "ID" 
              << std::setw(20) << "Nama Makanan" 
              << std::setw(15) << "Status" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    Pesanan* current = head;
    while (current != nullptr) {
        std::cout << std::left << std::setw(5) << current->id 
                  << std::setw(20) << current->namaMakanan 
                  << std::setw(15) << current->status << std::endl;
        current = current->next;
    }
}

int fibonacciSearch(int idDicari) {
    int fibMMm2 = 0;  
    int fibMMm1 = 1;   
    int fibM = fibMMm2 + fibMMm1;  

    Pesanan* current = head;
    int n = jumlahPesanan;
    std::vector<int> pesananIds;
    while (current != nullptr) {
        pesananIds.push_back(current->id);
        current = current->next;
    }

    while (fibM < n) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    while (fibM > 1) {
        int i = std::min(offset + fibMMm2, n - 1);

        if (pesananIds[i] < idDicari) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;
        } else if (pesananIds[i] > idDicari) {
            fibM = fibMMm2;
            fibMMm1 -= fibMMm2;
            fibMMm2 = fibM - fibMMm1;
        } else {
            return i;
        }
    }

    if (fibMMm1 && pesananIds[offset + 1] == idDicari) {
        return offset + 1;
    }

    return -1;
}

int jumpSearch(int idDicari) {
    Pesanan* current = head;
    std::vector<int> pesananIds;
    while (current != nullptr) {
        pesananIds.push_back(current->id);
        current = current->next;
    }

    int n = jumlahPesanan;
    int step = std::sqrt(n);
    int prev = 0;

    while (pesananIds[std::min(step, n) - 1] < idDicari) {
        prev = step;
        step += std::sqrt(n);
        if (prev >= n) return -1;
    }

    while (pesananIds[prev] < idDicari) {
        prev++;
        if (prev == std::min(step, n)) return -1;
    }

    if (pesananIds[prev] == idDicari) {
        return prev;
    }

    return -1;
}

int boyerMooreSearch(const std::string& pattern) {
    Pesanan* current = head;
    std::vector<std::string> makananNames;
    while (current != nullptr) {
        makananNames.push_back(current->namaMakanan);
        current = current->next;
    }

    int m = pattern.length();
    int n = makananNames.size();
    std::vector<int> badChar(256, -1);

    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }

    int s = 0;
    while (s <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == makananNames[s][j]) {
            j--;
        }

        if (j < 0) {
            return s;
        } else {
            s += std::max(1, j - badChar[makananNames[s][j]]);
        }
    }

    return -1;
}

int main() {
    int pilihan;
    do {
        std::cout << "\nMenu Sistem Manajemen Jasa Titip Gacoan:\n";
        std::cout << "1. Tambah Pesanan (Stack & Queue)" << std::endl;
        std::cout << "2. Tampilkan Pesanan" << std::endl;
        std::cout << "3. Cari Pesanan dengan Fibonacci Search" << std::endl;
        std::cout << "4. Cari Pesanan dengan Jump Search" << std::endl;
        std::cout << "5. Cari Pesanan dengan Boyer-Moore Search" << std::endl;
        std::cout << "6. Keluar" << std::endl;
        std::cout << "Pilih opsi (1/2/3/4/5/6): ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPesanan();
                break;
            case 2:
                tampilkanPesanan();
                break;
            case 3: {
                int idDicari;
                std::cout << "Masukkan ID pesanan yang dicari (Fibonacci Search): ";
                std::cin >> idDicari;
                int hasil = fibonacciSearch(idDicari);
                if (hasil != -1) {
                    std::cout << "Pesanan ditemukan pada indeks: " << hasil << std::endl;
                } else {
                    std::cout << "Pesanan tidak ditemukan." << std::endl;
                }
                break;
            }
            case 4: {
                int idDicari;
                std::cout << "Masukkan ID pesanan yang dicari (Jump Search): ";
                std::cin >> idDicari;
                int hasil = jumpSearch(idDicari);
                if (hasil != -1) {
                    std::cout << "Pesanan ditemukan pada indeks: " << hasil << std::endl;
                } else {
                    std::cout << "Pesanan tidak ditemukan." << std::endl;
                }
                break;
            }
            case 5: {
                std::string namaDicari;
                std::cout << "Masukkan nama makanan yang dicari (Boyer-Moore Search): ";
                std::cin >> namaDicari;
                int hasil = boyerMooreSearch(namaDicari);
                if (hasil != -1) {
                    std::cout << "Pesanan ditemukan pada indeks: " << hasil << std::endl;
                } else {
                    std::cout << "Pesanan tidak ditemukan." << std::endl;
                }
                break;
            }
            case 6:
                std::cout << "Terima kasih telah menggunakan program ini!" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid!" << std::endl;
        }
    } while (pilihan != 6);

    return 0;
}
