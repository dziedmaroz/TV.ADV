#ifndef TVADVERTISMENT_H
#define TVADVERTISMENT_H

#include "structures.h"
#include <vector>
#include <map>
#include <deque>
#include <fstream>
#include <iterator>
#include <istream>
#include <cmath>


using namespace std;
class TVAdvertisment
{
    vector<Programme> _programs;
    map<string,double> _advertisers;
    vector<Ad> _ads;

    double strToDouble (string str);
    int strToInt (string str);

    void totalMoneyAndTimeByGoodAndCompany (string companyName, string good, int& time, double& money);
public:
    TVAdvertisment();
    bool fillPrograms (string filename);
    bool fillAdvertisers (string filename);
    bool fillAds (string filename);

    void makeFirmReport (string filename);
    void makeProgrammReport (string filename);
    void makeTopCommodityReport (string filename);
    void makeTopProgrammReport (string filename);
    void makeGoodsReport (string filename);



};

#endif // TVADVERTISMENT_H
