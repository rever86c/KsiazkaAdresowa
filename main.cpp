#include <iostream>
#include <fstream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <bits/stdc++.h>
#include <sstream>

using namespace std;

struct Kontakt
{
    int kontaktID;
    string imie;
    string nazwisko;
    string nrTelefonu;
    string eMail;
    string adresZamieszkania;
};



void wyswietlWszystkieKontakty(vector <Kontakt> ksiazkaAdresowa)
{
    for(int i = 0; i <ksiazkaAdresowa.size(); i++ )
    {

        cout<< ksiazkaAdresowa[i].kontaktID <<". "<< ksiazkaAdresowa[i].imie <<", "<< ksiazkaAdresowa[i].nazwisko <<", ";
        cout<< ksiazkaAdresowa[i].nrTelefonu <<", "<< ksiazkaAdresowa[i].eMail <<", "<< ksiazkaAdresowa[i].adresZamieszkania <<endl;
    }
}

void zapiszKontaktWpliku(vector <Kontakt> ksiazkaAdresowa)
{
    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaAdresowa.txt", ios::out);
    if(plikTekstowy.good()==true)
    {
        for(int i =0; i<ksiazkaAdresowa.size(); i++)
        {
            plikTekstowy<<ksiazkaAdresowa[i].kontaktID<<"|";
            plikTekstowy<<ksiazkaAdresowa[i].imie<<"|";
            plikTekstowy<<ksiazkaAdresowa[i].nazwisko<<"|";
            plikTekstowy<<ksiazkaAdresowa[i].nrTelefonu<<"|";
            plikTekstowy<<ksiazkaAdresowa[i].eMail<<"|";
            plikTekstowy<<ksiazkaAdresowa[i].adresZamieszkania<<endl;
        }
        plikTekstowy.close();

    }
    else
    {
        cout<<"Nie mozna zapisac do pliku!"<<endl;
        plikTekstowy.close();
    }
}

vector <Kontakt> dodajNowyKontakt(vector <Kontakt> ksiazkaAdresowa)
{

    Kontakt nowyKontakt;

    cout<< "Podaj Imie nowego kontaktu: ";
    getline(cin,nowyKontakt.imie);
    cout<< "Podaj Nazwisko nowego kontaktu: ";
    getline(cin,nowyKontakt.nazwisko);
    cout<< "Podaj numer telefonu nowego kontaktu: ";
    getline(cin,nowyKontakt.nrTelefonu);
    cout<< "Podaj eMail nowego kontaktu: ";
    getline(cin,nowyKontakt.eMail);
    cout<< "Podaj adres zamieszkania nowego kontaktu: ";
    getline(cin,nowyKontakt.adresZamieszkania);

    if(ksiazkaAdresowa.size()==0)
    {
        nowyKontakt.kontaktID =1;
    }
    else
    {
        nowyKontakt.kontaktID=ksiazkaAdresowa[ksiazkaAdresowa.size()-1].kontaktID+1;
    }
    ksiazkaAdresowa.push_back(nowyKontakt);

    return ksiazkaAdresowa;
}

Kontakt pobierzDaneZlinii(string liniaKontaktu)
{
    Kontakt daneKontaktu;

    vector <string> rozdzieloneElementy;

    stringstream pobierz(liniaKontaktu);

    string elementy;

    while(getline(pobierz, elementy,'|'))
    {
        rozdzieloneElementy.push_back(elementy);
    }

    istringstream (rozdzieloneElementy[0]) >> daneKontaktu.kontaktID;
    daneKontaktu.imie = rozdzieloneElementy[1];
    daneKontaktu.nazwisko =rozdzieloneElementy[2];
    daneKontaktu.nrTelefonu = rozdzieloneElementy[3];
    daneKontaktu.eMail = rozdzieloneElementy[4];
    daneKontaktu.adresZamieszkania = rozdzieloneElementy[5];

    return daneKontaktu;
}


vector <Kontakt> wczytajKontaktyZpliku()
{
    fstream ksiazka;
    ksiazka.open("ksiazkaAdresowa.txt", ios::in);
    string liniaJednegoKontaktu;
    vector <Kontakt> odczytaneKontakty;
    if(ksiazka.good()==true)
    {
        while(getline(ksiazka,liniaJednegoKontaktu))
        {
            odczytaneKontakty.push_back(pobierzDaneZlinii(liniaJednegoKontaktu));
        }
        ksiazka.close();
    }
    return odczytaneKontakty;
}

bool sprawdzCzyImieWystepuje(vector<Kontakt> ksiazkaAdresowa, string imie)
{
    int liczbaKontaktowZtymImieniem=0;
    bool imieWystepuje = false;
    for(int i =0; i<ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].imie == imie)
        {
            liczbaKontaktowZtymImieniem++;
        }
    }

    if(liczbaKontaktowZtymImieniem>0)
    {
        imieWystepuje=true;
    }

    return imieWystepuje;
}

