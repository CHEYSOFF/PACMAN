#pragma once
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

#include "../variables.h"
#include "game/player.h"
#include "game/door.h"
#include "../screen.h"
#include "game/monsters.h"
#include "game/cherry.h"

using namespace std;

void threads_game(){

    thread cha(character);
    thread inp(input_key);
    thread door(door_time);
    thread screen(scr_upd_tim);
    thread mon(mon_thr);
    thread cherry(cherry_spawn);

    screen.join();
    cherry.detach();
    door.detach();
    cha.detach();
    inp.detach();
    mon.detach();

}

void var_reset(){
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
    energAct=0;
    gam.i=17;
    gam.j=13;
    curtime=0;
    gameContinue=1;
    fi_mon=u;
    se_mon=u;
    death=0;
    arr[gam.i][gam.j]=0;
    for( int i=0; i<mo_co+1; i++ ){
        monplaced[i]=0;
    }

    for(int i=0;i<he;i++){
        for(int j=0;j<wi;j++){
            if(arr[i][j]==5) arr[i][j]=0;
        }
    }

    return;

}

