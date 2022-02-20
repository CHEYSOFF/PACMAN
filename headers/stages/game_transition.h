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

#include "../screen.h"
#include "../variables.h"

using namespace std;


void transition(){

    for(int kt=2;kt>=0;kt--){
        updateScreen();

        for(int i=0;i<32;i++){
            cout<<UP;
        }

        for(int i=0;i<char_he;i++){
            string nu="";
            for(int j=0;j<char_wi;j++){
                if(nums[kt][i][j]==1){
                    for(int tt=0;tt<x_nu;tt++) nu+="@";
                }
                else for(int tt=0;tt<x_nu;tt++) nu+=RIG;
            }
            cout<<num_col[kt];
            for(int kkk=0; kkk<y_nu;kkk++){
                for(int j=0;j<18;j++) cout<<RIG;
                cout<<nu;
                cout<<'\n';
            }
            cout<<flush;
            
            
        }
        Sleep(1000);
    }
    

    

}