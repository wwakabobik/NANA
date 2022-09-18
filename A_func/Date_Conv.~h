#ifndef Date_ConvH
#define Date_ConvH
#include <vcl.h>

class DH_Converter {
private:
int ry,rm,rd,rh;
/*int a_years;
int a_months;
int a_days;
int a_hours;*/
int d_months, d_days, d_hours;
AnsiString MQuery;
AnsiString DQuery;
AnsiString HQuery;
public:
/*int MYear,MMonth; // CM
int DYear,DMonth,DDay; // CD
int HYear,HMonth,HDay,HHour; // CH*/
DH_Converter();
~DH_Converter();
void ConvertMonths(int,int,int,int);
void ConvertDays(int,int,int,int,int);
void ConvertHours(int,int,int,int,int,int);
AnsiString ReturnDQuery();
AnsiString ReturnMQuery();
AnsiString ReturnHQuery();
char* ReturnCDQuery();
char* ReturnCMQuery();
char* ReturnCHQuery();
};

#endif
 