#include "ft_god_mode.hpp"
#include "../../SDK/globals.hpp"
#include "../../SDK/Offsets/offsets.hpp"

void ft_god_mode::tick()
{
}

void ft_god_mode::on_enable()
{
	const auto game_image_base = Globals::g_pProcess->get_image_base(L"DOOMEternalx64vk.exe");

	if (!game_image_base)
		return;
	
	Globals::g_pProcess->write< char >( game_image_base + Offsets::god_mode_patch, 0xEB );
}

void ft_god_mode::on_disable()
{
	const auto game_image_base = Globals::g_pProcess->get_image_base(L"DOOMEternalx64vk.exe");

	if (!game_image_base)
		return;
	
	Globals::g_pProcess->write< char >( game_image_base + Offsets::god_mode_patch, 0x75 );
}

void ft_god_mode::on_first_activation()
{
}
