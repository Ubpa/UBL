#pragma once

namespace Ubpa {
	template<typename T, typename>
	T& Image::At(size_t x, size_t y) {
		assert(T::N == channel);
		return reinterpret_cast<T&>(At(x, y, 0));
	}
}
