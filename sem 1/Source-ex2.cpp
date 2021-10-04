#include<iostream>
#include<conio.h>






using namespace std;

void main() {
	int x = 10;

	cout << "Adresa lui X este :" << &x << endl;

	int *px = &x;
	cout << "Variabila px contine valoarea: " << px << endl;
	cout << "La adresa valorii variabilei px se afla: " << *px << endl;
	cout << "Adresa lui px este :" << &px << endl;
	//delete px; eroare fatala->incercam sa stergem ceva de pe stack

	int *py = new int(22);
	cout << "py = " << *py << endl;
	delete py;

	int N = 5;
	int *v = new int[N];
	for (int i = 0; i < N; i++) {
		v[i] = i + 2;
	}

	for (int i = 0; i < N; i++) {
		cout << v[i] << " ";
	}
	cout << endl;


	//vectori de pointeri sem 2
	int elementNou;
	cout << "elementNou = "; cin >> elementNou;

	int *aux = new int[N + 1];
	for (int i = 0; i < N; i++) {
		aux[i] = v[i];
	}

	aux[N++] = elementNou;
	delete v;
	v = aux;


	for (int i = 0; i < N; i++) {
		cout << v[i] << " ";
	}
	cout << endl;


	_getch();
}