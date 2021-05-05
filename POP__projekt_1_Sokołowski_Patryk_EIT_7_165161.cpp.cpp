// POP_projekt_1_Sokołowski_Patryk_EIT_7_165161    Dev-C++ 5.11
#include <iostream>
#include <windows.h> //system(), kolory
#include <cmath>  //sqrt()
#include <ctime>
#include <cstring>
#include <conio.h> //getch()

using namespace std;

struct licznik {
  	double srednia;
	int ilosc;
};

void instrukcja();
void ryspole(HANDLE hOut, string plansza[41][41]);
void rysuj(HANDLE hOut, string plansza[41][41]); 
void kwadrat(HANDLE hOut, string plansza[41][41], string obraz[39][39]);  
void trojkat(HANDLE hOut, string plansza[41][41], string obraz[39][39]);  
void romb(HANDLE hOut, string plansza[41][41], string obraz[39][39]);
void okrag(HANDLE hOut, string plansza[41][41], string obraz[39][39]);
void czysc(string plansza[41][41], string obraz[39][39]);
void wyniki(const licznik tab[5],clock_t najkr, clock_t najdl);
void srednia(licznik tab[5]);
int kolor();
void wypiszwykres(string wykres[10][4], int najwsr, int najmsr);

int main() {
	
	instrukcja();
		
	unsigned char znak;  //klawisz
	
	HANDLE hOut;								//potrzebne do
	hOut = GetStdHandle( STD_OUTPUT_HANDLE );	//ust kolorow
	
	licznik tab[5]; //  0-wszystkie, 1-kwadrat, 2-trojkat, 3-romb, 4-okrag
	
	tab[0].srednia = 0; //srednia calosci
  	tab[0].ilosc = 0;  // licznik calosci
	
	string plansza[41][41];
	string obraz[39][39];
	
	ryspole (hOut, plansza);	
	
	clock_t starttime;       //czas
	clock_t czas = 0;
	clock_t najkr = 10000;
	clock_t najdl = 0;
	clock_t endtime;
	starttime = clock();
	
	srand(time(NULL));

	do {
		system("cls");
		
		int fig = rand()%4;  //losowanie figury do rysowania
		
		endtime = clock() - starttime;
		endtime = 60 - endtime/1000;
		cout.width(23);
		cout<<endl<<tab[0].ilosc;
		cout.width(34);
		cout<<endtime<<endl<<endl;	
		
		if (fig == 0 ) {
			kwadrat (hOut, plansza, obraz);
			
			czas = clock();
			
			do {
				znak = getch();	
			}
			while (znak != 119);  // 119 to znak w
			
			czas = clock() - czas;
			if(najdl < czas) najdl = czas;
			if(najkr > czas) najkr = czas;
			tab[0].srednia += czas;
			tab[1].srednia += czas;
			
			tab[1].ilosc++;
		}
		if (fig == 1 ) {
			trojkat (hOut, plansza, obraz);
			
			czas = clock();
			
			do {
				znak = getch();	
			}
			while (znak != 115);  // 115 to znak s
			
			czas = clock() - czas;
			if(najdl < czas) najdl = czas;
			if(najkr > czas) najkr = czas;
			tab[0].srednia += czas;
			tab[2].srednia += czas;
			
			tab[2].ilosc++;
		}
		if (fig == 2 ) {
			romb (hOut, plansza, obraz);
			
			czas = clock();
			
			do {
			znak = getch();	
			}
			while (znak != 97);  // 97 to znak a
			
			czas = clock() - czas;
			if(najdl < czas) najdl = czas;
			if(najkr > czas) najkr = czas;
			tab[0].srednia += czas;
			tab[3].srednia += czas;
			
			tab[3].ilosc++;
		}
		if (fig == 3) {
			okrag (hOut, plansza, obraz);
			
			czas = clock();
			
			do {
				znak = getch();	
			}
			while (znak != 100);  // 119 to znak d
			
			czas = clock() - czas;
			if(najdl < czas) najdl = czas;
			if(najkr > czas) najkr = czas;
			tab[0].srednia += czas;
			tab[4].srednia += czas;
			
			tab[4].ilosc++;
		}
		tab[0].ilosc++;			
				
		czysc(plansza, obraz);
		
	} while(endtime > 0 );
	
	srednia(tab);
	
	system("cls");
		
	wyniki(tab, najkr, najdl);
	
	return 0;
}

