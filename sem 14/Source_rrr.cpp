#include<iostream>
#include<fstream>
#include<vector>
#include<list>

using namespace std;

class Locuinta {
private:
	char* numeClient;
	int suprafataUtila;
	float discount;

public:
	Locuinta() {
		this->numeClient = nullptr;

		this->suprafataUtila = 0;
		this->discount = 0;
	}

	Locuinta(const char* numeClient, int suprafataUtila, float discount) {
		this->numeClient = new char[strlen(numeClient) + 1];
		strcpy_s(this->numeClient, strlen(numeClient) + 1, numeClient);

		this->suprafataUtila = suprafataUtila;
		this->discount = discount;
	}

	Locuinta(const Locuinta& l) {
		if (l.numeClient != nullptr) {
			this->numeClient = new char[strlen(l.numeClient) + 1];
			strcpy_s(this->numeClient, strlen(l.numeClient) + 1, l.numeClient);
		}
		else {
			this->numeClient = nullptr;
		}

		this->suprafataUtila = l.suprafataUtila;
		this->discount = l.discount;
	}

	Locuinta& operator=(const Locuinta& l) {
		if (this != &l) {
			delete[] this->numeClient;

			if (l.numeClient != nullptr) {
				this->numeClient = new char[strlen(l.numeClient) + 1];
				strcpy_s(this->numeClient, strlen(l.numeClient) + 1, l.numeClient);
			}
			else {
				this->numeClient = nullptr;
			}

			this->suprafataUtila = l.suprafataUtila;
			this->discount = l.discount;
		}

		return *this;
	}

	~Locuinta() {
		if (numeClient != nullptr) {
			delete[] numeClient;
		}
	}
	//fct virtuala pura
	virtual int CalculChirie(int X, int Y) = 0;


	//operator++ si operator-- pre si post pt incrementarea si decrementarea discountului
	//intervalul 0-10
	const Locuinta& operator++() {
		if (discount > 0 && discount <= 9) {
			discount++;
		}

		return *this;
	}

	const Locuinta& operator++(int) {
		Locuinta* aux = this;

		if (discount > 0 && discount <= 9) {
			discount++;
		}

		return *aux;
	}

	const Locuinta& operator--() {
		if (discount >= 1 && discount <= 10) {
			discount--;
		}

		return *this;
	}

	const Locuinta& operator--(int) {
		Locuinta* aux = this;

		if (discount >= 1 && discount <= 10) {
			discount--;
		}

		return *aux;
	}

	bool operator==(Locuinta& l) {
		if (this == &l) {
			return true;
		}
		return strcmp(this->numeClient, l.numeClient) == 0 && this->discount == l.discount && this->suprafataUtila == l.suprafataUtila;
	}

	//Se va supraincarca operatorul de cast la intreg pentru returnarea suprafetei utile
	operator int() {
		return suprafataUtila;
	}

	friend ostream& operator<<(ostream& out, const Locuinta& l) {
		out << "Nume client " << l.numeClient << " suprafata utila " << l.suprafataUtila << " discount " << l.discount << endl;

		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Locuinta& l) {
		out << l.suprafataUtila << endl << l.numeClient << endl << l.discount << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, Locuinta& l) {
		in >> l.suprafataUtila;

		in.ignore();
		char aux[100];
		in.get(aux, 100);

		l.numeClient = new char[strlen(aux) + 1];
		strcpy_s(l.numeClient, strlen(aux) + 1, aux);

		in >> l.discount;

		return in;
	}

	int getSuprafataUtila() {
		return suprafataUtila;
	}

	float getDiscount() {
		return discount;
	}
};

class Apartament : public Locuinta {
	int etaj;

public:
	Apartament(const char* numeClient, int suprafataUtila, float discount, int etaj)
		:Locuinta(numeClient, suprafataUtila, discount) {
		this->etaj = etaj;
	}

	friend ofstream& operator<<(ofstream& out, const Apartament& a) {
		out << (Locuinta&)a;
		out << a.etaj << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Apartament& a) {
		in >> (Locuinta&)a;
		in >> a.etaj;

		return in;
	}

