#include <stdio.h>

#include "AppManager.h"

int main()
{
    setbuf(stdout, 0);

    FAppManager App;
    if (Init(&App) == 1)
    {
        Loop(&App);
    }

    return 1;
}
