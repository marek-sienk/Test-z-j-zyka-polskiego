//---------------------------------------------------------------------------

#include <windows.h>

#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>

using namespace std;

//---------------------------------------------------------------------------

struct rezultat
{
        char imie[20];
        char nazwisko[20];
        int poprawne;
        int wszystkie;
        float ocena;
};

struct zadanie
{
        char pytanie[100];
        char a[30];
        char b[30];
        char c[30];
        char d[30];
        char poprawna;
};

void dodaj (zadanie zad)
{
        cout << "Wprowadz pytanie:" << endl;
        cin.getline (zad.pytanie, 100, '\n');

        cout << "Odpowiedz a:" << endl;
        cin.getline (zad.a, 30, '\n');

        cout << "Odpowiedz b:" << endl;
        cin.getline (zad.b, 30, '\n');

        cout << "Odpowiedz c:" << endl;
        cin.getline (zad.c, 30, '\n');

        cout << "Odpowiedz d:" << endl;
        cin.getline (zad.d, 30, '\n');

        while (1)
        {
                cout << "Zaznacz poprawna odpowiedz (a, b, c, d):" << endl;
                cin >> zad.poprawna;
                if (zad.poprawna == 'a' || zad.poprawna == 'b' || zad.poprawna == 'c' || zad.poprawna == 'd')
                        break;
                else cout << "Blad zaznaczania poprawnej odpowiedzi!";
        }

        ofstream plik ("test.txt", ios::app);
        if (plik)
        {
                plik.write(reinterpret_cast<char*>(&zad),sizeof(zad));
                cout << "Pytanie zostalo dodane do testow";
        }
        else cout << "Blad zapisu do pliku!";
        plik.close();
}

void edytuj (zadanie zad, int i)
{
        HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);

        ifstream plik ("test.txt");
        plik.seekg (sizeof (struct zadanie) * i);
        plik.read (reinterpret_cast<char*> (&zad), sizeof (zad));
        plik.close();

        cout << i + 1<< ". " << zad.pytanie << endl;
        if (zad.poprawna == 'a')
        {
                SetConsoleTextAttribute (h, 10);
                cout << "(a) " << zad.a << endl;
                SetConsoleTextAttribute (h, 7);
                cout << "(b) " << zad.b << endl;
                cout << "(c) " << zad.c << endl;
                cout << "(d) " << zad.d << endl;
        }
        else if (zad.poprawna == 'b')
        {
                cout << "(a) " << zad.a << endl;
                SetConsoleTextAttribute (h, 10);
                cout << "(b) " << zad.b << endl;
                SetConsoleTextAttribute (h, 7);
                cout << "(c) " << zad.c << endl;
                cout << "(d) " << zad.d << endl;
        }
        else if (zad.poprawna == 'c')
        {
                cout << "(a) " << zad.a << endl;
                cout << "(b) " << zad.b << endl;
                SetConsoleTextAttribute (h, 10);
                cout << "(c) " << zad.c << endl;
                SetConsoleTextAttribute (h, 7);
                cout << "(d) " << zad.d << endl;
        }
        else if (zad.poprawna == 'd')
        {
                cout << "(a) " << zad.a << endl;
                cout << "(b) " << zad.b << endl;
                cout << "(c) " << zad.c << endl;
                SetConsoleTextAttribute (h, 10);
                cout << "(d) " << zad.d << endl;
                SetConsoleTextAttribute (h, 7);
        }

        cout << "Wprowadz pytanie:" << endl;
        cin.getline (zad.pytanie, 100, '\n');

        cout << "Odpowiedz a:" << endl;
        cin.getline (zad.a, 30, '\n');

        cout << "Odpowiedz b:" << endl;
        cin.getline (zad.b, 30, '\n');

        cout << "Odpowiedz c:" << endl;
        cin.getline (zad.c, 30, '\n');

        cout << "Odpowiedz d:" << endl;
        cin.getline (zad.d, 30, '\n');

        while (1)
        {
                cout << "Zaznacz poprawna odpowiedz (a, b, c, d):" << endl;
                cin >> zad.poprawna;
                if (zad.poprawna == 'a' || zad.poprawna == 'b' || zad.poprawna == 'c' || zad.poprawna == 'd')
                        break;
                else cout << "Blad zaznaczania poprawnej odpowiedzi!";
        }

        ofstream plik2 ("test.txt", ios::in);
        if (plik2)
        {
                plik2.seekp (sizeof(struct zadanie) * i);
                plik2.write (reinterpret_cast<char*> (&zad), sizeof(zad));
                cout << "Pytanie zostalo edytowane";
        }
        else cout << "Blad zapisu do pliku!";
        plik2.close();
}

