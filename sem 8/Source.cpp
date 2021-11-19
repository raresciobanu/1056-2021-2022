#include<iostream>

using namespace std;

//mostenire/derivare
class Vehicul {
	string culoare;
protected:
	long nrKm;
	int an;
public:
	string marca;
	char* serie;

	Vehicul() {
		this->serie = new char[strlen("HKGYHN6778") + 1];
		strcpy_s(this->serie, strlen("HKGYHN6778") + 1, "HKGYHN6778");
	}

	Vehicul(string culoare, long nrKm) {
		this->culoare = culoare;
		this->nrKm = nrKm;
	}

	Vehicul(string culoare, long nrKm, int an, string marca, const char* serie) {
		//cout << "Constructor (..,...,...,...,...) Vehicul\n";

		this->culoare = culoare;
		this->nrKm = nrKm;
		this->an = an;
		this->marca = marca;

		this->serie = new char[strlen(serie) + 1];
		strcpy_s(this->serie, strlen(serie) + 1, serie);
	}

	Vehicul(const Vehicul& v) {
		this->culoare = v.culoare;
		this->nrKm = v.nrKm;
		this->an = v.an;
		this->marca = v.marca;

		if (v.serie != nullptr) {
			this->serie = new char[strlen(v.serie) + 1];
			strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
		}
		else {
			this->serie = nullptr;//sau initializezi serie cu Anonim
		}
	}

	~Vehicul() {
		//cout << "Destructor Vehicul" << endl;

		if (this->serie != nullptr) {
			delete[] this->serie;
		}
	}

	Vehicul& operator=(const Vehicul& v) {
		//cout << "Op. = Vehicul\n";
		if (this != &v) {
			if (this->serie != nullptr) {
				delete[] this->serie;
			}

			this->culoare = v.culoare;
			this->nrKm = v.nrKm;
			this->an = v.an;
			this->marca = v.marca;

			if (v.serie != nullptr) {
				this->serie = new char[strlen(v.serie) + 1];
				strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
			}
			else {
				this->serie = nullptr;//sau initializezi serie cu Anonim
			}
		}

		return *this;
	}

	string getCuloare() {
		return culoare;
	}

	friend ostream& operator<<(ostream& out, const Vehicul& v) {
		cout << "Vehiculul are culoarea " << v.culoare << " nr km " << v.nrKm <<
			" este fabricat in anul " << v.an << " marca fiind " << v.marca <<
			" seria " << v.serie << endl;

		return out;
	}

	//cout<<(V1+10);
	Vehicul& operator+(int km) {
		this->nrKm += km;

		return *this;
	}

	bool operator==(Vehicul& v) {
		if (this == &v) {
			return true;
		}

		return this->an == v.an &&
			this->culoare == v.culoare &&
			this->marca == v.marca &&
			this->nrKm == v.nrKm &&
			strcmp(this->serie, v.serie) == 0;
	}
};

//Motocicleta "is a" Vehicul

//Motocicleta = Vehicul + arecasca
class Motocicleta : public Vehicul {
protected:
	int aaaCEVADINMOTOPROTECTED;
public:
	bool areCasca;

	Motocicleta() :Vehicul("Negru", 120000, 2011, "Hyundai", "XH2542X43243") {
		//cout << "Constructor () Motocicleta\n";

		this->areCasca = false;
	}

	Motocicleta(string culoare,
		long nrKm,
		int an,
		string marca,
		const char* serie,
		bool areCasca) :Vehicul(culoare, nrKm, an, marca, serie) {
		//cout << "Constructor (..,...,...,...,...) Motocicleta\n";

		this->areCasca = areCasca;
	}

	Motocicleta(const Motocicleta& m) : Vehicul(m) {
		//cout << "Constructor de copiere Motocicleta\n";
		this->areCasca = m.areCasca;
	}

	~Motocicleta() {
		//cout << "Destructor Motocicleta" << endl;
	}

	Motocicleta& operator=(const Motocicleta& m) {
		//cout << "Op. = Motocicleta\n\n";

		if (this != &m) {
			Vehicul::operator=(m);

			this->areCasca = m.areCasca;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Motocicleta& m) {
		//Poti transforma un copil in parinte (up-casting)
		out << (Vehicul)m;

		out << "Are casca: " << m.areCasca << endl;

		return out;
	}


	Motocicleta& operator+(int km) {
		Vehicul::operator+(km);

		return *this;
	}

	bool operator==(Motocicleta& m) {
		if (this == &m) {
			return true;
		}

		return this->areCasca == m.areCasca &&
			Vehicul::operator==(m);
	}
};


class TIR : private Vehicul {
public:
	int ceva;

};

class Masina :protected Vehicul {
public:
	int altceva;
};


//compunere
class ReprezentantaDeMotociclete {
	string denumire;
	Motocicleta* motociclete;
	int nrMotociclete;

public:
	ReprezentantaDeMotociclete(
		string denumire, Motocicleta* motociclete, int nrMotociclete) {

		this->denumire = denumire;

		this->nrMotociclete = nrMotociclete;

		this->motociclete = new Motocicleta[nrMotociclete];
		for (int i = 0; i < nrMotociclete; i++) {
			this->motociclete[i] = motociclete[i];
		}
	}

