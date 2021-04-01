#include <fstream>
#include <random>
#include <chrono>
#include <iostream>
#include <vector>

using namespace std;

double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}

int rand_uns(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

int main()
{
    vector <int> sv;
    const int amount = 3150000;
    const int iters = 10000;
    int * values = new int[amount];

    for(int i = 0; i < amount; i++)
    {
        values[i] = rand_uns(-50000, 50000);
    }
    sv.push_back(2);
    sv.push_back(2);
    sv.push_back(2);
    cout << "INIT" << endl;
    double start = 0, finish = 0;

    fstream fout("4v.csv");
    fout.fixed;
    fout.precision(4);

    for(int i = 1; i < amount; i++)
    {
        unsigned int pos[iters];
        for(int k  = 0; k < iters; k++)
        {
            pos[k] = rand_uns(0, i - 1);
        }
        start = get_time();
        for(int r = 0; r < iters; r++)
        {
            sv[pos[r]]++;
        }

        finish = get_time();
        fout << sv.size() << ", " << finish - start << endl;
        sv.push_back(values[i]);
    }


    fout.close();
    delete[] values;
    return 0;
}
