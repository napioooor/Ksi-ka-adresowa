#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

fstream bazaKontaktow;

struct wpis {
    string imie, nazwisko, email, adres, nr_telefonu;
    int LP;
};

vector <wpis> adresaci;
vector <int> nastepnyID;

int sprawdzanie_istnienia_bazy_i_dodawanie_z_niej_wpisow(int liczbaPorzadkowa);
int dodawanie_nowych_wpisow(int liczbaPorzadkowa);
//void dodawanie_brakujacych_ID();
void wyszukiwanie_po_imieniu(int iloscW);
void wyszukiwanie_po_nazwisku(int iloscW);
void wyswietlanie_wszystkich_wpisow(int iloscW);
int usuwanie_adresatow(int iloscW);
void edytowanie_adresatow();
void zapisywanie_adresow_do_pliku();

int main() {
    char wybor;
    int iloscWpisow = 0;

    iloscWpisow = sprawdzanie_istnienia_bazy_i_dodawanie_z_niej_wpisow(iloscWpisow);

    while(1) {
        system("cls");

        cout << "Witaj w ksiazce adresowej!" << endl;
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl cala ksiazke adresowa" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Opusc program" << endl;

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
        case '9':
            zapisywanie_adresow_do_pliku();
            exit(0);
        }
    }

    return 0;
}

