#ifndef FILESS_H
#define FILESS_H
#include<string>
using namespace std;
class filess
{
    long id;
    bool type;
    string name;
    long parentID;
public:
    filess(long, bool, string, long);
};

#endif // FILESS_H