void wyszukajPoImieniu(vector <Kontakt> ksiazkaAdresowa)
{
    cout<<"Wprowadz wyszukiwane imie: ";
    string wyszukiwaneImie;
    getline(cin, wyszukiwaneImie);

    if(sprawdzCzyImieWystepuje(ksiazkaAdresowa,wyszukiwaneImie))
    {
        for(int i =0; i<ksiazkaAdresowa.size(); i++)
        {
            if(ksiazkaAdresowa[i].imie == wyszukiwaneImie)
            {
                cout<< ksiazkaAdresowa[i].kontaktID <<". "<< ksiazkaAdresowa[i].imie <<", "<< ksiazkaAdresowa[i].nazwisko <<", ";
                cout<< ksiazkaAdresowa[i].nrTelefonu <<", "<< ksiazkaAdresowa[i].eMail <<", "<< ksiazkaAdresowa[i].adresZamieszkania <<endl;
            }
        }
    }
    else
    {
        cout<<"Brak kontaktow o takim imieniu"<<endl;
    }
}

bool sprawdzCzyNazwiskoWystepuje(vector <Kontakt> ksiazkaAdresowa, string nazwisko)
{
    int liczbaKontaktowZtymNazwiskiem=0;
    bool nazwiskoWystepuje = false;
    for(int i =0; i<ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].nazwisko == nazwisko)
        {
            liczbaKontaktowZtymNazwiskiem++;
        }
    }

    if(liczbaKontaktowZtymNazwiskiem>0)
    {
        nazwiskoWystepuje=true;
    }

    return nazwiskoWystepuje;
}
void wyszukajPoNazwisku(vector <Kontakt> ksiazkaAdresowa)
{
    cout<<"Wprowadz wyszukiwane nazwisko: ";
    string wyszukiwaneNazwisko;
    getline(cin, wyszukiwaneNazwisko);

    if(sprawdzCzyNazwiskoWystepuje(ksiazkaAdresowa,wyszukiwaneNazwisko))
    {
        for(int i =0; i<ksiazkaAdresowa.size(); i++)
        {
            if(ksiazkaAdresowa[i].nazwisko == wyszukiwaneNazwisko)
            {
                cout<< ksiazkaAdresowa[i].kontaktID <<". "<< ksiazkaAdresowa[i].imie <<", "<< ksiazkaAdresowa[i].nazwisko <<", ";
                cout<< ksiazkaAdresowa[i].nrTelefonu <<", "<< ksiazkaAdresowa[i].eMail <<", "<< ksiazkaAdresowa[i].adresZamieszkania <<endl;
            }
        }
    }
    else
    {
        cout<<"Brak kontaktow o takim nazwisku"<<endl;
    }
}

bool zapytajCzyUsunacKontakt()
{
    system("cls");
    bool czyUsunac = false;
    cout<<"Aby potwierdzic usuniecie kontaktu nacisnij t "<<endl;
    char wyborOpcji = getch();
    if(wyborOpcji=='t')
    {
        czyUsunac=true;
        cout<<"Kontakt zostal usuniety!"<<endl;
    }
    return czyUsunac;
}