	ReprezentantaDeMotociclete(const ReprezentantaDeMotociclete& reprezentanta) {
		this->denumire = reprezentanta.denumire;
		this->nrMotociclete = reprezentanta.nrMotociclete;
		this->motociclete = new Motocicleta[reprezentanta.nrMotociclete];
		for (int i = 0; i < nrMotociclete; i++) {
			this->motociclete[i] = reprezentanta.motociclete[i];
		}
	}

	~ReprezentantaDeMotociclete() {
		if (motociclete != nullptr) {
			delete[] motociclete;
		}
	}

	ReprezentantaDeMotociclete& operator=(const  ReprezentantaDeMotociclete& reprezentanta) {
		if (this != &reprezentanta) {
			if (this->motociclete != nullptr) {
				delete[] this->motociclete;
			}
			this->denumire = reprezentanta.denumire;
			this->nrMotociclete = reprezentanta.nrMotociclete;
			this->motociclete = new Motocicleta[reprezentanta.nrMotociclete];
			for (int i = 0; i < nrMotociclete; i++) {
				this->motociclete[i] = reprezentanta.motociclete[i];
			}
		}
		return *this;
	}

	int getNrMotociclete() {
		return nrMotociclete;
	}


	//e mai safe asa decat return motociclete;
	Motocicleta* getMotociclete() {
		Motocicleta* aux = new Motocicleta[nrMotociclete];
		for (int i = 0; i < nrMotociclete; i++) {
			aux[i] = motociclete[i];
		}

		return aux;
	}

	Motocicleta& operator[](int index) {
		if (index >= 0 && index < nrMotociclete) {
			return motociclete[index];
		}
		else {
			throw new exception("eroare in [] ");
		}
	}

	void adaugaMotocicleta(Motocicleta m) {
		Motocicleta* aux = new Motocicleta[nrMotociclete + 1];
		for (int i = 0; i < nrMotociclete; i++) {
			aux[i] = motociclete[i];
		}

		aux[nrMotociclete++] = m;
		delete[] motociclete;
		motociclete = aux;
	}

	//sterge toate aparitiile
	void stergereMotocicleta(Motocicleta m) {
		int nrDuplicate = 0;
		for (int i = 0; i < nrMotociclete; i++) {
			if (this->motociclete[i] == m) {
				nrDuplicate++;
			}
		}

		if (nrDuplicate > 0) {
			for (int i = 0; i < nrMotociclete; i++) {
				if (this->motociclete[i] == m) {
					for (int j = i; j < nrMotociclete - 1; j++) {
						this->motociclete[j] = motociclete[j + 1];
					}
					nrMotociclete--;
				}
			}

			Motocicleta* aux = new Motocicleta[nrMotociclete];
			for (int i = 0; i < nrMotociclete; i++) {
				aux[i] = motociclete[i];
			}

			delete[] motociclete;
			motociclete = aux;
		}
	}

	friend ostream& operator<<(ostream& out, ReprezentantaDeMotociclete& r) {
		out << "Denumire reprezentanta: " << r.denumire << endl;
		out << "Numar de motociclete disponibile: " << r.nrMotociclete << endl;
		for (int i = 0; i < r.nrMotociclete; i++) {
			out << r.motociclete[i];
		}

		return out;
	}
};

void main() {
	Motocicleta m;
	cout << m << endl;

	Motocicleta m1("rosu", 1000, 2021, "Suzuki", "JHKBVTY322", true);
	cout << m1 << endl;

	//mostenire publica, protected, private

	m.marca;//merge accesarea

	TIR t;
	Masina masina;
	//t.marca;//mostenirea fiind  private => nu ai acces la zona publica din bunic, pentru ca marca devine private...NU ai acces la ea doar din TIR
	//masina.marca;//mostenirea fiind protected => nu ai acces la zona publica din bunic, pentru ca marca devine protected...ai acces la ea doar din MASINA


	//refolosire cod mostenire pt a returna tot o motocicleta
	cout << (m1 + 10) << endl;

	cout << "\n\n=====COMPUNERE=====\n\n";
	Motocicleta m2("verde", 11000, 2011, "Audi", "OIHJKLS", true);
	Motocicleta m3("negru", 2221, 2020, "BMW", "XXXJGHK22", true);

	ReprezentantaDeMotociclete reprezentanta("Moto SRL", new Motocicleta[]{ m1 }, 1);
	reprezentanta.adaugaMotocicleta(m2);
	reprezentanta.adaugaMotocicleta(m3);

	cout << reprezentanta << endl;

	reprezentanta.stergereMotocicleta(m2);
	cout << reprezentanta << endl;
}