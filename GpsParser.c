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

static int ParseTime(const char* buffer, size_t size, struct Time* time)
{
	printf("Size: %d\n", (int)size );
	if( buffer && size >= TIME_FIELD_SIZE && time )
	{
		memcpy(time->hour,    buffer,     2);
		memcpy(time->minute,  buffer + 2, 2);
		memcpy(time->seconds, buffer + 4, 2);

		time->hour[2]    = '\0';
		time->minute[2]  = '\0';
		time->seconds[2] = '\0';

		debug(( "Hour: %s\n",    time->hour    ));
		debug(( "Minute: %s\n",  time->minute  ));
		debug(( "Seconds: %s\n", time->seconds ));
	}

	return -1;
}

static void ParseDefault(const char *ptr,
						 int *section,
						 unsigned int *fieldSize,
						 char *tempBuffer,
						 char *destination )
{
	if( *ptr == ',' )
	{
		tempBuffer[*fieldSize] = '\0';
		debug(( "Copy: %s Size: %d \n", tempBuffer, *fieldSize ));
		memcpy(destination, tempBuffer, *fieldSize + 1);

		*fieldSize = 0;
		(*section)++;
	}
	else if( *fieldSize < (MAX_FIELD - 1) )
	{
		tempBuffer[(*fieldSize)++] = *ptr;
	}
}

GPGGA ParseGPGGA(const char* buffer, const size_t size)
{
	GPGGA gppga;                       /* container for parsed GPGGA frame */
	const char *ptr        =  buffer;  /* pointer to current position      */
	unsigned int index     =  0;       /* current position                 */
	unsigned int fieldSize =  0;       /* size of current field            */

	enum GPGGA_Section section = GPGGA_TYPE; /* current section */
	char tempBuffer[MAX_FIELD];

	while( *ptr++ && index++ < size )
	{
		debug(("Current character: %c \n", *ptr));

		/* skip '$GPPGA' and quality */
		if( section == GPGGA_TYPE || section == GPGGA_QUALITY )
		{
			if( *ptr == ',' )
			{
				fieldSize = 0;
				section++;
				debug(( "\n\nSection up\n\n" ));
			}
		}

		/* capture time */
		else if( section == GPGGA_TIME )
		{
			if( fieldSize < TIME_FIELD_SIZE )
			{
				tempBuffer[fieldSize++] = *ptr;
			}

			if( *ptr == ',' )
			{
				ParseTime(tempBuffer, fieldSize, &gppga.time);
				fieldSize = 0;
				section++;
				debug(( "\n\nSection up\n\n" ));
			}
		}	

		/* capture latitude */
		else if( section == GPGGA_LATITUDE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gppga.latitude);
		}	

		else if( section == GPGGA_LATITUDE_VALUE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gppga.latitude_value);
		}	

		/* capture longitude */
		else if( section == GPGGA_LONGITUDE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gppga.longitude);
		}	

		else if( section == GPGGA_LONGITUDE_VALUE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gppga.longitude_value);
		}	

		/* capture number of satellites */
		else if( section == GPGGA_NUM_OF_SAT )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gppga.numOfSatellites);
		}

		debug(( "Section is: %d\n", (int) section));
	}

	return gppga;
}

GPRMC ParseGPRMC(const char* buffer, const size_t size)
{ 
	GPRMC gprmc;
	const char *ptr        =  buffer;  /* pointer to current position      */
	unsigned int index     =  0;       /* current position                 */
	unsigned int fieldSize =  0;       /* size of current field            */

	enum GPRMC_Section section = GPRMC_TYPE; /* current section */
	char tempBuffer[MAX_FIELD];

	while( *ptr++ && index++ < size )
	{
		debug(("Current character: %c \n", *ptr));

		/* skip '$GPPGA' and quality */
		if( section == GPRMC_TYPE )
		{
			if( *ptr == ',' )
			{
				fieldSize = 0;
				section++;
				debug(( "\n\nSection up\n\n" ));
			}
		}

		/* capture time */
		else if( section == GPRMC_TIME )
		{
			if( fieldSize < TIME_FIELD_SIZE )
			{
				tempBuffer[fieldSize++] = *ptr;
			}

			if( *ptr == ',' )
			{
				ParseTime(tempBuffer, fieldSize, &gprmc.time);
				fieldSize = 0;
				section++;
				debug(( "\n\nSection up\n\n" ));
			}
		}	

		/* capture latitude */
		else if( section == GPRMC_LATITUDE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.latitude);
		}	

		else if( section == GPRMC_LATITUDE_VALUE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.latitude_value);
		}	

		/* capture longitude */
		else if( section == GPRMC_LONGITUDE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.longitude);
		}	

		else if( section == GPRMC_LONGITUDE_VALUE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.longitude_value);
		}	

		else if( section == GPRMC_VALIDITY )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.validity);
		}

		else if( section == GPRMC_DATE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.date);
		}

		else if( section == GPRMC_SPEED )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.speed);
		}

		else if( section == GPRMC_COURSE )
		{
			ParseDefault(ptr, (int*)&section, &fieldSize, tempBuffer, gprmc.course);
		}

		debug(( "Section is: %d\n", (int) section));
	}

	return gprmc;
}