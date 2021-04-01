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
    const int amount = 2*3150000;
    int *values = new int[amount];
    unsigned *positions = new unsigned int[amount];

    for(int i = 0; i < amount; i++)
    {
        values[i] = rand_uns(-50000, 50000);
        positions[i] = rand_uns(0, i - 1);
        sv.push_back(values[i]);
    }
    sv.push_back(1);
    cout << "INIT" << endl;
    double start = 0, finish = 0;

    fstream fout("3vend2.csv");
    fout.fixed;
    fout.precision(4);
    positions[0] = 1;
    int percent = 0;
    cout << 0;
    for(int i = amount - 1; i >= 21; i -= 21)
    {
        start = get_time();
        //cout << "abba" << endl;
        sv.erase(sv.begin() + positions[i]);
        sv.erase(sv.begin() + positions[i - 1]);
        sv.erase(sv.begin() + positions[i - 2]);
        sv.erase(sv.begin() + positions[i - 3]);
        sv.erase(sv.begin() + positions[i - 4]);
        sv.erase(sv.begin() + positions[i - 5]);
        sv.erase(sv.begin() + positions[i - 6]);
        sv.erase(sv.begin() + positions[i - 7]);
        sv.erase(sv.begin() + positions[i - 8]);
        sv.erase(sv.begin() + positions[i - 9]);
        sv.erase(sv.begin() + positions[i - 10]);
        sv.erase(sv.begin() + positions[i - 11]);
        sv.erase(sv.begin() + positions[i - 12]);
        sv.erase(sv.begin() + positions[i - 13]);
        sv.erase(sv.begin() + positions[i - 14]);
        sv.erase(sv.begin() + positions[i - 15]);
        sv.erase(sv.begin() + positions[i - 16]);
        sv.erase(sv.begin() + positions[i - 17]);
        sv.erase(sv.begin() + positions[i - 18]);
        sv.erase(sv.begin() + positions[i - 19]);
        sv.erase(sv.begin() + positions[i - 20]);

        finish = get_time();
        double progress = ((amount - i) * 100.f / amount);
        if (progress > percent)
        {
            cout << '\b' << '\b' << percent;
            percent++;
        }
        fout << sv.size() << ", " << finish - start << endl;
    }
    cout << sv.capacity() << endl;

    fout.close();

    delete[] values;
    delete[] positions;
    return 0;
}
