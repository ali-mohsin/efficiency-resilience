#include <sys/time.h>
#include <iostream>
using namespace std;

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y)
{
    /* Perform the carry for the later subtraction by updating y. */
    if (x->tv_usec < y->tv_usec) {
        int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
        y->tv_usec -= 1000000 * nsec;
        y->tv_sec += nsec;
    }
    if (x->tv_usec - y->tv_usec > 1000000) {
        int nsec = (x->tv_usec - y->tv_usec) / 1000000;
        y->tv_usec += 1000000 * nsec;
        y->tv_sec -= nsec;
    }
    /* Compute the time remaining to wait.
    tv_usec is certainly positive. */
    result->tv_sec = x->tv_sec - y->tv_sec;
    result->tv_usec = x->tv_usec - y->tv_usec;
//    printf(result->tv_sec);
    /* Return 1 if result is negative. */
	return 0;
}

struct timeval t1, t2;
struct timezone tz;

void startTimer()
{
	gettimeofday(&t1, &tz);
}

int stopTimer(string func)
{

    gettimeofday(&t2, &tz);
    cout<<"It took "<< t2.tv_sec - t1.tv_sec <<" seconds and "<< t2.tv_usec - t1.tv_usec<<" micro for "<<func.c_str()<<endl;

}

// call "startTimer()" to start timer
// call "stopTimer()" to stop timer and print total time in microseconds.
