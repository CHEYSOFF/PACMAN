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
#include "../screen.h"

using namespace std;

void wait_for_input(){

    if(getch()){
        menuContinue=false;
        return;
    }

}

void letters_print(){

    

    for(int i=0;i<char_he;i++){
        string line_of_letter_w="";
        for(int j=0;j<char_wi;j++){
            if(char_w[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) line_of_letter_w+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) line_of_letter_w+=" ";
        }
        cout<<let_col[col_k%4];
        string tm="";
        for(int kkk=0; kkk<y_ch;kkk++){
            // for(int j=0;j<23;j++) cout<<" ";
            // cout<<line_of_letter_w;
            cen_out(line_of_letter_w);
            cout<<'\n';
        }
        
        
    }
    
    for(int i=0;i<char_he;i++){
        cout<<" ";
        string line_of_letter_a="";
        for(int j=0;j<char_wi;j++){
            if(char_a[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) line_of_letter_a+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) line_of_letter_a+=" ";
        }
        

        string line_of_letter_s="";
        for(int j=0;j<char_wi;j++){
            if(char_s[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) line_of_letter_s+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) line_of_letter_s+=" ";
        }
        


        string line_of_letter_d="";
        for(int j=0;j<char_wi;j++){
            if(char_d[i][j]==1){
                for(int tt=0;tt<x_ch;tt++) line_of_letter_d+="*";
            }
            else for(int tt=0;tt<x_ch;tt++) line_of_letter_d+=" ";
        }
        
        for(int kkk=0; kkk<y_ch;kkk++){
            string help=line_of_letter_a+"   "+line_of_letter_s+"   "+line_of_letter_d;
            cout<<let_col[(col_k+1)%4];
            int ots=margin(help);
            for(int i=0;i<ots;i++) cout<<" ";
            // for(int j=0;j<11;j++) cout<<" ";
            cout<<line_of_letter_a;
            cout<<"  ";
            cout<<let_col[(col_k+2)%4];
            cout<<line_of_letter_s;
            cout<<"  ";
            cout<<let_col[(col_k+3)%4];
            cout<<line_of_letter_d;
            cout<<'\n';
        }
        

    }
    cout<<'\n';



    cout<<flush;
    Sleep(500);

}

void text_print(){

    while(menuContinue){
        system("cls");
        cout<<'\n';
        cout<<'\n';
        string pabts="Press any button to start";
        string C="CONTROLS";
        cout<<RED;
        cen_out(pabts);
        cout<<'\n';
        cout<<'\n';
        cout<<'\n';
        cout<<CYA;
        cen_out(C);
        cout<<'\n';
        cout<<'\n';
        letters_print();
        col_k++;
        col_k%=4;
    }
    
}

void threads_menu(){
    
    thread txt(text_print);
    thread inp(wait_for_input);

    inp.join();
    txt.detach();

}

void start_menu(){

    
    threads_menu();


}