int sprawdzanie_istnienia_bazy_i_dodawanie_z_niej_wpisow(int liczbaPorzadkowa) {
    string linia;
    int nr_linii = 1;

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);

    if(bazaKontaktow.good() == true) {
        while(getline(bazaKontaktow, linia)) {
            if(bazaKontaktow.eof())
                break;

            int dlugoscLinii = linia.length();
            string czescTekstu = "";
            int LPdanych = 1;

            adresaci.push_back(wpis());

            for(int numerZnaku = 0; numerZnaku < dlugoscLinii; numerZnaku++) {
                if(linia[numerZnaku] != '|')
                    czescTekstu += linia[numerZnaku];

                else {
                    int dlugoscCzesciTekstu;

                    dlugoscCzesciTekstu = czescTekstu.length();

                    switch(LPdanych) {
                    case 1:
                        adresaci[nr_linii - 1].LP = atoi(czescTekstu.c_str());

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 2:
                        adresaci[nr_linii - 1].imie = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 3:
                        adresaci[nr_linii - 1].nazwisko = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 4:
                        adresaci[nr_linii - 1].email = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 5:
                        adresaci[nr_linii - 1].adres = czescTekstu;

                        czescTekstu = "";

                        linia.erase(0, dlugoscCzesciTekstu + 1);

                        numerZnaku = 0;
                        dlugoscLinii = linia.length();

                        LPdanych++;

                        break;

                    case 6:
                        adresaci[nr_linii - 1].nr_telefonu = czescTekstu;

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

        //dodawanie_brakujacych_ID();

        nastepnyID.push_back(adresaci[adresaci.size() - 1].LP + 1);

        bazaKontaktow.close();

        return nr_linii - 1;
    }

    else {
        nastepnyID.push_back(1);

        return 0;
    }
}

/*void dodawanie_brakujacych_ID() {
    int roznica = 1;

    for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
        if(adresaci[obecnyWpis].LP != (obecnyWpis + roznica)) {
            nastepnyID.push_back(obecnyWpis + roznica);

            roznica++;
            obecnyWpis--;
        }
    }

    return;
}*/

int dodawanie_nowych_wpisow(int liczbaPorzadkowa) {
    string imie, nazwisko, email, adres, nr_telefonu;

    system("cls");

    bazaKontaktow.open("Baza kontaktow.txt", ios::out | ios::app);

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
    adresaci[liczbaPorzadkowa].LP = nastepnyID[0];

    cout << "Nastepujace dane zostaly dodane: " << endl << endl;
    cout << "Imie i nazwisko: " << imie << " " << nazwisko << endl;
    cout << "Nr telefonu: " << nr_telefonu << endl;
    cout << "Adres email: " << email << endl;
    cout << "Adres: " << adres << endl;

    liczbaPorzadkowa++;

    nastepnyID.push_back(nastepnyID[nastepnyID.size() - 1] + 1);

    nastepnyID.erase(nastepnyID.begin());

    bazaKontaktow.close();

    zapisywanie_adresow_do_pliku();

    cout << endl << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
    system("pause");

    return liczbaPorzadkowa;
}

void wyszukiwanie_po_imieniu(int iloscW) {
    string imie, nazwisko, email, adres, nr_telefonu;
    int LP;

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);

    system("cls");

    if(bazaKontaktow.is_open()==false) {
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

    for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
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

    bazaKontaktow.close();

    return;
}

void wyszukiwanie_po_nazwisku(int iloscW) {
    string imie, nazwisko, email, adres, nr_telefonu;
    int LP;

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);

    system("cls");

    if(bazaKontaktow.is_open()==false) {
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

    for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
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

    bazaKontaktow.close();

    return;
}

void wyswietlanie_wszystkich_wpisow(int iloscW) {
    string imie, nazwisko, email, adres, nr_telefonu;
    int liczbaPorzadkowaWpisu;

    bazaKontaktow.open("Baza kontaktow.txt", ios::in);

    system("cls");

    if(bazaKontaktow.is_open()==false) {
        cout << "Brak kontaktow w bazie. Dodaj nowe kontakty z poziomumenu glownego." << endl << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
        system("pause");
        return;
    }

    sort(adresaci.begin(), adresaci.end(), [](wpis a, wpis b) {
        return a.LP < b.LP;
    });

    for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
        cout << "Lp: " << adresaci[obecnyWpis].LP << endl;
        cout << "Imie i nazwisko: " << adresaci[obecnyWpis].imie << " " << adresaci[obecnyWpis].nazwisko << endl;
        cout << "Nr telefonu: " << adresaci[obecnyWpis].nr_telefonu << endl;
        cout << "Adres email: " << adresaci[obecnyWpis].email << endl;
        cout << "Adres: " << adresaci[obecnyWpis].adres << endl << endl;
    }

    cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;
    system("pause");

    bazaKontaktow.close();

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
            for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
                if(adresaci[obecnyWpis].LP == IDdoUsuniecia) {
                    LPusuwanego = obecnyWpis;
                    break;
                }
            }

            if(LPusuwanego < 0) {
                system("cls");

                cout << "Nie znaleziono adresata o takim numerze. Sprobuj ponownie.";

                     Sleep(3000);

                continue;
            }

            adresaci.erase(adresaci.begin() + LPusuwanego);

            iloscW--;

            //nastepnyID.push_back(IDdoUsuniecia);

            //sort(nastepnyID.begin(), nastepnyID.end());

            zapisywanie_adresow_do_pliku();

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

        for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
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

        zapisywanie_adresow_do_pliku();

        cout << "Dane edytowane pomyslnie." << endl;

        cout << "Wcisnij dowolny klawisz, aby powrocic do menu glownego" << endl;

        system("pause");

        return;
    }
}

void zapisywanie_adresow_do_pliku() {
    bazaKontaktow.open("Baza kontaktow.txt", ios::out | ios::trunc);

    sort(adresaci.begin(), adresaci.end(), [](wpis a, wpis b) {
        return a.LP < b.LP;
    });

    for(int obecnyWpis = 0; obecnyWpis < adresaci.size(); obecnyWpis++) {
        bazaKontaktow << adresaci[obecnyWpis].LP << "|" << adresaci[obecnyWpis].imie << "|" << adresaci[obecnyWpis].nazwisko;
        bazaKontaktow << "|" << adresaci[obecnyWpis].email << "|" << adresaci[obecnyWpis].adres << "|" << adresaci[obecnyWpis].nr_telefonu << "|" << endl;
    }

    bazaKontaktow.close();

    return;
}
