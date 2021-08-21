#pragma once

#include "../Osmium/Cheat/cheat.hpp"

class doom_cheat : public cheat
{

public:

	bool setup_features() override;
	bool setup_offsets() override;
	
	void run() override;
	void shutdown() override;

	void print_features() override;
	void print_offsets() override;
	
};