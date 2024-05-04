#include "Proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Fonksiyon implementasyonları

struct Ders dersOlustur(const char* dersAdi, unsigned short int kredi, unsigned short int puan) {
    struct Ders yeniDers;
    yeniDers.dersAdi = strdup(dersAdi);
    yeniDers.kredi = kredi;
    yeniDers.puan = puan;
    return yeniDers;
}

struct Ogrenci ogrenciOlustur(const char* ogrAdi, const char* ogrSoyAdi, const char* bolumu, float ortalama, struct Ders* aldigiDersler) {
    struct Ogrenci yeniOgrenci;

    yeniOgrenci.ogrAdi = (char*)malloc(strlen(ogrAdi) + 1);
    strcpy(yeniOgrenci.ogrAdi, ogrAdi);

    yeniOgrenci.ogrSoyAdi = (char*)malloc(strlen(ogrSoyAdi) + 1);
    strcpy(yeniOgrenci.ogrSoyAdi, ogrSoyAdi);

    yeniOgrenci.bolumu = (char*)malloc(strlen(bolumu) + 1);
    strcpy(yeniOgrenci.bolumu, bolumu);

    yeniOgrenci.ortalama = ortalama;
    yeniOgrenci.aldigiDersler = aldigiDersler;

    return yeniOgrenci;
}

void ogrenciYazdir(struct Ogrenci ogrenci) {
    printf("Ad: %s, Soyad: %s, Bolum: %s, Ortalama: %.2f\n", ogrenci.ogrAdi, ogrenci.ogrSoyAdi, ogrenci.bolumu, ogrenci.ortalama);

    for (int i = 0; i < 10; i++) {
        if (ogrenci.aldigiDersler[i].dersAdi != NULL) {
            printf("  Ders Adi: %s, Kredi: %hu, Puan: %hu\n", ogrenci.aldigiDersler[i].dersAdi, ogrenci.aldigiDersler[i].kredi, ogrenci.aldigiDersler[i].puan);
        }
    }    
}

void ogrenciDizisiniYazdir(struct Ogrenci* ogrenciDizisi, int ogrenciSayisi) {
    for (int i = 0; i < ogrenciSayisi; i++) {
        ogrenciYazdir(ogrenciDizisi[i]);
    }
}

float dersinAritmetikOrtalamasi(struct Ders* dersler, int dersSayisi, const char* hedefDersAdi) {
    float toplamPuan = 0;
    int toplamKredi = 0;

    for (int i = 0; i < dersSayisi; i++) {
        if (strcmp(dersler[i].dersAdi, hedefDersAdi) == 0) {
            toplamPuan += dersler[i].puan * dersler[i].kredi;
            toplamKredi += dersler[i].kredi;
        }
    }

    if (toplamKredi > 0) {
        return toplamPuan / toplamKredi;
    } else {
        return 0; // Öğrencinin hiç dersi yoksa 0 dönecek
    }
}

float dersinStandartSapmasi(struct Ders* dersler, int dersSayisi, const char* hedefDersAdi) {
    float ortalama = dersinAritmetikOrtalamasi(dersler, dersSayisi, hedefDersAdi);
    float toplamKareFark = 0;
    int toplamKredi = 0;

    for (int i = 0; i < dersSayisi; i++) {
        if (strcmp(dersler[i].dersAdi, hedefDersAdi) == 0) {
            toplamKareFark += pow(dersler[i].puan - ortalama, 2) * dersler[i].kredi;
            toplamKredi += dersler[i].kredi;
        }
    }

    if (toplamKredi > 0) {
        return sqrt(toplamKareFark / toplamKredi);
    } else {
        return 0; // Eğer hiç ders bulunamazsa standard deviation sıfır olarak dönecek
    }
}

