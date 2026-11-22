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
