#include <windows.h>
#include <process.h>

long global1 = 0;
volatile long global2 = 0;

class MyClass
{
public:
    MyClass() : m(0)
    {
        ++m;
    }

    int fun(int v)
    {
        return m+v; //-----------9
    }

    void set(int v)
    {
        m = v;   //-------------10
    }
    int m;
};

MyClass global_object; //-------------8

unsigned int __stdcall thread_fun1(void *param)
{
    static int static2 = 0;
    static MyClass static_object; //--------6
    int local1 = 0;

    ++local1;     //-------1
    ++static2;    //-------2
    ++global1;    //-------3
    ++global2;    //-------4
    InterlockedIncrement(&global1); //--------5

    local1 = global_object.fun(local1); //----------7

    global_object.set(local1); //---------------11

    return 0;
}


unsigned int __stdcall thread_fun2(void *param)
{
    ++global1;    //-------3
    ++global2;    //-------4
    InterlockedIncrement(&global1); //--------5

    global_object.set(1); //-----------11
    return 0;
}


int main()
{
    HANDLE thread1 = (HANDLE)_beginthreadex(0,0,&thread_fun1,0,0,0); //thread 1
    HANDLE thread2 = (HANDLE)_beginthreadex(0,0,&thread_fun1,0,0,0); //thread 2
    HANDLE thread3 = (HANDLE)_beginthreadex(0,0,&thread_fun2,0,0,0); //thread 3

    WaitForSingleObject(thread1,INFINITE);
    WaitForSingleObject(thread2,INFINITE);
    WaitForSingleObject(thread3,INFINITE);

    return 0;
}
