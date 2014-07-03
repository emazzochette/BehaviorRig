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

#include <windows.h>
#include <queue>


template <typename T> class safe_queue
{
    std::queue<T> queue;

public:
	HANDLE mtx;
    void add(T item) {
        WaitForSingleObject(mtx, INFINITE);
        queue.push(item);
        ReleaseMutex(mtx);
    }
    
    T remove() {
        WaitForSingleObject(mtx, INFINITE);
		T item;
        if (!queue.empty()) {
            item = queue.front();
			queue.pop();
        }
		ReleaseMutex(mtx);
        return item;
    }
    
    int size() {
        WaitForSingleObject(mtx, INFINITE);
        int size = queue.size();
        ReleaseMutex(mtx);
        return size;
    }

	bool empty() {
		return (size() == 0);
	}
};

#endif
