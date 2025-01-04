#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#define CLEAR "cls" // cls untuk Windows
#else
#define CLEAR "clear" // clear untuk sistem MacOS/Linux/Unix.
#endif

int generate_question() {
    int num1 = rand() % 10 + 1;
    int num2 = rand() % 10 + 1;
    int operation = rand() % 4 + 1; // Randomize operation untuk mode gabungan (semua operasi)
    int correct_answer;

    switch (operation) {
        case 1:
            correct_answer = num1 + num2;
            printf("%d + %d = ?\n", num1, num2);
            break;
        case 2:
            correct_answer = num1 - num2;
            printf("%d - %d = ?\n", num1, num2);
            break;
        case 3:
            num1 = num1 * num2;
            correct_answer = num1 / num2;
            printf("%d / %d = ?\n", num1, num2);
            break;
        case 4:
            correct_answer = num1 * num2;
            printf("%d * %d = ?\n", num1, num2);
            break;
    }
    return correct_answer;
}

void quiz(const char* player_name, int* correct_count, double* total_time) {
    *correct_count = 0;
    *total_time = 0;
    clock_t start, end;
	
	int i;
    for (i = 0; i < 10; i++) { // 10 pertanyaan per kuis
        system(CLEAR);
        printf("Giliran %s! Soal ke-%d:\n", player_name, i + 1);

        int correct_answer = generate_question();

        int user_answer;
        start = clock();
        printf("Jawaban Anda: ");
        scanf("%d", &user_answer);
        end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        *total_time += time_taken;

        if (user_answer == correct_answer) {
            printf("Benar! Waktu: %.2f detik\n", time_taken);
            (*correct_count)++;
        } else {
            printf("Salah! Jawaban yang benar adalah %d. Waktu: %.2f detik\n", correct_answer, time_taken);
        }

        printf("Tekan Enter untuk melanjutkan...");
        getchar();
        getchar(); // Pause untuk user melihat hasil
    }
}

int main() {
    srand(time(NULL));

    char player1[50], player2[50];
    printf("Masukkan nama Player 1: ");
    scanf("%s", player1);
    printf("Masukkan nama Player 2: ");
    scanf("%s", player2);

    while (1) {
        int choice;
        system(CLEAR);
        printf("Pilih jenis quiz:\n");
        printf("1. Gabungan (semua operasi)\n");
        printf("2. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int correct1, correct2;
            double time1, time2;

            quiz(player1, &correct1, &time1);
            quiz(player2, &correct2, &time2);

            system(CLEAR);
            printf("Hasil Akhir:\n");
            printf("%s: %d benar, total waktu %.2f detik\n", player1, correct1, time1);
            printf("%s: %d benar, total waktu %.2f detik\n", player2, correct2, time2);

            if (correct1 > correct2 || (correct1 == correct2 && time1 < time2)) {
                printf("Pemenang: %s!\n", player1);
            } else if (correct2 > correct1 || (correct2 == correct1 && time2 < time1)) {
                printf("Pemenang: %s!\n", player2);
            } else {
                printf("Hasil Seri!\n");
            }

            printf("Tekan Enter untuk kembali ke menu utama...");
            getchar();
            getchar();
        } else if (choice == 2) {
            printf("Terima kasih telah bermain!\n");
            break;
        } else {
            printf("Pilihan tidak valid, coba lagi.\n");
            getchar();
            getchar();
        }
    }

    return 0;
}

