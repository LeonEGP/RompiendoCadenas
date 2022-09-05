
// ---------- DATOS DE ENTREGA ---------- //
//Programa que: Implementa la un algoritmo de Hash String.
//Programadores: León Emiliano García Pérez [A00573074], Carla Morales López [A01639225].
//Fecha de entrega: Martes 06 de Septiembre de 2022.

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

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

string aMayuscula(string cadena) {
    for (int i = 0; i < cadena.length(); i++) {
        cadena[i] = toupper(cadena[i]);
    }
    return cadena;
}

void hashString(string nombreArchivo, int n) {

    int longitudString;
    int columnas;
    vector <vector <char>> tabla;
    string linea;
    vector <long long int> resultado;
    vector <string> hexadecimal;
    string hashing;

    longitudString = n / 4;
    columnas = n;

    for (int i = 0; i < columnas; i++) {
        vector <char> columna;
        tabla.push_back(columna);
    }

    ifstream archivo(nombreArchivo.c_str());

    while (getline(archivo, linea)) {

        int iterador;
        iterador = 0;

        for (int i = 0; i < linea.length(); ++i) {

            char caracter;
            caracter = linea[i];
            tabla[iterador].push_back(caracter);

            if ((iterador + 1) == columnas) {
                iterador = 0;
            }
            else {
                iterador++;
            }

        }

        if (iterador != 0) {

            char caracter;

            if(n >= 10 && n < 19) {
                caracter = '1';
            }
            else if (n >= 20 && n < 29) {
                caracter = '2';
            }
            else if (n >= 30 && n < 39) {
                caracter = '3';
            }
            else if (n >= 40 && n < 49) {
                caracter = '4';
            }
            else if (n >= 50 && n < 59) {
                caracter = '5';
            }
            else if (n >= 60 && n < 69) {
                caracter = '6';
            }

            for (int j = iterador; j < columnas; j++) {
                tabla[j].push_back(caracter);
            }

        }

    }

    for (int i = 0; i < columnas; i++) {

        long long int suma;
        suma = 0;

        for (int j = 0; j < tabla[i].size(); j++) {
            suma += int(tabla[i][j]);
        }

        suma = suma % 256;
        resultado.push_back(suma);
    }

    for (int i = 0; i < resultado.size(); i++) {
        
        long long int valor;
        string converso;
        valor = resultado[i];

        ostringstream os;
        //os << "0x" << setfill('0') << setw(longitudString) << hex << valor;
        os << setfill('0') << setw(2) << hex << valor;

        converso = os.str();
        converso = aMayuscula(converso);
        hexadecimal.push_back(converso);
    }

    for (int i = 0; i < hexadecimal.size(); i++) {
        hashing += hexadecimal[i];
    }

    hashing = hashing.substr(hashing.size() - longitudString);

    cout << "RESULTADO HASHING: " << endl;
    cout << hashing << endl;

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
        cout << "VALOR DE N MAYOR AL ESPERADO, AJUSTANDO A 64" << endl;
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

