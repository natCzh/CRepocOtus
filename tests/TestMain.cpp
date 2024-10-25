#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "src/Common/ThreadDeque.h"
#include "src/Common/IThreadDeque.h"
#include "src/Command/ICommand.h"


// пример пользования очередью
TEST(TEST1, test)
{
	ThreadDeque<int> queue;
	//std::shared_ptr<IThreadDeque<int> > queue_ptr = std::make_shared<ThreadDeque<int> >(queue);
	int v = 1;
	queue.push(v);
	int s;
	auto res = queue.pop(1);
	res = queue.pop(0);

	// queue_ptr->tryPop(v, 1);

	int sdfs = 0;
}

