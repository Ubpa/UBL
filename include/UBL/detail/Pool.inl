#pragma once

#include <unordered_set>

namespace Ubpa {
	template<typename T>
	Pool<T>::Pool(Pool&& pool) noexcept
		: blocks{ std::move(pool.blocks) },
		freeAdresses{ std::move(pool.freeAdresses) }
	{
		pool.blocks.clear();
		pool.freeAdresses.clear();
	}

	template<typename T>
	Pool<T>::~Pool() {
		Clear();
	}

	template<typename T>
	template<typename... Args>
	T* Pool<T>::Request(Args&&... args) {
		if (freeAdresses.empty())
			NewBlock();
		T* freeAdress = freeAdresses.back();
		new(freeAdress)T{ std::forward<Args>(args)... };
		freeAdresses.pop_back();
		return freeAdress;
	}

	template<typename T>
	void Pool<T>::Recycle(T* object) {
		object->~T();
		freeAdresses.push_back(object);
	}

	template<typename T>
	void Pool<T>::Reserve(size_t n) {
		size_t blockNum = n / BLOCK_SIZE + static_cast<size_t>(n % BLOCK_SIZE > 0);
		for (size_t i = blocks.size(); i < blockNum; i++)
			NewBlock();
	}

	template<typename T>
	void Pool<T>::Clear() {
		std::unordered_set<T*> freeAdressesSet(freeAdresses.begin(), freeAdresses.end());
		for (auto block : blocks) {
			for (size_t i = 0; i < BLOCK_SIZE; i++) {
				T* adress = block->data() + i;
				if (freeAdressesSet.find(adress) == freeAdressesSet.end())
					adress->~T();
			}
			free(block);
		}
		blocks.clear();
		freeAdresses.clear();
	}

	template<typename T>
	void Pool<T>::NewBlock() {
		auto block = (Block*)malloc(sizeof(Block)); // won't call constructor
		blocks.push_back(block);
		for (size_t i = 0; i < BLOCK_SIZE; i++)
			freeAdresses.push_back(block->data() + i);
	}
}
