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

#include "../../score.h"
#include "../../point.h"
#include "../../variables.h"
#include "energizer.h"

using namespace std;

void input_key(){
    while(gameContinue){
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
        //0 вверх | 1 вправо | 2 вниз | 3 влево
        switch(getch()){
                
                case 72: // стрелочки 
                case 87: 
                case 119:
                    tmpdir=0;
                    break;

                
                case 77:
                case 68:
                case 100:
                    tmpdir=1;
                    break;

                
                case 80:
                case 83:
                case 115:
                    tmpdir=2;
                    break;

                
                case 75:
                case 65:
                case 97:
                    tmpdir=3;
                    break;
                
                case 27:
                    gameContinue=0;
                    death=-1;
                    break;
            }


    }
}

void pacmandeath(){
    if(se_mon==gam || fi_mon==gam || th_mon==gam || fo_mon==gam){

        if(energAct==0){
            gameContinue=0;
            death=1;

            
            return;  
        }
        else{
            addScore(gam);
            if(se_mon==gam) se_mon=se_mon_start;
            else if(fi_mon==gam) fi_mon=fi_mon_start;
            else if(th_mon==gam) th_mon=th_mon_start;
            else if(fo_mon==gam) fo_mon=fo_mon_start;
            
        }
        
    }
}

bool cango(point p){
    if( (arr[p.i][p.j]!=1 && !(p.i==12 && p.j>=11 && p.j<=16) ) || (p.i==14 && ( p.j==-1 || p.j==wi )  ) ) return true;
    return false;
}

bool playerMove(point p){
    if( cango(p) ){
        addScore(p);
        energizer(p);
        gam=p;
        pacmandeath();
        return true;
    }
    else return false;

}

//0 вверх | 1 вправо | 2 вниз | 3 влево
point pointSide(point tm, int side){
    point p=tm;
    p=p+hod[side];

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;
    return p;
}

bool goDir(int side){
    point p=pointSide(gam, side);
    return playerMove(p);
}

void character(){
    dir=1; //0 вверх | 1 вправо | 2 вниз | 3 влево
    tmpdir=1;
    while (gameContinue){
        if(goDir(tmpdir)){
            dir=tmpdir;
        }
        else goDir(dir);
        Sleep(wait_gamer);
    }
    return;
}