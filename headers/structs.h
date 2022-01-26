int StructRead();
void StructWrite();
void StructPrint();
void StructSearch();
void StructAdd();
void StructRemove();
void StructModify();
void StructReturn();
int CheckAvailability();
float FlightTime();
void Finance();
void GetsLink();
float WaitTime();
float GetsTotalFlightTime();
float GetsTotalWaitTime();
int CheckSeats();
int FreeSeats();
float TicketsPrice();
void Link();

typedef struct
{
    char Name[99];
    char City[99];
    char IATA[3];
    int Altitude;
} Airport;

typedef struct
{
    char Plate[7];
    char Brand[99];
    char Model[99];
    int Seats;
    int CruisingSpeed;
    float AverageFuelConsumption;
} Airplane;

// FIXME swap this struct for a string to reduce code length in some functions
typedef struct
{
    int Day;
    int Month;
    int Year;
    int Hour;
    int Minute;
} Date;

typedef struct
{
    char FlightNumber[99];
    Date Departure;
    Date Arrival;
    char OriginIATA[99];
    char DestinyIATA[99];
    char AirplanePlate[99];
} Flight;

typedef struct
{
    char FlightNumber[99];
    char Seat[99];
    float Distance;
    float Price;
    char Name[99];
    int NIF;
} Ticket;