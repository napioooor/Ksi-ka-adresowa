#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include "uzytkownik.h"

using namespace std;

fstream bazaUzytkownikow, bazaKontaktow, temp;

struct wpis {
    string imie, nazwisko, email, adres, nr_telefonu;
    int LP, IDdodajacego;
};

vector <wpis> adresaci;
vector <int> nastepnyIDadresata, nastepnyIDuzytkownika;
vector <Uzytkownik> uzytkownik;

int IDobecnegoUzytkownika = 0;

int sprawdzanie_istnienia_bazy_uzytkownikow_i_dodawanie_z_niej_wpisow(int iloscUzytkownikow);
bool logowanie(int iloscU);
int rejestracja(int iloscU);
void menu_glowne();
int sprawdzanie_istnienia_bazy_kontaktow_i_dodawanie_z_niej_wpisow(int liczbaPorzadkowa);
int dodawanie_nowych_wpisow(int liczbaPorzadkowa);
void wyszukiwanie_po_imieniu(int iloscW);
void wyszukiwanie_po_nazwisku(int iloscW);
void wyswietlanie_wszystkich_wpisow(int iloscW);
int usuwanie_adresatow(int iloscW);
void edytowanie_adresatow();
void zmiana_hasla();
void zapisywanie_adresow_do_pliku(int IDusunietego);
void zapis_edytowanego_adresata(int IDedytowanego, int LPedytowanego);
void zamiana_temp();
void zapisywanie_uzytkownikow_do_pliku();

int main() {
    char wybor;
    int iloscUzytkownikow = 0;

    iloscUzytkownikow = sprawdzanie_istnienia_bazy_uzytkownikow_i_dodawanie_z_niej_wpisow(iloscUzytkownikow);

    while(1) {
        system("cls");

        cout << "Witaj w ksiazce adresowej!" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "9. Zamknij program" << endl;

        cin >> wybor;
        switch(wybor) {
        case '1':
            if(logowanie(iloscUzytkownikow) == true)
                menu_glowne();
            else {
                system("cls");
                cout << "Bledny login lub haslo" << endl;
                cout << "Wcisnij dowolny klawisz, aby powrocic do menu startowego" << endl;

                system("pause");

                continue;
            }
            break;
        case '2':
            iloscUzytkownikow = rejestracja(iloscUzytkownikow);
            break;
        case '9':
            exit(0);
        }
    }
}


int sprawdzanie_istnienia_bazy_uzytkownikow_i_dodawanie_z_niej_wpisow(int liczbaPorzadkowa){
    string linia;
    int nr_linii = 1;

    bazaUzytkownikow.open("Uzytkownicy.txt", ios::in);

    if(bazaUzytkownikow.good() == true) {
        while(getline(bazaUzytkownikow, linia)) {
            if(bazaUzytkownikow.eof())
                break;

            int dlugoscLinii = linia.length();
            string czescTekstu = "";
            int LPdanych = 1;

            uzytkownik.push_back(Uzytkownik());

            for(int numerZnaku = 0; numerZnaku < dlugoscLinii; numerZnaku++) {
                if(linia[numerZnaku] != '|')
                    czescTekstu += linia[numerZnaku];

                else {
                    int dlugoscCzesciTekstu;

                    dlugoscCzesciTekstu = czescTekstu.length();

                    switch(LPdanych) {
                    case 1:
                        uzytkownik[nr_linii - 1].LP = atoi(czescTekstu.c_str());

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 2:
                        uzytkownik[nr_linii - 1].login = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 3:
                        uzytkownik[nr_linii - 1].haslo = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych = 1;

                        break;
                    }
                }
            }

            nr_linii++;
        }

        nastepnyIDuzytkownika.push_back(uzytkownik[uzytkownik.size() - 1].LP + 1);

        bazaUzytkownikow.close();

        return nr_linii - 1;
    }

    else {
        nastepnyIDuzytkownika.push_back(1);

        return 0;
    }
}

