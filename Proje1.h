#ifndef PROJE1_H
#define PROJE1_H
#include <stdio.h>

typedef struct  Ders{
    char* dersAd[256];
    unsigned short int kredi;
    unsigned short int puan;
}Ders;


typedef struct Ogrenci {
    char* ogrAdi[256];
    char* ogrSoyAdi[256];
    char* bolumu[256];
    float ortalama;
    Ders* aldigiDersler[10];
} Ogrenci;

// Fonksiyon prototipleri
struct Ders dersOlustur(const char* dersAdi, unsigned short int kredi, unsigned short int puan);
struct Ogrenci ogrenciOlustur(const char* ogrAdi, const char* ogrSoyAdi, const char* bolumu, float ortalama, struct Ders* aldigiDersler);
void ogrenciYazdir(struct Ogrenci ogrenci);
void ogrenciDizisiniYazdir(struct Ogrenci* ogrenciDizisi, int ogrenciSayisi);
float dersinAritmetikOrtalamasi(struct Ders* dersler, int dersSayisi, const char* hedefDersAdi);
float dersinStandartSapmasi(struct Ders* dersler, int dersSayisi, const char* hedefDersAdi);
float kovaryansHesapla(struct Ders* ders1, struct Ders* ders2, int ogrenciSayisi);
void yuksekNotAlanOgrencileriListele(struct Ogrenci* ogrenciDizisi, int ogrenciSayisi, const char* hedefDersAdi);
void dosyayaYaz(Ogrenci* ogrenciDizisi, int ogrenciSayisi, FILE* file);
void dosyadanOku(Ogrenci** ogrenciDizisi, int* ogrenciSayisi, FILE* file);

#endif
