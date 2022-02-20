#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <Winuser.h>
#include <time.h>
#include <thread>
#include <string>
#include <queue>
#include <algorithm>
#include <atomic>
#include <chrono>
#include <random>
#include <fstream>

#include "headers/stages/game/door.h"
#include "headers/point.h"
#include "headers/variables.h"
#include "headers/stages/game/cherry.h"
#include "headers/score.h"
#include "headers/stages/game/player.h"
#include "headers/stages/game/monsters.h"
#include "headers/screen.h"
#include "headers/leaderboard.h"
#include "headers/stages/game_start.h"
#include "headers/stages/game_end.h"
#include "headers/stages/menu.h"
#include "headers/stages/game_transition.h"

// void hidecursor()
// {
//    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//    CONSOLE_CURSOR_INFO info;
//    info.dwSize = 100;
//    info.bVisible = FALSE;
//    SetConsoleCursorInfo(consoleHandle, &info);
// }

using namespace std;

int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    // скрывает курсор
    void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(handle,&structCursorInfo);
    structCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo( handle, &structCursorInfo );
    //

    // hidecursor();
    


    srand(time(NULL));
    
    u.i=-1;
    u.j=-1;

    // убирает скролл бар
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;
    short scrBufferWidth = scrBufferInfo.dwSize.X;        
    short scrBufferHeight = scrBufferInfo.dwSize.Y;        
    COORD newSize;
    newSize.X = scrBufferWidth;
    newSize.Y = winHeight;
    SetConsoleScreenBufferSize(hOut, newSize);
    //

    // задает размер окна
    HWND hwnd = GetConsoleWindow();
    ShowScrollBar(hwnd, SB_BOTH, 0);
    RECT ConsoleRect;
    GetWindowRect(hwnd, &ConsoleRect);
    MoveWindow(hwnd, ConsoleRect.left, ConsoleRect.top, win_wi, win_he, TRUE);
    //
    
    var_reset();
    start_menu();
    
    while(lives!=0){
        var_reset();
        transition();
        var_reset();

        system("cls");
        cout<<flush;
        updateScreen();
        
        
        
        
        threads_game();

        if(death==-1){
            break;
        }

        lives--;

        for(int i=0;i<5;i++) cout<<UP;
        cout<<'\n';
        cout<<'\n';
        
        string yd="YOU DIED";
        cout<<GRA<<mar_left;
        cout<<RED;
        cen_out(yd);
        cout<<"     ";//чтобы закрыть предыдущий текст :(
        cout<<'\n';
        cout<<GRA<<mar_left;
        cout<<RED;
        string ll="LIVES LEFT: "+to_string(lives);
        cen_out(ll);
        cout<<'\n';
        cout<<flush;
        Sleep(1000);

    }
    system("cls");
    leave();
    
    return 0;

    



    
    /*
      119-W
      97-A
      115-S
      100-D
      27-ESC
    */

    


    
    return 0;


}