	//fct virtuala pura suprascriere
	int CalculChirie(int X, int Y) {
		return X * getSuprafataUtila() * (1 - Y * getDiscount() / 100.0);
	}
};

class Casa : public Locuinta {
	int suprafataCurte;
	int nrEtaje;
	float* suprafataEtaje;

public:
	Casa(const char* numeClient, int suprafataUtila, float discount, int suprafataCurte, int nrEtaje, float* suprafataEtaje)
		:Locuinta(numeClient, suprafataUtila, discount) {
		this->suprafataCurte = suprafataCurte;
		this->nrEtaje = nrEtaje;
		this->suprafataEtaje = new float[nrEtaje];
		for (int i = 0; i < nrEtaje; i++) {
			this->suprafataEtaje[i] = suprafataEtaje[i];
		}
	}

	friend ofstream& operator<<(ofstream& out, const Casa& c) {
		out << (Locuinta&)c;
		out << c.suprafataCurte << endl;
		out << c.nrEtaje << endl;
		for (int i = 0; i < c.nrEtaje; i++) {
			out << c.suprafataEtaje[i] << " ";
		}
		out << endl;

		return out;
	}

	friend ifstream& operator>>(ifstream& in, Casa& c) {
		in >> (Locuinta&)c;
		in >> c.suprafataCurte;
		in >> c.nrEtaje;
		for (int i = 0; i < c.nrEtaje; i++) {
			in >> c.suprafataEtaje[i];
		}

		return in;
	}

	//fct virtuala pura suprascriere
	int CalculChirie(int X, int Y) {
		return X * (getSuprafataUtila() + 0.2 * suprafataCurte) * (1 - Y * getDiscount() / 100.0);
	}

};

//todo week 14
//void scriereInFisierText(vector<Locuinta*> locuinte) {
//	ofstream fout("fisierLocuinte.txt");
//	if (fout.is_open() && !locuinte.empty()) {
//		fout << locuinte.size() << endl;
//
//		for (int i = 0; i < locuinte.size(); i++) {
//			fout << *locuinte[i];
//		}
//
//		fout.close();
//	}
//	else {
//		cout << "fisierLocuinte.txt nu poate fi deschis sau n ai locuinte in vector \n";
//	}
//}

//void citireDinFisierText(vector<Locuinta*>& locuinte) {
//	ifstream fin("fisierLocuinte.txt");
//	if (fin.is_open()) {
//		int nrAp = 0;
//		fin >> nrAp; //citesc intai cate lopcuinte sunt in fisier
//
//		for (int i = 0; i < nrAp; i++) {
//			Locuinta* l = new Locuinta();
//			fin >> *l;
//
//			locuinte.push_back(l);
//		}
//
//		fin.close();
//	}
//	else {
//		cout << "fisierLocuinte.txt nu poate fi deschis\n";
//	}
//}

class AgentieImobiliara {
private:
	list<Locuinta*> locuinte;

public:
	AgentieImobiliara(list<Locuinta*> locuinte) {
		this->locuinte = locuinte;
	}

	friend ostream& operator<<(ostream& out, const AgentieImobiliara& agentieImobiliara) {
		out << "\n\nAgentieImobiliara\n\n";
		for (Locuinta* l : agentieImobiliara.locuinte) {
			out << *l << endl;
		}

		return out;
	}

	void operator+=(Locuinta* l) {
		locuinte.push_back(l);
	}

	void operator-=(Locuinta* l) {
		list<Locuinta*>::iterator itr;

		for (itr = locuinte.begin(); itr != locuinte.end();)
		{
			if (*(*itr) == *l)
				itr = locuinte.erase(itr);
			else
				++itr;
		}
	}
};

template<class Y>
class Gestiune {
	int N;
	int* valoareChirii; //

