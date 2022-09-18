#include "Date_Conv.h"
#include <string.h>
#include <vcl.h>

DH_Converter::DH_Converter()
{
/*DQuery=new char[2048];
HQuery=new char[2048];
MQuery=new char[2048];*/
AnsiString DQuery;
AnsiString HQuery;
AnsiString MQuery;
ry=0,rm=0,rd=0,rh=0;
//a_years=0; a_months=0; a_days=0; a_hours=0;
d_months=0, d_days=0, d_hours=0;
}

void DH_Converter::ConvertMonths(int a_years,int a_months,int in_p, int rs)
{
ry=0,rm=0,rd=0,rh=0;
//a_years=0; a_months=0; a_days=0; a_hours=0;
d_months=0, d_days=0, d_hours=0;
        //if (((a_months-in_p)<-11) || a_months<5)
        if (((a_months-in_p)<-11))
        {
        ry=a_years-2;
        rm=24+a_months-in_p;
        MQuery="select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" UNION select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry+1)+" UNION select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(a_years)+" AND s_month<"+AnsiString(a_months)+" LIMIT "+AnsiString(in_p);
        }
        else
        {
        ry=a_years-1;
        rm=12+a_months-in_p;
        MQuery="select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month>="+AnsiString(rm)+" UNION select id_station, s_year, s_month, s_level as a_level from HM_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(a_years)+" AND s_month<"+AnsiString(a_months)+" LIMIT "+AnsiString(in_p);
        }

}
void DH_Converter::ConvertDays(int a_years,int a_months,int a_days,int in_p,int rs)
{
ry=0,rm=0,rd=0,rh=0;
//a_years=0; a_months=0; a_days=0; a_hours=0;
d_months=0, d_days=0, d_hours=0;
        /* ONLY TESTING*///
        //int s_year; s_month; s_day; s_hour; // results
        d_hours=0;
                //d_days=a_days-(1-int(d_hours/24));
                d_days=a_days-in_p;
                if (d_days>1)
                {ry=a_years; rm=a_months; rd=d_days;}
                else
                        {
                        d_months=a_months-1;
                        if (d_months>0)
                                {
                                if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                                        {
                                        d_days=31+d_days;
                                        ry=a_years; rm=d_months; rd=d_days;
                                        }
                                else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                                        {
                                        d_days=30+d_days;
                                        ry=a_years; rm=d_months; rd=d_days;
                                        }
                                else if (d_months==2)
                                        {
                                        if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                                d_days=29+d_days;
                                        else
                                                d_days=28+d_days;
                                        ry=a_years; rm=d_months; rd=d_days;
                                        }
                                }
                        else // month a more !!!!!!!!!!!! here!/&
                                {
                                d_days=31+d_days;
                                d_months=12;
                                ry=a_years-1; rm=d_months; rd=d_days;
                                }
                        }

//ShowMessage(AnsiString(rd)+" "+AnsiString(a_days));
if ((a_days-in_p)<=0)
{
DQuery="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" UNION select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(a_years)+" AND s_month="+AnsiString(a_months)+" AND s_day<="+AnsiString(a_days)+" LIMIT "+AnsiString(in_p);
}
else
DQuery="select id_station, s_year, s_month, s_day, s_level as a_level from HD_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day>="+AnsiString(rd)+" LIMIT "+AnsiString(in_p);
}

void DH_Converter::ConvertHours(int a_years,int a_months,int a_days, int a_hours, int in_p, int rs)
{
ry=0,rm=0,rd=0,rh=0;
//a_years=0; a_months=0; a_days=0; a_hours=0;
d_months=0, d_days=0, d_hours=0;
        //ShowMessage(AnsiString(a_hours)+" "+AnsiString(in_p));
        d_hours=a_hours-in_p;
        if (d_hours>=0) // interval less than one day
                {ry=a_years; rm=a_months; rd=a_days; rh=d_hours;}
        else
        {
                d_days=a_days-(1-int(d_hours/24));
                if (d_days>1)
                        if (d_hours%24!=0)
                                {ry=a_years; rm=a_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours;}
                        else
                                {ry=a_years; rm=a_months; rd=d_days-1; rh=0;}
                else
                        {
                        d_months=a_months-1;
                        if (d_months>0)
                                {
                                if (d_months==3 || d_months==5 || d_months==7 || d_months==8 || d_months==10 || d_months==12)
                                        {
                                        d_days=31+d_days;
                                        if (d_hours%24!=0)
                                                {ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours;}
                                        else
                                                {ry=a_years; rm=d_months; rd=d_days-1; rh=0;}
                                        }
                                else if (d_months==4 || d_months==6 || d_months==9 || d_months==11)
                                        {
                                        d_days=30+d_days;
                                        if (d_hours%24!=0)
                                                {ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours;}
                                        else
                                                {ry=a_years; rm=d_months; rd=d_days-1; rh=0;}
                                        }
                                else if (d_months==2)
                                        {
                                        if (a_years%400==0 || ((a_years%4==0) && (a_years%100!=0)))
                                                d_days=29+d_days;
                                        else
                                                d_days=28+d_days;
                                        if (d_hours%24!=0)
                                                {ry=a_years; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours;}
                                        else
                                                {ry=a_years; rm=d_months; rd=d_days-1; rh=0;}
                                        }
                                }
                        else // month a more !!!!!!!!!!!! here!/&
                                {
                                d_days=31+d_days;
                                d_months=12;
                                if (d_hours%24!=0)
                                        {ry=a_years-1; rm=d_months; rd=d_days; rh=24*(1-int(d_hours/24))+d_hours;}
                                else
                                        {ry=a_years-1; rm=d_months; rd=d_days-1; rh=0;}
                                }
                        }

                }
if ((a_hours-in_p)<0)
HQuery="select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day="+AnsiString(rd)+" AND s_hour>"+AnsiString(rh)+" GROUP BY id_station, s_year, s_month, s_day, s_hour UNION select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(a_years)+" AND s_month="+AnsiString(a_months)+" AND s_day="+AnsiString(a_days)+" AND s_hour<="+AnsiString(a_hours)+" GROUP BY id_station, s_year, s_month, s_day, s_hour LIMIT "+AnsiString(in_p);
else
HQuery="select id_station, s_year, s_month, s_day, s_hour, avg(s_level) as a_level from H_DATA where id_station="+AnsiString(rs)+" AND s_year="+AnsiString(ry)+" AND s_month="+AnsiString(rm)+" AND s_day="+AnsiString(rd)+" AND s_hour>"+AnsiString(rh)+" GROUP BY id_station, s_year, s_month, s_day, s_hour LIMIT "+AnsiString(in_p);
}

DH_Converter::~DH_Converter()
{
//delete HQuery;
//delete DQuery;
//delete MQuery;
ry=0,rm=0,rd=0,rh=0;
//a_years=0; a_months=0; a_days=0; a_hours=0;
d_months=0, d_days=0, d_hours=0;
}

AnsiString DH_Converter::ReturnHQuery()
{
return HQuery;
}

AnsiString DH_Converter::ReturnMQuery()
{
return MQuery;
}

AnsiString DH_Converter::ReturnDQuery()
{
return DQuery;
}

char* DH_Converter::ReturnCMQuery()
{
return MQuery.c_str();
}

char* DH_Converter::ReturnCDQuery()
{
return DQuery.c_str();
}

char* DH_Converter::ReturnCHQuery()
{
return HQuery.c_str();
}
