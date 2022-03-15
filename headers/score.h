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

#include "variables.h"
// #include "stages/game/monsters.h"

using namespace std;

void addScore(point p){
    if(arr[p.i][p.j]==2){
        curscore+=1;
        arr[p.i][p.j]=0;
        onesleft--;
        if(onesleft<=0){
            
            onesleft=points_at_all;
            if(cherryInd!=u) onesleft--;
            for(int i=0;i<he;i++){
                for(int j=0;j<wi;j++){
                    if(!(i==12 && j>=11 && j<=16) ) arr[i][j]=ones[i][j];
                }
            }

            round_num++;
            mon_speed_change();
        }
    }
    else if(arr[p.i][p.j]==5){
        curscore+=cherryCost;
        arr[p.i][p.j]=0;
    }
    else if(p==se_mon || p==fi_mon || p==th_mon || p==fo_mon){
        curscore+=20;
    }
}