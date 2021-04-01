#include <fstream>
#include <random>
#include <chrono>
#include <iostream>
#include <list>

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
    list <int> sv;
    const int iters = 100000;
    const long long int amount = 31500000;
    int * values = new int[amount];
    int percent = 0;
    cout << endl << 0;
    for( long long int i = 0; i < amount; i++)
    {
        values[i] = rand_uns(-50000, 50000);
        double progress = (i * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
    }
    sv.push_front(2);
    sv.push_front(2);

    cout << "INIT" << endl;
    double start = 0, finish = 0;

    fstream fout("7fl.csv");
    fout.fixed;
    fout.precision(4);

    percent = 0;
    cout << endl << 0;
    for(long long int i = 0; i < amount - iters - 10; i += iters)
    {
        auto it = sv.begin();
        start = get_time();
        for(; it != sv.end() ; it++)
        {
            *it++;
        }
        finish = get_time();

        for(long long int r = 0; r < iters; r++)
        {
            sv.push_front(values[i + r]);
        }
        double progress = (i * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
        fout << i << ", " << finish - start << endl;
    }


    fout.close();
    delete[] values;
    return 0;
}
