#ifndef SEM_H_
#define SEM_H_
#include <semaphore.h>

class MultiThreadLocker
{

private:
	sem_t sem;

public:
	MultiThreadLocker(int n);
	void lock();
	void unlock();
	~MultiThreadLocker();
};

#endif /* SEM_H_ */
