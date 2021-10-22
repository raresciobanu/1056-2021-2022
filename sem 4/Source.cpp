#include<iostream>
#include<string>

using namespace std;

enum GEN { FEMEIE, BARBAT = 3, NECUNOSCUT = 5 };

//private, protected, public
class Student {
	//by default daca nu scrii nimic totul e private
	const int ID_Matricol;
	GEN gen;
	char* nume;
	string prenume = "Aaaa";
	int varsta = 22;
	int nrNote;
	double* note;
public:
	static int anCurent;

	//contr. default
	Student() :ID_Matricol(11) {
		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int id) :ID_Matricol(id) {
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

	/*Student(const Student& stud1, const Student& stud2):ID_Matricol(stud2.ID_Matricol) {
		this->nume = new char[strlen(stud1.nume) + 1];
		strcpy_s(this->nume, strlen(stud1.nume) + 1, stud1.nume);

		this->prenume = stud1.prenume;
		this->varsta = stud2.varsta;
		this->nrNote = stud2.nrNote;

		this->note = new double[stud2.nrNote];
		for (int i = 0; i < stud2.nrNote; i++) {
			this->note[i] = stud2.note[i];
		}

		this->gen = stud2.gen;
	}*/

	Student(const  Student& stud) :ID_Matricol(stud.ID_Matricol) {
		cout << "Constr. de copiere" << endl;
		this->nume = new char[strlen(stud.nume) + 1];
		strcpy_s(this->nume, strlen(stud.nume) + 1, stud.nume);

		this->prenume = stud.prenume;
		this->varsta = stud.varsta;
		this->nrNote = stud.nrNote;

		this->note = new double[stud.nrNote];
		for (int i = 0; i < stud.nrNote; i++) {
			this->note[i] = stud.note[i];
		}

		this->gen = stud.gen;
	}

	~Student() {
		cout << "destructor" << endl;

		if (this->nume != nullptr) {
			delete[] this->nume;
		}

		if (this->note != nullptr) {
			delete[] this->note;
		}
	}

	//op egal
	Student& operator=(const Student& stud) {//s1=s1
		if (this != &stud) {
			if (this->nume != nullptr) {
				delete[] this->nume;
			}

			if (this->note != nullptr) {
				delete[] this->note;
			}

			this->nume = new char[strlen(stud.nume) + 1];
			strcpy_s(this->nume, strlen(stud.nume) + 1, stud.nume);

			this->prenume = stud.prenume;
			this->varsta = stud.varsta;
			this->nrNote = stud.nrNote;

			this->note = new double[stud.nrNote];
			for (int i = 0; i < stud.nrNote; i++) {
				this->note[i] = stud.note[i];
			}

			this->gen = stud.gen;
		}

		return *this;
	}

	const char* getGenInCaractere() {
		switch (gen) {
		case FEMEIE:
			return "femeie";
			break;
		case BARBAT:
			return "barbat";
			break;
		case NECUNOSCUT:
			return "necunoscut";
			break;
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

	// getteri si setteri

	char* getNume() {
		return nume;
	}

	string getPrenume() {
		return prenume;
	}

	int getVarsta() {
		return varsta;
	}

	int getNrNote() {
		return nrNote;
	}

	double getNota(int index) {
		return note[index];
	}

	GEN getGen() {
		return gen;
	}

	int getIDMatricol() {
		return ID_Matricol;
	}

	double* getNote() {
		return note;
	}

	void setVarsta(int varsta) {
		this->varsta = varsta;
	}

	void setNrNote(int nrNote) {
		this->nrNote = nrNote;
	}

	void setPrenume(string prenume) {
		if (prenume.empty()) {
			throw new exception("Prenumele este gol.");
		}
		this->prenume = prenume;
	}

	void setNume(const char* nume) {
		if (nume != nullptr) {
			delete[] this->nume;//pt a evita memory leaks

			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}
		else {
			throw new exception("Numele este null.");
		}
	}

	void setNote(double* note, int nrNote) {
		if (note != nullptr && nrNote > 0) {
			this->nrNote = nrNote;

			delete[] this->note; //pt a evita memory leaks

			this->note = new double[nrNote];
			for (int i = 0; i < nrNote; i++) {
				this->note[i] = note[i];
			}

		}
		else {
			throw new exception("Note este null sau nrNote este <=0.");
		}
	}

	friend double calculeazaMedieNoteFctPrietena(Student s);
	friend ostream& operator<<(ostream& out, const Student& s);
	friend istream& operator>>(istream& in, Student& s);

	//operatori
	//op. unari
	//op. ++ - pre-incrementare
	const Student& operator++() {
		varsta++;

		return *this;
	}

	//op. ++ - post-incrementare
	const Student operator++(int) {
		Student aux(*this);

		varsta++;

		return aux;
	}

	//op binari
	//op. + (ex: cout<<s5+2;)
	int operator+(int x) {
		return varsta + x;
	}

	//op. +  (ex: cout<<s4+s3;)
	Student& operator+(Student& student) {
		Student aux(*this);

		aux.prenume = aux.prenume + "-" + student.prenume;

		return aux;
	}

	//op. + (ex: cout<<10+s3;)
	friend int operator+(int x, Student& student);

	//op += (s5+=3;)
	void operator+=(int x) {
		varsta += x;
	}
};

int Student::anCurent = 2021;

//op. + (ex: cout<<10+s3;)
int operator+(int x, Student& student) {
	return x + student.varsta;
}

ostream& operator<<(ostream& out, const Student& s) {
	out << "Studentul are numele " << (s.nume != nullptr ? s.nume : "---numele nu este setat---") << " si prenumele "
		<< s.prenume << " cu ID ul matricol " << s.ID_Matricol << " are varsta de "
		<< s.varsta << " genul este " << s.gen << " si notele: ";
	for (int i = 0; i < s.nrNote; i++) {
		out << s.note[i] << " ";
	}

	out << endl;

	return out;
}

istream& operator>>(istream& in, Student& s) {
	char aux[100];
	cout << "Nume: ";  in >> aux;

	//eviti memory leaks
	if (s.nume != nullptr) {
		delete[] s.nume;
	}

	s.nume = new char[strlen(aux) + 1];
	strcpy_s(s.nume, strlen(aux) + 1, aux);

	cout << "Prenume: ";  in >> s.prenume;
	cout << "Varsta: ";  in >> s.varsta;

	int auxGen;
	cout << "GEN: ";  in >> auxGen;
	switch (auxGen)
	{
	case 0:
		s.gen = FEMEIE;
	case 3:
		s.gen = BARBAT;
	case 5:
		s.gen = NECUNOSCUT;
	}

	cout << "NrNote: ";  in >> s.nrNote;

	//eviti memory leaks
	if (s.note != nullptr) {
		delete[] s.note;
	}

	s.note = new double[s.nrNote];
	for (int i = 0; i < s.nrNote; i++) {
		in >> s.note[i];
	}

	return in;
}

double calculeazaMedieNote(Student s) {
	double medie = 0;
	for (int i = 0; i < s.getNrNote(); i++) {
		medie += s.getNota(i);
	}
	medie = medie / s.getNrNote();

	return medie;
}

double calculeazaMedieNoteFctPrietena(Student s) {
	double medie = 0;
	for (int i = 0; i < s.nrNote; i++) {
		medie += s.note[i];
	}
	medie = medie / s.nrNote;

	return medie;
}

void main() {
	Student s;
	s.afisare();

	Student s1(2);
	s1.afisare();
	s1.anCurent = 2000;

	Student s2("Rares", 26);
	s2.afisare();
	s2.anCurent = 2001;

	double v[] = { 6.5, 7, 8, 10, 9.8 };
	Student s3(100, "Popescu", "Ionel", 22, 5, v, GEN::BARBAT);
	s3.afisare();
	s2.anCurent = 2009;

	cout << endl << endl << endl;
	Student s4(s3);
	s4.afisare();

	Student s5 = s4;
	s5.afisare();


	cout << endl << endl;
	Student s6;
	s6 = s5 = s4 = s3;
	s6.afisare();
	s6.setNume("Ion");
	s6.setPrenume("Pavel");
	s6.setVarsta(25);
	double v2[] = { 6.5, 7, 8, 10, 9.8, 10, 10, 5.5, 8, 9 };
	s6.setNote(v2, 10);

	//s6.getNume();

	// operator << afisare Student;
	cout << s6;
	//operator ++ pre-incrementare
	cout << ++s6;


	//operator ++ post-incrementare
	cout << s6++;

	//op +
	cout << s6 + 2;
}