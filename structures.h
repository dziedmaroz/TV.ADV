#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
using namespace std;

struct Programme
{
    string programmeTitle;
    string chanel;
    string broadcastTime;
    double price;
};

struct Advertiser
{
   string companyName;
   double discount;
};

struct Ad
{
    string date;
    string programmeTitle;
    string companyName;
    string commodity;
    int length;
};
#endif // STRUCTURES_H
