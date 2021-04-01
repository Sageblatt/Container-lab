#include <iostream>
using namespace std;

class subvector
{
public:
    subvector();//
    bool push_back(int d);//
    void insert(unsigned int pos, int d);
    void erase(unsigned int pos);
    int pop_back();//
    bool resize(unsigned int new_capacity);//
    void shrink_to_fit();//
    void clear();//
    int sum();
    int capacity_check();
    int top_check();
    ~subvector();
    int& operator [] (const unsigned int ind);
private:
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

int& subvector::operator [] (const unsigned int ind)
{
    return mas[ind];
}

subvector::subvector()
{
    this->capacity = 2000;
    this->top = 0;
    this->mas = new int[this->capacity];
}

bool subvector::resize(unsigned int new_capacity){
    if(new_capacity <= this->capacity){
        return 0;
    }
    unsigned int *a = &(this->capacity);
    int oldc = *a;
    *a = new_capacity;
    int *b = new int[*a];
    int i = 0;
    while(i < oldc){
        b[i]=this->mas[i];
        i++;
    }
    delete[] this->mas;
    this->mas = b;
    return 1;
}

bool subvector::push_back(int d)
{
    if((this->top) == this->capacity){
        unsigned int b = this->capacity + 100;//
        this->resize(b);
    }
    this->mas[this->top] = d;
    this->top++;
    return 1;
}

int subvector::pop_back(){
    if(this->top > 0){
        this->top--;
        return this->mas[this->top];
    }
    else{
        return 0;
    }
}

void subvector::shrink_to_fit(){
    int * b = new int[this->top];
    for(int i = 0; i < this->top; i++){
        b[i] = this->mas[i];
    }
    delete[] this->mas;
    this->mas = b;
    this->capacity = this->top;
}

void subvector::clear(){
    this->top = 0;
}

int subvector::sum()
{
    long long int s = 0;
    for(int i = 0; i < this->top; i++)
    {
        s += this->mas[i];
    }
    return s;
}

subvector::~subvector(){
    delete[] this->mas;
    this->mas = nullptr;
    this->top = 0;
    this->capacity = 0;
}

int subvector::capacity_check()
{
    return this->capacity;
}

int subvector::top_check()
{
    return this->top;
}

void subvector::insert(unsigned int pos, int d)
{
    if(top == capacity || top == capacity - 1)
    {
        resize(capacity + 50);
    }
    if(pos > top || top == 0)
    {
        push_back(d);
        return;
    }
    top++;
    for(int i = top; i > pos - 1; i-- )
    {
        mas[i] = mas[i - 1];
    }
    mas[pos - 1] = d;
}

void subvector::erase(unsigned int pos)
{
    if(pos > top)
    {
        return;
    }
    if(capacity - 50 > top)
    {
        shrink_to_fit();
    }
    if(top == 1)
    {
        clear();
        return;
    }
    for(int i = pos; i < top; i++ )
    {
        mas[i - 1] = mas[i];
    }
    top--;
}

/*int main()
{
    subvector qwer;
    int i;
    for(i = 0; i <= 10; i++)
    {
        qwer.push_back(i);
    }
    qwer.insert(1, 15);
    cout << qwer.sum() <<  endl;
    cout << qwer.top_check() << endl;
    cout << qwer.capacity_check() << endl;
    cout << qwer[0] << endl << qwer[1] << endl << qwer[2] << endl;
    qwer.erase(1);
    cout << qwer[0] << endl << qwer[1] << endl << qwer[2] << endl;

}*/

