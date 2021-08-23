#include "ft_free_upgrades.hpp"
#include "../../SDK/globals.hpp"
#include "../../SDK/Offsets/offsets.hpp"

void ft_free_upgrades::on_disable()
{
	const auto game_image_base = Globals::g_pProcess->get_image_base( L"DOOMEternalx64vk.exe" );

	if (!game_image_base)
		return;

	Globals::g_pProcess->write< char >( game_image_base + Offsets::free_upgrades_patch, 0x01 );
}

void ft_free_upgrades::on_enable()
{
	const auto game_image_base = Globals::g_pProcess->get_image_base( L"DOOMEternalx64vk.exe" );

	if ( !game_image_base )
		return;

	Globals::g_pProcess->write< char >( game_image_base + Offsets::free_upgrades_patch, 0x29 );
}

void ft_free_upgrades::on_first_activation()
{
}

void ft_free_upgrades::tick()
{
}
