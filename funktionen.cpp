/*
    Autor:  Alex Attila Wittmann
    MatrNr: 1326430
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <cmath>

#include "myHeader.h"
using namespace std;



int Konto::kontoanzahle = 0;

/* ******************KONSTRUKTORS****************/

Konto::Konto()
{
    kontoanzahle++;
}

Konto::Konto(int nummer, const char *name, int einzahlung)
{
    kontonummer = nummer;
    kontostand = einzahlung;
    kontobonus = NORMAL;

    strncpy(kontoname, name, sizeof(kontoname) - 1);
    kontoname[sizeof(kontoname) - 1] = 0;

    kontoanzahle++;
}
/* *********************DESTRUKTOR*****************/
Konto::~Konto()
{
    kontoanzahle--;
}
/* ******************FUNKTIONS*********************/
void Konto::zeige()
{
    cout << "Kontonummer: " << kontonummer << "\nKonto Name: " <<
         kontoname << "\nKontostand: " << kontostand/100 << "EUR " <<
         kontostand % 100 << "Cent\nBonusgrad: "
         << bonusstrings[kontobonus] << "\n" <<endl;

}

void Konto::aendern_name()
{
    cout << "Neue Name eingeben: " << endl;
    cin.ignore();
    cin.getline(kontoname, 50);
}

void Konto::aendern_stand_pos(int paramEUR, int paramCent)
{
    if((paramEUR == 0) && (paramCent == 0))     //fuer Geldeinzahlung
    {
        int tempEUR = 0, tempCent = 0;
        cout << "Einzahlung:\nEUR: " << endl;
        cin >> tempEUR;
        cout << "Cent: " << endl;
        cin >> tempCent;
        if((tempEUR < 0) || (tempCent < 0))
        {

            cout << "Falsche Eingabe, EUR oder Cent war kleiner 0! EUR: " << tempEUR
                 << " Cent: " << tempCent  << endl;
            return;
        }
        else
            kontostand += 100 * tempEUR + tempCent;
    }

    else                                        //fuer Ueberweisung
    {
        if((paramEUR < 0) || (paramCent < 0))
        {

            cout << "Falsche Eingabe, EUR oder Cent war kleiner 0! EUR: " << paramEUR
                 << " Cent: " << paramCent  << endl;
            return;
        }
        else
            kontostand += 100 * paramEUR + paramCent;
    }

}

void Konto::aendern_stand_neg(int paramEUR, int paramCent)
{
    if((paramEUR == 0) && (paramCent == 0))     //fuer Geldeinzahlung
    {
        int tempEUR = 0, tempCent = 0;
        cout << "Abhebung:\nEUR: " << endl;
        cin >> tempEUR;
        cout << "Cent: " << endl;
        cin >> tempCent;
        if((tempEUR < 0) || (tempCent < 0))
        {

            cout << "Falsche Eingabe, EUR oder Cent war kleiner 0! EUR: " << tempEUR
                 << " Cent: " << tempCent  << endl;
            return;
        }
        else if ((100* tempEUR + tempCent) > kontostand)
        {
            cout << "Nicht genug Geld auf Konto! Kontostand: " << kontostand /100
                 <<"EUR " << kontostand % 100 << "Cent\nAbgehobene Summe: " << tempEUR
                 <<" EUR " <<tempCent<< " Cent" <<endl;
            return;
        }
        else
            kontostand -= 100 * tempEUR + tempCent;
    }

    else                                        //fuer Ueberwesung
    {
        if((paramEUR < 0) || (paramCent < 0))
        {

            cout << "Falsche Eingabe, EUR oder Cent war kleiner 0! EUR: " << paramEUR
                 << " Cent: " << paramCent  << endl;
            return;
        }
        else if ((100* paramEUR + paramCent) > kontostand)
        {
            cout << "Nicht genug Geld auf Konto! Kontostand: " << kontostand /100
                 <<"EUR " << kontostand % 100 << "Cent\nAbgehobene Summe: " << paramEUR
                 <<" EUR " <<paramCent<< " Cent" <<endl;
            return;
        }
        else
            kontostand -= 100 * paramEUR + paramCent;
    }

}