void usun (zadanie zad, int i)
{
        int j=0;

        ifstream p ("test.txt");
        p.seekg (sizeof (struct zadanie) * i);
        p.read (reinterpret_cast<char*> (&zad), sizeof (zad));
        p.close();

        cout << "Usunieto:" << endl;
        cout << i + 1 << ". " << zad.pytanie << endl;
        cout << "(a) " << zad.a << endl;
        cout << "(b) " << zad.b << endl;
        cout << "(c) " << zad.c << endl;
        cout << "(d) " << zad.d << endl;

        ofstream plik ("tmp.txt", ios::trunc);
        ifstream plik2 ("test.txt");

        while (1)
        {
                plik2.read (reinterpret_cast<char*> (&zad), sizeof (zad));
                if (plik2.eof())
                        break;
                if (j!=i)
                        plik.write (reinterpret_cast<char*> (&zad), sizeof(zad));
                j++;
        }

        plik.close();
        plik2.close();

        ifstream odczyt ("tmp.txt");
        ofstream zapis ("test.txt");
        while (1)
        {
                odczyt.read (reinterpret_cast<char*> (&zad), sizeof (zad));
                if (odczyt.eof())
                        break;
                zapis.write (reinterpret_cast<char*> (&zad), sizeof(zad));
        }
        odczyt.close();
        zapis.close();
}

void wypisz_pyt (zadanie zad)
{
        int i=1;
        ifstream plik ("test.txt");

        while (1)
        {
                plik.read (reinterpret_cast<char*> (&zad), sizeof (zad));
                if (plik.eof())
                        break;
                cout << i << ". " << zad.pytanie << endl;
                i++;
        }
        plik.close();
}

void wypisz_pyt_odp (zadanie zad)
{
        int i=1;
        HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
        ifstream plik ("test.txt");

        while (1)
        {
                plik.read (reinterpret_cast<char*> (&zad), sizeof (zad));
                if (plik.eof())
                        break;
                cout << i << ". " << zad.pytanie << endl;

                if (zad.poprawna == 'a')
                {
                        SetConsoleTextAttribute (h, 10);
                        cout << "(a) " << zad.a << endl;
                        SetConsoleTextAttribute (h, 7);
                        cout << "(b) " << zad.b << endl;
                        cout << "(c) " << zad.c << endl;
                        cout << "(d) " << zad.d << endl;
                }
                else if (zad.poprawna == 'b')
                {
                        cout << "(a) " << zad.a << endl;
                        SetConsoleTextAttribute (h, 10);
                        cout << "(b) " << zad.b << endl;
                        SetConsoleTextAttribute (h, 7);
                        cout << "(c) " << zad.c << endl;
                        cout << "(d) " << zad.d << endl;
                }
                else if (zad.poprawna == 'c')
                {
                        cout << "(a) " << zad.a << endl;
                        cout << "(b) " << zad.b << endl;
                        SetConsoleTextAttribute (h, 10);
                        cout << "(c) " << zad.c << endl;
                        SetConsoleTextAttribute (h, 7);
                        cout << "(d) " << zad.d << endl;
                }
                else if (zad.poprawna == 'd')
                {
                        cout << "(a) " << zad.a << endl;
                        cout << "(b) " << zad.b << endl;
                        cout << "(c) " << zad.c << endl;
                        SetConsoleTextAttribute (h, 10);
                        cout << "(d) " << zad.d << endl;
                        SetConsoleTextAttribute (h, 7);
                }
                i++;
        }
        plik.close();
}

void wypisz_wyniki (rezultat rez)
{
        int i=1;
        ifstream plik ("wyniki.txt");
        while (1)
        {
                plik.read (reinterpret_cast<char*> (&rez), sizeof (rez));
                if (plik.eof())
                        break;
                cout << i << ". " << rez.nazwisko << " " << rez.imie << endl;
                cout << "  poprawne odpowiedzi: " << rez.poprawne;
                cout << " wszystkie odpowiedzi:" << rez.wszystkie;
                cout << " procent: " << (float)rez.poprawne/(float)rez.wszystkie * 100;
                cout << " ocena: " << rez.ocena << endl;
                i++;
        }
        plik.close();
}

void sort_wyniki_nazw (rezultat rez, rezultat rez2, int n)
{
        int i, j, ktory;

        for (i=0; i<n; i++)
        {
                ifstream plik ("wyniki.txt");
                ofstream plik2 ("wyniki.txt", ios::in);

                for (j=0; j<n-1; j++)
                {
                        plik.seekg (sizeof(struct rezultat)*(j));
                        plik.read (reinterpret_cast<char*>(&rez2), sizeof(rez2));
                        plik.read (reinterpret_cast<char*>(&rez), sizeof(rez));

                        if (strcmp (rez2.nazwisko, rez.nazwisko) > 0)
                        {
                                plik2.seekp(sizeof(struct rezultat)*(j+1));
                                plik2.write(reinterpret_cast<char*>(&rez2), sizeof(rez2));

                                plik2.seekp(sizeof(struct rezultat)*(j));
                                plik2.write(reinterpret_cast<char*>(&rez), sizeof(rez));
                        }
                }
                plik.close();
                plik2.close();

        }
}