bool logowanie(int iloscU) {
    string login, haslo = "";
    char znak;

    system("cls");

    cout << "Podaj login: ";
    cin >> login;

    system("cls");

    cout << "Podaj haslo: ";
    while(znak = getch()){
        if(znak == '\r')
            break;

        cout<<"*";
        haslo += znak;
    }

    for(int obecnyUzytkownik = 0; obecnyUzytkownik < iloscU; obecnyUzytkownik++) {
        if((uzytkownik[obecnyUzytkownik].login == login) && (uzytkownik[obecnyUzytkownik].haslo == haslo)) {
        IDobecnegoUzytkownika = uzytkownik[obecnyUzytkownik].LP;
        return true;
        }
    }
    return false;
}

int rejestracja(int iloscU) {
    string login, haslo1 = "", haslo2 = "";
    char znak;

    system("cls");

    cout << "Podaj login: ";
    cin >> login;

    for(int obecnyUzytkownik = 0; obecnyUzytkownik < iloscU; obecnyUzytkownik++) {
        if(uzytkownik[obecnyUzytkownik].login == login) {
            cout << "Podany login jest juz zajety. Sproboj ponownie." << endl;

            system("pause");

            return iloscU;
        }
    }

    while(1) {
        system("cls");

        haslo1 = "";

        cout << "Podaj haslo: ";
        while(znak = getch()) {
            if(znak == '\r')
                break;

            cout<<"*";
            haslo1 += znak;
        }
        haslo2 = "";

        system("cls");

        cout << "Powtorz haslo: ";
        while(znak = getch()) {
            if(znak == '\r')
                break;

            cout<<"*";
            haslo2 += znak;
        }
        system("cls");

        if(haslo1 == haslo2)
            break;

        cout << "Hasla nie sa identyczne, sprobuj ponownie." << endl;

        system("pause");
    }
    uzytkownik.push_back(Uzytkownik());

    uzytkownik[iloscU].login = login;
    uzytkownik[iloscU].haslo = haslo1;
    uzytkownik[iloscU].LP = nastepnyIDuzytkownika[0];

    bazaUzytkownikow.open("Uzytkownicy.txt", ios::out | ios::app);

    bazaUzytkownikow << uzytkownik[iloscU].LP << "|" << uzytkownik[iloscU].login << "|" << uzytkownik[iloscU].haslo << "|" << endl;

    bazaUzytkownikow.close();

    iloscU++;

    nastepnyIDuzytkownika.push_back(nastepnyIDuzytkownika[nastepnyIDuzytkownika.size() - 1] + 1);

    nastepnyIDuzytkownika.erase(nastepnyIDuzytkownika.begin());

    cout << "Konto zalozone pomyslnie!" << endl;
    cout << "Wcisnij dowolny klawisz, aby powrocic do menu startowego" << endl;

    system("pause");

    return iloscU;
}

void menu_glowne(){
    char wybor;
    int iloscWpisow = 0;

    iloscWpisow = sprawdzanie_istnienia_bazy_kontaktow_i_dodawanie_z_niej_wpisow(iloscWpisow);

    while(1) {
        system("cls");

        cout << "Zalogowano sie pomyslnie!" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl cala ksiazke adresowa" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "7. Zmien haslo" << endl;
        cout << "9. Wyloguj sie" << endl;

        cin >> wybor;

        switch(wybor) {
        case '1':
            iloscWpisow = dodawanie_nowych_wpisow(iloscWpisow);
            break;
        case '2':
            wyszukiwanie_po_imieniu(iloscWpisow);
            break;
        case '3':
            wyszukiwanie_po_nazwisku(iloscWpisow);
            break;
        case '4':
            wyswietlanie_wszystkich_wpisow(iloscWpisow);
            break;
        case '5':
            iloscWpisow = usuwanie_adresatow(iloscWpisow);
            break;
        case '6':
            edytowanie_adresatow();
            break;
        case '7':
            zmiana_hasla();
            break;
        case '9':
            return;
        }
    }
}

