#pragma once
#include "framework.h"
#include <string>

namespace crypt {
	bool computeSHA256(LPCWSTR filename, std::string& szHash);
}
