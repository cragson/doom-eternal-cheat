#pragma once
#include <memory>
#include "../Osmium/Memory/Process/process.hpp"
#include "doom_cheat.hpp"

namespace Globals
{
	inline std::unique_ptr< doom_cheat > g_pCheat = std::make_unique< doom_cheat >();

	inline std::unique_ptr< process > g_pProcess = std::make_unique< process >();
}
