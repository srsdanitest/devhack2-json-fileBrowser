#include "filess.h"
#include<string>
using namespace std;
filess::filess(long idd, bool tyype, string namee, long parenttID=0 )
{
    id=idd;
    type=tyype;
    name=namee;
    parentID=parenttID;
}
