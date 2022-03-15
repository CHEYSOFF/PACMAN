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

using namespace std;

void cherry_spawn(){
    
    while(gameContinue){
        Sleep(cherrySpawn);
        static std::uniform_int_distribution<int> uidi(1,he-2+1);
        static std::uniform_int_distribution<int> uidj(1,wi-2+1);
        int ib=uidi(rng);
        int jb=uidj(rng);
        
        for(int i=jb;i<he;i++){
            for(int j=jb;j<wi;j++){
                if(i>=12 && i<=16 && j>=10 && j<=17) continue;
                if(arr[i][j]==0 /*|| arr[i][j]==2*/){
                    arr[i][j]=5;
                    ib=i;
                    jb=j;
                    i=he;
                    j=wi;
                    cherryInd.i=ib;
                    cherryInd.j=jb;
                }
            }
        }
        Sleep(cherrySleep);
        arr[cherryInd.i][cherryInd.j]=0;
        cherryInd=u;
    }
}