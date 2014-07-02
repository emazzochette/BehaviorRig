//
//  safe_queue.h
//
//  Thread safe queue based on generic C++ libraries. Designed
//  to be used as a producer/consumer queue.
//
//  Created by John Whitworth on 6/30/14.
//
//

#ifndef _safe_queue_h
#define _safe_queue_h
#define _AFXDLL

#include <queue>
#include <afxmt.h>


template <typename T> class safe_queue
{
    std::queue<T> queue;
    CMutex mtx;
	CSingleLock lock(&mtx);
    //std::condition_variable condv;
    
public:
    void add(T item) {
        lock.Lock(INFINITE);
        queue.push(item);
        //condv.notify_all();
        lock.Unlock();
    }
    
    T remove() {
        lock.Lock(INFINITE);
        if (!queue.empty()) {
            T item = queue.front();
			queue.pop();
        }
		lock.Unlock();
        return item;
    }
    
    int size() {
        lock.Lock(INFINITE);
        int size = queue.size();
        lock.Unlock();
        return size;
    }

	bool empty() {
		return (size() == 0);
	}
};

#endif
