/*
    Autor:  Alex Attila Wittmann
    MatrNr: 1326430
*/

#include <iostream>
#include <fstream>
#include <vector>

#include "myHeader.h"
using namespace std;


int main()
{
    vector<Konto*> myKontoPointerListe;              //reference_wrappers haben nicht funktioniert
    vector<int> KontonummerListe;

    my_read(myKontoPointerListe, KontonummerListe);                   //Datenbank initialisieren

    int menu, kontoID, iterFlagFound, whilenummer = 1;      //fuer switch, 2x fuer Punkt 2,3,4,5,6,7,8,9, und fuer while
    int pos = 0, saveToDeleteFlag;                          //fuer Punkt 2
    int neunummer, tempEUR, tempCent, kontoGleichFlag = 0;  //fuer Punkt 1
    char kontoName[50];                                     //fuer Punkt 1
    int kontoIDZiel, iterFlagFound2;                        //fuer Punkt 8
    vector<Konto*>::iterator iter;
    vector<Konto*>::iterator iter2;
    vector<int>::iterator intiter;

    cout << "***********************************************\
    \n*******EINFACHES DATENBANK FUER EIN BANK*******\
    \n*********ALEX ATTILA WITTMANN, 1326430*********\
    \n*******Technisches Programmieren in C++********\
    \n***********************************************" << endl;

    do
    {
        iterFlagFound = 0, iterFlagFound2 = 0, kontoGleichFlag = 0, saveToDeleteFlag = 0;
        cout << "\nMENU, bitte wahlen:\n\t1. Neue Konto oeffnen (erstellen)\
            \n\t2. Konto loeschen\n\t3. Geld einzahlen\n\t4. Geld abheben\
            \n\t5. Geld wechseln\n\t6. Kontoname aendern\n\t7. Bonusstufe aendern\
            \n\t8. Geld ueberweisen\n\t9. Konto zeigen\n\t10. Alle Konten zeigen\
            \n\t11. Programm abbrechen\
            \nIHRE WAHL: " << endl;
        cin >> menu;
        switch(menu)
        {
        case 1: //Neue Konto oeffnen (erstellen)
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> neunummer;

            for(intiter = KontonummerListe.begin(); intiter != KontonummerListe.end(); ++intiter)
            {
                if((*intiter) == neunummer)
                {
                    cout << "Kontonummer bereits in Datenbank!" << endl;
                    kontoGleichFlag = 1;
                }
            }
            if(kontoGleichFlag == 0)
            {
                cout << "Name der Kontoinhaber eingeben: " << endl;
                cin.ignore();
                cin.getline(kontoName, 50);
                kontoName[sizeof(kontoName) - 1] = 0;
                cout << "Einzahlung:\nEUR: " << endl;
                cin >> tempEUR;
                cout << "Cent: " << endl;
                cin >> tempCent;
                Konto *neuekonto = new Konto(neunummer, kontoName, tempEUR*100 + tempCent); //macht ein neues Objekt
                myKontoPointerListe.push_back(neuekonto);           //pointer wird gespeichert
                KontonummerListe.push_back(neunummer);              //Kontonummer wird gespeichert um duplicates zu vermeiden
            }
        }
        break;

        case 2: //Konto loeschen
        {
            if(Konto::kontoanzahle == 0)
            {
                cout << "Keine Konto in Datenbank!" << endl;
                pos = 0;
                break;
            }
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    saveToDeleteFlag = 1;
                    break;
                }
                else
                    pos++;
            }
            if(saveToDeleteFlag == 1)
            {
                cout << "Konto Nr. " << (*iter)->get_kontonummer() << " geloescht" << endl;
                delete myKontoPointerListe[pos];
                myKontoPointerListe.erase(myKontoPointerListe.begin() + pos);
                KontonummerListe.erase(KontonummerListe.begin() + pos);
            }
            else
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
            pos = 0;                // Wert zuruecksetzen damit naechstes mal wieder von 0 anfaengt
        }
        break;

        case 3: //Geld einzahlen
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    (*iter)->aendern_stand_pos();
                    iterFlagFound = 1;
                }
            }
            if (iterFlagFound == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
        }
        break;

        case 4: //Geld abheben
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    (*iter)->aendern_stand_neg();
                    iterFlagFound = 1;
                }
            }
            if (iterFlagFound == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
        }
        break;

        case 5: //Geld wechseln
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    (*iter)->geldwechsel();
                    iterFlagFound = 1;
                }
            }
            if (iterFlagFound == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
        }
        break;

        case 6: //Kontoname aendern
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    (*iter)->aendern_name();
                    iterFlagFound = 1;
                }
            }
            if (iterFlagFound == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
        }
        break;

        case 7: //Bonusstufe aendern
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    (*iter)->aendern_bonus();
                    iterFlagFound = 1;
                }
            }
            if (iterFlagFound == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
        }
        break;

        case 8: //Geld ueberweisen
        {
            cout << "Von welche Konto ueberweisen?: " << endl;
            cin >> kontoID;
            cout << "Auf welche Konto ueberweisen?: " << endl;
            cin >> kontoIDZiel;

            for(intiter = KontonummerListe.begin(); intiter != KontonummerListe.end(); ++intiter)
            {
                if((*intiter) == kontoID)
                    iterFlagFound = 1;
            }
            for(intiter = KontonummerListe.begin(); intiter != KontonummerListe.end(); ++intiter)
            {
                if((*intiter) == kontoIDZiel)
                    iterFlagFound2 = 1;
            }
            if ((iterFlagFound == 0) || iterFlagFound2 == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
            else
            {


                cout << "Weiviel ueberweisen:\nEUR: " << endl;
                cin >> tempEUR;
                cout << "Cent: " << endl;
                cin >> tempCent;


                for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
                {
                    if((*iter)->get_kontonummer() == kontoID)
                    {
                        (*iter)->aendern_stand_neg(tempEUR, tempCent);

                    }
                }

                for(iter2 = myKontoPointerListe.begin(); iter2 != myKontoPointerListe.end(); ++iter2)
                {
                    if((*iter2)->get_kontonummer() == kontoIDZiel)
                    {
                        (*iter2)->aendern_stand_pos(tempEUR, tempCent);
                        iterFlagFound2 = 1;
                    }
                }
            }
        }
        break;

        case 9: //Konto zeigen
        {
            cout << "Kontonummer eingeben: " << endl;
            cin >> kontoID;


            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
            {
                if((*iter)->get_kontonummer() == kontoID)
                {
                    cout <<"IM HERE"<<endl;
                    (*iter)->zeige();
                    iterFlagFound = 1;
                }
            }
            if (iterFlagFound == 0)
                cout << "FEHLER!! Konto nicht gefunden!" << endl;
        }
        break;

        case 10: //Alle Konten zeigen
        {

            for(iter = myKontoPointerListe.begin(); iter != myKontoPointerListe.end(); ++iter)
                (*iter)->zeige();
            cout << "\nAnzahl Kontos: " << Konto::kontoanzahle <<endl;
        }
        break;

        case 11: //Programm abbrechen
        {
            whilenummer = 0;
            cout << "Programm endet, auf Wiedersehen!" << endl;
            cout << "********************************" << endl;
        }
        break;

        default:
            cout << "Falsche eingabe, bitte versuchen Sie nochmals" << endl;
            break;
        }
    }
    while(whilenummer);
    my_write(myKontoPointerListe);
    return 0;
}

