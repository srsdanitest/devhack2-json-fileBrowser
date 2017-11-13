#ifndef FILESS_H
#define FILESS_H
#include<string>
using namespace std;
class filess
{
    double id;      //id comes out as double from QJson, even if it's integer. Set to double to avoid int to double conversion
    bool type;      //true/false, store if we have a file or directory
    string name;    //name for file/directory
    long parentID;  //store parentID.
public:
    filess(double, bool, string, long);
    double getID(){return id;};
    bool returnType(){return type;}
    string returnName(){return name;};
    long returnParentID(){return parentID;};
};

#endif // FILESS_H