int sprawdzanie_istnienia_bazy_kontaktow_i_dodawanie_z_niej_wpisow(int liczbaPorzadkowa) {
    string linia;
    int nr_linii = 1, LPnastepnegoAdresata = 1, adresat = 0;

    adresaci.clear();

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);

    if(bazaKontaktow.good() == true) {
        while(getline(bazaKontaktow, linia)) {
            if(bazaKontaktow.eof())
                break;

            int dlugoscLinii = linia.length();
            string czescTekstu = "";
            int LPdanych = 1;

            string imie = "", nazwisko = "", nr_telefonu = "", adres = "", email = "";
            int LP = 0, IDdodajacego = 0;

            for(int numerZnaku = 0; numerZnaku < dlugoscLinii; numerZnaku++) {
                if(linia[numerZnaku] != '|')
                    czescTekstu += linia[numerZnaku];

                else {
                    int dlugoscCzesciTekstu;

                    dlugoscCzesciTekstu = czescTekstu.length();

                    switch(LPdanych) {
                    case 1:
                        LP = atoi(czescTekstu.c_str());

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 2:
                        IDdodajacego = atoi(czescTekstu.c_str());

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 3:
                        imie = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 4:
                        nazwisko = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 5:
                        email = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 6:
                        adres = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 7:
                        nr_telefonu = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych = 1;

                        break;

                    }
                }
            }
            if(IDdodajacego == IDobecnegoUzytkownika)
            {
                adresaci.push_back(wpis());
                adresaci[adresat].LP = LP;
                adresaci[adresat].IDdodajacego = IDdodajacego;
                adresaci[adresat].imie = imie;
                adresaci[adresat].nazwisko = nazwisko;
                adresaci[adresat].adres = adres;
                adresaci[adresat].email = email;
                adresaci[adresat].nr_telefonu = nr_telefonu;

                adresat++;
            }

            nr_linii++;
            LPnastepnegoAdresata = LP + 1;
        }

        nastepnyIDadresata.push_back(LPnastepnegoAdresata);

        bazaKontaktow.close();

        return adresat;
    }

    else {
        nastepnyIDadresata.push_back(LPnastepnegoAdresata);

        bazaKontaktow.close();

        return 0;
    }
}

int dodawanie_nowych_wpisow(int liczbaPorzadkowa) {
    string imie, nazwisko, email, adres, nr_telefonu;

    system("cls");

    cout << "Podaj imie: " << endl;
    cin >> imie;
    system("cls");

    cout << "Podaj nazwisko: " << endl;
    cin >> nazwisko;
    system("cls");

    cout << "Podaj nr telefonu: " << endl;
    cin >> nr_telefonu;
    system("cls");

    cout << "Podaj email: " << endl;
    cin >> email;
    system("cls");

    cout << "Podaj adres: " << endl;
    getline(cin >> ws, adres);
    system("cls");

    adresaci.push_back(wpis());

    adresaci[liczbaPorzadkowa].imie = imie;
    adresaci[liczbaPorzadkowa].nazwisko = nazwisko;
    adresaci[liczbaPorzadkowa].nr_telefonu = nr_telefonu;
    adresaci[liczbaPorzadkowa].email = email;
    adresaci[liczbaPorzadkowa].adres = adres;
    adresaci[liczbaPorzadkowa].LP = nastepnyIDadresata[0];
    adresaci[liczbaPorzadkowa].IDdodajacego = IDobecnegoUzytkownika;

    bazaKontaktow.open("Baza kontaktow.txt", ios::out | ios::app);

    bazaKontaktow << adresaci[liczbaPorzadkowa].LP << "|" << adresaci[liczbaPorzadkowa].IDdodajacego << "|" << adresaci[liczbaPorzadkowa].imie << "|" << adresaci[liczbaPorzadkowa].nazwisko;
    bazaKontaktow << "|" << adresaci[liczbaPorzadkowa].email << "|" << adresaci[liczbaPorzadkowa].adres << "|" << adresaci[liczbaPorzadkowa].nr_telefonu << "|" << endl;

    bazaKontaktow.close();

    cout << "Nastepujace dane zostaly dodane: " << endl << endl;
    cout << "Imie i nazwisko: " << imie << " " << nazwisko << endl;
    cout << "Nr telefonu: " << nr_telefonu << endl;
    cout << "Adres email: " << email << endl;
    cout << "Adres: " << adres << endl;

    liczbaPorzadkowa++;

    nastepnyIDadresata.push_back(nastepnyIDadresata[nastepnyIDadresata.size() - 1] + 1);

    nastepnyIDadresata.erase(nastepnyIDadresata.begin());

    cout << endl << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
    system("pause");

    return liczbaPorzadkowa;
}

