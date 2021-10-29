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
	bool sex;//1 - B , 0 - F
public:
	static int anCurent;

	//contr. default
	Student() :ID_Matricol(11) {
		this->sex = true;

		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int id) :ID_Matricol(id) {
		this->sex = true;

		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(string prenume, int varsta) :ID_Matricol(90) {
		if (varsta <= 0) {
			throw new exception("Varsta nu este valida!");
		}
		else {
			this->varsta = varsta;
		}
		if (prenume.empty()) {
			throw new exception("Prenumele este gol.");
		}
		else {
			this->prenume = prenume;
		}

		this->sex = true;

		this->nume = new char[strlen("Anonim") + 1];
		strcpy_s(this->nume, strlen("Anonim") + 1, "Anonim");
	}

	Student(int id, const char* nume, string prenume, int varsta, int nrNote, double* note, GEN gen) :ID_Matricol(id) {

		if (nume == nullptr)
			throw new exception("numele este invalid");
		else
		{
			this->nume = new char[strlen(nume) + 1];
			strcpy_s(this->nume, strlen(nume) + 1, nume);
		}

		if (prenume.empty()) {
			throw new exception("Prenumele este gol.");
		}
		else
		{
			this->prenume = prenume;
		}

		if (varsta <= 0) {
			throw new exception("Varsta nu este valida!");
		}
		else {
			this->varsta = varsta;
		}

		if (nrNote <= 0)
			throw new exception("Numar de note invalid");
		else
			this->nrNote = nrNote;

		if (note == nullptr)
			throw new exception("vectorul de note este invalid");
		else
		{
			this->note = new double[nrNote];
			for (int i = 0; i < nrNote; i++) {
				this->note[i] = note[i];
			}
		}

		if (gen != 1 && gen != 3 && gen != 5)
			throw new exception("genul este invalid");
		else
		{
			this->gen = gen;
			if (gen == BARBAT) {
				this->sex = true;
			}
			else {
				this->sex = false;
			}
		}
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
		this->nume = new char[strlen(stud.nume) + 1];
		strcpy_s(this->nume, strlen(stud.nume) + 1, stud.nume);

		this->prenume = stud.prenume;
		this->varsta = stud.varsta;
		this->nrNote = stud.nrNote;
		this->sex = stud.sex;

		this->note = new double[stud.nrNote];
		for (int i = 0; i < stud.nrNote; i++) {
			this->note[i] = stud.note[i];
		}

		this->gen = stud.gen;
	}

	~Student() {
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
			this->sex = stud.sex;

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
	Student operator+(Student& student) {
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

	//op !
	bool operator!() {
		return !sex;
	}

	//op ==
	bool operator==(Student& s) {
		if (this == &s) {
			return true;
		}

		bool normalFields = strcmp(this->nume, s.nume) == 0 &&
			this->prenume == s.prenume &&
			this->varsta == s.varsta &&
			this->sex == s.sex &&
			this->gen == s.gen &&
			this->nrNote == s.nrNote;

		if (normalFields == true) {
			for (int i = 0; i < nrNote; i++) {
				if (this->note[i] != s.note[i]) {
					return false;
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	//op functie ()
	void operator()(int valoare) {
		if (valoare >= 1 && valoare <= 3) {
			for (int i = 0; i < nrNote; i++) {
				if (this->note[i] + valoare <= 10)
					this->note[i] += valoare;
			}
		}
		else {
			throw new exception("Eroare: valoare < 1 sau valoare >3");
		}
	}

	//op index[]
	double &operator[](int index) {
		if (index >= 0 && index < nrNote) {
			return note[index];
		}
		else {
			throw new exception("Eroare: index < 0 sau index > nrNote");
		}
	}

	//operator cast - implicit sau explicit
	operator int() {
		return varsta;
	}


	void adaugaNotaLaFinal(double nota) {
		double* aux = new double[nrNote + 1];

		for (int i = 0; i < nrNote; i++) {
			aux[i] = note[i];
		}

		aux[nrNote++] = nota;
		delete[] note; //evitam memory leaks
		note = aux;
	}

	void stergereAparitiiNota(double nota) {
		int k = 0;
		for (int i = 0; i < nrNote; i++) {
			if (nota == note[i]) {
				k++;
			}
		}
		if (k > 0) {
			int j = 0;
			double* aux = new double[nrNote - k];
			for (int i = 0; i < nrNote; i++) {
				if (nota != note[i]) {
					aux[j++] = note[i];
				}
			}
			nrNote -= k;
			delete[] note; //evitam memory leaks
			note = aux;
		}
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
		<< s.varsta << " genul este " << s.gen << " sexul: " << s.sex << " si notele: ";
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

//supraincarcare - overload
//suprascriere - override


//supraincarcare - overload
int suma(int a, int b) {
	return a + b;
}

int suma(int a, double b) {
	return a + b;
}

double suma(double a, double b, int c) {
	return a + b + c;
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
	cout << s6 << endl << endl;
	//operator ++ pre-incrementare
	cout << ++s6 << endl << endl;


	//operator ++ post-incrementare
	cout << s6++ << endl << endl;

	//op +
	cout << s6 + 10 << endl << endl;

	//op +
	cout << 3 + s6 << endl << endl;

	//op +
	cout << s6 + s2 << endl << endl;

	//op +=
	s6 += 1;
	cout << s6 << endl << endl;

	//op !
	if (!s6) {
		cout << "femeie" << endl << endl;
	}
	else {
		cout << "barbat" << endl << endl;
	}

	//op ==
	if (s3==s6) {
		cout << "s3==s6" << endl << endl;
	}
	else {
		cout << "s3!=s6" << endl << endl;
	}

	// op ()
	s6(2);
	cout << "op functie:\n"<<s6<<endl<<endl;

	//op []
	cout << s6[2] << endl << endl;

	//op cast explicit
	cout << "(int)s6=" << (int)s6 << endl << endl;

	//op cast implicit
	int varsta = s6;
	cout << "varsta=" << varsta << endl << endl;

	//supraincarcare
	cout << suma(10, 100) << endl;
	cout << suma(10, 9.3) << endl;
	cout << suma(4.4, 3.3, 10) << endl;

	
}