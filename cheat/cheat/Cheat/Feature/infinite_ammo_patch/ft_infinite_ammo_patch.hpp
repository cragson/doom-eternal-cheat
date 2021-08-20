#pragma once
#include "../feature.hpp"
#include "../../../SDK/Includings/custom_data_types.hpp"

class ft_infinite_ammo_patch : public feature
{
	
public:

	void on_disable() override;

	void on_enable() override;

	void on_first_activation() override;

	void tick() override;

private:

	byte_vector m_original_bytes;
};