void wyszukiwanie_po_imieniu(int iloscW) {
    string imie, nazwisko, email, adres, nr_telefonu;

    system("cls");

    if(adresaci.empty()) {
        cout << "Brak kontaktow w bazie. Dodaj nowe kontakty z poziomumenu glownego." << endl << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
        system("pause");

        return;
    }

    sort(adresaci.begin(), adresaci.end(), [](wpis a, wpis b) {
        return a.LP < b.LP;
    });

    cout << "Podaj imie do wyszukania: " << endl;
    cin >> imie;

    system("cls");

    for(long long unsigned int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
        if(imie == adresaci[obecnyWpis].imie) {
            cout << "Lp: " << adresaci[obecnyWpis].LP << endl;
            cout << "Imie i nazwisko: " << adresaci[obecnyWpis].imie << " " << adresaci[obecnyWpis].nazwisko << endl;
            cout << "Nr telefonu: " << adresaci[obecnyWpis].nr_telefonu << endl;
            cout << "Adres email: " << adresaci[obecnyWpis].email << endl;
            cout << "Adres: " << adresaci[obecnyWpis].adres << endl << endl;
        }
    }

    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
    system("pause");

    return;
}

void wyszukiwanie_po_nazwisku(int iloscW) {
    string imie, nazwisko, email, adres, nr_telefonu;

    system("cls");

    if(adresaci.empty()) {
        cout << "Brak kontaktow w bazie. Dodaj nowe kontakty z poziomumenu glownego." << endl << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
        system("pause");

        return;
    }

    sort(adresaci.begin(), adresaci.end(), [](wpis a, wpis b) {
        return a.LP < b.LP;
    });

    cout << "Podaj nazwisko do wyszukania: " << endl;
    cin >> nazwisko;

    system("cls");

    for(long long unsigned int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
        if(nazwisko == adresaci[obecnyWpis].nazwisko) {
            cout << "Lp: " << adresaci[obecnyWpis].LP << endl;
            cout << "Imie i nazwisko: " << adresaci[obecnyWpis].imie << " " << adresaci[obecnyWpis].nazwisko << endl;
            cout << "Nr telefonu: " << adresaci[obecnyWpis].nr_telefonu << endl;
            cout << "Adres email: " << adresaci[obecnyWpis].email << endl;
            cout << "Adres: " << adresaci[obecnyWpis].adres << endl << endl;
        }
    }

    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
    system("pause");

    return;
}

void wyswietlanie_wszystkich_wpisow(int iloscW) {
    string imie, nazwisko, email, adres, nr_telefonu;

    system("cls");

    if(adresaci.empty()) {
        cout << "Brak kontaktow w bazie. Dodaj nowe kontakty z poziomumenu glownego." << endl << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
        system("pause");
        return;
    }

    sort(adresaci.begin(), adresaci.end(), [](wpis a, wpis b) {
        return a.LP < b.LP;
    });

    for(long long unsigned int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
        cout << "Lp: " << adresaci[obecnyWpis].LP << endl;
        cout << "Imie i nazwisko: " << adresaci[obecnyWpis].imie << " " << adresaci[obecnyWpis].nazwisko << endl;
        cout << "Nr telefonu: " << adresaci[obecnyWpis].nr_telefonu << endl;
        cout << "Adres email: " << adresaci[obecnyWpis].email << endl;
        cout << "Adres: " << adresaci[obecnyWpis].adres << endl << endl;
    }

    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
    system("pause");

    return;
}

