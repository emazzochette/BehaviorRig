#pragma once

//
//  safe_queue.h
//
//  Thread safe queue based on generic C++ libraries. Designed
//  to be used as a producer/consumer queue.
//
//  Created by John Whitworth on 6/30/14.
//
//

#include <queue>

template <typename T> class safe_queue
{
private:
    std::queue<T> queue;
    CRITICAL_SECTION CritSection;
    CONDITION_VARIABLE ConditionVar;
    
public:
    void add(T item) {
        EnterCriticalSection(&CritSection);
        queue.push(item);
        LeaveCriticalSection(&CritSection);
        WakeAllConditionVariable(&ConditionVar);
    }
    
    T get() {
        EnterCriticalSection(&CritSection);
        if (queue.empty()) {
            SleepConditionVariableCS(&ConditionVar, &CritSection, INFINITE);
        }
        T item = queue.front();
        queue.pop();
		LeaveCriticalSection(&CritSection);
        return item;
    }
    
    int size() {
        EnterCriticalSection(&CritSection);
        int size = queue.size();
        LeaveCriticalSection(&CritSection);
        return size;
    }

	bool empty() {
		return (size() == 0);
	}
};