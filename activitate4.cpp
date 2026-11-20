#include<iostream>
#include<string>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj) {}
};

class Produs {
private:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() :id(0), denumire("Laptop"), pret(5000) {
	}

	Produs(int idP, string denumireP, float pretP) :id(idP), denumire(denumireP), pret(pretP) {
		if (pret < PRET_MINIM) {
			throw ExceptieCustom("Pretul este prea mic!");
		}
	}

	virtual void afisare() {
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;
	}

	~Produs() {
	}

	virtual float getProcentReducere() = 0;

};

const float Produs::PRET_MINIM = 1;

class ProdusRedus : public Produs {
private:
	float procentReducere;
public:
	ProdusRedus() :Produs(), procentReducere(10) {}

	ProdusRedus(int id, string denumire, float pret, float procentReducere) :Produs(id, denumire, pret), procentReducere(procentReducere) {}

	void afisare() {
		this->Produs::afisare();
		cout << endl << "Procent reducere: " << this->procentReducere;
	}

	float getProcentReducere() {
		return this->procentReducere;
	}
};

class MathInterface {
public:
	virtual int adunare(int a, int b) = 0;
	virtual int scadere(int a, int b) = 0;
	virtual int inmultire(int a, int b) = 0;
	virtual int impartire(int a, int b) = 0;
};

class MathOperation : public MathInterface {
public:
	int adunare(int a, int b) {
		return a + b;
	}

	int scadere(int a, int b) {
		return a - b;
	}

	int inmultire(int a, int b) {
		return a * b;

	}

	int impartire(int a, int b) {
		if (b != 0) {
			return a / b;
		}
		else {
			throw ExceptieCustom("Nu putem avea impartire la 0!");
		}
	}
};

void main() {

	//try {
	//	Produs frigider(1, "Frigider", 0);
	//}
	//catch (ExceptieCustom e) {
	//	cout << endl << e.what();
	//}

	//Produs frigider(1, "Frigider", 5000);
	//frigider.afisare();

	//ProdusRedus laptop(2, "Laptop", 6000, 10);
	//laptop.afisare();

	Produs* vectorProduse[3];

	vectorProduse[0] = new ProdusRedus(1, "Paine", 2, 10);
	vectorProduse[1] = new ProdusRedus(2, "Peste", 15, 8);
	vectorProduse[2] = new ProdusRedus(3, "Portocale", 10, 12);

	for (int i = 0; i < 3; i++) {
		vectorProduse[i]->afisare();
		delete vectorProduse[i];
	}

	MathInterface* operation = new MathOperation();
	cout << endl << operation->adunare(1, 2);
}

//Model

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Companie {
private:
    const int idCompanie;   // atribut nemodificabil -> const int
    char* numeCompanie;     // atribut alocat dinamic -> char*
    float cifraDeAfaceri;   // atribut numeric

public:
    // 1. Constructorul default (fara parametri) - (1p)
    Companie() : idCompanie(0) {
        this->numeCompanie = new char[strlen("Necunoscuta") + 1];
        strcpy(this->numeCompanie, "Necunoscuta");
        this->cifraDeAfaceri = 0;
    }

    // 2. Constructorul cu un parametru (ex: doar id-ul) - (1p)
    // (Daca cere cu un parametru pentru nume, vezi explicatia de mai jos)
    Companie(int id) : idCompanie(id) {
        this->numeCompanie = new char[strlen("Necunoscuta") + 1];
        strcpy(this->numeCompanie, "Necunoscuta");
        this->cifraDeAfaceri = 0;
    }

    // Constructor de copiere (obligatoriu cand avem char* ca sa nu crape la transmitere prin valoare)
    Companie(const Companie& copie) : idCompanie(copie.idCompanie) {
        this->cifraDeAfaceri = copie.cifraDeAfaceri;
        if (copie.numeCompanie != nullptr) {
            this->numeCompanie = new char[strlen(copie.numeCompanie) + 1];
            strcpy(this->numeCompanie, copie.numeCompanie);
        }
        else {
            this->numeCompanie = nullptr;
        }
    }

    // 3. Metoda get pentru atributul constant - (1p)
    int getIdCompanie() {
        return this->idCompanie;
    }

    // 4. Metoda set pentru atributul alocat dinamic (char*) - (2p)
    void setNumeCompanie(const char* numeNou) {
        if (numeNou != nullptr && strlen(numeNou) > 0) {
            if (this->numeCompanie != nullptr) {
                delete[] this->numeCompanie; // dezalocam memoria veche!
            }
            this->numeCompanie = new char[strlen(numeNou) + 1];
            strcpy(this->numeCompanie, numeNou);
        }
    }

    // 5. Operatorul = (atribuire) - (2p)
    Companie& operator=(const Companie& copie) {
        if (this != &copie) { // evitam auto-atribuirea (c1 = c1)
            this->cifraDeAfaceri = copie.cifraDeAfaceri;

            if (this->numeCompanie != nullptr) {
                delete[] this->numeCompanie;
                this->numeCompanie = nullptr;
            }

            if (copie.numeCompanie != nullptr) {
                this->numeCompanie = new char[strlen(copie.numeCompanie) + 1];
                strcpy(this->numeCompanie, copie.numeCompanie);
            }
            else {
                this->numeCompanie = nullptr;
            }
        }
        return *this;
    }

    // 6. Metoda de afisare a atributelor - (1p)
    void afisare() {
        cout << endl << "ID Companie: " << this->idCompanie;
        cout << endl << "Nume Companie: " << (this->numeCompanie != nullptr ? this->numeCompanie : "N/A");
        cout << endl << "Cifra de afaceri: " << this->cifraDeAfaceri << " lei" << endl;
    }

    // Destructor (obligatoriu pentru a nu avea memory leaks -> altfel -1p!)
    ~Companie() {
        if (this->numeCompanie != nullptr) {
            delete[] this->numeCompanie;
            this->numeCompanie = nullptr;
        }
    }
};

