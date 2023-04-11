
void lmd(int Rd, int I, string Imd)
{
    if (I)
    {
        // conversion
        {
          int tmp=hex_i(Imd);
          tmp%=hex_i("100");
          Imd=i_hex(tmp);
        }

        RB[Rd] = mem[Imd];
        cout << "temp(E) MAR(E,L) \n RAM(E) R" << Rd << "(L)" << endl;
    }
    else
    {
        RB[Rd] = hex_i(Imd);
        cout << "R" << Rd << "(L) temp(E)" << endl;
    }
    effectFlag(RB[Rd]);
    RB[Rd] %= hex_i("100");

    flag.Print();
    printRb();
    printMem();
}

void sdm(int Rd, int I, string Imd)
{
    
     // conversion
        {
          int tmp=hex_i(Imd);
          tmp%=hex_i("100");
          Imd=i_hex(tmp);
        }


    if (I)
    {
        mem[Imd] = RB[Rd];
        cout << "temp(E),MAR(E,L)\n RAM(L) R" << Rd << "(E)" << endl;
    }
    effectFlag(RB[Rd]);
    flag.Print();
    printMem();
}

int lShift(int val, int op, int am)
{
    if (op)
    {
        return val >> am;
    }
    else
        return val << am;
}
int asr(int val, int am)
{
    int ok = val & (1 << 7) ? 1 : 0;
    int ans = val >> am;
    if (ok)
    {
        int s = 7;
        while (am--)
        {
            ans += 1 << s;
            s--;
        }
    }
    return ans;
}
int ror(int val, int am)
{

    int c = flag.c;
    while (am--)
    {
        int tc = val & 1;
        val = val >> 1;
        if (c)
        {
            val += 1 << 7;
        }
        c = tc;
    }
    flag.c = c;
    return val;
}
int barrel(int val, string ty, int am)
{
    int tt = typRot[ty];
    int ans;
    if (tt < 2)
    {
        ans = lShift(val, tt, am);
    }
    else
    {
        if (tt == 2)
        {
            ans = asr(val, am);
        }
        else
        {
            ans = ror(val, am);
        }
    }
    return ans;
}
void mov(int Rd, int Rs1, int I, string ty, string Imd, int Rm)
{

    if (I)
    {
        int val;
        if (Rm != -1)
        {
              
            int tmp = barrel(RB[Rs1], ty, RB[Rm] & 7);
            RB[Rd] = tmp;
        }
        else
        {
                int temp=RB[Rm]&7;
           
              debug(RB[Rs1],ty,temp);
            int tmp = barrel(RB[Rs1], ty, hex_i(Imd));
            RB[Rd] = tmp;
        }
        cout << "R" << Rs1 << "(E), temp(E) Barrel(L) R" << Rd << "(L) Barrel(E)" << endl;
    }
    else
    {
        cout << "R" << Rs1 << "(E) R" << Rd << "(L)" << endl;
        RB[Rd] = RB[Rs1];
    }
    effectFlag(RB[Rd]);
    RB[Rd]%=hex_i("100");
    flag.Print();
    printRb();
    printMem();
}

void add(int Rd, int Rs1, int Rs2, int I, string ty, string Imd, int Rm)
{
    int a,b;
    if (I)
    {
        int tmp;
        if (Rm != -1)
        {
            tmp = barrel(RB[Rs2], ty, RB[Rm] & 7);
        }
        else
        {
            tmp = barrel(RB[Rs2], ty, hex_i(Imd));
        }
        a=RB[Rs1],b=tmp;
        RB[Rd] = RB[Rs1] + tmp;
        cout << "R" << Rs2 << "(E) temp(E) Barrel(E) \nR" << Rs1 << "(E) Barrel(E) ALU(L)\n R" << Rd << "(L) ALU(E)" << endl;
    }
    else
    {
        if (Rs2 != -1)
        {
            a=RB[Rs1];
            b=RB[Rs2];
            RB[Rd] = RB[Rs1] + RB[Rs2];

            cout << "R" << Rs1 << "(E) R" << Rs2 << "(E)"
                 << "ALU(L)" << endl;
            cout << "R" << Rd << "(L) ALU(E)" << endl;
        }
        else
        {
            a=RB[Rs1];
            b=hex_i(Imd);
            RB[Rd] = RB[Rs1] + hex_i(Imd);
            cout << "R" << Rs1 << "(E) temp(E) ALU(L) \nR" << Rd << "(L) ALU(E)" << endl;
        }
    }
    effectFlag(RB[Rd],a,b);
    RB[Rd] %= hex_i("100");
    flag.Print();
    printRb();
    printMem();
}
void sub(int Rd, int Rs1, int Rs2, int I, string ty, string Imd, int Rm)
{
    int a=RB[Rs1],b;
    if (I)
    {
        int tmp;
        if (Rm != -1)
        {
            tmp = barrel(RB[Rs2], ty, RB[Rm] & 7);
        }
        else
        {
            tmp = barrel(RB[Rs2], ty, hex_i(Imd));
        }
        b=tmp;
        RB[Rd] = RB[Rs1] - tmp;
        cout << "R" << Rs2 << "(E) temp(E) Barrel(E) \nR" << Rs1 << "(E) Barrel(E) ALU(L)\n R" << Rd << "(L) ALU(E)" << endl;
    }
    else
    {
        if (Rs2 != -1)
        {
            b=RB[Rs2];
            RB[Rd] = RB[Rs1] - RB[Rs2];

            cout << "R" << Rs1 << "(E) R" << Rs2 << "(E)"
                 << "ALU(L)" << endl;
            cout << "R" << Rd << "(L) ALU(E)" << endl;
        }
        else
        {
            b=RB[Rs2];
            RB[Rd] = RB[Rs1] - hex_i(Imd);
            cout << "R" << Rs1 << "(E) temp(E) ALU(L) \nR" << Rd << "(L) ALU(E)" << endl;
        }
    }
    effectFlag(RB[Rd],a,b);
    RB[Rd] %= hex_i("100");
    if (RB[Rd] < 0)
        RB[Rd] += hex_i("100");
    flag.Print();
    printRb();
    printMem();
}

