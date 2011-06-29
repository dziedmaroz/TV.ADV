#include "TVAdvertisment.h"
#include <iostream>
TVAdvertisment::TVAdvertisment()
{
}

bool TVAdvertisment::fillAds (string filename)
{
     ifstream fin (filename.c_str ());

     while (!fin.eof ())
     {
         Ad tmp;
         char* tmpStr = new char [500];
         fin.getline (tmpStr,500,'|');
         fin.getline (tmpStr,500,'|');
         tmp.date = tmpStr;
         if (tmp.date.length ()==0)
         {
             break;
         }
         fin.getline (tmpStr,500,'|');
         tmp.programmeTitle = tmpStr;
         fin.getline (tmpStr,500,'|');
         tmp.companyName = tmpStr;
         fin.getline (tmpStr,500,'|');
         tmp.commodity = tmpStr;
         fin.getline (tmpStr,500,'|');
         string s = tmpStr;
         tmp.length = strToInt (s);
         delete [] tmpStr;
         _ads.push_back (tmp);
     }     
     return true;
}

bool TVAdvertisment::fillAdvertisers (string filename)
{
    ifstream fin (filename.c_str ());
    while (!fin.eof ())
    {
        Advertiser tmp;
        char* tmpStr = new char [500];
        fin.getline (tmpStr,500,'|');
        fin.getline (tmpStr,500,'|');

        tmp.companyName=tmpStr;
        if (tmp.companyName.length ()==0)
        {
            break;
        }
        fin.getline (tmpStr,500,'|');
        string s = tmpStr;
        tmp.discount = strToDouble (s);
        _advertisers[tmp.companyName]=tmp.discount;

        delete [] tmpStr;
    }
    return true;
}

bool TVAdvertisment::fillPrograms (string filename)
{
    ifstream fin (filename.c_str ());

    while (!fin.eof ())
    {
        Programme tmp;
        char* tmpStr = new char [500];
        fin.getline (tmpStr,500,'|');
        fin.getline (tmpStr,500,'|');
        tmp.programmeTitle=tmpStr;
        if (tmp.programmeTitle.length ()==0)
        {
            break;
        }
        fin.getline (tmpStr,500,'|');
        tmp.chanel=tmpStr;
        fin.getline (tmpStr,500,'|');
        tmp.broadcastTime=tmpStr;
        fin.getline (tmpStr,500,'|');
        string s = tmpStr;
        tmp.price=strToDouble (s);
        _programs.push_back (tmp);
        delete [] tmpStr;
    }
    return true;
}

double TVAdvertisment::strToDouble (string str)
{
    int sign = 1 ;
    if (str[0]=='-')
    {
        sign = -1;
        str.begin ()++;
    }
    int pos = str.find ('.');
    double res =0;
    for (int i=0;i<str.length ();i++)
    {
        if ((str[i]>'9'||str[i]<'0') && i!=str.find ('.'))
        {
            return 0;
        }
        else
        {
            if (i!=str.find ('.'))
            {
                int degree;
                if (i<str.find ('.'))
                {
                    degree = str.find ('.')-1-i;
                }
                else
                {
                    degree = str.find ('.')-i;
                }
                res+=(str[i]-'0')*pow(10,degree);
            }
        }
    }
    return res*sign;
}

int TVAdvertisment::strToInt (string str)
{
    int sign=1;
    if (str[0]=='-')
    {
        sign = -1;
        str.begin ()++;
    }

    int res = 0;
    for (int i=0;i<str.length ();i++)
    {
        if (str[i]>'9'||str[i]<'0')
        {
            return 0;
        }
        else
        {
            res+=(str[i]-'0')*pow(10,str.length ()-i-1);
        }
    }
    return res*sign;
}

void TVAdvertisment::makeFirmReport (string filename)
{
    ofstream fout (filename.c_str ());
    fout<<"<html><head><title>Companies report</title></head>";

    for (map<string,double>::iterator i=_advertisers.begin ();i!=_advertisers.end ();i++)
    {
        string firmName = i->first;
        int imap [100];
        int imapTop = 0;
        for (int i=0;i<_ads.size ();i++)
        {
            if (_ads[i].companyName == firmName)
            {
               imap[imapTop]=i;
               imapTop++;
            }
        }
        fout<<"<h2>"<<firmName<<"</h2>";
        fout<<"<h3>Goods:</h2><table width=\"100%\">";
        fout<<"<tr><td align=left width=100px><b>Product</b></td><td align=center><b>Money</b></td><td align=right><b>Time</b></td></tr>";
        for (int i=0;i<imapTop;i++)
        {
            int time=0;
            double money = 0;
            totalMoneyAndTimeByGoodAndCompany (firmName,_ads[imap[i]].commodity,time,money);
            fout<<"<tr><td align=left><b>"<<_ads[imap[i]].commodity<<"</b></td><td align=center><i>"<<money<<"cr.</td><td align=right>"<<time<<" min</i></td></tr>";
        }
        fout<<"</table><hr>";
     }
    fout<<"</html>";
}

void TVAdvertisment::totalMoneyAndTimeByGoodAndCompany (string companyName, string good, int &time, double &money)
{

    for (int i=0;i<_ads.size ();i++)
    {
        if (_ads[i].companyName==companyName && _ads[i].commodity==good)
        {
            double timePrice = 0;
            for (int j=0;j<_programs.size ();j++)
            {
                if (_programs[j].programmeTitle==_ads[i].programmeTitle)
                {
                    timePrice=_programs[j].price;
                }
            }
            money+=_ads[i].length*timePrice - _ads[i].length*timePrice*_advertisers[companyName];
            time +=_ads[i].length;
        }
    }
}

