#include "ft_infinite_ammo_patch.hpp"
#include "../../../SDK/globals.hpp"
#include "../../../SDK/Memory/Offsets/offsets.hpp"

void ft_infinite_ammo_patch::on_disable()
{
	if ( this->m_original_bytes.empty() )
		return;

	const auto game_image_base = Globals::g_pProcess->get_image_base( L"DOOMEternalx64vk.exe" );

	if ( !game_image_base )
		return;

	for( size_t i = 0; i < this->m_original_bytes.size(); i++ )
		Globals::g_pProcess->write< std::byte >( game_image_base + Offsets::infinite_ammo_patch + i, this->m_original_bytes.at( i )  );
}

void ft_infinite_ammo_patch::on_enable()
{
	if( this->m_original_bytes.empty() )
		return;
	
	const auto game_image_base = Globals::g_pProcess->get_image_base( L"DOOMEternalx64vk.exe" );

	if( !game_image_base )
		return;
	
	Globals::g_pProcess->nop_bytes( game_image_base + Offsets::infinite_ammo_patch, 9 );
	Globals::g_pProcess->write< uint64_t >( game_image_base + Offsets::infinite_ammo_patch, 0x90000006664043C7 );
}

void ft_infinite_ammo_patch::on_first_activation()
{
	const auto game_image_base = Globals::g_pProcess->get_image_base( L"DOOMEternalx64vk.exe" );

	if( !game_image_base )
	{
		printf( "[!] Could not retrieve original bytes, disabling this feature!\n" );
		return;
	}

	for( size_t i = 0; i < 9; i++ )
		this->m_original_bytes.push_back( Globals::g_pProcess->read< std::byte >( game_image_base + Offsets::infinite_ammo_patch + i ) );
}

void ft_infinite_ammo_patch::tick()
{
}
