
#include <bits/stdc++.h>

using namespace std;

#ifndef ONLINE_JUDGE 
 #define debug(x...)
 #else
 #define debug(x...)
 #endif 

#include "./utility_fun.h"
#include "./global_var.h"
#include "./print_fun.h"
#include "./instruction.h"
#include "./fetch_decode.h"
#include "./init_readCode.h"

#define FILE freopen("../out.txt", "w", stdout);

signed main()
{
    FILE
    init_set();
    flag.c=1;
    int pc = 0;

    vector<vector<string>> code = readCode();

    // debug(code);
    int END = code.size();
    int Invalid = 0;
    while (pc != END and !Invalid)
    {
        // Fetch
        vector<string> line = code[pc];
        debug(line);
        print_fetch(pc, line);
        pc++;

        string opr, Imd, barRot;
        int Rd = -1, Rs1 = -1, Rs2 = -1, Rm = -1, I = 0;
        opr = line[0];
        vector<int> indx;
        for (int i = 1; i < line.size(); i++)
        {
            string s = line[i];
            if (s[0] == 'R' and '0'<=s[1] and s[1]<='9')
            {
                int ind = stoi(s.substr(1));
                indx.push_back(ind);
            }
            else
            {
                if (s=="I")
                {
                    I = 1;
                }
                else if (s[0] == '#')



                {
                    Imd = s.substr(1);
                }
                else
                {
                    barRot = s;
                }
            }
        }
       
        while (indx.size() < 4)
            indx.push_back(-1);



        Rd = indx[0], Rs1 = indx[1], Rs2 = indx[2], Rm = indx[3];
        if(opr=="MOV" and I)swap(Rs2,Rm);
        // debug(opCode[opr], Rd, Rs1, Rs2, I, Imd, barRot, Rm);
        print_decode(opCode[opr], Rd, Rs1, Rs2, I, Imd, barRot, Rm);
       
      cout<<"Excute :\n \t";
      
        switch (opCode[opr])
        {
        case 0:
            lmd(Rd, I, Imd);
            break;
        case 1:
            sdm(Rd, I, Imd);
            break;
        case 2:
            mov(Rd, Rs1, I, barRot, Imd, Rm);
            break;
        case 3:
            add(Rd, Rs1, Rs2, I, barRot, Imd, Rm);
            break;
        case 4:
            sub(Rd, Rs1, Rs2, I, barRot, Imd, Rm);
            break;
        case 5:
            AND(Rd, Rs1, Rs2, I, barRot, Imd, Rm);
            break;
        case 6:
            OR(Rd, Rs1, Rs2, I, barRot, Imd, Rm);
            break;
        case 7:
            XOR(Rd, Rs1, Rs2, I, barRot, Imd, Rm);
            break;
        case 8:
            CSB(Rd, Rs1, Imd, I);
            break;

        default:
        {
            cout << "Invalid intruction" << endl;
            Invalid = 1;
        }
        break;
        }

        // string input;
        // getline(cin, input);
        // if (input == "-1")
        //     break;
        cout << breakLine << endl;
       
    }

    return 0;
}
