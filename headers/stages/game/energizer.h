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

#include "../../point.h"
#include "../../variables.h"

using namespace std;

void energizer_timer(){
    energAct=1;
    energTime=energizerSleep;
    while(energTime>0){
        if(gh_white) gh_white=0;
        else gh_white=1;
        // gh_white+=1;
        // gh_white%=2;
        energTime-=morg;
        if(energTime<=3*energizerSleep/10){
            energCol++;
            energCol=energCol%2;
        }
        Sleep(morg);
    }

    // Sleep(energizerSleep*7/10);
    // for(int i=0;i<3*energizerSleep/10/morg; i++){
    //     energCol++;
    //     energCol=energCol%2;
    //     Sleep(morg);
    // }
    energAct=0;
    gh_white=0;
}

void energizer( point p ){

    if( arr[p.i][p.j]!=3 ) return;

    arr[p.i][p.j]=0;
    
    gam=p;
    energCol=0;
    if(energAct==1){
        energTime=energizerSleep;
        
    }
    else{
        // cout<<"asgasgsag";
        thread nrg(energizer_timer);
        nrg.detach();
    }
    
    
    return;

}