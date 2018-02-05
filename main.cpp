#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <string>

using namespace std;

struct Adresat
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch (numerPojedynczejDanejAdresata)
            {
            case 1:
                adresat.id = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 3:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
        pojedynczaDanaAdresata = "";
        numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

void wczytajOsobyZPliku (vector <Adresat> &adresaci)
{
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    fstream plik;

    plik.open("KsiazkaAdresowa.txt", ios::in);
    if (plik.good() == true)
    {
    while(getline(plik, daneJednegoAdresataOddzielonePionowymiKreskami))
    {
        adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
        adresaci.push_back(adresat);
    }
    plik.close();
    }
}

void dopiszAdresataDoPliku(Adresat adresat)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << adresat.id << "|" << adresat.imie << "|"  << adresat.nazwisko << "|"  << adresat.numerTelefonu << "|"  << adresat.email << "|"  << adresat.adres << "|"  << endl;

        plik.close();

        cout << "Osoba zostala dodana." << endl;
        system("pause");
    }
    else
    {
        cout << "Nie mozna otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale (string daneAdresata)
{
    for (int i = 0; i < daneAdresata.length(); i++)
    {
        if (i == 0)
        {
            daneAdresata[i] = toupper(daneAdresata[i]);
        }
        else if (i > 0)
        {
            daneAdresata[i] = tolower(daneAdresata[i]);
        }
    }
    return daneAdresata;
}

void dodajOsobe (vector <Adresat> &adresaci)
{
    Adresat adresat;

    system("cls");
    cout << ">>> Dodawanie nowego adresata <<<" << endl;

    if (adresaci.empty() == true)
        {
            adresat.id = 1;
        }
    else{
            adresat.id = adresaci.back().id + 1;
        }

    cout << "Podaj imie: ";
    cin >> adresat.imie;
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.imie);

    cout << "Podaj nazwisko: ";
    cin >> adresat.nazwisko;
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);

    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, adresat.numerTelefonu);

    cout << "Podaj email: ";
    cin >> adresat.email;

    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adresat.adres);
    adresat.adres = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.adres);

    adresaci.push_back(adresat);
    dopiszAdresataDoPliku(adresat);
}

void wyszukajAdresatowPoImieniu(vector <Adresat> &adresaci)
{
    string imiePoszukiwanegoAdresata;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW PO IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        cin >> imiePoszukiwanegoAdresata;
        //

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> imie == imiePoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:             " << itr -> id << endl;
                cout << "Imie:           " << itr -> imie << endl;
                cout << "Nazwisko:       " << itr -> nazwisko << endl;
                cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
                cout << "Email:          " << itr -> email << endl;
                cout << "Adres:          " << itr -> adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        }
        else{
            cout << endl << "Ilosc adresatow z imieniem: " << imiePoszukiwanegoAdresata;
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system ("pause");
}

