#include "filess.h"
#include<string>
using namespace std;
filess::filess(double idd, bool tyype=false, string namee="", long parenttID=0 )
{
    id=idd;
    type=tyype;
    name=namee;
    parentID=parenttID;
}
