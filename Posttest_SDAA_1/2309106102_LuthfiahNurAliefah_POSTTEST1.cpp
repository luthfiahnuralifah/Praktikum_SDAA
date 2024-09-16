#include <iostream>
using namespace std;

int hitung_nilai_pada_pascals_triangle(int baris, int kolom) {
    if (kolom == 0 || kolom == baris) {
        return 1;
    } else {
        return hitung_nilai_pada_pascals_triangle(baris - 1, kolom - 1) + hitung_nilai_pada_pascals_triangle(baris - 1, kolom);
    }
}

void cetak_segitiga_pascals_triangle(int jumlah_baris) {
    for (int baris = 0; baris < jumlah_baris; baris++) {
        for (int kolom = 0; kolom <= baris; kolom++) {
            cout << hitung_nilai_pada_pascals_triangle(baris, kolom) << " ";
        }
        cout << endl;  
    }
}

int main() {
    int jumlah_baris = 3;  
    cetak_segitiga_pascals_triangle(jumlah_baris);
    
    return 0;
}