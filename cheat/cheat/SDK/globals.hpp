#pragma once
#include <memory>
#include "../Cheat/cheat.hpp"
#include "Memory/Process/process.hpp"


namespace Globals
{
	inline std::unique_ptr< cheat > g_pCheat = std::make_unique< cheat >();

	inline std::unique_ptr< process > g_pProcess = std::make_unique< process >();
}
