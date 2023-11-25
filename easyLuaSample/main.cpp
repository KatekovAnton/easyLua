#include "UsageSample.hpp"
#include "ByteBuffer.h"



int main()
{
    UsageSample s;
    ByteBuffer buffer;
    s.Test(&buffer);


    UsageSample s1;
    s.TestSaved(&buffer);
    return 0;
}
