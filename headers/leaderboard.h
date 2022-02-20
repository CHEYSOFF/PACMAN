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

string space_suf_del(string s){
    int k=s.size();
    for(int i=s.size()-1;i>=0;i--){
        if(s[i]==' '){
            k=i;
        }
        else{
            break;
        }
    }
    s=s.substr(0, k);
    return s;
}

void leader_board(string p_name){
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE) );
    ifstream fin;
    
    fin.open("leaderboard.txt");
    
    
    
    vector< pair< int, string >  > results;
    string s;
    while(getline(fin, s)){
        string name;
        int score;
        string rev=s;
        reverse(rev.begin(), rev.end());
        auto tm=rev.find(' ');
        if(tm==std::string::npos) continue;
        int ind_sp=s.size()-tm-1;
        name=s.substr(0, ind_sp);
        cout<<ind_sp<<" "<<name<<endl;
        try{
            score=stoi(s.substr(ind_sp+1, s.size()-ind_sp-1));
        } catch( std::invalid_argument ){
            continue;
        }
        
        results.push_back({score, name});

    }
    fin.close();
    results.push_back( {curscore, p_name} );

    vector< pair< int, string >  > results_tmp;

    for(int i=0; i<results.size(); i++){
        string tmstr=results[i].second;
        if(tmstr.size()>=3 && tmstr.substr( tmstr.size()-3, 3 ) == "..." ){
            tmstr=tmstr.substr(0, tmstr.size()-3);
        }
        tmstr=space_suf_del(tmstr);
        results[i].second=tmstr;
        if(results[i].second.size()!=0){
            results_tmp.push_back(results[i]);
        }
    }

    results=results_tmp;
    

    sort( results.begin(), results.end(), greater<pair<int, string> >() );
    int n=results.size();

    ofstream fout;
    fout.open("leaderboard.txt");
    lbsize=min(lbsize, n);
    for(int i=0;i<lbsize; i++ ){
        lbscore.push_back( {results[i].second, results[i].first} );
        fout<<results[i].second<<" "<<results[i].first<<'\n';
    }
    fout.close();
    return;
    
}