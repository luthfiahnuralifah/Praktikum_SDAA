#include <iostream>
#include <string>
#include <iomanip>

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

void ubahStatusPesanan() {
    int id;
    std::cout << "Masukkan ID pesanan yang ingin diubah status: ";
    std::cin >> id;

    if (id < 1 || id > jumlahPesanan) {
        std::cout << "ID tidak valid!" << std::endl;
        return;
    }

    Pesanan* current = head;
    while (current != nullptr && current->id != id) {
        current = current->next;
    }

    if (current != nullptr) {
        int pilihanStatus;
        std::cout << "Masukkan status baru (Belum Dibeli (0), Sudah Dibeli (1)): ";
        std::cin >> pilihanStatus;

        if (pilihanStatus == 0) {
            current->status = "Belum Dibeli";
        } else if (pilihanStatus == 1) {
            current->status = "Sudah Dibeli";
        } else {
            std::cout << "Pilihan tidak valid!" << std::endl;
            return;
        }

        std::cout << "Status pesanan telah diubah!" << std::endl;
    } else {
        std::cout << "Pesanan tidak ditemukan!" << std::endl;
    }
}

void hapusPesananQueue() {
    if (head == nullptr) {
        std::cout << "Tidak ada pesanan untuk dihapus." << std::endl;
        return;
    }

    Pesanan* temp = head;
    head = head->next;
    
    std::cout << "Pesanan dengan ID " << temp->id << " telah dihapus!" << std::endl;
    delete temp;
    jumlahPesanan--;
}

void hapusPesananStack() {
    if (head == nullptr) {
        std::cout << "Tidak ada pesanan untuk dihapus." << std::endl;
        return;
    }

    Pesanan* temp = head;
    head = head->next;
    
    std::cout << "Pesanan dengan ID " << temp->id << " telah dihapus (Stack)!" << std::endl;
    delete temp;
    jumlahPesanan--;
}

Pesanan* getLast(Pesanan* curr) {
    while (curr != nullptr && curr->next != nullptr) {
        curr = curr->next;
    }
    return curr;
}

Pesanan* mergeSorted(Pesanan* a, Pesanan* b) {
    if (!a) return b;
    if (!b) return a;
    
    Pesanan* result = nullptr;
    if (a->id < b->id) {
        result = a;
        result->next = mergeSorted(a->next, b);
    } else {
        result = b;
        result->next = mergeSorted(a->next, b);
    }
    return result;
}

Pesanan* getMiddle(Pesanan* head) {
    if (!head) return head;
    
    Pesanan* slow = head;
    Pesanan* fast = head->next;
    
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Pesanan* mergeSort(Pesanan* head) {
    if (!head || !head->next) return head;

    Pesanan* middle = getMiddle(head);
    Pesanan* nextToMiddle = middle->next;
    
    middle->next = nullptr;
    
    Pesanan* left = mergeSort(head);
    Pesanan* right = mergeSort(nextToMiddle);
    
    Pesanan* sortedList = mergeSorted(left, right);
    return sortedList;
}

void sortAscending() {
    if (head == nullptr || head->next == nullptr) {
        std::cout << "Pesanan sudah terurut." << std::endl;
        return;
    }
    head = mergeSort(head);
    std::cout << "Pesanan berhasil diurutkan secara ascending (berdasarkan ID)!" << std::endl;
}

Pesanan* partition(Pesanan* low, Pesanan* high, Pesanan** newLow, Pesanan** newHigh) {
    Pesanan* pivot = high;
    Pesanan* prev = nullptr;
    Pesanan* curr = low;
    Pesanan* tail = pivot;

    while (curr != pivot) {
        if (curr->id > pivot->id) {
            if ((*newLow) == nullptr) (*newLow) = curr;
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) prev->next = curr->next;
            Pesanan* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if ((*newLow) == nullptr) (*newLow) = pivot;

    (*newHigh) = tail;

    return pivot;
}

Pesanan* quickSort(Pesanan* low, Pesanan* high) {
    if (!low || low == high) return low;

    Pesanan* newLow = nullptr;
    Pesanan* newHigh = nullptr;
    Pesanan* pivot = partition(low, high, &newLow, &newHigh);

    if (newLow != pivot) {
        Pesanan* temp = newLow;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newLow = quickSort(newLow, temp);
        temp = getLast(newLow);
        temp->next = pivot;
    }

    pivot->next = quickSort(pivot->next, newHigh);
    return newLow;
}

void sortDescending() {
    if (head == nullptr || head->next == nullptr) {
        std::cout << "Pesanan sudah terurut." << std::endl;
        return;
    }
    head = quickSort(head, getLast(head));
    std::cout << "Pesanan berhasil diurutkan secara descending (berdasarkan ID)!" << std::endl;
}

int main() {
    int pilihan;
    do {
        std::cout << "\nMenu Sistem Manajemen Jasa Titip Gacoan:\n";
        std::cout << "1. Tambah Pesanan (Stack & Queue)" << std::endl;
        std::cout << "2. Tampilkan Pesanan" << std::endl;
        std::cout << "3. Ubah Status Pesanan" << std::endl;
        std::cout << "4. Hapus Pesanan (Queue - FIFO)" << std::endl;
        std::cout << "5. Hapus Pesanan (Stack - LIFO)" << std::endl;
        std::cout << "6. Urutkan Pesanan Ascending (Merge Sort)" << std::endl;
        std::cout << "7. Urutkan Pesanan Descending (Quick Sort)" << std::endl;
        std::cout << "8. Keluar" << std::endl;
        std::cout << "Pilih opsi (1/2/3/4/5/6/7/8):  ";
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
                hapusPesananQueue();
                break;
            case 5:
                hapusPesananStack();
                break;
            case 6:
                sortAscending();
                break;
            case 7:
                sortDescending();
                break;
            case 8:
                std::cout << "Terima kasih telah menggunakan program ini!" << std::endl;
                    break;
            default:
                std::cout << "Pilihan tidak valid!" << std::endl;
        }
    } while (pilihan != 8);

    return 0;
}
