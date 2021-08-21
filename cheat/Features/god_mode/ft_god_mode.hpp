#pragma once

#include "../../Osmium/Cheat/Feature/feature.hpp"

class ft_god_mode : public feature
{
public:

	void tick() override;

	void on_enable() override;

	void on_disable() override;

	void on_first_activation() override;
};