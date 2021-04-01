#include <fstream>
#include <random>
#include <chrono>
#include "subvector.cpp"

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
    subvector sv;
    const int amount = 3150000;
    int *values = new int[amount];
    unsigned *positions = new unsigned int[amount];

    for(int i = 0; i < amount; i++)
    {
        values[i] = rand_uns(-50000, 50000);
        positions[i] = rand_uns(0, i - 1);
        sv.push_back(values[i]);
    }
    cout << "INIT" << endl;
    double start = 0, finish = 0;

    fstream fout("3sub.csv");
    fout.fixed;
    fout.precision(4);

    for(int i = amount - 1; i >= 0; i--)
    {
        start = get_time();
        //cout << "abba" << endl;
        sv.erase(positions[i]);

        finish = get_time();
        fout << sv.top_check() << ", " << finish - start << endl;
    }


    fout.close();

    delete[] values;
    delete[] positions;
    return 0;
}
