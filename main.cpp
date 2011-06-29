#include <iostream>
#include <map>
#include <vector>
#include "structures.h"
#include "TVAdvertisment.h"


int main(int argc, char *argv[])
{
    TVAdvertisment tvadv;
    tvadv.fillAds ("ads.txt");
    tvadv.fillAdvertisers ("advertisers.txt");
    tvadv.fillPrograms ("programms.txt");
    tvadv.makeFirmReport ("frim.report.html");
    tvadv.makeGoodsReport ("goods.report.html");
    tvadv.makeProgrammReport ("programms.report.html");
    tvadv.makeTopCommodityReport ("top.commodity.report.html");
    tvadv.makeTopProgrammReport ("top.programm.report.html");
    return 0;
}
