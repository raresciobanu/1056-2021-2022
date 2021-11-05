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

	Vehicul(string culoare, long nrKm, int an, string marca, const char* serie) {
		cout << "Constructor (..,...,...,...,...) Vehicul\n";

		this->culoare = culoare;
		this->nrKm = nrKm;
		this->an = an;
		this->marca = marca;

		this->serie = new char[strlen(serie) + 1];
		strcpy_s(this->serie, strlen(serie) + 1, serie);
	}

	Vehicul(const Vehicul& v) {
		//cout << "Constructor copiere Vehicul\n";

		this->culoare = v.culoare;
		this->nrKm = v.nrKm;
		this->an = v.an;
		this->marca = v.marca;

		this->serie = new char[strlen(v.serie) + 1];
		strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
	}

	~Vehicul() {
		//cout << "Destructor Vehicul" << endl;

		if (this->serie != nullptr) {
			delete[] this->serie;
		}
	}

	Vehicul& operator=(const Vehicul& v) {
		cout << "Op. = Vehicul\n";
		if (this != &v) {
			if (this->serie != nullptr) {
				delete[] this->serie;
			}
			
			this->culoare = v.culoare;
			this->nrKm = v.nrKm;
			this->an = v.an;
			this->marca = v.marca;

			this->serie = new char[strlen(v.serie) + 1];
			strcpy_s(this->serie, strlen(v.serie) + 1, v.serie);
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
};

//Motocicleta "is a" Vehicul

//Motocicleta = Vehicul + arecasca
class Motocicleta : public Vehicul {
protected:
	int aaaCEVADINMOTOPROTECTED;
public:
	bool areCasca;
	
	Motocicleta() :Vehicul("Negru", 120000, 2011, "Hyundai", "XH2542X43243") {
		cout << "Constructor () Motocicleta\n";
		
		this->areCasca = false;
	}

	Motocicleta(string culoare,
		long nrKm,
		int an,
		string marca,
		const char* serie,
		bool areCasca) :Vehicul(culoare, nrKm, an, marca, serie) {
		cout << "Constructor (..,...,...,...,...) Motocicleta\n";
		
		this->areCasca = areCasca;
	}

	Motocicleta(const Motocicleta& m) : Vehicul(m) {
		cout << "Constructor de copiere Motocicleta\n";
		this->areCasca = m.areCasca;
	}

	~Motocicleta() {
		//cout << "Destructor Motocicleta" << endl;
	}

	Motocicleta& operator=(const Motocicleta& m) {
		cout << "Op. = Motocicleta\n\n";

		if (this != &m) {
			Vehicul::operator=(m);

			this->areCasca = m.areCasca;
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, const Motocicleta& m) {
		//Poti transforma un copil in parinte (up-casting)
		out << (Vehicul) m;

		out << "Are casca: " << m.areCasca << endl;

		return out;
	}
};


void main() {
	Motocicleta m;
	cout << m<<endl;
	
	Motocicleta m1("rosu", 1000, 2021, "Suzuki", "JHKBVTY322", true);
	cout << m1 << endl;
}