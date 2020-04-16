#include <UBL/Image.h>

#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;
using namespace Ubpa;

int main() {
	Image img(1024, 1024, 3);
	for (size_t j = 0; j < 1024; j++) {
		for (size_t i = 0; i < 1024; i++) {
			img.At<rgbf>(i, j) = { 1.f,0,1.f };
		}
	}
	if (!fs::exists("../data/test/00_image") || !fs::directory_entry("../data/test/00_image").is_directory())
		fs::create_directories("../data/test/00_image");
	img.Save("../data/test/00_image/rst0.png");
	img.Init("../data/test/00_image/rst0.png");
	for (size_t j = 0; j < 1024; j++) {
		for (size_t i = 0; i < 1024; i++) {
			img.At<rgbf>(i, j) += {0.f, 0.5f, 0.f};
		}
	}
	img.Save("../data/test/00_image/rst1.png");
	return 0;
}
