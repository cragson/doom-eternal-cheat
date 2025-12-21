#pragma once
#include "../../Osmium/Cheat/Feature/feature.hpp"

class ft_free_upgrades : public feature
{

public:

	void on_disable() override;

	void on_enable() override;

	void on_first_activation() override;

	void tick() override;

	void on_render() override {}

	void on_shutdown() override {}
};