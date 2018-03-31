#include "GameLib\Framework.h"

namespace GameLib {
	void Framework::update() {
		static unsigned idx = 0;
		auto vram = videoMemory();

		vram[idx] += idx * 100;
		idx += 9973;
		idx %= (width() * height());
	}
}