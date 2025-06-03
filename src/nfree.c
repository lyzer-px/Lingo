#include <stdlib.h>

void *nfree(void *ptr)
{
    free(ptr);
    return nullptr;
}

bool bfree(void *ptr)
{
    free(ptr);
    return false;
}
