#include "tests.h"
#include <time.h>
#include <stdlib.h>

/*

We can see test3 using the JKI algorithm is the fastest.

*/

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    test1();
    test2();
    test3();

    return 0;
}
