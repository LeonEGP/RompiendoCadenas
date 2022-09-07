// ---------- DATOS DE ENTREGA ---------- //
//Programa que: Implementa la un algoritmo de Hash String.
//Programadores: León Emiliano García Pérez [A00573074], Carla Morales López [A01639225].
//Fecha de entrega: Martes 06 de Septiembre de 2022.

//Inclusión de librerías.
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

//Ajuste a estandar.
using namespace std;

//Función que imprime en consola un salto de línea, no recibe parámetros y no tiene valor de retorno.
void espacio() { //Complejidad Computacional: O(1).
    cout << endl;
}

//Función que verifica la multiplicidad entre dos números, recibe dos valores enteros y retorna un valor booleano.
bool multiplicidad(int numero, int multiplo) { //Complejidad Computacional: O(1).
    if (numero % multiplo == 0) {
        return true;
    }
    else {
        return false;
    }
}

//Función que encuentra el múltiplo más cercano a un número, recibe un entero como número y un entero como base, retorna el múltiplo entero más cercano. 
int multiploCercano(int numero, int base) { //Complejidad Computacional: O(1).
    
    numero = numero + base / 2;
    numero = numero - (numero % base);

    if (base > numero) {
        return base;
    }
    return numero;
}

//Función que convierte un string a una string en solo mayúsculas, recibe como parámetro el string a convertir y retorna el string en mayúsculas.
string aMayuscula(string cadena) { //Complejidad Computacional: O(n), siendo n la cantidad de caracteres del string.
    for (int i = 0; i < cadena.length(); i++) {
        cadena[i] = toupper(cadena[i]);
    }
    return cadena;
}

//Función que da el hasheo de un archivo de texto, recibe como parámetro un string que es el nombre del archivo, un entero n multiplo de 4 entre 16 y 64, retorna un string con el hasheo. 
string hashString(string nombreArchivo, int n) { //Complejidad Computacional: O(n), siendo n la cantidad de caracteres del archivo de texto.

    //Declaración/Inicialización de variables.
    int longitudString;
    int columnas;
    char auxiliar;
    string linea;
    string hashing;
    vector <long long int> resultado;
    vector <string> hexadecimal;
    vector <vector <char>> tabla;
    
    longitudString = n / 4; //Dentro de lo solicitado se menciona que el output es de tamaño n/4.
    columnas = n; //Variable que toma el valor de n, por practicidad.

    //Para llenar la tabla con los valores faltantes de cada linea, fue solicitado que se ingresara el valor de n, como solo se puede tomar un char del valor entero, se opta por tomar el valor de las decenas como representativo.
    if (n >= 10 && n < 19) {
        auxiliar = '1';
    }
    else if (n >= 20 && n < 29) {
        auxiliar = '2';
    }
    else if (n >= 30 && n < 39) {
        auxiliar = '3';
    }
    else if (n >= 40 && n < 49) {
        auxiliar = '4';
    }
    else if (n >= 50 && n < 59) {
        auxiliar = '5';
    }
    else if (n >= 60 && n < 69) {
        auxiliar = '6';
    }

    //Formación de la tabla con n columnas.
    for (int i = 0; i < columnas; i++) {
        vector <char> columna;
        tabla.push_back(columna);
    }

    //Apertura del archivo a analizar. 
    ifstream archivo(nombreArchivo.c_str());

    //Lectura de cada renglón del archivo. 
    while (getline(archivo, linea)) {

        int iterador; //Iterador que se actualiza desde 0 a n.
        iterador = 0;

        //Ciclo que va a acomodar el char de cada string (renglón).
        for (int i = 0; i < linea.length(); ++i) {

            char caracter;
            caracter = linea[i];
            tabla[iterador].push_back(caracter); 

            //Actualización del iterador.
            if ((iterador + 1) == columnas) {
                iterador = 0;
            }
            else {
                iterador++;
            }
        }

        //Comprueba si hay espacios faltantes, si es así: se rellena con el char valor representativo de n.
        if (iterador != 0) {
            for (int j = iterador; j < columnas; j++) {
                tabla[j].push_back(auxiliar);
            }
        }

    }

    //Ciclo que suma cada columna de la tabla, obtiene de la sumatoria %256 y lo almacena en el vector de resultados. 
    for (int i = 0; i < columnas; i++) {

        long long int suma;
        suma = 0;

        for (int j = 0; j < tabla[i].size(); j++) {
            suma += int(tabla[i][j]);
        }

        suma = suma % 256;
        resultado.push_back(suma);
    }

    //Ciclo que convierte del vector de resultados anterior, cada valor a hexadecimal, almacenándolos en dicho vector. 
    for (int i = 0; i < resultado.size(); i++) {
        
        long long int valor;
        string converso;
        valor = resultado[i];
        ostringstream os;

        // Si se quisiera una notación correcta, respecto a lo tradicional -> os << "0x" << setfill('0') << setw(longitudString) << hex << valor;
        os << setfill('0') << setw(2) << hex << valor; //Considerando que se busca notación a dos valores en hexadecimal. 

        converso = os.str(); //Se convierte a string. 
        converso = aMayuscula(converso); //Se convierte a mayúsculas, ya que es requerido que sea en mayúsculas la notación representativa en hexadecimal. 
        hexadecimal.push_back(converso);
    }

    //Ciclo que concatena los anteriores valores hexadecimales en un solo string.
    for (int i = 0; i < hexadecimal.size(); i++) {
        hashing += hexadecimal[i];
    }

    //Dentro de lo solicitado se solicita que el output sea de longitud n/4, considerando que la concatenación de los valores hexadecimales de las colummas es de longitud: 2n,
    // Entonces es que se opta por reducir el tamaño de dicha concatenación, tomando los primeros n valores del string resultado, ya que es en dicho espacio donde se encuentra más información. 
    
    // Esto es si se quisieran los últimos n caracteres -> hashing = hashing.substr(hashing.size() - longitudString); //Pérdida aún mayor de información. 
    hashing = hashing.substr(0, longitudString);

    //Retorna el hash.
    return hashing;
    
}

//Función main que ejecuta el programa, no recibe parámetros, retorna un entero [return 0].
int main() { //Complejidad Computacional: O(1).

    // ---------- DECLARACIÓN DE VARIABLES ---------- //
    string archivo;
    int n;
    string hashing;

    // ---------- INICIA PROGRAMA ---------- //
    cout << "INGRESE EL NOMBRE DEL ARCHIVO: " << endl;
    cin >> archivo;
    espacio();
    cout << "INGRESE EL VALOR N: " << endl;
    cin >> n;

    // ---------- DETECCIÓN DE ERRORES DE INPUT ---------- //
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

    // ---------- HASHEO DEL ARCHIVO ---------- //
    hashing = hashString(archivo,n);
    espacio();
    cout << "RESULTADO HASHING: " << endl;
    cout << hashing << endl;

    // ---------- TERMINA PROGRAMA ---------- //
    return 0;
}
