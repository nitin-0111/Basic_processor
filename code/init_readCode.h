void init_set()
{
    cout << "set Register(index , value(Hex)) " << endl;

    string inputfile = "../config.txt";
    ifstream fin(inputfile);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        int x;
        string val;
        fin >> x;
        fin >> val;

        RB[x] = hex_i(val.substr(1));
    }
    printRb();

    fin >> n;
    for (int i = 0; i < n; i++)
    {
        string add, val;
        fin >> add;
        fin >> val;
        for (auto &x : add)
            x = tolower(x);

        assert(hex_i(add.substr(1)) <= hex_i("ff"));
        mem[add.substr(1)] = hex_i(val.substr(1));
    }

    printMem();
    fin.close();
    cout << breakLine << endl;
}

vector<vector<string>> readCode()
{
    string inputfile = "../in.txt";
    ifstream fin(inputfile);
    string input;
    vector<vector<string>> code;

    while (getline(fin, input))
    {
        vector<string> words;
        stringstream ss(input);
        string word;

        while (ss >> word)
        {
            words.push_back(word);
        }
        if (words.size())
            code.push_back(words);
    }

    fin.close();
    return code;
}
