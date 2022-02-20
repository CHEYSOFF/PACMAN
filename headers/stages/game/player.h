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
        
    
        switch(getch()){
                // case 246:
                // case 214:
                case 87:
                case 119:
                    if(arr[gam.i-1][gam.j]!=1){
                        dir=0;
                    }
                    
                    break;
                // case 219:
                // case 251:
                case 83:
                case 115:
                    if(arr[gam.i+1][gam.j]!=1){
                        dir=2;
                    }
                    
                    break;
                // case 212:
                // case 244:
                // case 192:
                case 65:
                case 97:
                    if( (gam.j>=0 && arr[gam.i][gam.j-1]!=1) || (gam.i==14 && gam.j==0 )  ){
                        dir=3;
                    }
                    
                    break;
                // case 194:
                // case 226:
                case 68:
                case 100:
                    if( (gam.j+1<wi && arr[gam.i][gam.j+1]!=1) || (gam.i==14 && gam.j==wi-1) ){
                        dir=1;
                    }
                    
                    break;
                case 27:
                    gameContinue=0;
                    death=-1;
                    break;
            }


    }
}

void pacmandeath(){
    if(se_mon==gam || fi_mon==gam){

        if(energAct==0){
            gameContinue=0;
            death=1;

            
            return;  
        }
        else{

            if(se_mon==gam){
                se_mon=se_mon_start;
                addScore(gam);
            }
            else if(fi_mon==gam){
                fi_mon=fi_mon_start;
                addScore(gam);
            }

        }
        
    }
}

bool cango(point p){
    if( (arr[p.i][p.j]!=1 && !(p.i==12 && p.j>=11 && p.j<=16) ) || (p.i==14 && ( p.j==-1 || p.j==wi )  ) ) return true;
    return false;
}

void goup(){
    
    point p=gam;
    p.i--;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if( cango(p) ){
        addScore(p);
        energizer(p);
        gam=p;
        pacmandeath();
        return;
    }


    
}

void godown(){
    point p=gam;
    p.i++;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if(cango(p) ){
        addScore(p);
        energizer(p);
        gam=p;
        pacmandeath(); 
        return;
    }

}

void goleft(){
    point p=gam;
    p.j--;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if(cango( p ) ){
        addScore(p);
        energizer(p);
        gam=p;
        pacmandeath();
        return;
    }
    


    
}

void goright(){

    point p=gam;
    p.j++;

    p.i+=he;
    p.j+=wi;

    p.i%=he;
    p.j%=wi;

    if(cango( p ) ){
        addScore(p);
        energizer(p);
        gam=p;
        pacmandeath();
        return;


    }

    


    
}

void character(){
    dir=1; //0 вверх | 1 вправо | 2 вниз | 3 влево

    while (gameContinue){
        
        switch(dir){
            case 0:
                goup();
                break;
            case 2:
                godown();
                break;
            case 3:
                goleft();
                break;
            case 1:
                goright();
                break;
        }


        Sleep(wait_gamer);
    }
    return;
}