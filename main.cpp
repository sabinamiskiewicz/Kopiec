#include <cstdlib>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#define MAX 1024
#define ZAKRES 50
#define TAB_MAX 26

using namespace std;

template<class T>
class Kopiec
{
int * pamiec;						//Wskaznik na tablice elementow kopca
	int licznik;							//Licznik elementow
	void sortdokorz(int wybranyEl);		//Sortuje w strone korzenia zaczynajac od elementu o indeksie "wybranyEl"  SORTFORPUSH    "nrElem"
	void sortodkorz(int wybranyEl = 0);	//Sortuje w strone mlodszych pokolen zaczynajac od elementu o indeksie "wybranyEl"  sortForPop
	int nrLewegoSyna(int wybranyEl)		//Zwraca numer lewego syna elementu o indeksie "wybranyEl"
	{	return 2*wybranyEl+1;	}
	int nrPrawegoSyna(int wybranyEl)		//Zwraca numer prawego syna elementu o indeksie "wybranyEl"
	{	return 2*wybranyEl+2;	}
	int nrOjca(int wybranyEl)				//Zwraca numer ojca elementu o indeksie "wybranyEl"
	{	return (wybranyEl-1)/2;	}
public:
	Kopiec();							//Rezerwuje pamiec dla kopca oraz zeruje zmienna "licznik" 
	Kopiec(int tab[], int elemCount);	//Przekopiowuje elementy z tablicy "tab" do dopiero co zarezerwowanej pamieci kopca
	Kopiec(T){}
	~Kopiec()							//Usuwa pamiec dynamiczna kopca
	{	delete [] pamiec;	}
	void napraw();						//Rezerwuje nowa pamiec dla kopca oraz wstawia pojedynczo elementy funkcja "sortdokorz"
	void push(int element);				//Wstawia nowy element do pamieci, inkrementuje licznik i wywoluje funkcje "sortdokorz"
	int pop();							//Zwraca wartosc korzenia oraz wywoluje funkcje sortujaca "sortodkorz"
	void wyswietl();					//Wyswietla elementy kolejnych pokolen
	int ilePokolen();					//Zwraca liczbe pokolen znajdujacych sie w drzewie	
	
};

int potega(int liczba, int wykladnik)
{
if(wykladnik==1) return liczba;
return liczba*potega(liczba,wykladnik-1);
}

template<class T>
Kopiec<T>::Kopiec()							
{	
licznik = 0; pamiec = new int[MAX];	
}

template<class T>
Kopiec<T>::Kopiec(int tab[], int elemCount)
{	
pamiec = new int[MAX];		//Rezerwacja pamieci
for(int i=0; i<elemCount; i++) pamiec[i] = tab[i];	//Kopiowanie elementow
licznik = elemCount;					//Wpisanie ilosci elementow
}

template<class T>
void Kopiec<T>::napraw()
{							
for(int i=0; i<licznik; i++)
		sortdokorz(i);					//Wywolywanie sortowania dla kolejnych elementow kopca
}

template<class T>
void Kopiec<T>::push(int element)
{	pamiec[licznik++] = element;			
	sortdokorz(licznik-1);				
}

template<class T>
void Kopiec<T>::sortdokorz(int wybranyEl)
{	
	if(wybranyEl==0) return;				//Gdy kopiec nie ma elementow
	int nrOjca = (wybranyEl-1)/2;			
	if(pamiec[wybranyEl]>pamiec[nrOjca])	
	{	int temp = pamiec[nrOjca];		//Zmienna tymczasowa
		pamiec[nrOjca] = pamiec[wybranyEl];
		pamiec[wybranyEl] = temp;
		sortdokorz(nrOjca);			//Rekurencyjne wywolanie funkcji dla ojca elementu o indeksie "nrElem"
	}
}

template<class T>
int Kopiec<T>::pop()
{
	int temp = pamiec[0];				//Zapamietuje zmienna, ktora powinien zwrocic
	pamiec[0] = pamiec[--licznik];
	sortodkorz();
	return temp;
}

template<class T>
void Kopiec<T>::sortodkorz(int wybranyEl )
	{	int nrLewSyna = 2*wybranyEl+1;		//Wylicza sobie polozenie synow
		int nrPrawSyna = 2*wybranyEl+2;
		int nrWymienianego = 0;			//Zmienna zapamieta, ktory element ma zostac wymieniony
		if(nrLewSyna>=licznik) return;	//Kiedy dany element nie ma zadnego syna
		if(nrPrawSyna<=licznik)			//Kiedy dany element ma obu synow
		{
			if(pamiec[nrLewSyna]<pamiec[nrPrawSyna])	//Kiedy syn prawy jest wiekszy niz lewy
				nrWymienianego = nrPrawSyna;
			else										//Kiedy lewy syn jest wiekszy
				nrWymienianego = nrLewSyna;
		}
		else							//Kiedy jest tylko jeden syn
			nrWymienianego = nrLewSyna;

		//Etap zamiany elementow
		if(pamiec[wybranyEl]<pamiec[nrWymienianego])	//Wymienia tylko kiedy ojciec jest mniejszy ni¿ wymieniany
		{
			int temp = pamiec[nrWymienianego];
			pamiec[nrWymienianego] = pamiec[wybranyEl];
			pamiec[wybranyEl] = temp;
			sortodkorz(nrWymienianego);				//Od razu sortuje zaczynajac od wymienionego elementu
		}
	}

template<class T>
void Kopiec<T>::wyswietl()
{	
	int wybranyEl = 0;					//Licznik elementow wyswietlonych
	int wykl = 1;					//wykladnik potegi
	int warunkowy = 1;				//Po ilu elementach nalezy zejsc do nastepnej lini
	while(wybranyEl < licznik)			
	{
		cout<<licznik << left << 10 << pamiec[wybranyEl++];     //ustawia szerokosc wydruku liczby
		if(wybranyEl == warunkowy)		//Sprawdzenie czy koniec pokolenia
		{	cout<<licznik << endl;
			warunkowy += potega(2,wykl++);
		}
	}
}

template<class T>
int Kopiec<T>::ilePokolen()
{
	int ile_poziomow = 0;
	int licznik_temp = licznik; 
	while(licznik_temp > 0)
	{	licznik_temp /= 2;	
		ile_poziomow++;
	}
	return ile_poziomow;
}

void losujElementy(int tab[], int elemCount)
{	srand(time(NULL));
	for(int i=0; i<elemCount; i++)
		tab[i] = (int)(ZAKRES*rand())/RAND_MAX;
}
int main()
{
	int tablica[TAB_MAX];		//Tablica, przechowujaca losowe elementy
	losujElementy(tablica,TAB_MAX);
	Kopiec<int> nowy;
	nowy.wyswietl();
	cout << endl << endl;
	nowy.napraw();
	nowy.wyswietl();
	cout << endl << endl;
	cin.ignore();
	getchar();
return 0;
}