int usuwanie_adresatow(int iloscW) {
    for(;;) {
        system("cls");

        int IDdoUsuniecia, LPusuwanego = -1;
        char wybor;

        cout << "Podaj nr ID adresata do usuniecia: " << endl;
        cin >> IDdoUsuniecia;

        system("cls");

        cout << "Wybrano adresata o numerze ID: " << IDdoUsuniecia << " Czy potwierdzasz usuniecie? [T/N]" << endl;
        cin >> wybor;

        if(wybor == 't') {
            for(long long unsigned int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
                if(adresaci[obecnyWpis].LP == IDdoUsuniecia) {
                    LPusuwanego = obecnyWpis;
                    break;
                }
            }

            if(LPusuwanego < 0) {
                system("cls");

                cout << "Nie znaleziono adresata o takim numerze. Sprobuj ponownie.";

                system("pause");

                continue;
            }

            adresaci.erase(adresaci.begin() + LPusuwanego);

            iloscW--;

            zapisywanie_adresow_do_pliku(IDdoUsuniecia);

            system("cls");

            cout << "Adresat usuniety pomyslnie" << endl;

            cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;

            system("pause");

            return iloscW;

        }
        if(wybor == 'n')
            return iloscW;
    }
}

void edytowanie_adresatow() {
    for(;;) {
        int IDdoEdytowania, LPedytowanego = -1;
        char wybor;
        string noweDane;

        system("cls");

        cout << "Podaj numer ID adresata do edytowania: " << endl;
        cin >> IDdoEdytowania;

        for(long long unsigned int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
            if(adresaci[obecnyWpis].LP == IDdoEdytowania) {
                LPedytowanego = obecnyWpis;
                break;
            }
        }

        if(LPedytowanego < 0) {
            system("cls");

            cout << "Nie znaleziono adresata o takim numerze. Sprobuj ponownie.";

            Sleep(3000);

            continue;
        }

        system("cls");

        cout << "Wybierz dane do edytowania: " << endl;
        cout << "1. Imie" << endl;
        cout << "2. Nazwisko" << endl;
        cout << "3. Numer telefonu" << endl;
        cout << "4. Email" << endl;
        cout << "5. Adres" << endl;
        cout << "9. Powrot do menu" << endl;

        cin >> wybor;

        switch(wybor){
        case '1':
            system("cls");
            cout << "Podaj nowe imie: " << endl;
            cin >> noweDane;
            adresaci[LPedytowanego].imie = noweDane;
            break;
        case '2':
            system("cls");
            cout << "Podaj nowe nazwisko: " << endl;
            cin >> noweDane;
            adresaci[LPedytowanego].nazwisko = noweDane;
            break;
        case '3':
            system("cls");
            cout << "Podaj nowy numer telefonu: " << endl;
            cin >> noweDane;
            adresaci[LPedytowanego].nr_telefonu = noweDane;
            break;
        case '4':
            system("cls");
            cout << "Podaj nowy email: " << endl;
            cin >> noweDane;
            adresaci[LPedytowanego].email = noweDane;
            break;
        case '5':
            system("cls");
            cout << "Podaj nowy adres: " << endl;
            cin >> noweDane;
            adresaci[LPedytowanego].adres = noweDane;
            break;
        case '9':
            return;
        }

        zapis_edytowanego_adresata(IDdoEdytowania, LPedytowanego);

        cout << "Dane edytowane pomyslnie." << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;

        system("pause");

        return;
    }
}

