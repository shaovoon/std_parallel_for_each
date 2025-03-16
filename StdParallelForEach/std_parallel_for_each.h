// The MIT License (MIT)
// C++ Standard parallel for_each for Apple Clang 0.1.0
// Copyright (C) 2025, by Wong Shao Voon (shaovoon@yahoo.com)
//
// http://opensource.org/licenses/MIT

#pragma once
#include <memory>
#include <thread>
#include <vector>
#include <iterator>

namespace loop
{
	namespace execution
	{
		struct sequenced_policy {};
		struct parallel_policy {};

		inline constexpr sequenced_policy seq{};
		inline constexpr parallel_policy par{};
	}

	template<typename ForwardIt, typename Func>
	void for_each(execution::sequenced_policy, ForwardIt begin, ForwardIt end, Func f)
	{
		for(;begin != end; ++begin)
			f(*begin);
	}

	template<typename ForwardIt, typename Func>
	void for_each(execution::parallel_policy, ForwardIt begin, ForwardIt end, Func f)
	{
		int	numOfThreads = static_cast<int>(std::thread::hardware_concurrency());

		auto count = std::distance(begin, end);

		if ((int)(count) < numOfThreads)
			numOfThreads = (int)(count);

		const int elementPerThread = (int)(count) / numOfThreads;
		const int remainder = (int)(count) % numOfThreads;
		int beginIndex = 0;
		int elementCount = elementPerThread;

		std::vector<std::shared_ptr<std::thread>> threads;
		for (int j = 0; j < numOfThreads; ++j)
		{
			if (j == numOfThreads - 1)
				elementCount = elementPerThread + remainder;
			std::shared_ptr<std::thread> threadPtr =
				std::make_shared<std::thread>(
					[begin, beginIndex, elementCount, f]() -> void {
						ForwardIt it = begin;
						std::advance(it, beginIndex);
						for (int i = 0; i < elementCount; ++i, ++it)
						{
							f(*it);
						}
					});
			threads.emplace_back(threadPtr);
			beginIndex += elementPerThread;
		}

		for (auto& threadPtr : threads)
			threadPtr->join();
	}

} // ns loop