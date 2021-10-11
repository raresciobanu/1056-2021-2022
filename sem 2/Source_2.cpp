#include<iostream>
#include<string>

using namespace std;

enum GEN { FEMEIE, BARBAT = 3, NECUNOSCUT = 5 };

//private, protected, public
class Student {
	//by default daca nu scrii nimic totul e private
	const int ID_Matricol;
	GEN gen;
public:
	char* nume;
	string prenume = "Aaaa";
	int varsta = 22;
	int nrNote;
	double* note;

	//contr. default
	Student() :ID_Matricol(11) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int idMatricol) :ID_Matricol(idMatricol) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(string prenume, int varsta) :ID_Matricol(90) {
		this->varsta = varsta;
		this->prenume = prenume;

		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int id, const char* nume, string prenume, int varsta, int nrNote, double* note, GEN gen) :ID_Matricol(id) {
		this->nume = new char[strlen(nume) + 1];
		strcpy_s(this->nume, strlen(nume) + 1, nume);

		this->prenume = prenume;
		this->varsta = varsta;
		this->nrNote = nrNote;

		this->note = new double[nrNote];
		for (int i = 0; i < nrNote; i++) {
			this->note[i] = note[i];
		}

		this->gen = gen;
	}

	const char* getGenInCaractere() {
		switch (gen) {
		case FEMEIE:
			return "femeie";
		case BARBAT:
			return "barbat";
		case NECUNOSCUT:
			return "necunoscut";
		}
	}

	void afisare() {
		cout << "Studentul are numele " << (nume != nullptr ? nume : "---numele nu este setat---") << " si prenumele " << prenume << " cu ID ul matricol " << ID_Matricol
			<< " are varsta de " << varsta << " genul este " << getGenInCaractere() << " si notele: ";
		for (int i = 0; i < nrNote; i++) {
			cout << note[i] << " ";
		}

		cout << endl;
	}
};



void main() {
	Student s;
	s.afisare();

	Student s1(2);
	s1.afisare();

	Student s2("Rares", 26);
	s2.afisare();

	double v[] = { 6.5, 7, 8, 10, 9.8 };
	Student s3(100, "Popescu", "Ionel", 22, 5, v, GEN::BARBAT);
	s3.afisare();


}