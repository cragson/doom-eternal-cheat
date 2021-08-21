#include "doom_cheat.hpp"

#include "../Features/infinite_ammo_patch/ft_infinite_ammo_patch.hpp"
#include "globals.hpp"
#include "Offsets/offsets.hpp"
#include "../Utils/utils.hpp"

bool doom_cheat::setup_features()
{
	auto infinite_ammo = std::make_unique< ft_infinite_ammo_patch >();
	infinite_ammo->set_virtual_key_code( VK_NUMPAD1 );
	infinite_ammo->set_activation_delay( 420 );
	this->m_features.push_back( std::move( infinite_ammo ) );

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
	const auto msg = [](const std::string& name, const int16_t virtual_key, const bool sub = false)
	{
		if (sub)
			printf("\t %-20s -> %s\n", name.c_str(), utils::virtual_key_as_string(virtual_key).c_str());
		else
			printf("[>] %-25s-> %s\n", name.c_str(), utils::virtual_key_as_string(virtual_key).c_str());
	};

	msg("infinite ammo", VK_NUMPAD1);

	printf("\n");
}

void doom_cheat::print_offsets()
{
	printf("\n");

	const auto msg = [](const std::wstring& name, const std::uintptr_t value)
	{
		printf("[>] %-35ws -> 0x%llX\n", name.c_str(), value);
	};

	msg(L"Infinite Ammo Patch", Offsets::infinite_ammo_patch);

	printf("\n");
}


