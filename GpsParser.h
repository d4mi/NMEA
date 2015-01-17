#ifndef __GPS_PARSER__
#define __GPS_PARSER__

#define NMEA_TYPE_SIZE     5   /* Size of NMEA type   */
#define TIME_FIELD_SIZE    6   /* Size of time field  */            


enum NMEA_Type {
	NMEA_GPGGA,    /* Global Positioning System Fix Data             */
	NMEA_GPRMC,    /* Recommended minimum specific GPS/Transit data  */
	NMEA_UNKNOWN   /* Unknown type                                   */
};

/* returns type of given frame */
enum NMEA_Type NMEA_type(const char*, const size_t);


/* GPGGA (Global Positioning System Fix Data) frame */
typedef struct _GPGGA 
{
	struct Time
	{
		char hour[3];
		char minute[3];
		char seconds[3];
	} time;

	float         longitude;       /* e.g. 4124.8963, N                         */
    float         latitude;        /* e.g. 08151.6838, W                        */
    unsigned int  numOfSatellites; /* Number of Satellites                      */
    float         hdop;            /* Horizontal Dilution of Precision (HDOP)   */
    float         altitude;        /* Meters above mean sea level               */
    float         height;          /* Height of geoid above WGS84 ellipsoid     */

} GPGGA;

GPGGA ParseGPGGA(const char*, const size_t);

/* return 0 if character is valid */
static int CanRead(const char);
/* parse time field */
static int ParseTime(const char*, size_t, struct Time*);

#endif

