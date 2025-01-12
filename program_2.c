#include <stdio.h>
#include <stdlib.h>

int main() {
    int M, N; // Görüntü matrisi boyutları
    int k;    // Filtre matrisi 
    int i, j, x, y; //Ekstra Değişkenleri

    // 1) Görüntü boyutlarını al
    printf("Goruntu matrisi boyutlarini giriniz (M N): ");
    scanf("%d %d", &M, &N);

    // Görüntü matrisi için yer ayır
    int **G = (int **)malloc(M * sizeof(int *));
    for (i = 0; i < M; i++) {
        G[i] = (int *)malloc(N * sizeof(int));
    }

    // 2) Görüntü matrisini kullanıcıdan oku
    printf("Goruntu matrisi elemanlarini giriniz:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    // 3) Filtre boyutunu al (k x k)
    printf("Filtre boyutu k giriniz: ");
    scanf("%d", &k);

    // Filtre matrisi için yer ayır
    int **F = (int **)malloc(k * sizeof(int *));
    for (i = 0; i < k; i++) {
        F[i] = (int *)malloc(k * sizeof(int));
    }

    // 4) Filtre matrisini kullanıcıdan oku
    printf("Filtre matrisi elemanlarini giriniz:\n");
    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            scanf("%d", &F[i][j]);
        }
    }

    // 5) Filtre matrisinin toplamını bul (bölme işlemi için)
    int filtre_toplam = 0;
    for (i = 0; i < k; i++) {
        for (j = 0; j < k; j++) {
            filtre_toplam += F[i][j];
        }
    }

    // Eğer filtre_toplam 0 ise, 1 yap
    if (filtre_toplam == 0) {
        filtre_toplam = 1;
    }

    // 6) Sonuç matrisinin boyutu: (M - k + 1) x (N - k + 1)
    int R_satir = M - k + 1;
    int R_sutun = N - k + 1;
    int **R = (int **)malloc(R_satir * sizeof(int *));
    for (i = 0; i < R_satir; i++) {
        R[i] = (int *)malloc(R_sutun * sizeof(int));
    }

    // 7) Konvolüsyon hesaplaması
    for (i = 0; i < R_satir; i++) {
        for (j = 0; j < R_sutun; j++) {
            int toplam = 0;
            // k x k'lik pencere
            for (x = 0; x < k; x++) {
                for (y = 0; y < k; y++) {
                    toplam += G[i + x][j + y] * F[x][y];
                }
            }
            // Bölme işlemi
            R[i][j] = toplam / filtre_toplam;
        }
    }

    // 8) Sonuç matrisini ekrana yaz
    printf("\nSonuc matrisi R:\n");
    for (i = 0; i < R_satir; i++) {
        for (j = 0; j < R_sutun; j++) {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }

    // Belleği temizle
    for (i = 0; i < M; i++) {
        free(G[i]);
    }
    free(G);

    for (i = 0; i < k; i++) {
        free(F[i]);
    }
    free(F);

    for (i = 0; i < R_satir; i++) {
        free(R[i]);
    }
    free(R);

    return 0;
}