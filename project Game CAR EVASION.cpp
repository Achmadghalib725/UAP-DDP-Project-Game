//Kelompok 6
//Project Game
//Anggota : 
//Achmad Ghalib Hafaizh 
//S Agung setiawan
//Maura Helena
//Citra Fardiani 

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<time.h>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define ROAD_WIDTH 2

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int enemyY[3];
int enemyX[3];
int enemyFlag[3];
char car[4][4] = {' ', '|', '|', ' ',
                  '0', '-', '-', '0',
                  ' ', '|', '|', ' ',
                  '0', '-', '-', '0'};

int carPos = WIN_WIDTH / 2;
int score = 0;

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = visible;
    cursor.dwSize = size;
    SetConsoleCursorInfo(console, &cursor);
}

void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        for (int j = 0; j < 17; j++) {
            gotoxy(0 + j, i); cout << "�";
            gotoxy(WIN_WIDTH - j, i); cout << "�";
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(SCREEN_WIDTH, i); cout << "�";
    }
}
void drawRoad() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH / 2 - ROAD_WIDTH / 2, i);
        for (int j = 0; j < ROAD_WIDTH; j++) {
            cout << "|";
        }
    }
}
void drawBorderAndRoad() {
    drawBorder();
    drawRoad();
}

void genEnemy(int ind) {
    enemyX[ind] = 17 + rand() % (33);
}

void drawEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        gotoxy(enemyX[ind], enemyY[ind]); cout <<     "0**0";
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << " ** ";
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "0**0";
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << " ** ";
    }
}

void eraseEnemy(int ind) {
    if (enemyFlag[ind] == true) {
        gotoxy(enemyX[ind], enemyY[ind]); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << "    ";
    }
}

void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << car[i][j];
        }
    }
}

void eraseCar() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gotoxy(j + carPos, i + 22); cout << " ";
        }
    }
}

int collision() {
    if (enemyY[0] + 4 >= 23) {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9) {
            return 1;
        }
    }
    return 0;
}

void gameover() {
    system("cls");
    cout << endl;
    cout << "\t\t------------------------" << endl;
    cout << "\t\t------- Game Over ------" << endl;
    cout << "\t\t------------------------" << endl;
    
    cout << "\t\tSkor Anda : " << score << endl; 
    cout << "\t\tPress any key to go back to the menu.";

    getch();
}

void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5); cout << "Score: " << score << endl;
}

void instructions() {
    system("cls");
    cout << "Instruksi";
    cout << "\n-----------------------------------------------------";
    cout << "\n Hindari mobil dengan bergerak ke kanan atau kekiri. ";
    cout << "\n\n Tekan 'a' untuk bergerak ke kiri";
    cout << "\n Tekan 'd' untuk bergerak ke kanan";
    cout << "\n Tekan 'escape' untuk keluar";
    cout << "\n\n Tekan apapun untuk kembali ke menu";
    getch();
}

void play() {
    carPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawRoad();  
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2); cout << "Car Evasion";
    gotoxy(WIN_WIDTH + 6, 4); cout << "-----------";
    gotoxy(WIN_WIDTH + 6, 6); cout << "-----------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "Control ";
    gotoxy(WIN_WIDTH + 7, 13); cout << "-----------";
    gotoxy(WIN_WIDTH + 2, 14); cout << " A Key - Left";
    gotoxy(WIN_WIDTH + 2, 15); cout << " D Key - Right";

    gotoxy(18, 5); cout << "Press any key to start";
    getch();
    gotoxy(18, 5); cout << "                       ";

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if (ch == 'a' || ch == 'A') {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D') {
                if (carPos < 50)
                    carPos += 4;
            }
            if (ch == 27) {
                break;
            }
        }
        drawBorderAndRoad();
        drawRoad(); 
        drawCar();   
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1) {
            gameover();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}



int main() {
    setcursor(0, 0);
    srand(static_cast<unsigned>(time(NULL)));

    do {
        system("cls");
        gotoxy(25, 5); cout << "------------------------------------------------------------------------------ "; 
        gotoxy(25, 6); cout << "|    ######   ##   #####    ###### #      #   ##   ###### # ###### ##    #    | ";
        gotoxy(25, 7); cout << "|    #       #  #  #    #   #       #    #   #  #  #      # #    # # #   #    | ";
        gotoxy(25, 8); cout << "|    #      ###### #####    ######  #    #  ######  ##### # #    # #  #  #    | ";
        gotoxy(25, 9); cout << "|    #      #    # #    #   #        #  #   #    #      # # #    # #   # #    | ";
        gotoxy(25, 10); cout <<"|    ###### #    # #    #   ######    ##    #    # ###### # ###### #    ##    | ";
        gotoxy(25, 11); cout <<"------------------------------------------------------------------------------ ";
        gotoxy(45, 13); cout << "1. Start Game";
        gotoxy(45, 14); cout << "2. Instruksi";
        gotoxy(45, 15); cout << "3. Keluar";
        gotoxy(45, 17); cout << "Pilih Pilihan : ";
        char op = _getche();

        if (op == '1')
            play();
        else if (op == '2')
            instructions();
        else if (op == '3')
            exit(0);

    } while (1);

    return 0;
}

