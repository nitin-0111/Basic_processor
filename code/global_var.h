
vector<int> RB(8, 0);
string breakLine(50, '-');

map<string, int> mem;
map<string, int> opCode = {{"LDM", 0}, {"SDM", 1}, {"MOV", 2}, {"ADD", 3}, {"SUB", 4}, {"AND", 5}, {"OR", 6}, {"XOR", 7}, {"CSB", 8}};
map<string, int> typRot = {{"LSL", 0}, {"LSR", 1}, {"ASR", 2}, {"ROR", 3}};


class FLAG
{
public:
    int z, v, c, n;
    FLAG()
    {
        z = 0, v = 0, c = 0, n = 0;
    }

    void Print()
    {
        cout << "Flags: Z V C N =>" << z << v << c << n << endl;
    }
};

FLAG flag;
void effectFlag(int res ,int a=0,int b=0)
{
    int mx=max(a,b);
    int sbit=msbSet(mx);
    if (res == 0)
        flag.z = 1;
    if (res & (1 << 7))
        flag.n = 1;
    if (hex_i("ff") < res)
    {
        flag.v = 1;
        
    }
    if(res&(1<<sbit))
    flag.c=1;

    // if (res & (1LL << 9))
    //     flag.c = 1;
}