void wyszukajAdresatowPoNazwisku(vector <Adresat> &adresaci)
{
    string nazwiskoPoszukiwanegoAdresata;
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty())
    {
        cout << ">>> WYSZUKIWANIE ADRESATOW PO NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        cin >> nazwiskoPoszukiwanegoAdresata;
        //

        for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
        {
            if (itr -> nazwisko == nazwiskoPoszukiwanegoAdresata)
            {
                cout << endl;
                cout << "Id:             " << itr -> id << endl;
                cout << "Imie:           " << itr -> imie << endl;
                cout << "Nazwisko:       " << itr -> nazwisko << endl;
                cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
                cout << "Email:          " << itr -> email << endl;
                cout << "Adres:          " << itr -> adres << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0)
        {
            cout << endl << "Nie ma adresatow z tym nazwiskiem w ksiazce adresowej" << endl;
        }
        else{
            cout << endl << "Ilosc adresatow z nazwiskiem: " << nazwiskoPoszukiwanegoAdresata;
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system ("pause");
}

void zapiszWszystkichAdresatowDoPlikuTekstowego (vector <Adresat> &adresaci)
{
    fstream plik;
    plik.clear();
    plik.open("KsiazkaAdresowa.txt", ios::out);

    if (plik.good() == true)
    {
        for ( unsigned i = 0; i < adresaci.size(); i++)
        {
        plik << adresaci[i].id << "|" << adresaci[i].imie << "|"  << adresaci[i].nazwisko << "|"  << adresaci[i].numerTelefonu << "|"  << adresaci[i].email << "|"  << adresaci[i].adres << "|"  << endl;

        plik.close();
        }
    }
    else
    {
        cout << "Nie mozna otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void edytujAdresatow (vector <Adresat> &adresaci)
{
    Adresat adresat;
    int idEdytowanegoAdresata;
    char wybor;
    bool czyIstniejeAdresat = false;

    system ("cls");
    if (!adresaci.empty())
    {
    cout << ">>> EDYCJA KONTAKTOW <<<" << endl << endl;

    cout << "Podaj ID adresata, ktorego dane chcesz edytowac: ";
    cin >> idEdytowanegoAdresata;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
    if (itr -> id == idEdytowanegoAdresata)
    {
        czyIstniejeAdresat = true;
    cout << endl;
    cout << "Ktore dane chcesz edytowac?" << endl;

    cout << "1 - Imie            " << itr -> imie << endl;
    cout << "2 - Nazwisko        " << itr -> nazwisko << endl;
    cout << "3 - Numer telefonu  " << itr -> numerTelefonu << endl;
    cout << "4 - Email           " << itr -> email << endl;
    cout << "5 - Adres           " << itr -> adres << endl;
    cout << "6 - Powrot" << endl;
    cout << "Wybierz 1-6: ";
    cin >> wybor;

    switch (wybor)
    {
    case '1':
        cout << "Podaj nowe imie adresata: ";
        cin >> itr -> imie;
        itr -> imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr -> imie);
        cout << endl << "Imie zostalo zmienione" << endl;
        zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
        system("pause");
        break;
    case '2':
        cout << "Podaj nowe nazwisko adresata: ";
        cin >> itr -> nazwisko;
        itr -> nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr -> nazwisko);
        cout << endl << "Nazwisko zostalo zmienione" << endl;
        zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
        system("pause");
        break;
    case '3':
        cout << "Podaj nowy numer telefonu adresata: ";
        cin.sync();
        getline(cin, itr -> numerTelefonu);
        cout << endl << "Numer telefonu zostal zmieniony" << endl;
        zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
        system("pause");
        break;
    case '4':
        cout << "Podaj nowy email adresata: ";
        cin >> itr -> email;
        cout << endl << "Email zostal zmieniony" << endl;
        zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
        system("pause");
        break;
    case '5':
        cout << "Podaj nowy adres adresata: ";
        cin.sync();
        getline(cin, itr -> adres);
        itr -> adres = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr -> adres);
        cout << endl << "Adres zostal zmieniony" << endl;
        zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
        system("pause");
        break;
    case '6':
        cout << "Powrot do menu glownego" << endl;
        Sleep(1000);
        break;
    default:
        cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl;
        Sleep(2000);
        break;
    }
    }
    }
    }

    if (czyIstniejeAdresat == false)
    {
        cout << "W ksiazce adresowej nie ma adresata o podanym numerze ID." << endl;
        system("pause");
    }
}

void kasujAdresatow (vector <Adresat> &adresaci)
{
    Adresat adresat;
    int idKasowanegoAdresata;
    char znak;
    bool czyIstniejeAdresat = false;
    cout << "Podaj numer adresata, ktorego chcesz skasowac: ";
    cin >> idKasowanegoAdresata;
    cout << endl;

    for (vector <Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++)
    {
    if (itr -> id == idKasowanegoAdresata)
    {
        czyIstniejeAdresat = true;
        cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
        cin >> znak;
        if (znak == 't')
        {
            itr = adresaci.erase(itr);
            cout << endl << endl << "Szukany adresat zostal USUNIETY." << endl;
            zapiszWszystkichAdresatowDoPlikuTekstowego(adresaci);
            Sleep(1000);
            break;
        }
        else{
            cout << endl << endl << "Wybrany adresat NIE zostal usuniety." << endl;
            Sleep(1000);
            break;
        }
    }
    }
    if (czyIstniejeAdresat == false){
        cout << "W ksiazce adresowej nie ma adresata o podanym numerze ID." << endl;
        system("pause");
    }

}

int main()
{
    vector <Adresat> adresaci;
    wczytajOsobyZPliku(adresaci);
    int iloscOsob = adresaci.size();
    cout << iloscOsob << endl;
    system("pause");

    char wybor;

    while (true)
    {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyswietl kontakty" << endl;
        cout << "3. Wyszukaj po imieniu" << endl;
        cout << "4. Wyszukaj po nazwisku" << endl;
        cout << "5. Edytuj kontakty" << endl;
        cout << "6. Usun kontakty" << endl;
        cout << "9. Zakoncz program" << endl;
        cin >> wybor;

        if (wybor == '1')
        {
            dodajOsobe(adresaci);
        }
        else if (wybor == '2')
        {
            system("cls");
            for (unsigned i = 0; i < adresaci.size(); i++)
            {
                cout << adresaci[i].id << "|" << adresaci[i].imie << "|" << adresaci[i].nazwisko << "|" << adresaci[i].numerTelefonu <<  "|" << adresaci[i].email <<  "|" << adresaci[i].adres <<  "|" << endl;
            }
            getch();
        }
        else if (wybor == '3')
        {
            wyszukajAdresatowPoImieniu(adresaci);
        }
        else if (wybor == '4')
        {
            wyszukajAdresatowPoNazwisku(adresaci);
        }
        else if (wybor == '5')
        {
            edytujAdresatow(adresaci);
        }
        else if (wybor == '6')
        {
            kasujAdresatow(adresaci);
        }
        else if (wybor == '9')
        {
            exit(0);
        }
    }

    return 0;
}
