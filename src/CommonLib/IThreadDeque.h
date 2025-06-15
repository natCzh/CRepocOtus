#ifndef _I_THREAD_DEQUE_H_
#define _I_THREAD_DEQUE_H_

#include <deque>

template <typename T>
class IThreadDeque
{
public:

	virtual ~IThreadDeque() {}

	virtual void push(T const& value) = 0;

	/// @params[in] dur - кол-во микросек ожидания
	virtual bool istryPop(int dur) = 0;
	virtual T pop(int dur) = 0;

	size_t getSize()
	{
		return d_queue.size();
	}

protected:
	std::deque<T>           d_queue;
};

#endif /* _I_THREAD_DEQUE_H_ */