void Konto::geldwechsel()
{
    int tempEUR = 0, tempCent = 0, wechsel;
    float neuHaupt, neuWechsel;
    cout << "Abhebung von Konto:\nEUR: " << endl;
    cin >> tempEUR;
    cout << "Cent: " << endl;
    cin >> tempCent;
    if((tempEUR < 0) || (tempCent < 0))
    {

        cout << "Falsche Eingabe, EUR oder Cent war kleiner 0! EUR: " << tempEUR
             << " Cent: " << tempCent  << endl;
        return;
    }
    else if ((100* tempEUR + tempCent) > kontostand)
    {
        cout << "Nicht genug Geld auf Konto! Kontostand: " << kontostand /100
             <<"EUR " << kontostand % 100 << "Cent\nAbgehobene Summe: " << tempEUR
             <<" EUR " <<tempCent<< " Cent" <<endl;
        return;
    }
    else
    {
        cout << "Welche Waehrung moechten Sie haben? (Zahl eingeben): " << endl;        //Daten aus oenb.at
        cout << "1. USD (US-Dollar) fuer 1,09\n2. GBP (Britisches Pfund) fuer 0,85\
        \n3. JPY (Japanischer Yen) fuer 123,3\n4. CHF (Schweizer Franken) fuer 1,08\
        \n5. HUF (Ungarische Forint) fuer 311.5" << endl;
        cout << "Ihre Wahl:" << endl;
        cin >> wechsel;

        switch(wechsel)
        {
        case 1:
        {
            neuHaupt = (100*tempEUR + tempCent) * 1.09 / 100;
            neuWechsel = ((100*tempEUR + tempCent) * 1.09) - (floor(neuHaupt) * 100);
            cout << "Fuer " << tempEUR << "EUR " << tempCent << "Cent bekommen Sie "
                 << floor(neuHaupt) << "Dollar " << round(neuWechsel) << "Cent." <<endl;
            kontostand -= 100 * tempEUR + tempCent;
        }
        break;

        case 2:
        {
            neuHaupt = (100*tempEUR + tempCent) * 0.85 / 100;
            neuWechsel = ((100*tempEUR + tempCent) * 0.85) - (floor(neuHaupt) * 100);
            cout << "Fuer " << tempEUR << "EUR " << tempCent << "Cent bekommen Sie "
                 << floor(neuHaupt) << "Pfund " << round(neuWechsel) << "Pence." <<endl;
            kontostand -= 100 * tempEUR + tempCent;
        }
        break;

        case 3:
        {
            neuHaupt = (100*tempEUR + tempCent) * 123.3 / 100;
            neuWechsel = ((100*tempEUR + tempCent) * 123.3) - (floor(neuHaupt) * 100);
            cout << "Fuer " << tempEUR << "EUR " << tempCent << "Cent bekommen Sie "
                 << floor(neuHaupt) << "YEN " << round(neuWechsel) << "Sen." <<endl;
            kontostand -= 100 * tempEUR + tempCent;
        }
        break;

        case 4:
        {
            neuHaupt = (100*tempEUR + tempCent) * 1.08 / 100;
            neuWechsel = ((100*tempEUR + tempCent) * 1.08) - (floor(neuHaupt) * 100);
            cout << "Fuer " << tempEUR << "EUR " << tempCent << "Cent bekommen Sie "
                 << floor(neuHaupt) << "Franken " << round(neuWechsel) << "Rappen." <<endl;
            kontostand -= 100 * tempEUR + tempCent;
        }
        break;

        case 5:
        {
            neuHaupt = (100*tempEUR + tempCent) * 311.5 / 100;
            //neuWechsel = ((100*tempEUR + tempCent) * 311.5) - (floor(neuHaupt) * 100);    //Forint hat keine Unterteilung
            cout << "Fuer " << tempEUR << "EUR " << tempCent << "Cent bekommen Sie "
                 << floor(neuHaupt) << "Forint." <<endl;
            kontostand -= 100 * tempEUR + tempCent;
        }
        break;

        default:
            cout <<"Falsche Eingabe, bitte versuchen Sie noch einmal!" << endl;
        }
    }
}

void Konto::aendern_bonus()
{
    int tempBonus = 0;
    cout << "Neue Bonusstufe eingeben (Zahl):\
    \n0 fuer NORMAL\n1 fuer SILBER\n2 fuer GOLD\
    \n3 fuer PLATIN" << endl;
    cout << "Ihre Wahl:" << endl;
    cin >> tempBonus;

    switch(tempBonus)
    {
    case 0:
        kontobonus = NORMAL;
        break;
    case 1:
        kontobonus = SILBER;
        break;
    case 2:
        kontobonus = GOLD;
        break;
    case 3:
        kontobonus = PLATIN;
        break;
    default:
        cout << "Falsche Eingabe, bitte versuchen Sie noch einmal!" << endl;
    }
}

/* **************GETTERS-SETTERS*****************/
int Konto::get_kontonummer()
{
    return kontonummer;
}

char* Konto::get_kontoname()
{
    return kontoname;
}

int Konto::get_kontostand()
{
    return kontostand;
}

Konto::Bonus Konto::get_kontobonus()
{
    return kontobonus;
}

void Konto::set_kontonummer(int parKontoNummer)
{
    kontonummer = parKontoNummer;
}

void Konto::set_kontoname(char* parKontoName)
{
    strncpy(kontoname, parKontoName, sizeof(kontoname) - 1);
    kontoname[sizeof(kontoname) - 1] = 0;
}

void Konto::set_kontostand(int parKontoStand)
{
    kontostand = parKontoStand;
}

void Konto::set_kontobonus(Konto::Bonus parKontoBonus)
{
    kontobonus = parKontoBonus;
}

/* **********NON-CLASS FUNCTIONS****************/
void my_write(vector<Konto*>& kontoListe)
{
    ofstream outFile;
    outFile.open(filename);
    if(!outFile)
    {
        cerr << "File koennte nicht geoeffnet werden!" << endl;
        return;
    }
    for(const auto& temp: kontoListe)
    {
        outFile << temp->get_kontonummer() << " " << temp->get_kontoname() <<
                " " << temp->get_kontostand() << " " << temp->get_kontobonus() << "\n";
    }
    outFile.close();
}


void my_read(vector<Konto*>& KontoList, vector<int>& NummerList)
{
    ifstream inFile;
    inFile.open(filename);
    if (!inFile)
    {
        cerr << "File koennte nicht geoeffnet werden!" << endl;
    }
    Konto temp;
    int helpKontoNummer, helpKontoStand, helpKontoBonus;
    char helpKontoName[50];
    while (inFile >> helpKontoNummer >> helpKontoName >> helpKontoStand >> helpKontoBonus)
    {
        Konto::Bonus helpbonus = (Konto::Bonus) helpKontoBonus;
        Konto *asd = new Konto(helpKontoNummer, helpKontoName, helpKontoStand);
        asd->set_kontobonus(helpbonus);
        KontoList.push_back(asd);
        NummerList.push_back(helpKontoNummer);
    }
    /*
    for(const auto& temp: KontoList)       // fuer debugging
    {
        cout << temp->get_kontonummer() << " " << temp->get_kontoname() <<
             " " << temp->get_kontostand() << "\n" << endl;
    }
    */
}