	int M;
	Y* nrClientiSiNume; //"2 Ion Popescu si Maria Popescu" char** ?

public:
	Gestiune(int N, int* valoareChirii, int M, Y* nrClientiSiNume) {
		this->N = N;
		this->valoareChirii = new int[N];
		for (int i = 0; i < N; i++) {
			this->valoareChirii[i] = valoareChirii[i];
		}

		this->M = M;
		this->nrClientiSiNume = new Y[M];
		for (int i = 0; i < M; i++) {
			this->nrClientiSiNume[i] = nrClientiSiNume[i]; //faci shallow copy 
		}
	}

	~Gestiune() {
		delete[] valoareChirii;

		delete[] nrClientiSiNume;
	}

	friend ostream& operator<<(ostream& out, const Gestiune& gestiune) {
		out << "\n\Gestiune\n\n";

		out << gestiune.N << endl;
		for (int i = 0; i < gestiune.N; i++) {
			out << gestiune.valoareChirii[i] << " ";
		}

		out << endl << endl << endl;
		for (int i = 0; i < gestiune.M; i++) {
			out << gestiune.nrClientiSiNume[i] << endl;;
		}

		return out;
	}
};

int main() {
	//Locuinta l;
	//Locuinta l2(l);

	Locuinta* l3 = new Apartament("Rares Ciobanu", 93, 5.5, 5);
	//pre
	cout << --(*l3);
	cout << (*l3)--;
	cout << (*l3);


	int suprafataUtilaL2 = *l3; //cast implicit
	cout << "Suprafata utilizata pt l3: " << (int)l3 << endl;//cast explicit


	Apartament a1("Andrei Popescu", 73, 2.5, 8);
	Apartament a2("Ion Ionescu", 83, 6.5, 3);
	Apartament a3("Magda Popescu", 63, 7.7, 9);


	Casa c1("George Pascale", 163, 2.5, 500, 3, new float[3]{ 100,200,200 });
	Casa c2("Andrian Popa", 200, 2.5, 140, 1, new float[1]{ 140 });
	Casa c3("Andreeea Pana", 232, 2.5, 1000, 2, new float[2]{ 400,500 });

	//stl
	vector<Locuinta*> locuinte;

	locuinte.push_back(l3);
	locuinte.push_back(&a1);
	locuinte.push_back(&a2);
	locuinte.push_back(&a3);
	locuinte.push_back(&c1);
	locuinte.push_back(&c2);
	locuinte.push_back(&c3);

	//scriereInFisierText(locuinte);


	//vector<Locuinta*> locuinteCititeDinFisier;
	//citireDinFisierText(locuinteCititeDinFisier);



	/*if (!locuinteCititeDinFisier.empty()) {
		for (int i = 0; i < locuinteCititeDinFisier.size(); i++) {
			cout << *locuinteCititeDinFisier[i];
		}
	}*/


	//fct virtuala pura
	cout << endl << endl << "fct virtuala pura" << endl << endl;
	for (int i = 0; i < locuinte.size(); i++) {
		cout << locuinte[i]->CalculChirie(1000, 1) << endl;
	}



	//list 
	list<Locuinta*> locuinteLista;

	locuinteLista.push_back(l3);
	locuinteLista.push_back(&a1);
	locuinteLista.push_back(&a2);
	locuinteLista.push_back(&a3);
	locuinteLista.push_back(&c1);
	locuinteLista.push_back(&c2);
	locuinteLista.push_back(&c3);

	AgentieImobiliara ag(locuinteLista);
	cout << ag;

	ag += &c3;
	cout << ag;

	ag -= &c3;
	cout << ag;


	//template
	char* ceva1 = new char[strlen("2 Cosmin si Ana") + 1];
	strcpy_s(ceva1, strlen("2 Cosmin si Ana") + 1, "2 Cosmin si Ana");

	char* ceva2 = new char[strlen("3 Rares Ionel Marcel") + 1];
	strcpy_s(ceva2, strlen("3 Rares Ionel Marcel") + 1, "3 Rares Ionel Marcel");

	char* ceva3 = new char[strlen("1 Adrian") + 1];
	strcpy_s(ceva3, strlen("1 Adrian") + 1, "1 Adrian");

	Gestiune<char*> gestiune(3, new int[3]{ 100,300,400 }, 3, new char* [3]{ ceva1,ceva2,ceva3 });
	cout << gestiune;
}