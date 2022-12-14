#include "chilon.h"

char* chilon_iter_INT(int x, int y, int nb_col, int size_output, char * buffer, void* data)
{
    int v = *(((int*)data+y*nb_col)+x);
    snprintf(buffer, size_output, "%d", v);
    return buffer;
}

char* chilon_iter_SHORT(int x, int y, int nb_col, int size_output, char * buffer, void* data)
{
    short v = *(((short*)data+y*nb_col)+x);
    snprintf(buffer, size_output, "%d", v);
    return buffer;
}

char* chilon_iter_LONG(int x, int y, int nb_col, int size_output, char * buffer, void* data)
{
    long v = *(((long*)data+y*nb_col)+x);
    snprintf(buffer, size_output, "%ld", v);
    return buffer;
}

char* chilon_iter_POINTER(int x, int y, int nb_col, int size_output, char * buffer, void* data)
{
    void* v = (((void*)data+y*nb_col)+x);
    snprintf(buffer, size_output, "%p", v);
    return buffer;
}

char* chilon_iter_DOUBLE(int x, int y, int nb_col, int size_output, char * buffer, void* data)
{
    double v = *(((double*)data+y*nb_col)+x);
    snprintf(buffer, size_output, "%lf", v);
    return buffer;
}

char* chilon_iter_FLOAT(int x, int y, int nb_col, int size_output, char * buffer, void* data)
{
    float v = *(((float*)data+y*nb_col)+x);
    snprintf(buffer, size_output, "%f", v);
    return buffer;
}