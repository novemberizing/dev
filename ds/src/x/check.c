#include <stdio.h>

#include <x/log.h>

int main(int argc, char ** argv)
{
    functionLog("%s %s", "hello", "world");
    criticalLog("%s %s", "hello", "world");
    errorLog("%s %s", "hello", "world");
    warningLog("%s %s", "hello", "world");
    cautionLog("%s %s", "hello", "world");
    noticeLog("%s %s", "hello", "world");
    informationLog("%s %s", "hello", "world");
    debugLog("%s %s", "hello", "world");
    assertion(false, "hello world");

    return 0;
}
