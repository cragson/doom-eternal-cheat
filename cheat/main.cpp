#include <iostream>
#include <Windows.h>

#include "SDK/globals.hpp"
#include "Utils/utils.hpp"

int main()
{
    SetConsoleTitleA( "Doom Eternal Cheat" );

	printf( "[+] Preparing the game process.." );

	while( !Globals::g_pProcess->setup_process( L"DOOMEternal" ) )
	{
		printf( "." );

		Sleep( 1420 );
	}
	printf( "done!\n" );

	printf( "[+] Dumped %.2lf MBs of images!\n", Globals::g_pProcess->get_map_size_in_mbytes() );

	printf( "[+] Scanning for signatures.." );

	while( !Globals::g_pCheat->setup_offsets() )
	{
		printf( "." );

		Sleep( 1420 );
	}
	printf( "done!\n" );

	Globals::g_pCheat->print_offsets();

	Globals::g_pCheat->setup_features();

	Globals::g_pCheat->print_features();

	while ( true )
	{
		Globals::g_pCheat->run();

		if ( utils::is_key_pressed( VK_END ) )
			break;

		Sleep( 3 );
	}

	Globals::g_pCheat->shutdown();
}

