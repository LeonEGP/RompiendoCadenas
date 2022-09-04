
#include <iostream>
#include <string>

using namespace std;

void espacio() {
    cout << endl;
}

bool multiplicidad(int numero, int multiplo) {

    if (numero % multiplo == 0) {
        return true;
    }
    else {
        return false;
    }

}

int multiploCercano(int numero, int base) {
    
    numero = numero + base / 2;
    numero = numero - (numero % base);

    if (base > numero) {
        return base;
    }

    return numero;
}

void hashString(string archivo, int n) {

    int longitudString;
    int columnas;

    longitudString = n / 4;
    columnas = n;

}

int main() {

    string archivo;
    int n;

    cout << "INGRESE EL NOMBRE DEL ARCHIVO: " << endl;
    cin >> archivo;

    espacio();

    cout << "INGRESE EL VALOR N: " << endl;
    cin >> n;

    if (n < 16) {
        cout << "VALOR DE N MENOR AL ESPERADO, AJUSTANDO A 16" << endl;
        n = 16;
    } 
    else if (n > 64) {
        cout << "VALOR DE N MAYOR AL ESPERADO, AJUSTANDO A 16" << endl;
        n = 64;
    }
    else {
        if (multiplicidad(n, 4) != true) {
            n = multiploCercano(n, 4);
        }
    }

    hashString(archivo,n);

    return 0;
}

