#ifndef FILESS_H
#define FILESS_H
#include<string>
using namespace std;
class filess
{
    double id;
    bool type;
    string name;
    long parentID;
public:
    filess(double, bool, string, long);
    double getID(){return id;};
    bool returnType(){return type;}
    string returnName(){return name;};
    long returnParentID(){return parentID;};
};

#endif // FILESS_H
