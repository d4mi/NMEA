#include <stdio.h>
#include <stdlib.h>

#include "GpsParser.h"

void NMEA_Type_test()
{
	char gppga[] = "$GPGGA,115154.743,5628.050,N,00643.277,E,0,00,,,M,,M,,*49";
	char gprmc[] = "$GPRMC,115155.743,V,1952.534,S,01050.070,E,84.8,16.63,170115,,E*73";

	enum NMEA_Type type1 = NMEA_type(gppga + 1, sizeof(gppga) - 1);
	enum NMEA_Type type2 = NMEA_type(gprmc + 1, sizeof(gprmc) - 1);

	printf("GPGGA: %d. Expected: %d\n", (int) type1, (int)NMEA_GPGGA);	
	printf("GPRMC: %d. Expected: %d\n", (int) type2, (int)NMEA_GPRMC);
}

void ParseGPGGA_test()
{
	char gppga[] = "$GPGGA,115154.743,5628.050,N,00643.277,E,0,00,,,M,,M,,*49";

	ParseGPGGA(gppga, sizeof(gppga));
}

int main()
{
	NMEA_Type_test();
	ParseGPGGA_test();
}