   
void printRb()
{
    cout << "Register Bank [8]: \n\t";
    int MX = 1 << 8 - 1;

    for (int i = 0; i < 8; i++)
    {
        cout << "0x" << i_hex(RB[i]) << "\t";
    }
    cout << endl;
}
void printMem()
{
    cout << "Memory: \n\t";
    //  int MX=(1<<8)-1;
    for (auto [s, x] : mem)
    {
        cout << "0x" << s << " 0x" << i_hex(x) << endl;
    }
    cout << endl;
}
