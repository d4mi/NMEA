#ifndef __GPS_PARSER__
#define __GPS_PARSER__

#define NMEA_TYPE_SIZE     5    /* Size of NMEA type   */
#define TIME_FIELD_SIZE    6    /* Size of time field  */ 
#define MAX_FIELD          200         

#define DEBUG 0
#define debug(x) if (DEBUG) printf x;


enum NMEA_Type {
	NMEA_GPGGA,    /* Global Positioning System Fix Data             */
	NMEA_GPRMC,    /* Recommended minimum specific GPS/Transit data  */
	NMEA_UNKNOWN   /* Unknown type                                   */
};

/* returns type of given frame */
enum NMEA_Type NMEA_type(const char*, const size_t);

enum GPGGA_Section {
	GPGGA_TYPE,
	GPGGA_TIME,
	GPGGA_LATITUDE_VALUE,
	GPGGA_LATITUDE,
	GPGGA_LONGITUDE_VALUE,
	GPGGA_LONGITUDE,
	GPGGA_QUALITY,
	GPGGA_NUM_OF_SAT
};

struct Time
{
	char hour[3];
	char minute[3];
	char seconds[3];
};

/* GPGGA (Global Positioning System Fix Data) frame */
typedef struct _GPGGA 
{
	struct Time time;

#if 0 
	/* converted values */
	float         longitude;       /* e.g. 4124.8963, N                         */
    float         latitude;        /* e.g. 08151.6838, W                        */
    unsigned int  numOfSatellites; /* Number of Satellites                      */
    float         hdop;            /* Horizontal Dilution of Precision (HDOP)   */
    float         altitude;        /* Meters above mean sea level               */
    float         height;          /* Height of geoid above WGS84 ellipsoid     */
#else
	char         longitude_value[MAX_FIELD];       /* e.g. 4124.8963, N                         */
	char         longitude[MAX_FIELD];       /* e.g. 4124.8963, N                         */
    char         latitude_value[MAX_FIELD];        /* e.g. 08151.6838, W                        */
    char         latitude[MAX_FIELD];        /* e.g. 08151.6838, W                        */
    char         numOfSatellites[MAX_FIELD]; /* Number of Satellites                      */
    char         hdop[MAX_FIELD];            /* Horizontal Dilution of Precision (HDOP)   */
    char         altitude[MAX_FIELD];        /* Meters above mean sea level               */
    char         height[MAX_FIELD];          /* Height of geoid above WGS84 ellipsoid     */
#endif

} GPGGA;

GPGGA ParseGPGGA(const char*, const size_t);

enum GPRMC_Section {
	GPRMC_TYPE,
	GPRMC_TIME,
	GPRMC_VALIDITY,
	GPRMC_LATITUDE_VALUE,
	GPRMC_LATITUDE,
	GPRMC_LONGITUDE_VALUE,
	GPRMC_LONGITUDE,
	GPRMC_SPEED,
	GPRMC_COURSE,
	GPRMC_DATE
};

typedef struct _GPRMC 
{
	struct Time time;
	
	char         validity[MAX_FIELD];
	char         longitude_value[MAX_FIELD];    
	char         longitude[MAX_FIELD];       
    char         latitude_value[MAX_FIELD];     
    char         latitude[MAX_FIELD];       
    char         speed[MAX_FIELD];
    char         course[MAX_FIELD];   
    char         date[MAX_FIELD]; 
} GPRMC;

GPRMC ParseGPRMC(const char*, const size_t);

#endif