void instrukcja() {
	cout<<endl<<"REFLEKST"<<endl<<endl<<"Test trwa 60s, polaga na rozpozaniu figury w mozliwie krotkim czasie."<<endl<<endl
	<<"Klawisze:"<<endl<<"A - romb"<<endl<<"S - trojkat"<<endl<<"W - kwadrat"<<endl<<"D - okrag"<<endl;
	
	cout<<endl<<"WCISNIJ DOWOLNY KLAWISZ BY ROZPOACZAC TEST!"<<endl;
	getch(); //dowolny klawisz by rozpocz¹æ test	
	system("cls");
}

int kolor() {
	
	int a = rand()%256;  // a to liczba odpowiadajaca za kolor
	if ( !(a%17 == 0 || a%17 == 1 || a%17 == 16))  //odrzucenie nie kontrastujacych kolorow
		return a;
	else kolor();
}
void srednia(licznik tab[5]) {
	for (int i = 0; i < 5; i++) {
		tab[i].srednia = tab[i].srednia/(tab[i].ilosc); 
	}	
}

void wyniki(const licznik tab[5], clock_t najkr, clock_t najdl) {
	
	//tabela
	cout<<endl<<endl<<'\t'<<'\t'<<"Figury: "<<"|  "<<"Sredni czas: "<<"|"<<'\t'<<"Czasy (ms): "<<endl;
	
	for(int i = 0; i < 65; i++)	cout<<"-";
	
	cout<<endl<<"Kwadraty: "<<'\t'<<tab[1].ilosc<<'\t'<<"|"<<'\t'<<tab[1].srednia<<'\t'<<"|"<<'\t'<<"Najkrotszy: "<<najkr << endl;
		for(int i = 0; i < 65; i++)	cout<<"-";
	cout<<endl<<"Trojkaty: "<<'\t'<<tab[2].ilosc<<'\t'<<"|"<<'\t'<<tab[2].srednia<<'\t'<<"|"<<'\t'<<"Najdluzszy: "<<najdl<< endl;
		for(int i = 0; i < 65; i++)	cout<<"-";
	cout<<endl<<"Romby: "<<'\t'<<'\t'<<tab[3].ilosc<<'\t'<<"|"<<'\t'<<tab[3].srednia<<'\t'<<"|"<<'\t'<<"Srednia: "<<tab[0].srednia<< endl;
		for(int i = 0; i < 65; i++)	cout<<"-";
	cout<<endl<<"Okregi: "<<'\t'<<tab[4].ilosc<<'\t'<<"|"<<'\t'<<tab[4].srednia<<endl<<endl;
	
	int najwsr = 0;
	for(int i = 1; i < 5; i++) if(najwsr < tab[i].srednia) najwsr=tab[i].srednia;
	
	int najmsr = najwsr;
	for(int i = 1; i < 5; i++) if(najmsr > tab[i].srednia) najmsr=tab[i].srednia;
	
	// tworzenia wykres	
	string wykres[10][4];
	int minwykresu = najmsr/((najwsr-najmsr)/10); 
	int maxwykresu = najwsr/((najwsr-najmsr)/10);
	for (int i = minwykresu; i < maxwykresu; i++) {  //wykres od najmniejszej do najwiekszej wartosci sredniej co 10%
		for (int j = 0; j < 4 ; j++) {
			if( i > (tab[j+1].srednia/((najwsr-najmsr)/10)) ) wykres[i-minwykresu][j] = " "; //tab[1].srednia do tab[4].srednia to wartosci srednich dla figur
			else wykres[i-minwykresu][j] = "_";
		}
	}
		
	wypiszwykres( wykres, najwsr, najmsr );

}

void wypiszwykres(string wykres[10][4], int najwsr, int najmsr) {
	cout<<endl<<"k  t  r  o  "<<najwsr<<endl;
	for (int i = 9; i >= 0; i--) { 
		for (int j = 0; j < 4 ; j++) {
			cout<<wykres[i][j]<<"  ";
		}
		cout<<endl;
	}
	cout<<"            "<<najmsr<<endl;
}

