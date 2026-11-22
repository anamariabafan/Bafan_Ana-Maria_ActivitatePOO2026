#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class Autoturism {
private:
    const int codInmatriculare;
    char* marca;
    float pret;
    int anFabricatie;

public:
    static int nrAutoturisme;

    // Constructor default
    Autoturism() : codInmatriculare(++nrAutoturisme) {
        this->marca = new char[strlen("Necunoscuta") + 1];
        strcpy(this->marca, "Necunoscuta");
        this->pret = 0;
        this->anFabricatie = 2000;
    }

    // Constructor cu parametri
    Autoturism(int cod, const char* marca, float pret, int anFabricatie) : codInmatriculare(cod) {
        nrAutoturisme++;
        if (marca != nullptr) {
            this->marca = new char[strlen(marca) + 1];
            strcpy(this->marca, marca);
        }
        else {
            this->marca = new char[strlen("Necunoscuta") + 1];
            strcpy(this->marca, "Necunoscuta");
        }
        this->pret = pret;
        this->anFabricatie = anFabricatie;
    }

    // Constructor de copiere
    Autoturism(const Autoturism& copie) : codInmatriculare(++nrAutoturisme) {
        this->pret = copie.pret;
        this->anFabricatie = copie.anFabricatie;
        if (copie.marca != nullptr) {
            this->marca = new char[strlen(copie.marca) + 1];
            strcpy(this->marca, copie.marca);
        }
        else {
            this->marca = nullptr;
        }
    }

    // Getter pentru atributul constant
    int getCodInmatriculare() {
        return this->codInmatriculare;
    }

    // Setter pentru atributul alocat dinamic (char*)
    void setMarca(const char* marcaNoua) {
        if (marcaNoua != nullptr && strlen(marcaNoua) > 0) {
            if (this->marca != nullptr) {
                delete[] this->marca;
            }
            this->marca = new char[strlen(marcaNoua) + 1];
            strcpy(this->marca, marcaNoua);
        }
    }

    // Getter si setter pentru pret
    float getPret() {
        return this->pret;
    }

    void setPret(float pretNou) {
        if (pretNou > 0) {
            this->pret = pretNou;
        }
    }

    // Operatorul =
    Autoturism& operator=(const Autoturism& copie) {
        if (this != &copie) {
            this->pret = copie.pret;
            this->anFabricatie = copie.anFabricatie;

            if (this->marca != nullptr) {
                delete[] this->marca;
                this->marca = nullptr;
            }

            if (copie.marca != nullptr) {
                this->marca = new char[strlen(copie.marca) + 1];
                strcpy(this->marca, copie.marca);
            }
            else {
                this->marca = nullptr;
            }
        }
        return *this;
    }

    // Metoda de afisare
    void afisare() {
        cout << endl << "Cod inmatriculare: " << this->codInmatriculare;
        cout << endl << "Marca: " << (this->marca != nullptr ? this->marca : "N/A");
        cout << endl << "Pret: " << this->pret << " euro";
        cout << endl << "An fabricatie: " << this->anFabricatie << endl;
    }

    // Destructor
    ~Autoturism() {
        if (this->marca != nullptr) {
            delete[] this->marca;
            this->marca = nullptr;
        }
    }
};

int Autoturism::nrAutoturisme = 0;

int main() {
    Autoturism a1;
    a1.afisare();

    Autoturism a2(101, "Dacia", 12500, 2023);
    a2.afisare();

    a2.setMarca("Renault");
    a2.setPret(14000);
    cout << endl << "Codul pentru a2 este: " << a2.getCodInmatriculare() << endl;
    a2.afisare();

    Autoturism a3 = a2;
    a3.afisare();

    Autoturism a4;
    a4 = a2;
    a4.afisare();

    cout << endl << "Total autoturisme create: " << Autoturism::nrAutoturisme << endl;

    return 0;
}