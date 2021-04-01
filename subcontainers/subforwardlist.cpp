#include <iostream>

using namespace std;

class sublist{
private:
    struct subforwardlist{
        int data;
        subforwardlist* next;
    };
    subforwardlist** first;
    subforwardlist * motion(subforwardlist * sfl){return sfl->next;}
public:
    sublist();//
    bool push_back(int d);//
    int pop_back();//
    bool push_forward(int d);//
    int pop_forward();//
    bool push_where(unsigned int where, int d);//
    bool erase_where(unsigned int where);//
    unsigned int size();//
    void clear();
    ~sublist();
};

sublist::sublist(){
    first = new subforwardlist*;
    *first = nullptr;
    cout << "INIT SUCCESS" << endl;
}

bool sublist::push_back(int d){
    subforwardlist * sfl = *first;
    if(*first == nullptr){
        sfl = new subforwardlist;
        sfl->data = d;
        sfl->next = nullptr;
        *first = sfl;
        return 1;
    }
    subforwardlist * a = sfl;
    while(a->next != nullptr){
        a = motion(a);
    }
    subforwardlist * b = new subforwardlist;
    a->next = b;
    b->data = d;
    b->next = nullptr;
    return 1;
}

int sublist::pop_back(){
    subforwardlist * sfl = *first;
    if(*first == nullptr){
        cout << endl << "ERROR: EMPTY LIST CANNOT POP_BACK" << endl;
        return 1;
    }
    if(sfl->next == nullptr){
        int r = sfl->data;
        delete *first;
        *first = nullptr;
        return r;
    }
    subforwardlist * a = sfl;
    subforwardlist * last;
    while(a->next->next != nullptr){
        a = motion(a);
    }
    last = a->next;
    int etr = last->data;
    a->next = nullptr;
    delete last;
    return etr;
}

bool sublist::push_forward(int d){
    subforwardlist * oldone = *first;
    if(oldone == nullptr){
        oldone = new subforwardlist;
        oldone->data = d;
        oldone->next = nullptr;
        *first = oldone;
        return 1;
    }
    subforwardlist * newone = new subforwardlist;
    newone->data = d;
    newone->next = *first;
    *first = newone;
    return 1;
}

int sublist::pop_forward(){
    subforwardlist * oldone = *first;
    if(*first == nullptr){
        cout << endl << "ERROR: EMPTY LIST CANNOT POP_FORWARD" << endl;
        return 0;
    }
    if(oldone->next == nullptr){
        int r = oldone->data;
        delete oldone;
        *first = nullptr;
        return r;
    }
    subforwardlist * newstart = oldone->next;
    int output = oldone->data;
    *first = newstart;
    delete oldone;
    return output;
}

bool sublist::push_where(unsigned int where, int d){
    subforwardlist * start = *first;
    if(start == nullptr && where != 0){
        cout << endl << "WARNING: EMPTY LIST, VALUE HAS BEEN PUT IN THE FIRST PLACE" << endl;
        push_back(d);
        return 0;
    }
    if(start == nullptr && where == 0){
        push_back(d);
        return 0;
    }
    if(where == 0){
        push_forward(d);
        return 1;
    }
    for(int i = 0; i != where-1; i++){
        if(start->next != nullptr){
            start = motion(start);
        }
        else{
            cout << endl << "WARNING: REACHED THE END OF THE LIST, VALUE HAS BEEN PUT IN THE " << i+1 << " PLACE" << endl;
            push_back(d);
            return 0;
        }
    }
    subforwardlist * nextone = start->next;
    subforwardlist * b = new subforwardlist;
    b->data = d;
    b->next = nextone;
    start->next = b;
    return 1;
}

bool sublist::erase_where(unsigned int where){
    subforwardlist * impostor = *first;
    subforwardlist * novice = *first;
    subforwardlist * sfl = *first;
    if(sfl == nullptr){
        cout << "ERROR: EMPTY LIST" << endl;
        return 0;
    }
    if(sfl->next == nullptr && where != 0){
        cout << "ERROR: " << where << " PLACE DOESN'T EXIST IN THIS LIST" << endl;
        return 0;
    }
    if(sfl->next == nullptr && where == 0){
        sfl->next = sfl;
        return 1;
    }
    if(where == 0){
        pop_forward();
        return 1;
    }
    for(int i = 0; i != where; i++){
        if(impostor->next != nullptr){
            impostor = motion(impostor);
        }
        else{
            cout << "ERROR: " << where << " PLACE DOESN'T EXIST IN THIS LIST" << endl;
            return 0;
        }
        if(i < where - 1){
            novice = motion(novice);
        }
    }
    novice->next = impostor->next;
    delete impostor;
    return 1;
}

unsigned int sublist::size(){
    subforwardlist * sfl = *first;
    int i = 1;
    subforwardlist * a = sfl;
    if(a == nullptr){
        return 0;
    }
    while(a->next != nullptr){
        a = motion(a);
        i++;
    }
    return i;
}

void sublist::clear(){
    subforwardlist * sfl = *first;
    unsigned int d = size();
    for(int i = 0; i < d; i++){
        pop_back();
    }
    //delete *sfl2;
    *first = nullptr;
}

sublist::~sublist(){
    delete first;
}
