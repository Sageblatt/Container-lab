#include <fstream>
#include <random>
#include <chrono>
#include "subforwardlist.cpp"

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
    sublist sv;
    const int iters = 1000;
    const int amount = 3150000;
    int * values = new int[amount];
    int percent = 0;
    cout << 0;
    for(int i = 0; i < amount; i++)
    {
        //values[i] = rand_uns(-50000, 50000);
        sv.push_forward(rand_uns(-50000, 50000));
        double progress = (i * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
    }

    cout << endl << "INIT" << endl;
    double start = 0, finish = 0;

    fstream fout("6sub.csv");
    fout.fixed;
    fout.precision(4);

    percent = 0;
    cout << endl << 0;
    for(int i = 0; i < amount - iters; i += iters)
    {
        start = get_time();
        for(int r = 0; r < iters; r++)
        {
            sv.pop_forward();
        }
        finish = get_time();
        double progress = (i * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
        fout << sv.size() << ", " << finish - start << endl;
    }


    fout.close();
    delete[] values;
    return 0;
}
