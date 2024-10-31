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

	ThreadDeque()
	{}

	ThreadDeque(const ThreadDeque &orig)
		: d_mutex(orig.d_mutex)
		, d_condition(orig.d_condition)
	{}

	virtual ~ThreadDeque() {}

    void push(T const& value)
	{
        {
            std::unique_lock<std::mutex> lock(this->d_mutex);
            IThreadDeque<T>::d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }

	bool istryPop(int dur)
	{
		std::unique_lock<std::mutex> lock(this->d_mutex);
		if (!this->d_condition.wait_for(lock,  std::chrono::milliseconds(dur), [=]{ return !this->IThreadDeque<T>::d_queue.empty(); })) {
			return false;
		}
		return true;
	} 

	T pop(int dur)
	{
        std::unique_lock<std::mutex> lock(this->d_mutex);
        this->d_condition.wait(lock, [=]{ return !this->IThreadDeque<T>::d_queue.empty(); });
        T rc(std::move(this->IThreadDeque<T>::d_queue.back()));
        this->IThreadDeque<T>::d_queue.pop_back();
        return rc;
	} 

	T getDataForIndex(size_t index)
	{
		std::unique_lock<std::mutex> lock(this->d_mutex);
		return d_queue[index];
	}
};

#endif /* _THREAD_DEQUE_H_ */