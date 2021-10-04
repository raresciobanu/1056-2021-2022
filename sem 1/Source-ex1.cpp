#include<iostream>
#include<conio.h>
using namespace std;

void fct1(int a, int b) {
	cout << "a = " << a << " b = " << b << endl;

	a = 300;
	b = 400;
}


void fct2(int &c, int &d) {
	cout << "c = " << c << " d = " << d << endl;

	c = 900;
	d = 770;
}


typedef struct {
	int varsta;
	bool gen; //true B or else F
	char nume[100];
	double greutate;
}persoana;

void main() {
	cout << "Salut!\n";

	persoana p;
	p.varsta = 20;
	p.gen = true;
	p.greutate = 81.5;
	strcpy_s(p.nume, "Popescu Ion");

	cout << "Persoana cu numele " << p.nume << "  are varsta " << p.varsta << " si greutatea de " << p.greutate
		<< " kg, si este de gen " << ((p.gen == true) ? "masculin" : "feminin") << endl << "\n";


	int vector[] = { 2,10,9,8 };

	for (int i = 0; i < 4; i++) {
		cout << vector[i] << " ";
	}
	cout << endl;

	int a = 100, b = 200;
	fct1(a, b);
	cout << "a = " << a << " b = " << b << endl;


	int c = 160, d = 260;
	fct2(c, d);
	cout << "c = " << c << " d = " << d << endl;

	cout << "&c = " << &c << " &d = " << &d << endl;

	_getch();
}