void sort_wyniki_ocena (rezultat rez, rezultat rez2, int n)
{
        int i, j, ktory;

        for (i=0; i<n; i++)
        {
                ifstream plik ("wyniki.txt", ios::in);
                ofstream plik2 ("wyniki.txt", ios::in);

                for (j=0; j<n-1; j++)
                {
                        plik.seekg (sizeof(struct rezultat)*(j));
                        plik.read (reinterpret_cast<char*>(&rez2), sizeof(rez2));
                        plik.read (reinterpret_cast<char*>(&rez), sizeof(rez));

                        if (rez.ocena > rez2.ocena)
                        {
                                plik2.seekp(sizeof(struct rezultat)*(j+1));
                                plik2.write(reinterpret_cast<char*>(&rez2), sizeof(rez2));

                                plik2.seekp(sizeof(struct rezultat)*(j));
                                plik2.write(reinterpret_cast<char*>(&rez), sizeof(rez));
                        }
                }
                plik.close();
                plik2.close();

        }
}

void losuj (zadanie zad, zadanie zad2, int n)
{
        int i, j;
        time_t t;
        srand((unsigned) time(&t));
        for (i=0; i<n; i++)
        {
                ifstream plik ("test.txt");
                ofstream plik2 ("test.txt", ios::in);
                plik.seekg (sizeof(struct zadanie)*(i));
                plik.read (reinterpret_cast<char*>(&zad), sizeof(zad));
                j = rand()%n;
                plik.seekg (sizeof(struct zadanie)*(j));
                plik.read (reinterpret_cast<char*>(&zad2), sizeof(zad2));

                plik2.seekp(sizeof(struct zadanie)*(i));
                plik2.write(reinterpret_cast<char*>(&zad2), sizeof(zad2));
                plik2.seekp(sizeof(struct zadanie)*(j));
                plik2.write(reinterpret_cast<char*>(&zad), sizeof(zad));
                plik.close();
                plik2.close();
        }
}

void rozwiaz (zadanie zad, zadanie zad2, rezultat rez, int ile)
{
        HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
        int i, j, wynik=0;
        char odp;

        cout << "Wprowadz dane" << endl;
        cout << "Imie: "; cin >> rez.imie;
        cout << "Nazwisko: "; cin >> rez.nazwisko;
        system("cls");

        ifstream plik ("test.txt");
        for (i=0; i<ile; i++)
        {
                plik.seekg (sizeof(struct zadanie)*(i));
                plik.read (reinterpret_cast<char*>(&zad), sizeof(zad));
                cout << i+1 << ". " << zad.pytanie << endl;
                cout << "(a) " << zad.a << endl;
                cout << "(b) " << zad.b << endl;
                cout << "(c) " << zad.c << endl;
                cout << "(d) " << zad.d << endl;
                while (1)
                {
                        cout << "odpowiedz:" << endl;
                        cin >> odp;
                        if (odp == 'a' || odp == 'b' || odp == 'c' || odp == 'd')
                                break;
                }
                if (odp == zad.poprawna)
                {
                        wynik++;
                        SetConsoleTextAttribute (h, 10);
                        cout << "dobrze!";
                        SetConsoleTextAttribute (h, 7);
                }
                else
                {
                        SetConsoleTextAttribute (h, 4); // 4 - czerwony
                        cout << "zle!";
                        SetConsoleTextAttribute (h, 7);
                }
		getch();
                system("cls");
        }
        plik.close();

        rez.poprawne = wynik;
        rez.wszystkie = ile;

        cout << "Wyniki:" << endl;
        cout << "Liczba pytan: " << ile << endl;
        cout << "Liczba poprawnych odpowiedzi: " << wynik << endl;
        float proc = float(wynik)/float(ile) * 100;
        cout << "Procent poprawnych odpowiedzi: " << proc << "%" << endl;

        if ((proc>=51) && (proc<=60))
                rez.ocena = 3;
        else if ((proc>=61) && (proc<=70))
                rez.ocena = 3.5;
        else if ((proc>=71) && (proc<=80))
                rez.ocena = 4;
        else if ((proc>=81) && (proc<=90))
                rez.ocena = 4.5;
        else if (proc>=91)
                rez.ocena = 5;
        else
                rez.ocena = 2;

        cout << "Ocena za test: " << rez.ocena;

        ofstream plik2 ("wyniki.txt", ios::app);
        plik2.write(reinterpret_cast<char*>(&rez),sizeof(rez));
        plik2.close();

}


