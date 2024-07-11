#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;

#define WIDTH 50 // ���� ����
#define HEIGHT 40 // ���� ����
#define SLEEP_TIME 100 // �ǵ��� ����
#define width_ 4 // ���η� ��ĭ �ٱ�
#define height_ 5// ���η� ��ĭ �ٱ�

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void textcolor(int text, int bg) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, text | (bg << 4));
}

// ���� ǥ��
static void draw_wire(int I) {
    for (int y = 0; y <= HEIGHT + height_ + 1; ++y) {
        for (int x = 0; x <= WIDTH + width_ + 1; ++x) {
            if (y == height_ && x >= width_ && x <= WIDTH) {
                gotoxy(x, y);
                textcolor(7, 7);
                printf(" ");
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            }
            else if (y == HEIGHT / 2 && x >= width_ && x <= WIDTH) {
                gotoxy(x, y);
                textcolor(7, 7);
                printf(" ");
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            }
            else if (x == width_ && y < HEIGHT / 2 && y > height_) {
                gotoxy(x, y);
                textcolor(7, 7);
                printf("  ");
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            }
            else if (x == WIDTH && y <  HEIGHT / 2 && y > height_) {
                gotoxy(x, y);
                textcolor(7, 7);
                printf("  ");
                textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            }
            else {
                gotoxy(x, y);
                printf(" ");
            }
        }

    }
}

static void move_electrons(int elec_amount, int I, int NUM_ELECTRONS_X, int NUM_ELECTRONS_Y) {
    // ������ ���� ����Ʈ
    int* electron_positions1 = (int*)malloc(NUM_ELECTRONS_X * sizeof(int));
    int* electron_positions2 = (int*)malloc(NUM_ELECTRONS_X * sizeof(int));

    // ������ ���� ����Ʈ
    int* electron_positions3 = (int*)malloc(NUM_ELECTRONS_Y * sizeof(int));
    int* electron_positions4 = (int*)malloc(NUM_ELECTRONS_Y * sizeof(int));

    // ������ ���� ����
    for (int i = 0; i < NUM_ELECTRONS_X; ++i) {
        electron_positions1[i] = WIDTH - (i * ((WIDTH - width_) / NUM_ELECTRONS_X));
    }

    for (int i = 0; i < NUM_ELECTRONS_X; ++i) {
        electron_positions2[i] = i * ((WIDTH - width_) / NUM_ELECTRONS_X) + width_;
    }

    // ������ ���� ���� 
    for (int i = 0; i < NUM_ELECTRONS_Y; ++i) {
        electron_positions3[i] = i * ((HEIGHT / 2 - height_) / NUM_ELECTRONS_Y) + height_;
    }

    for (int i = 0; i < NUM_ELECTRONS_Y; ++i) {
        electron_positions4[i] = HEIGHT / 2 - (i * ((HEIGHT / 2 - height_) / NUM_ELECTRONS_Y));
    }

    while (1) {

        // ������ ǥ��
        gotoxy(0, HEIGHT / 2 + 5);
        printf("������: %d", I);

        // ������ ���� ����
        for (int i = 0; i < NUM_ELECTRONS_X; ++i) {
            gotoxy(electron_positions1[i], height_);
            if (NUM_ELECTRONS_X + NUM_ELECTRONS_Y < 10) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
            printf("��");
        }
        for (int i = 0; i < NUM_ELECTRONS_X; ++i) {
            gotoxy(electron_positions2[i], HEIGHT / 2);
            printf("��");
        }

        // ������ ���� ����
        for (int i = 0; i < NUM_ELECTRONS_Y; ++i) {
            gotoxy(width_, electron_positions3[i]);
            printf("�� ");
        }
        for (int i = 0; i < NUM_ELECTRONS_Y; ++i) {
            gotoxy(WIDTH, electron_positions4[i]);
            printf("�� ");
        }

        Sleep(SLEEP_TIME);

        // ������ ���� �̵�
        for (int i = 0; i < NUM_ELECTRONS_X; ++i) {
            gotoxy(electron_positions1[i], height_);
            textcolor(7, 7);
            printf(" ");
            textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            if (I < 50) electron_positions1[i]--;
            else electron_positions1[i] -= 3;
            if (electron_positions1[i] < width_) {
                electron_positions1[i] = WIDTH;
            }
        }

        for (int i = 0; i < NUM_ELECTRONS_X; ++i) {
            gotoxy(electron_positions2[i], HEIGHT / 2);
            textcolor(7, 7);
            printf(" ");
            textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            if (I < 50) electron_positions2[i]++;
            else electron_positions2[i] += 3;
            if (electron_positions2[i] > WIDTH) {
                electron_positions2[i] = width_;
            }
        }

        // ������ ���� �̵�
        for (int i = 0; i < NUM_ELECTRONS_Y; ++i) {
            gotoxy(width_, electron_positions3[i]);
            textcolor(7, 7);
            printf("  ");
            textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);
            if (I < 50) electron_positions3[i]++;
            else electron_positions3[i] += 3;
            if (electron_positions3[i] > HEIGHT / 2 - 1) {
                electron_positions3[i] = height_ + 1;
            }
        }

        for (int i = 0; i < NUM_ELECTRONS_Y; ++i) {
            gotoxy(WIDTH, electron_positions4[i]);
            textcolor(7, 7);
            printf("  ");
            textcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE, 0);

            if (I < 50) electron_positions4[i]--;
            else electron_positions4[i] -= 3;

            if (electron_positions4[i] < height_ + 1) {
                electron_positions4[i] = HEIGHT / 2 - 1;
            }
        }
    }
}

int main() {
    int elec_amount = 10; // ������
    int I = 30; // ���� ����
    int NUM_ELECTRONS_X = 4;
    int NUM_ELECTRONS_Y = 2;

    system("cls");
    draw_wire(I); // ���� ǥ��
    move_electrons(elec_amount, I, NUM_ELECTRONS_X, NUM_ELECTRONS_Y); // ���� �̵�
    return 0;
}