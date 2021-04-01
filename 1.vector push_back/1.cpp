#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    fstream outFile;
    outFile.open("out2.csv");

    unsigned long long int i;

    vector<int> cont;
    int n = 4;
    for(i = 0; i < pow(10, n); i++)
    {
        cont.push_back(i);
        outFile << i << ", " << cont.size() << ", " << cont.capacity() << endl;
    }


    outFile.close();
    return 0;
}
