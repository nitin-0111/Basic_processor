
// utility funtion
int hex_i(string s) // hex->int
{
    if (s[0] == '#')
        s = s.substr(1);

    // debug(s);
    int hexInt = stoi(s, nullptr, 16);
    return hexInt;
}

string i_hex(int n) // int->hex;
{
    stringstream ss;
    ss << hex << n;
    string s=ss.str();
    if(s.size()<2)
    s='0'+s;
    return s;
}

int msbSet(int n) {
    int pos = 0;
    while (n > 0) {
        pos++;
        n = n >> 1;
    }
    return pos;
}