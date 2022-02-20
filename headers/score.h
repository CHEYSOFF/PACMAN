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

using namespace std;

void addScore(point p){
    if(arr[p.i][p.j]==2){
        curscore+=1;
        arr[p.i][p.j]=0;
        onesleft--;
        if(onesleft<=0){
            onesleft=299;
            for(int i=0;i<he;i++){
                for(int j=0;j<wi;j++){
                    if(!(i==12 && j>=11 && j<=16) ) arr[i][j]=ones[i][j];
                }
            }
        }
    }
    else if(arr[p.i][p.j]==5){
        curscore+=5;
        arr[p.i][p.j]=0;
    }
    else if(p==se_mon || p==fi_mon){
        curscore+=20;
    }
}