int main(int argc, char* argv[])
{
        zadanie zad, zad2;
        rezultat rez, rez2;
        int odp, n=0, nr, ile, n2=0;

        ifstream plik ("test.txt");
        if (plik)
        {
                while (1)
                {
                        plik.read (reinterpret_cast<char*> (&zad), sizeof (zad));
                        if (plik.eof())
                                break;
                        n++;
                }
        }
        plik.close();

        ifstream plik2 ("wyniki.txt");
        if (plik2)
        {
                while (1)
                {
                        plik2.read (reinterpret_cast<char*> (&rez), sizeof (rez));
                        if (plik2.eof())
                                break;
                        n2++;
                }
        }
        plik2.close();

        while (1)
        {
                system("cls");
                cout << "TEST Z JEZYKA POLSKIEGO, AUTOR: Marek Sienkiewicz" << endl;
                cout << "-----------------------------------------------" << endl;
                cout << "1. Rozwiaz test" << endl;
                cout << "2. Wyswietl wyniki" << endl;
                cout << "3. Wyswietl pytania" << endl;
                cout << "4. Wyswietl pytania + odpowiedzi" << endl;
                cout << "5. Wprowadz pytanie + odpowiedzi do niego" << endl;
                cout << "6. Edytuj pytanie" << endl;
                cout << "7. Usun pytanie" << endl;
                cout << "8. Sortuj wyniki wg nazwisk" << endl;
                cout << "9. Sortuj wyniki wg ocen" << endl;
                cout << "10. Koniec" << endl;
                cout << "-----------------------------------------------" << endl;
                cin >> odp;
                cin.ignore();
                system("cls");
                switch (odp)
                {
                        case 1:
                        {
                                system("cls");
                                while (1)
                                {
                                        cout << "Ile pytan? (5, 10, 20): ";
                                        cin >> ile;
                                        if (ile == 5 || ile == 10 || ile == 20)
                                                break;
                                }
                                if (ile <= n)
                                {
                                        losuj (zad, zad2, n);
                                        rozwiaz (zad, zad2, rez, ile);
                                        n2++;
                                }
                                else
                                        cout << "Brak takiej ilosci pytan!";
                                getch();
                                break;
                        }
                        case 2:
                        {
                                system("cls");
                                if (n2>0)
                                {
                                        wypisz_wyniki (rez);
                                }
                                else
                                        cout <<"Brak wynikow do wyswietlenia!";
                                getch();
                                break;
                        }
                        case 3:
                        {
                                system("cls");
                                if (n>0)
                                {
                                        wypisz_pyt (zad);
                                }
                                else
                                        cout <<"Brak pytan do wyswietlenia!";
                                getch();
                                break;
                        }
                        case 4:
                        {
                                system("cls");
                                if (n>0)
                                {
                                        wypisz_pyt_odp (zad);
                                }
                                else
                                        cout <<"Brak pytan do wyswietlenia!";
                                getch();
                                break;
                        }
                        case 5:
                        {
                                system("cls");
                                dodaj(zad);
                                n++;
                                getch();
                                break;
                        }
                        case 6:
                        {
                                system("cls");
                                cout << "Podaj nr zadania: ";
                                cin >> nr;
                                cin.ignore();
                                if (nr > 0 && nr <=n)
                                        edytuj(zad, nr-1);
                                else
                                        cout << "Brak zadania o tym numerze";
                                getch();
                                break;
                        }
                        case 7:
                        {
                                system("cls");
                                cout << "Podaj nr zadania: ";
                                cin >> nr;
                                cin.ignore();
                                if (nr > 0 && nr <=n)
                                {
                                        usun(zad, nr-1);
                                        n--;
                                }
                                else
                                        cout << "Brak zadania o tym numerze";
                                getch();
                                break;
                        }
                        case 8:
                        {
                                system("cls");
                                if (n2>0)
                                {
                                        sort_wyniki_nazw(rez, rez2, n2);
                                        wypisz_wyniki (rez);
                                }
                                else
                                        cout <<"Brak wynikow do sortowania!";
                                getch();
                                break;
                        }
                        case 9:
                        {
                                system("cls");
                                if (n2>0)
                                {
                                        sort_wyniki_ocena(rez, rez2, n2);
                                        wypisz_wyniki (rez);
                                }
                                else
                                        cout <<"Brak wynikow do sortowania!";
                                getch();
                                break;
                        }
                        case 10:
                        {
                                exit(1);
                                break;
                        }
                }
        }
}
//---------------------------------------------------------------------------