void zmiana_hasla(){
    string noweHaslo1, noweHaslo2;
    char znak;

    while(1) {
        system("cls");

        noweHaslo1 = "";

        cout << "Podaj haslo: ";
        while(znak = getch()) {
            if(znak == '\r')
                break;

            cout<<"*";
            noweHaslo1 += znak;
        }
        noweHaslo2 = "";

        system("cls");

        cout << "Powtorz haslo: ";
        while(znak = getch()) {
            if(znak == '\r')
                break;

            cout<<"*";
            noweHaslo2 += znak;
        }
        system("cls");

        if(noweHaslo1 == noweHaslo2)
            break;

        cout << "Hasla nie sa identyczne, sprobuj ponownie." << endl;

        system("pause");
    }
    system("cls");

    uzytkownik[IDobecnegoUzytkownika - 1].haslo = noweHaslo1;

    zapisywanie_uzytkownikow_do_pliku();

    cout << "Haslo zmienione pomyslnie." << endl;

    system("pause");

    return;
}

void zapisywanie_adresow_do_pliku(int IDusunietego) {
    string linia;

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);
    temp.open("temp.txt", ios::out | ios::trunc);

    if(bazaKontaktow.good() == true) {
        while(getline(bazaKontaktow, linia)) {
            if(bazaKontaktow.eof())
                break;

            int dlugoscLinii = linia.length();
            string czescTekstu = "";

            int LP = 0;

            for(int numerZnaku = 0; numerZnaku < dlugoscLinii; numerZnaku++) {
                if(linia[numerZnaku] != '|')
                    czescTekstu += linia[numerZnaku];

                else {
                    LP = atoi(czescTekstu.c_str());

                    if(LP != IDusunietego)
                        temp << linia << endl;

                    czescTekstu = "";

                    linia = "";

                    dlugoscLinii = linia.length();
                }
            }
        }
    }

    bazaKontaktow.close();
    temp.close();

    zamiana_temp();

    return;
}

void zapis_edytowanego_adresata(int IDedytowanego, int LPedytowanego) {
    string linia;

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);
    temp.open("temp.txt", ios::out | ios::trunc);

    if(bazaKontaktow.good() == true) {
        while(getline(bazaKontaktow, linia)) {
            if(bazaKontaktow.eof())
                break;

            int dlugoscLinii = linia.length();
            string czescTekstu = "";

            int LP = 0;

            for(int numerZnaku = 0; numerZnaku < dlugoscLinii; numerZnaku++) {
                if(linia[numerZnaku] != '|')
                    czescTekstu += linia[numerZnaku];

                else {
                    LP = atoi(czescTekstu.c_str());

                    if(LP != IDedytowanego)
                        temp << linia << endl;

                    else {
                        temp << adresaci[LPedytowanego].LP << "|" << adresaci[LPedytowanego].IDdodajacego << "|" << adresaci[LPedytowanego].imie << "|" << adresaci[LPedytowanego].nazwisko;
                        temp << "|" << adresaci[LPedytowanego].email << "|" << adresaci[LPedytowanego].adres << "|" << adresaci[LPedytowanego].nr_telefonu << "|" << endl;
                    }

                    czescTekstu = "";

                    linia = "";

                    dlugoscLinii = linia.length();
                }
            }
        }
    }

    bazaKontaktow.close();
    temp.close();

    zamiana_temp();

    return;
}

void zamiana_temp(){
    string linia;

    bazaKontaktow.open("Baza kontaktow.txt", ios::out | ios::trunc);
    temp.open("temp.txt", ios::in | ios::app);

    if(temp.good() == true) {
        while(getline(temp, linia)) {
            if(temp.eof())
                break;

            bazaKontaktow << linia << endl;
        }
    }
    bazaKontaktow.close();
    temp.close();

    remove("temp.txt");

    return;
}

void zapisywanie_uzytkownikow_do_pliku(){
    bazaUzytkownikow.open("Uzytkownicy.txt", ios::out | ios::trunc);

    for(long long unsigned int obecnyU = 0; obecnyU < uzytkownik.size(); obecnyU++){
        bazaUzytkownikow << uzytkownik[obecnyU].LP << "|" << uzytkownik[obecnyU].login << "|" << uzytkownik[obecnyU].haslo << "|" << endl;
    }
}