vector <Kontakt> usunKontakt(vector <Kontakt> ksiazkaAdresowa)
{
    int idKontaktuDoUsuniecia;
    cout<<"Wprowadz numer ID kontakt ktory chcesz usunac: ";
    cin>> idKontaktuDoUsuniecia;
    cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    int pozycjaKontaktuDoUsuniecia;
    bool kontaktDoUsunieciaZnaleziony = false;
    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoUsuniecia)
        {
            pozycjaKontaktuDoUsuniecia = i;
            kontaktDoUsunieciaZnaleziony = true;
            break;
        }
    }

    if(kontaktDoUsunieciaZnaleziony)
    {
        if(zapytajCzyUsunacKontakt())
        {
            vector <Kontakt> ::iterator wskaznikDoElementuDoUsuniecia = ksiazkaAdresowa.begin() + pozycjaKontaktuDoUsuniecia;
            ksiazkaAdresowa.erase(wskaznikDoElementuDoUsuniecia);
        }
    }
    else
    {
        cout<<"Nie ma takiego ID kontaktu!"<<endl;
        Sleep(1000);
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujImie(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowe imie: ";
    string noweImie;
    getline(cin, noweImie);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].imie = noweImie;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujNazwisko(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowe nazwisko: ";
    string noweNazwisko;
    getline(cin, noweNazwisko);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].nazwisko = noweNazwisko;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujTelefon(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowy numer telefonu: ";
    string nowyTelefon;
    getline(cin, nowyTelefon);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].nrTelefonu = nowyTelefon;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujMaila(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowy adres Email: ";
    string nowyMail;
    getline(cin, nowyMail);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].eMail = nowyMail;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujAdres(vector <Kontakt> ksiazkaAdresowa, int idKontaktuDoEdycji)
{
    cout<<"Wprowadz nowy adres: ";
    string nowyAdres;
    getline(cin, nowyAdres);

    for(int i =0; i <ksiazkaAdresowa.size(); i++)
    {
        if(ksiazkaAdresowa[i].kontaktID == idKontaktuDoEdycji)
        {
            ksiazkaAdresowa[i].adresZamieszkania = nowyAdres;
            break;
        }
    }
    return ksiazkaAdresowa;
}

vector <Kontakt> edytujKontakt(vector <Kontakt> ksiazkaAdresowa)
{
    int idKontaktuDoEdycji;
    cout<<"Wprowadz ID kontaktu ktory chcesz edytowac: ";
    cin>>idKontaktuDoEdycji;
    cin.ignore( std::numeric_limits < std::streamsize >::max(), '\n' );
    system("cls");
    cout<<"Ktore pole chcesz edytowac?"<<endl;
    cout<<"1. Imie."<<endl;
    cout<<"2. Nazwisko."<<endl;
    cout<<"3. Numer telefonu."<<endl;
    cout<<"4. Email."<<endl;
    cout<<"5. Adres."<<endl;
    cout<<"6. Powrot do menu glownego."<<endl;

    char wyborOpcji = getch();

    switch(wyborOpcji)
    {
    case '1':
        system("cls");
        ksiazkaAdresowa=edytujImie(ksiazkaAdresowa, idKontaktuDoEdycji);
        break;
    case '2':
        system("cls");
        ksiazkaAdresowa=edytujNazwisko(ksiazkaAdresowa, idKontaktuDoEdycji);
        break;
    case '3':
        system("cls");
        ksiazkaAdresowa=edytujTelefon(ksiazkaAdresowa, idKontaktuDoEdycji);
        break;
    case '4':
        system("cls");
        ksiazkaAdresowa=edytujMaila(ksiazkaAdresowa, idKontaktuDoEdycji);
        break;
    case '5':
        system("cls");
        ksiazkaAdresowa=edytujAdres(ksiazkaAdresowa, idKontaktuDoEdycji);
        break;
    case '6':
        break;
    }
    return ksiazkaAdresowa;
}

void oczekiwanieNaEnter()
{
    cout<<endl<<"Nacisnij enter aby wrocic do menu glownego."<<endl;
    cin.get();
}

int main()
{
    char wyborOpcji;
    vector <Kontakt> kontaktyWksiazce = wczytajKontaktyZpliku();

    //kontaktyWksiazce = wczytajKontaktyZpliku();
    //wyswietlWszystkieKontakty(kontaktyWksiazce);
    // kontaktyWksiazce=dodajNowyKontakt(kontaktyWksiazce);
    // wyswietlWszystkieKontakty(kontaktyWksiazce);
    //wyszukajPoNazwisku(kontaktyWksiazce);
    while(1)
    {
        system("cls");
        cout<<"KSIAZKA ADRESOWA"<<endl;
        cout<<"1. Dodaj kontakt."<<endl;
        cout<<"2. Wyszukaj kontakt po imieniu."<<endl;
        cout<<"3. Wyszukaj kontakt po nazwisku."<<endl;
        cout<<"4. Wyswietl wszystkie kontakty."<<endl;
        cout<<"5. Usun kontakt."<<endl;
        cout<<"6. Edytuj kontakt."<<endl;
        cout<<"9. Wyjdz z programu."<<endl;
        wyborOpcji = getch();

        switch(wyborOpcji)
        {
        case '1':
            system("cls");
            kontaktyWksiazce=dodajNowyKontakt(kontaktyWksiazce);
            oczekiwanieNaEnter();
            break;
        case '2':
            system("cls");
            wyszukajPoImieniu(kontaktyWksiazce);
            oczekiwanieNaEnter();
            break;
        case '3':
            system("cls");
            wyszukajPoNazwisku(kontaktyWksiazce);
            oczekiwanieNaEnter();
            break;
        case '4':
            system("cls");
            wyswietlWszystkieKontakty(kontaktyWksiazce);
            oczekiwanieNaEnter();
            break;
        case '5':
            system("cls");
            kontaktyWksiazce= usunKontakt(kontaktyWksiazce);
            oczekiwanieNaEnter();
            break;
        case '6':
            system("cls");
            kontaktyWksiazce= edytujKontakt(kontaktyWksiazce);
            oczekiwanieNaEnter();
            break;
        case '9':
            zapiszKontaktWpliku(kontaktyWksiazce);
            system("cls");
            exit(0);
            break;
        }

    }

    return 0;
}