float kovaryansHesapla(struct Ders* ders1, struct Ders* ders2, int ogrenciSayisi) {
    float toplamUzaklik = 0;

    for (int i = 0; i < ogrenciSayisi; i++) {
        toplamUzaklik += (ders1[i].puan - dersinAritmetikOrtalamasi(ders1, ogrenciSayisi, ders1[i].dersAdi)) *
                         (ders2[i].puan - dersinAritmetikOrtalamasi(ders2, ogrenciSayisi, ders2[i].dersAdi)) *
                         ders1[i].kredi;
    }

    return toplamUzaklik / ogrenciSayisi;
}

void yuksekNotAlanOgrencileriListele(struct Ogrenci* ogrenciDizisi, int ogrenciSayisi, const char* hedefDersAdi) {
    for (int i = 0; i < ogrenciSayisi; i++) {
        for (int j = 0; j < 10; j++) {
            if (ogrenciDizisi[i].aldigiDersler[j].dersAdi != NULL &&
                strcmp(ogrenciDizisi[i].aldigiDersler[j].dersAdi, hedefDersAdi) == 0 &&
                ogrenciDizisi[i].aldigiDersler[j].puan > dersinAritmetikOrtalamasi(ogrenciDizisi[i].aldigiDersler, 10, hedefDersAdi)) {
                ogrenciYazdir(ogrenciDizisi[i]);
                break;  // Aynı öğrenciyi tekrar yazdırmamak için
            }
        }
    }
}

void dosyayaYaz(Ogrenci* ogrenciDizisi, int ogrenciSayisi, FILE* file) {
    if (file == NULL) {
        fprintf(stderr, "Dosya acilamadi: %p\n", (void*)file);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ogrenciSayisi; i++) {
        fprintf(file, "%s %s %s %.2f", ogrenciDizisi[i].ogrAdi, ogrenciDizisi[i].ogrSoyAdi, ogrenciDizisi[i].bolumu, ogrenciDizisi[i].ortalama);

        for (int j = 0; j < 10; j++) {
            if (ogrenciDizisi[i].aldigiDersler[j].dersAdi != NULL) {
                fprintf(file, " %s %hu %hu", ogrenciDizisi[i].aldigiDersler[j].dersAdi, ogrenciDizisi[i].aldigiDersler[j].kredi, ogrenciDizisi[i].aldigiDersler[j].puan);
            }
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void dosyadanOku(Ogrenci** ogrenciDizisi, int* ogrenciSayisi, FILE* file) {
    if (file == NULL) {
        fprintf(stderr, "Dosya acilamadi: %p\n", (void*)file);
        exit(EXIT_FAILURE);
    }

    int kapasite = 5;
    *ogrenciDizisi = (struct Ogrenci*)malloc(kapasite * sizeof(struct Ogrenci));
    *ogrenciSayisi = 0;

    while (fscanf(file, "%s %s %s %f", (*ogrenciDizisi)[*ogrenciSayisi].ogrAdi, (*ogrenciDizisi)[*ogrenciSayisi].ogrSoyAdi,
                  (*ogrenciDizisi)[*ogrenciSayisi].bolumu, &(*ogrenciDizisi)[*ogrenciSayisi].ortalama) == 4) {

        (*ogrenciDizisi)[*ogrenciSayisi].aldigiDersler = (struct Ders*)malloc(10 * sizeof(struct Ders));

        for (int i = 0; i < 10; i++) {
            if (fscanf(file, " %s %hu %hu", (*ogrenciDizisi)[*ogrenciSayisi].aldigiDersler[i].dersAdi,
                       &(*ogrenciDizisi)[*ogrenciSayisi].aldigiDersler[i].kredi, &(*ogrenciDizisi)[*ogrenciSayisi].aldigiDersler[i].puan) != 3) {
                break;
            }
        }

        (*ogrenciSayisi)++;

        if (*ogrenciSayisi == kapasite) {
            kapasite *= 2;
            *ogrenciDizisi = (struct Ogrenci*)realloc(*ogrenciDizisi, kapasite * sizeof(struct Ogrenci));
        }
    }
}
