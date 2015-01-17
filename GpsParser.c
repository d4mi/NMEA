#include <stdio.h>
#include <string.h>

#include "GpsParser.h"

enum NMEA_Type NMEA_type(const char* buffer, const size_t size)
{
	if( buffer && size >= NMEA_TYPE_SIZE )
	{
		if( !strncmp(buffer, "GPGGA", NMEA_TYPE_SIZE) )
		{
			return NMEA_GPGGA;
		}

		if( !strncmp(buffer, "GPRMC", NMEA_TYPE_SIZE) )
		{
			return NMEA_GPRMC;
		}
	}

	return NMEA_UNKNOWN;
}

static int CanRead(const char character)
{
	return ( isprint(character) &&
		     character != ','   &&
		     character != '*' );
}

static int ParseTime(const char* buffer, size_t size, struct Time* time)
{
	printf("Size: %d", (int)size );
	if( buffer && size >= TIME_FIELD_SIZE && time )
	{
		memcpy(time->hour,   buffer,     2);
		memcpy(time->minute, buffer + 2, 2);
		memcpy(time->minute, buffer + 4, 2);

		time->hour[2]    = '\0';
		time->minute[2]  = '\0';
		time->seconds[2] = '\0';

		printf("Hour: %s\n", time->hour );
		printf("Minute: %s\n", time->minute );
		printf("Seconds: %s\n", time->seconds );
	}

	return -1;
}

GPGGA ParseGPGGA(const char* buffer, const size_t size)
{
	GPGGA gppga;                    /* container for parsed GPGGA frame */
	const char *ptr     =  buffer;  /* pointer to current position      */
	unsigned int index  =  0;       /* current position                 */
	unsigned fieldSize  =  0;       /* size of current field            */

	while( *ptr && index < size )
	{
		const char* fieldStart = ptr;
		while(CanRead(*ptr++) && index++);
		ParseTime(fieldStart, index, &gppga.time);
	}

}