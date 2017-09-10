#include "MultiThreadLocker.h"

MultiThreadLocker::MultiThreadLocker(int n)
{
	sem_init(&sem,0,n);
}

void MultiThreadLocker::lock()
{
	sem_wait(&sem);
}

void MultiThreadLocker::unlock()
{
	sem_post(&sem);
}

MultiThreadLocker::~MultiThreadLocker()
{
	sem_destroy(&sem);
}
