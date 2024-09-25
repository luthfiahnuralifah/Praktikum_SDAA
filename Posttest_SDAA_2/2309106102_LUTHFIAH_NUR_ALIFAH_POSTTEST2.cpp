#include <iostream>
#include <string>

const int MAX_PESANAN = 100;

struct Pesanan {
    int id;
    std::string namaMakanan;
    std::string status; 
};

Pesanan pesananList[MAX_PESANAN];
int jumlahPesanan = 0;

void tambahPesanan() {
    if (jumlahPesanan >= MAX_PESANAN) {
        std::cout << "Daftar pesanan sudah penuh!" << std::endl;
        return;
    }
    Pesanan p;
    p.id = jumlahPesanan + 1; 
    std::cout << "Masukkan nama makanan: ";
    std::cin >> p.namaMakanan;
    p.status = "Belum Dibeli";
    pesananList[jumlahPesanan++] = p;
    std::cout << "Pesanan ditambahkan!" << std::endl;
}

void tampilkanPesanan() {
    std::cout << "Daftar Pesanan:" << std::endl;
    for (int i = 0; i < jumlahPesanan; i++) {
        std::cout << "ID: " << pesananList[i].id 
                  << ", Nama Makanan: " << pesananList[i].namaMakanan 
                  << ", Status: " << pesananList[i].status << std::endl;
    }
}

void ubahStatusPesanan() {
    int id;
    std::cout << "Masukkan ID pesanan yang ingin diubah status: ";
    std::cin >> id;
    if (id < 1 || id > jumlahPesanan) {
        std::cout << "ID tidak valid!" << std::endl;
        return;
    }
    std::string statusBaru;
    std::cout << "Masukkan status baru (Belum Dibeli/Sudah Dibeli): ";
    std::cin >> statusBaru;
    pesananList[id - 1].status = statusBaru;
    std::cout << "Status pesanan telah diubah!" << std::endl;
}

void hapusPesanan() {
    int id;
    std::cout << "Masukkan ID pesanan yang ingin dihapus: ";
    std::cin >> id;
    if (id < 1 || id > jumlahPesanan) {
        std::cout << "ID tidak valid!" << std::endl;
        return;
    }
    for (int i = id - 1; i < jumlahPesanan - 1; i++) {
        pesananList[i] = pesananList[i + 1];
    }
    jumlahPesanan--;
    std::cout << "Pesanan telah dihapus!" << std::endl;
}

int main() {
    int pilihan;
    do {
        std::cout << "\nMenu Sistem Manajemen Jasa Titip Gacoan:" << std::endl;
        std::cout << "1. Tambah Pesanan" << std::endl;
        std::cout << "2. Tampilkan Pesanan" << std::endl;
        std::cout << "3. Ubah Status Pesanan" << std::endl;
        std::cout << "4. Hapus Pesanan" << std::endl;
        std::cout << "5. Keluar" << std::endl;
        std::cout << "Pilih opsi: ";
        std::cin >> pilihan;

        switch (pilihan) {
            case 1:
                tambahPesanan();
                break;
            case 2:
                tampilkanPesanan();
                break;
            case 3:
                ubahStatusPesanan();
                break;
            case 4:
                hapusPesanan();
                break;
            case 5:
                std::cout << "Terima kasih!" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid!" << std::endl;
        }
    } while (pilihan != 5);
    
    return 0;
}
