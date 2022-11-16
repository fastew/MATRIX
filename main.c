#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> 
typedef enum { on, off }ON_OFF;
typedef struct signal{
    int x,y,speed;
    ON_OFF on;
    char num;
}signal;
void makesign();
void gotoxy(int x,int y);
void raise();
void draw();
void reset();
void CursorView();

signal sig[100];
int tim;
int main() {
    CursorView();
    system("mode con cols=110 lines=25");
    reset();

    for (tim = 0;; tim++) {
        if (tim % 10 == 0) {
            makesign();
        }

        draw();
        raise();
        Sleep(50);

    }
    
}


void makesign() {
    for (int i = 0; i < 100; i++) {
        if (sig[i].on == off) {
            sig[i].on = on;
            sig[i].x = rand() % 80;
            sig[i].y = 0;
            sig[i].num = rand() % 95 + 32;
            sig[i].speed = rand() % 20 +1;
            break;
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 100; i++) {
            if (sig[i].on == off) {
                sig[i].on = on;
                sig[i].x = rand() % 80;
                sig[i].y = 0;
                sig[i].num = ' ';
                sig[i].speed = 1;
                break;


            }
        }
    }

    
}
void reset() {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 100; i++) {
        sig[i].on = off;
    }
}

void raise() {
    for (int i = 0; i < 100; i++) {
        if (sig[i].on == on && sig[i].y == 23) {
            sig[i].on = off;
        }

        if (sig[i].on == on && tim % sig[i].speed == 0) {
            if (rand() % 24 == 0) {
                sig[i].num = ' ';
            }    
            if (sig[i].num != ' ') {
                sig[i].num = rand() % 95 + 32;
            }
            sig[i].y++;
        }
        
    }

}

void draw() {
    for (int i = 0; i < 100; i++) {
        if (sig[i].on == on) {
            gotoxy(sig[i].x, sig[i].y);
            printf("%c", sig[i].num);
           
        }

    }
}

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}