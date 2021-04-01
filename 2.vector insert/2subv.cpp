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
    const long int amount = 31500000;
    int *values = new int[amount];
    unsigned *positions = new unsigned int[amount];

    int percent = 0;
    cout << 0;
    for(long int i = 0; i < amount; i++)
    {
        values[i] = rand_uns(-50000, 50000);
        positions[i] = rand_uns(0, i - 1);
        double progress = (i * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
    }

    double start = 0, finish = 0;

    fstream fout("2subv1.csv");
    fout.fixed;
    fout.precision(4);
    subvector sv;
    percent = 0;
    cout << endl << 0;
    for(long int i = 0; i < amount; i++)
    {
        start = get_time();
        //cout << "abba" << endl;
        sv.insert(positions[i], values[i]);

        finish = get_time();
        double progress = (i * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
        fout << sv.top_check() << ", " << finish - start << endl;
    }


    fout.close();

    delete[] values;
    delete[] positions;
    return 0;
}
