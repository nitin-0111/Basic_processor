
void print_fetch(int pc, vector<string> mdr)
{
    cout << " Fetch: \n\t PC " << pc << " \n \t";
    cout << "PC(E)  MDR(E,L)"
         << " \n \t";
    cout << "PC(I)" << endl;
    cout << "\t MDR: ";
    string smdr;
    for (auto x : mdr)
        smdr += x + "  ";
    cout << smdr << endl;
}

void print_decode(int op, int Rd, int Rs1, int Rs2, int I, string Imd, string barRot, int Rm)
{

    string invalid(3, 'x');

    bitset<4> bop(op);
    bitset<3> brd(Rd), brs1(Rs1), brs2(Rs2), brm(Rm);
    // debug(op)
    assert(Rd != -1);
    cout << "Decode: \n\tIR :  " << bop << " ";

    {
        if (Rd == -1)
        {
            cout << invalid << " ";
        }
        else
        {
            cout << brd << " ";
        }
        if (Rs1 == -1)
        {
            cout << invalid << " ";
        }
        else
        {
            cout << brs1 << " ";
        }

        if (Rs2 == -1)
        {
            cout << invalid << " ";
        }
        else
        {
            cout << brs2 << " ";
        }
    }
    cout << I << " ";
    if (op < 2)
    {
        string Imdstr;
        if (Imd.size())
        {
            bitset<8> bb(hex_i(Imd));
            cout << bb.to_string() << endl;
        }
    }
    else
    {
        if (barRot.size())
        {

            bitset<2> ty(typRot[barRot]);

            string ss = ty.to_string() ;
            if (Rm != -1)
            {
                bitset<3> bb(Rm);
                ss += bb.to_string()+"xxx";
            }
            else
            {
                bitset<3> bb(hex_i(Imd));
                ss +="xxx"+ bb.to_string();
            }
            cout << ss << endl;
        }
        else
        {
            string ss(8, 'x');
            cout << ss << endl;
        }
    }
}
