#include "doom_cheat.hpp"

#include "../Features/infinite_ammo_patch/ft_infinite_ammo_patch.hpp"
#include "globals.hpp"
#include "Offsets/offsets.hpp"
#include "../Utils/utils.hpp"
#include "../Features/god_mode/ft_god_mode.hpp"
#include "../Features/free_upgrades/ft_free_upgrades.hpp"
#include "../ft_god_mode.hpp"

bool doom_cheat::setup_features()
{
	auto infinite_ammo = std::make_unique< ft_infinite_ammo_patch >();
	infinite_ammo->set_name( L"Infinite Ammo" );
	infinite_ammo->set_virtual_key_code( VK_NUMPAD1 );
	infinite_ammo->set_activation_delay( 420 );
	infinite_ammo->enable_print_status();
	this->m_features.push_back( std::move( infinite_ammo ) );

	auto god_mode = std::make_unique< ft_god_mode >();
	god_mode->set_name( L"God Mode" );
	god_mode->set_virtual_key_code( VK_NUMPAD2 );
	god_mode->set_activation_delay( 420 );
	god_mode->enable_print_status();
	this->m_features.push_back( std::move( god_mode ) );

	auto free_upgrades = std::make_unique< ft_free_upgrades >();
	free_upgrades->set_name( L"Free Upgrades" );
	free_upgrades->set_virtual_key_code( VK_NUMPAD3 );
	free_upgrades->set_activation_delay( 420 );
	free_upgrades->enable_print_status();
	this->m_features.push_back( std::move( free_upgrades ) );
	
	return true;
}

bool doom_cheat::setup_offsets()
{
	if ( !Globals::g_pProcess->does_image_exist_in_map( L"DOOMEternalx64vk.exe" ) )
		return false;

	const auto game_image = Globals::g_pProcess->get_image_ptr_by_name( L"DOOMEternalx64vk.exe" );

	const auto ammo_patch = game_image->find_pattern( L"39 73 40 7D 07 03 FE" );
	if ( !ammo_patch )
		return false;

	Offsets::infinite_ammo_patch = ammo_patch + 3;

	
	const auto god_patch = game_image->find_pattern( L"84 C0 75 0C F3 0F 10 44 24 4C" );
	if( !god_patch )
		return false;

	Offsets::god_mode_patch = god_patch + 2;

	const auto upgrades_patch = game_image->find_pattern( L"41 8B E8 48 8B D9 44 01 84 B1" );
	if( !upgrades_patch )
		return false;

	Offsets::free_upgrades_patch = upgrades_patch + 7;

	return true;
}


void doom_cheat::run()
{
	for ( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if ( utils::is_key_pressed( feature->get_virtual_key_code() ) )
			feature->toggle();

		// let the feature tick() when active
		if ( feature->is_active() )
			feature->tick();
	}
}

void doom_cheat::shutdown()
{
	// disable every feature here
	for ( const auto& feature : this->m_features )
		if ( feature->is_active() )
			feature->disable();

	// clear image map here
	if ( Globals::g_pProcess )
		Globals::g_pProcess->clear_image_map();
}

void doom_cheat::print_features()
{
	printf("\n");

	printf("Feature-Name -> Feature-Hotkey\n");

	for( const auto & feature : this->m_features )
		printf( "[>] %-25ws -> %s\n", feature->get_name().c_str(), utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str() );
	msg("infinite ammo", VK_NUMPAD1);
	msg( "god mode", VK_NUMPAD2);
	for( const auto & feature : this->m_features )
		printf( "[>] %-25ws -> %s\n", feature->get_name().c_str(), utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str() );

	printf("\n");
}

void doom_cheat::print_offsets()
{
	printf("\n");

	const auto msg = [](const std::wstring& name, const std::uintptr_t value)
	{
		printf("[>] %-35ws -> 0x%08X\n", name.c_str(), value );
	};

	msg( L"Infinite Ammo Patch", Offsets::infinite_ammo_patch );
	msg( L"God mode Patch", Offsets::god_mode_patch );
	msg( L"Free Upgrades", Offsets::free_upgrades_patch );
	msg(L"Infinite Ammo Patch", Offsets::infinite_ammo_patch);
	msg( L"God mode Patch", Offsets::god_mode_patch );
	msg( L"Infinite Ammo Patch", Offsets::infinite_ammo_patch );
	msg( L"God mode Patch", Offsets::god_mode_patch );
	msg( L"Free Upgrades", Offsets::free_upgrades_patch );

	printf("\n");
}


