#include<iostream>
#include<list>
using namespace std;

class Persoana {
	string CNP;
	string nume;

public:
	Persoana() {

	}

	Persoana(string CNP, string nume) {
		this->CNP = CNP;
		this->nume = nume;
	}

	friend ostream& operator<<(ostream& out, const  Persoana& p) {
		out << "CNP: " << p.CNP << " nume: " << p.nume << endl;

		return out;
	}

	bool operator==(Persoana p) {
		return this->CNP == p.CNP && this->nume == p.nume;
	}

	virtual int getCotizatie() {
		return 0;
	}

	string getCNP() {
		return this->CNP;
	}

	string getNume() {
		return this->nume;
	}
};

class MembruPlin :public Persoana {

public:
	MembruPlin() :Persoana() {
	}

	MembruPlin(string CNP, string nume) :Persoana(CNP, nume) {
	}

	friend ostream& operator<<(ostream& out, const  MembruPlin& m) {
		out << (Persoana)m;

		return out;
	}

	int getCotizatie() {
		return 100;
	}


};


class MembruSimpatizant :public Persoana {

public:
	MembruSimpatizant() :Persoana() {
	}

	MembruSimpatizant(string CNP, string nume) :Persoana(CNP, nume) {
	}

	friend ostream& operator<<(ostream& out, const  MembruSimpatizant& m) {
		out << (Persoana)m;

		return out;
	}

	int getCotizatie() {
		return 50;
	}

	operator MembruPlin() {
		MembruPlin m(getCNP(), getNume());
		return m;
	}
};

class AsociatieDePersoane {
	list<Persoana*> persoane;
	int N;

public:
	AsociatieDePersoane() {

	}

	AsociatieDePersoane(list<Persoana*> persoane, int N) {//inainte era AsociatieDePersoane(Persoana *persoane, int N)
		this->N = N;
		/*this->persoane = new Persoana[N];
		for (int i = 0; i < N; i++) {
			this->persoane[i] = persoane[i];
		}*/
		this->persoane = persoane;
	}

	AsociatieDePersoane(const AsociatieDePersoane& ap) {
		this->N = ap.N;
		/*this->persoane = new Persoana[ap.N];
		for (int i = 0; i < ap.N; i++) {
			this->persoane[i] = ap.persoane[i];
		}*/
		this->persoane = ap.persoane;

	}

	~AsociatieDePersoane() {
		/*if (this->persoane != nullptr) {
			delete[] this->persoane;
		}*/
	}

	friend ostream& operator<<(ostream& out, const  AsociatieDePersoane& a) {
		out << "N=" << a.N << endl;

		/*	for (int i = 0; i < a.N; i++) {
				out << a.persoane[i] << endl;

			}*/

		for (Persoana* p : a.persoane) {
			out << *p << endl;
		}

		return out;
	}

	void operator+=(Persoana* p) {
		/*	Persoana* aux = new Persoana[N + 1];
			for (int i = 0; i < N; i++) {
				aux[i] = this->persoane[i];
			}

			aux[N++] = p;
			delete[] this->persoane;
			this->persoane = aux;*/

		this->persoane.push_back(p);
	}

	void operator-=(Persoana* p) {
		/*int ok = 0;
		for (int i = 0; i < N; i++) {
			if (p == this->persoane[i]) {
				ok = 1;
			}
		}

		if (ok == 1) {
			int k = 0;
			Persoana* aux = new Persoana[N - 1];
			for (int i = 0; i < N; i++) {
				if (!(p == this->persoane[i])) {
					aux[k++] = this->persoane[i];
				}
			}

			N--;
			delete[] this->persoane;
			this->persoane = aux;
		}*/
		this->persoane.remove(p);
	}

	list<Persoana*> getPersoane() {
		return this->persoane;
	}
};


class PartidPolitic :private AsociatieDePersoane {
	int cotizatie;
public:
	PartidPolitic() {
		this->cotizatie = 0;
	}

	//PartidPolitic(Persoana* persoane, int N, int cotizatie) :AsociatieDePersoane(persoane, N) {
	//	this->cotizatie = cotizatie;
	//}

	PartidPolitic(list<Persoana*> persoane, int N, int cotizatie) :AsociatieDePersoane(persoane, N) {
		this->cotizatie = cotizatie;
	}

	friend ostream& operator<<(ostream& out, const  PartidPolitic& p) {
		out << (AsociatieDePersoane)p;
		out << "cotizatie: " << p.cotizatie << endl;

		return out;
	}

	void operator+=(Persoana* p) {
		AsociatieDePersoane::operator+=(p);
	}

	~PartidPolitic() {

	}

	list<Persoana*> getPersoane() {
		return AsociatieDePersoane::getPersoane();
	}
};


int main() {
	//Persoana p1("2121211212", "Ion Popescu");
	//Persoana p2("32436654", "Vasile Tudpr");
	//Persoana p3("9797756656", "Maria Victor");

	Persoana* p1 = new Persoana("2121211212", "Ion Popescu");
	Persoana* p2 = new Persoana("32436654", "Vasile Tudpr");
	Persoana* p3 = new Persoana("9797756656", "Maria Victor");

	AsociatieDePersoane asociatie;
	asociatie.operator+=(p1);
	asociatie += (p2);
	asociatie += (p3);

	//Persoana p4("555577777", "Marius Strat");
	Persoana* p4 = new Persoana("555577777", "Marius Strat");

	asociatie += (p4);

	cout << asociatie << endl << endl;
	asociatie -= (p4);
	cout << asociatie << endl << endl;

	MembruSimpatizant membruSimpatizant("332222", "George");

	MembruPlin membruPlin = membruSimpatizant;
	cout << membruPlin << endl;

	MembruPlin mp1("22", "Rares");
	MembruPlin mp2("23", "Andreea");
	MembruSimpatizant ms1("28", "Mihai");
	MembruSimpatizant ms2("27", "John");

	//late binding - nu uitati tot timpul de constructorul de copiere in clasele cu pointeri...de asta crapa la seminar
	/*Persoana** persoane = new Persoana * [4]{ &mp1, &mp2, &ms1, &ms2 };
	double cotizatie = 0;
	for (int i = 0; i < 4; i++) {
		cotizatie += persoane[i]->getCotizatie();
	}
	cout << "cotizatie = " << cotizatie << endl;*/

	//STL - se inlocuieste Persoana * cu list<Persoana*>......
	//ca sa mearga late binding ul in partid si asociatie asociatie ar fi trebuit la ex de mai sus sa schimb Persoana * cu Persoana **

	//in schimb am testat in main cu Persoana** late binding-ul....daca la examen ti se cere sa faci modificarile in clasa atunci trebuie sa schimbi
	//Persoana * in Persoana **

	list<Persoana*> listaPersoane;
	listaPersoane.push_back(&mp1);
	listaPersoane.push_back(&mp2);
	listaPersoane.push_back(&ms1);
	listaPersoane.push_back(&ms2);

	PartidPolitic pp(listaPersoane, listaPersoane.size(), 1000);
	cout << pp << endl << endl;

	double cotizatie = 0;
	for (Persoana* p : pp.getPersoane()) {
		cotizatie += p->getCotizatie();
	}
	cout << "cotizatie = " << cotizatie << endl;
}