void AND(int Rd, int Rs1, int Rs2, int I, string ty, string Imd, int Rm)
{
    if (I)
    {
        int tmp;
        if (Rm != -1)
        {
            tmp = barrel(RB[Rs2], ty, RB[Rm] & 7);
        }
        else
        {
            tmp = barrel(RB[Rs2], ty, hex_i(Imd));
        }
        RB[Rd] = RB[Rs1] & tmp;
        cout << "R" << Rs2 << "(E) temp(E) Barrel(E) \nR" << Rs1 << "(E) Barrel(E) ALU(L)\n R" << Rd << "(L) ALU(E)" << endl;
    }
    else
    {
        if (Rs2 != -1)
        {
            RB[Rd] = RB[Rs1] & RB[Rs2];

            cout << "R" << Rs1 << "(E) R" << Rs2 << "(E)"
                 << "ALU(L)" << endl;
            cout << "R" << Rd << "(L) ALU(E)" << endl;
        }
        else
        {
            RB[Rd] = RB[Rs1] & hex_i(Imd);
            cout << "R" << Rs1 << "(E) temp(E) ALU(L) \nR" << Rd << "(L) ALU(E)" << endl;
        }
    }
    effectFlag(RB[Rd]);
    RB[Rd] %= hex_i("100");
    flag.Print();
    printRb();
    printMem();
}

void OR(int Rd, int Rs1, int Rs2, int I, string ty, string Imd, int Rm)
{
    if (I)
    {
        int tmp;
        if (Rm != -1)
        {
            tmp = barrel(RB[Rs2], ty, RB[Rm] & 7);
        }
        else
        {
            tmp = barrel(RB[Rs2], ty, hex_i(Imd));
        }
        RB[Rd] = RB[Rs1] | tmp;
        cout << "R" << Rs2 << "(E) temp(E) Barrel(E) \nR" << Rs1 << "(E) Barrel(E) ALU(L)\n R" << Rd << "(L) ALU(E)" << endl;
    }
    else
    {
        if (Rs2 != -1)
        {
            RB[Rd] = RB[Rs1] | RB[Rs2];

            cout << "R" << Rs1 << "(E) R" << Rs2 << "(E)"
                 << "ALU(L)" << endl;
            cout << "R" << Rd << "(L) ALU(E)" << endl;
        }
        else
        {
            RB[Rd] = RB[Rs1] | hex_i(Imd);
            cout << "R" << Rs1 << "(E) temp(E) ALU(L) \nR" << Rd << "(L) ALU(E)" << endl;
        }
    }
    effectFlag(RB[Rd]);
    RB[Rd] %= hex_i("100");
    flag.Print();
    printRb();
    printMem();
}

void XOR(int Rd, int Rs1, int Rs2, int I, string ty, string Imd, int Rm)
{
    if (I)
    {
        int tmp;
        if (Rm != -1)
        {
            tmp = barrel(RB[Rs2], ty, RB[Rm] & 7);
        }
        else
        {
            tmp = barrel(RB[Rs2], ty, hex_i(Imd));
        }
        RB[Rd] = RB[Rs1] ^ tmp;
        cout << "R" << Rs2 << "(E) temp(E) Barrel(E) \nR" << Rs1 << "(E) Barrel(E) ALU(L)\n R" << Rd << "(L) ALU(E)" << endl;
    }
    else
    {
        if (Rs2 != -1)
        {
            RB[Rd] = RB[Rs1] ^ RB[Rs2];

            cout << "R" << Rs1 << "(E) R" << Rs2 << "(E)"
                 << "ALU(L)" << endl;
            cout << "R" << Rd << "(L) ALU(E)" << endl;
        }
        else
        {
            RB[Rd] = RB[Rs1] ^ hex_i(Imd);
            cout << "R" << Rs1 << "(E) temp(E) ALU(L) \nR" << Rd << "(L) ALU(E)" << endl;
        }
    }
    effectFlag(RB[Rd]);
    RB[Rd] %= hex_i("100");
    flag.Print();
    printRb();
    printMem();
}

void CSB(int Rd, int Rs1, string Imd, int I)
{
    if (Rs1 != -1)
    {
        RB[Rd] = __builtin_popcount(RB[Rs1]);
        cout << "R" << Rs1 << "ALU(L) \n ALU(E) R" << Rd << "(L)" << endl;
    }
    else
    {
        int tmp;
        if (I)
        {
            tmp = mem[Imd];
            cout << "temp(E) MAR(E,L) \nRAM(E) ALU(L) \n ALU(E) R" << Rd << "(L)" << endl;
        }
        else
        {
            tmp = hex_i(Imd);
            cout << "temp(E) ALU(L) \n ALU(E) R" << Rd << "(L)" << endl;
        }
        RB[Rd] = __builtin_popcount(tmp);
    }
    effectFlag(RB[Rd]);
    flag.Print();
    printRb();
    printMem();
}