void TVAdvertisment::makeGoodsReport (string filename)
{
    ofstream fout (filename.c_str ());
    typedef multimap<string,int> ProgrammTime;
    typedef map<string,ProgrammTime> GoodProgramm;
    GoodProgramm goodProgramm;
    for (int i=0;i<_ads.size ();i++)
    {
        ProgrammTime tmpPT;
        for (int j=0;j<_ads.size ();j++)
        {
            if (_ads[i].commodity == _ads[j].commodity)
            {
                tmpPT.insert (pair<string,int>(_ads[i].programmeTitle,_ads[i].length));
            }
        }
        goodProgramm[_ads[i].commodity]=tmpPT;
    }
    fout<<"<html><head><title>Goods report</title></head>";
    for (GoodProgramm::iterator i = goodProgramm.begin();i!=goodProgramm.end();i++)
    {
        int sum =0;
        fout<<"<h2>"<<i->first<<":</h2><table width=\"100%\"><tr><td align=left width=100px><b>Programme<b></td><td align=right><b>Ad time</b></td>";
        for (ProgrammTime::iterator j = i->second.begin();j!=i->second.end();j++)
        {
            fout<<"<tr><td align=left>"<<j->first<<"</td><td align=right>"<<j->second<<"</td></tr>";
        }
        fout<<"</table>";
    }
   fout<<"</html>";
}

void TVAdvertisment::makeProgrammReport (string filename)
{
    ofstream fout (filename.c_str ());
    fout<<"<html><head><title>Programms report</title></head>";
    for (int i=0;i<_programs.size ();i++)
        {
            fout<<"<h2>"<<_programs[i].programmeTitle<<":</h2><table width=100% border=1px><tr><td align=left><b>Firm<b></td><td align=right width=100px><b>Time</b></td><td align=right><b>Money</b></td>";
            for (int j=0;j<_ads.size ();j++)
            {
                if (_programs[i].programmeTitle==_ads[j].programmeTitle)
                {
                    fout<<"<tr><td align=left>"<<_ads[j].companyName<<"</td><td align=right>"<<_ads[j].length<<" min</td><td align=right><i>"<<_ads[j].length*_programs[i].price*(1-_advertisers[_ads[j].companyName])<<" cr.</i></td>";
                }
            }
            fout<<"</table>";
        }
    fout<<"</html>";
}

void TVAdvertisment::makeTopCommodityReport (string filename)
{
    map<string,int> goods;
    for (int i=0;i<_ads.size ();i++)
    {
        goods[_ads[i].commodity]=goods[_ads[i].commodity]+1;
    }
    string max = goods.begin ()->first;
    for (map<string,int>::iterator i=goods.begin ();i!=goods.end ();i++)
    {
        if (goods[max]<i->second) max = i->first;
    }

    ofstream fout (filename.c_str ());
    fout<<"<html><head><title>#1 product report</title></head>";
    fout<<"<table width=100% border=1px><tr><td>Programm</td><td>Time</td><td>Price</td></tr>";
    fout<<"<h3>#1 Product: "<<max<<"</h3>";
    for (int i=0;i<_ads.size ();i++)
    {
        if (_ads[i].commodity==max)
        {
            double price;
            for (int j=0;j<_programs.size ();j++)
            {
                if (_programs[j].programmeTitle == _ads[i].programmeTitle)
                {
                    price = _programs[j].price;
                }
            }
            fout<<"<tr><td>"<<_ads[i].programmeTitle<<"</td><td>"<<_ads[i].length<<" min</td><td>"<<price<<" cr.</td>";
        }
    }
    fout<<"</table></html>";
}

void TVAdvertisment::makeTopProgrammReport (string filename)
{
    map<string,int> programms;
    for (int i=0;i<_ads.size ();i++)
    {
        programms[_ads[i].programmeTitle]=programms[_ads[i].programmeTitle]+1;
    }

    string max = programms.begin ()->first;
    for (map<string,int>::iterator i=programms.begin ();i!=programms.end ();i++)
    {
        if (programms[max]<i->second) max = i->first;
    }
    ofstream fout (filename.c_str ());
    fout<<"<html><head><title>#1 programme report</title></head>";
    int ind=0;
    for (int i=0;i<_programs.size ();i++)
    {
        if (_programs[i].programmeTitle==max)
        {
            ind = i;
            break;
        }
    }
    fout<<"<h3>Programme info:</h3>";
    fout<<"<b>Title: </b>"<<_programs[ind].programmeTitle<<"<br>";
    fout<<"<b>Chanel: </b>"<<_programs[ind].chanel<<"<br>";
    fout<<"<b>Broadcast time: </b>"<<_programs[ind].broadcastTime<<"<br>";
    fout<<"<b>Ad price: </b><i>"<<_programs[ind].price<<" cr.</i><br>";

    double money =0 ;
    double time=0;
    for (int i=0;i<_ads.size ();i++)
    {
        if (_ads[i].programmeTitle == max)
        {
            time += _ads[i].length;
            money += _ads[i].length*_programs[ind].price*(1-_advertisers[_ads[i].companyName]);
        }
    }

    fout<<"<b>Income: </b><i>"<<money<<" cr.</i> <br>";
    fout<<"<b>Total ad time: </b>"<<time<<" min<br>";
    fout<<"</html>";
}
