/*
* @Öğrenci yönetim sistemi
* @description Bu program öğrenci ve ders bilgilerini düzenleyen ve yöneten bir sistemdir.
* @assignment proje1
* @date 10/12/2023
* @author Mohamed Marwan Abdel Wahed - Mail: eng.mervan@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#include "Proje1.h"

int main(int argc, char *argv[]) {
    // Örnek dersler 
    struct Ders ders1 = dersOlustur("Matematik", 3, 85);
    struct Ders ders2 = dersOlustur("Fizik", 4, 75);

    // Örnek öğrenciler 
    struct Ogrenci ogrenci1 = ogrenciOlustur("Ahmet", "Yılmaz", "Bilgisayar Mühendisliği", 90.5, &ders1);
    struct Ogrenci ogrenci2 = ogrenciOlustur("Ayşe", "Kara", "Elektrik Mühendisliği", 88.0, &ders2);

    //  öğrenciler yazdırılıyor
    printf("Ogrenci 1:\n");
    ogrenciYazdir(ogrenci1);

    printf("\nOgrenci 2:\n");
    ogrenciYazdir(ogrenci2);

    // dersin aritmetik ortalaması 
    float matematikOrtalama = dersinAritmetikOrtalamasi(&ders1, 1, "Matematik");
    printf("\nMatematik Dersinin Aritmetik Ortalamasi: %.2f\n", matematikOrtalama);

    // Yüksek not alan öğrenciler listesi
    printf("\nYuksek Not Alan Ogrenciler (Matematik Dersinden): \n");
    yuksekNotAlanOgrencileriListele(&ogrenci1, 1, "Matematik");

    // Dosyaya yazma işlemi
    FILE* file = fopen("file.txt", "w");

   
    if (file == NULL) {
        fprintf(stderr, "Dosya acilamadi.\n");
        return 1;
    }

   
    dosyayaYaz(&ogrenci1, 2, file);

    
    fclose(file);

    // Dosyadan öğrenci bilgileri okunuyor
    struct Ogrenci* okunanOgrenciDizisi;
    int okunanOgrenciSayisi;

    
    FILE* fileRead = fopen("file.txt", "r");


    if (fileRead == NULL) {
        fprintf(stderr, "Dosya acilamadi.\n");
        return 1;
    }

    
    dosyadanOku(&okunanOgrenciDizisi, &okunanOgrenciSayisi, fileRead);

    // Okunan öğrenci bilgileri ekrana yazdırılıyor
    printf("\nDosyadan Okunan Ogrenci Bilgileri: \n");
    ogrenciDizisiniYazdir(okunanOgrenciDizisi, okunanOgrenciSayisi);

    
    // Bellekten ayrılma işlemleri
    free(ders1.dersAdi);
    free(ders2.dersAdi);
    free(ogrenci1.ogrAdi);
    free(ogrenci1.ogrSoyAdi);
    free(ogrenci1.bolumu);
    free(ogrenci2.ogrAdi);
    free(ogrenci2.ogrSoyAdi);
    free(ogrenci2.bolumu);
    free(okunanOgrenciDizisi);

    return 0;
}
