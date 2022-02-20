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







void dopen(){
    for(int j=11;j<=16;j++) arr[12][j]=0;
}

void dclose(){
    for(int j=11;j<=16;j++) arr[12][j]=1;
}

void door_time(){
    while(gameContinue){

        dopen();
        Sleep(dop);
        if(curtime<cycle*3) curtime+=dop;
        
        dclose();
        Sleep(dcl);
        if(curtime<cycle*3) curtime+=dcl;



    }
}