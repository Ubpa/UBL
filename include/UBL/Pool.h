#pragma once

#include <vector>
#include <array>

namespace Ubpa {
	template<typename T>
	class Pool {
	public:
		Pool() = default;
		Pool(Pool&& pool) noexcept;
		~Pool();

		template<typename... Args>
		T* Request(Args&&... args);
		void Recycle(T* object);
		void Reserve(size_t n);
		void Clear();

	private:
		void NewBlock();

	private:
		static const size_t BLOCK_SIZE = 1024;
		using Block = std::array<T, BLOCK_SIZE>;

		std::vector<Block*> blocks;
		std::vector<T*> freeAdresses;
	};
}

#include "detail/Pool.inl"
