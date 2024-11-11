#ifndef _ID_SCOPE_H_
#define _ID_SCOPE_H_

// класс для присвоения ид скоупам
// тут можно задать порог в кол-ве скоупов например, смотря по ид

#include <atomic>
#include <vector>

namespace Scopes
{
	std::atomic<size_t> IdScope::sourceId(0);

	class IdScope
	{
	public:
		IdScope(size_t maxSizeCur)
			: maxSize(maxSizeCur)
		{}

		size_t getId()
		{
			return sourceId++;
		}

	protected:
		static std::atomic<size_t>									sourceId;
		size_t														maxSize;						//  максимальное кол-во ид
		std::vector<size_t>											freeId;							// вектор уже освободившихся ид
	};
}

#endif /* _ID_SCOPE_H_ */