#pragma once

#include <UGM/rgba.h>
#include <UGM/point.h>

#include <UDP/Basic/Read.h>

#include <string>

namespace Ubpa {
	class Image {
	public:
		Read<Image, float*> data{ nullptr };
		Read<Image, size_t> width{ static_cast<size_t>(0) };
		Read<Image, size_t> height{ static_cast<size_t>(0) };
		Read<Image, size_t> channel{ static_cast<size_t>(0) };

		Image() = default;
		~Image();
		Image(const std::string& path);
		Image(size_t width, size_t height, size_t channel);
		Image(size_t width, size_t height, size_t channel, const float* data);
		Image(Image&& image) noexcept;
		Image(const Image& image);
		Image& operator=(Image&& image) noexcept;
		Image& operator=(const Image& image);

		bool Init(const std::string& path);
		void Init(size_t width, size_t height, size_t channel);
		void Init(size_t width, size_t height, size_t channel, const float* data);
		
		template<typename T, // float, rgbf or rgbaf
			typename = std::enable_if_t<std::is_same_v<T, float> || std::is_same_v<T, rgbf> || std::is_same_v<T, rgbaf>>>
		void SetAll(const T& color);
		// png, bmp, tga, jpg, hdr
		bool Save(const std::string& path) const;
		void Clear();

		bool IsValid() const noexcept;

		float& At(size_t x, size_t y, size_t c);
		const float& At(size_t x, size_t y, size_t c) const;
		const rgbaf At(size_t x, size_t y) const;
		template<typename T, // float, rgbf or rgbaf
			typename = std::enable_if_t<std::is_same_v<T, float> || std::is_same_v<T, rgbf> || std::is_same_v<T, rgbaf>>>
		T& At(size_t x, size_t y);

		const rgbaf SampleNearest(const pointf2& uv) const;
		const rgbaf SampleLinear(const pointf2& uv) const;
	};
}

#include "detail/Image.inl"
