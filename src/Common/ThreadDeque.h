#ifndef _THREAD_DEQUE_H_
#define _THREAD_DEQUE_H_

#include <mutex>
#include <condition_variable>

#include "IThreadDeque.h"

template <typename T>
class ThreadDeque: public IThreadDeque<T>
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
public:

	ThreadDeque() = default;

	virtual ~ThreadDeque() {}

    void push(T const& value)
	{
        {
            std::unique_lock<std::mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }

	bool istryPop(int dur)
	{
		std::unique_lock<std::mutex> lock(this->d_mutex);
		if (!this->d_condition.wait_for(lock,  std::chrono::milliseconds(dur), [=]{ return !this->d_queue.empty(); })) {
			return false;
		}
		return true;
	} 

	T pop(int dur)
	{
        std::unique_lock<std::mutex> lock(this->d_mutex);
        this->d_condition.wait_for(lock, std::chrono::milliseconds(dur), [=]{ return !this->d_queue.empty(); });
        T rc(std::move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
	} 
};

#endif /* _THREAD_DEQUE_H_ */