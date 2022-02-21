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

using namespace std;


int main(){
    
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
    // // скрывает курсор
    // void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
    // CONSOLE_CURSOR_INFO structCursorInfo;
    // GetConsoleCursorInfo(handle,&structCursorInfo);
    // structCursorInfo.bVisible = FALSE;
    // SetConsoleCursorInfo( handle, &structCursorInfo );
    // //

    // printf("\e[?25l");





    
    


    srand(time(NULL));
    
    u.i=-1;
    u.j=-1;
    se_mon_start.i=14;
    se_mon_start.j=11;
    fi_mon_start.i=14;
    fi_mon_start.j=12;
    th_mon_start.i=14;
    th_mon_start.j=13;

    hideCursor();
    hideScrollBar();
    setWindowSize();
    
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