void ryspole(HANDLE hOut, string plansza[41][41]) {

 	for (int i = 0; i < 41; i++) {
		for (int j = 0; j < 41; j++) {

			if (i == 0) plansza[i][j] = ".";

			if (j == 0) plansza[i][j] = ".";	
			
			if (j == 40) plansza[i][j] = ".";
			
			if ( j > 0 and j < 40 and i > 0 and i < 40) plansza[i][j] = " ";	

			if (i == 40) plansza[i][j] = ".";

		}
	}
	
	for (int i = 0; i < 41; i++) {
		cout.width(19);
		cout <<( cout.fill() );
		for (int j = 0; j < 41; j++) {
			cout<<plansza[i][j];
		}
		cout<<endl;
	}
}

void rysuj(HANDLE hOut, string plansza[41][41]) {
	
	int kol = kolor();
	
	for (int i = 0; i < 41; i++) {
		cout.width(19);
		cout <<( cout.fill() );
		for (int j = 0; j < 41; j++) {
			SetConsoleTextAttribute( hOut, kol );
			cout<<plansza[i][j];
			SetConsoleTextAttribute( hOut, 7 );
		}
		cout<<endl;
	}
 	
}

void kwadrat(HANDLE hOut, string plansza[41][41],string obraz[39][39]) {
	
 	for (int i = 0; i < 39; i++) {
		for (int j = 0; j < 39; j++) {

			if (( (i == 11 or i == 27) and j > 10 and j < 28 ) or ((j == 11 or j == 27) and i > 11 and i < 27)) {
				obraz[i][j] = "*";
				plansza[i+1][j+1] = obraz[i][j];
			}		
		}
	}

	rysuj (hOut, plansza);
}

void trojkat(HANDLE hOut, string plansza[41][41],string obraz[39][39]) {
	
 	for (int i = 15; i < 26; i++) {  //ograniczenie z gory i dolu
		for (int j = 10; j < 31; j++) {  //ograniczenie z lewej i prawej
			for (int k = 0; k < 10; k++) {
					if( i == (15+k) and j == (20-k)) {
					obraz[i+k][j-k] = "*";
					plansza[i+1][j+1] = obraz[i+k][j-k];
					} 
					if( i == (15+k) and j == (20+k)) {
					obraz[i+k][j+k] = "*";
					plansza[i+1][j+1] = obraz[i+k][j+k];
					} 
					if( i == 25) {
					obraz[i+k][j+k] = "*";
					plansza[i+1][j+1] = obraz[i+k][j+k];
					}

			}
		}
	}

	rysuj (hOut, plansza);
}

void romb(HANDLE hOut, string plansza[41][41],string obraz[39][39]) {
	
 	for (int i = 10; i < 31; i++) {  //ograniczenie z gory i dolu
		for (int j = 10; j < 31; j++) {  //ograniczenie z lewej i prawej
			for (int k = 0; k < 10; k++) {
					if( (i == (10+k) and j == (20-k)) or (i == (19+k) and j == (29-k)) ) {
					obraz[i+k][j-k] = "*";
					plansza[i+1][j+1] = obraz[i+k][j-k];
					} 
					if( ( i == (10+k) and j == (20+k)) or ( i == (19+k) and j == (11+k)) ) {
					obraz[i+k][j+k] = "*";
					plansza[i+1][j+1] = obraz[i+k][j+k];
					} 

			}
		}
	}
	rysuj (hOut, plansza);
}

void okrag(HANDLE hOut, string plansza[41][41],string obraz[39][39]) {
	
	for (int i = 0; i < 39; i++)
	{
    	for (int j = 0; j < 39; j++)
    	{
        float r = sqrt((i - 20)*(i - 20) + (j - 20)*(j - 20));
        	if (r > 10 and r < 11)
        	{
        	obraz[i][j] = "*";
        	plansza[i+1][j+1] = obraz[i][j];
        	}
   		}
	}
	rysuj (hOut, plansza);
}

void czysc(string plansza[41][41], string obraz[39][39]) {
	for (int i = 0; i < 39; i++) {
		for (int j = 0; j < 39; j++) {
			obraz[i][j] = " ";
			plansza[i+1][j+1] = obraz[i][j];
		}
	}
}

