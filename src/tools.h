/*
 * 	Copyright (c) 2016 Arkanite
 *
 *	
 *	tools.h
 *
 *
 */

 

/// DIRECTORY TOOLS ---------------------------------
void dir_create( const char *dir )
	{
	char dir_copy[0x400] = {0};
	snprintf( dir_copy, sizeof( dir_copy ) - 2, "%s", dir );
	dir_copy[strlen( dir_copy )] = '/';
	char *c;
	for ( c = dir_copy; *c; ++c )
		{
		if (*c == '/') { *c = '\0'; sceIoMkdir( dir_copy, 0777 ); *c = '/'; }
		}
	}

// DEBUGGING ----------------------------------------
void logcat_add( char *str1, char *str2, char *str3 )
	{
	FILE *lf 	= fopen( "ux0:/data/vitaAudio/debug.log", "a+" );
	if ( lf != NULL )
		{
		fprintf( lf, "%s%s%s", str1, str2, str3 );
		}
	else
		{
		FILE *lf 	= fopen( "ux0:/data/vitaAudio/debug.log", "ab+" );
		fprintf( lf, "%s%s%s", str1, str2, str3 );
		}
	fclose( lf );
	
	
	
	}