int main() {
    // Testare constructor default
    Companie c1;
    c1.afisare();

    // Testare constructor cu un parametru
    Companie c2(101);
    c2.afisare();

    // Testare metoda get pentru atributul constant
    cout << endl << "ID-ul companiei c2 este: " << c2.getIdCompanie() << endl;

    // Testare metoda set pentru atributul alocat dinamic
    c2.setNumeCompanie("Bitdefender");
    c2.afisare();

    // Testare operator =
    Companie c3;
    c3 = c2;
    c3.afisare();

    return 0;
}


//MODEL 2

#include <iostream>
#include <string>

using namespace std;

class Student {
private:
    const int nrMatricol;   // atribut nemodificabil -> const int
    string nume;            // text simplu -> string (nu necesita alocare dinamica)
    int nrNote;             // dimensiunea vectorului (OBLIGATORIU cand ai vector dinamic!)
    float* note;            // atribut alocat dinamic -> float*

public:
    // 1. Constructorul default (fara parametri)
    Student() : nrMatricol(0) {
        this->nume = "Anonim";
        this->nrNote = 0;
        this->note = nullptr;
    }

    // 2. Constructorul cu un parametru (ex: doar nrMatricol)
    Student(int nrMatricol) : nrMatricol(nrMatricol) {
        this->nume = "Anonim";
        this->nrNote = 0;
        this->note = nullptr;
    }

    // Constructor de copiere (obligatoriu cand ai pointeri)
    Student(const Student& copie) : nrMatricol(copie.nrMatricol) {
        this->nume = copie.nume;
        this->nrNote = copie.nrNote;

        if (copie.note != nullptr && copie.nrNote > 0) {
            this->note = new float[this->nrNote];
            for (int i = 0; i < this->nrNote; i++) {
                this->note[i] = copie.note[i];
            }
        }
        else {
            this->note = nullptr;
        }
    }

    // 3. Metoda get pentru atributul constant
    int getNrMatricol() {
        return this->nrMatricol;
    }

    // 4. Metoda set pentru vectorul alocat dinamic (primeste vectorul SI dimensiunea lui!)
    void setNote(float* noteNoi, int nrNoteNoi) {
        if (noteNoi != nullptr && nrNoteNoi > 0) {
            // Pas 1: Dezaloaca memoria veche!
            if (this->note != nullptr) {
                delete[] this->note;
            }
            // Pas 2: Actualizeaza dimensiunea si aloca memorie noua
            this->nrNote = nrNoteNoi;
            this->note = new float[this->nrNote];
            // Pas 3: Copiaza elementele cu for
            for (int i = 0; i < this->nrNote; i++) {
                this->note[i] = noteNoi[i];
            }
        }
    }

    // 5. Operatorul = (atribuire)
    Student& operator=(const Student& copie) {
        if (this != &copie) {
            this->nume = copie.nume;
            this->nrNote = copie.nrNote;

            if (this->note != nullptr) {
                delete[] this->note;
                this->note = nullptr;
            }

            if (copie.note != nullptr && copie.nrNote > 0) {
                this->note = new float[this->nrNote];
                for (int i = 0; i < this->nrNote; i++) {
                    this->note[i] = copie.note[i];
                }
            }
            else {
                this->note = nullptr;
            }
        }
        return *this;
    }

    // 6. Metoda de afisare
    void afisare() {
        cout << endl << "Nr. Matricol: " << this->nrMatricol;
        cout << endl << "Nume: " << this->nume;
        cout << endl << "Nr. note: " << this->nrNote;
        if (this->nrNote > 0 && this->note != nullptr) {
            cout << " -> Note: ";
            for (int i = 0; i < this->nrNote; i++) {
                cout << this->note[i] << " ";
            }
        }
        cout << endl;
    }

    // Destructor (obligatoriu ca sa nu ai memory leaks!)
    ~Student() {
        if (this->note != nullptr) {
            delete[] this->note;
            this->note = nullptr;
        }
    }
};

int main() {
    Student s1;
    s1.afisare();

    Student s2(1050);
    cout << endl << "Nr matricol s2: " << s2.getNrMatricol() << endl;

    // Cand testezi setter-ul pentru vector, declari un vector local si il trimiti
    float noteTest[] = { 9.5, 10, 8.75 };
    s2.setNote(noteTest, 3);
    s2.afisare();

    Student s3;
    s3 = s2;
    s3.afisare();

    return 0;
}