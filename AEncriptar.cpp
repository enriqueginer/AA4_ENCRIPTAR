#include "AEncriptar.h"
#include <fstream>
#include <iostream>

using namespace std;


const int CLAVE = 3;

string encriptar(string texto, int& checksum) //Cifrado
{
    string resultado = "";
    checksum = 0;

    for (int i = 0; i < texto.length(); i++)
    {
        char c = texto[i];

        if (c >= 'a' && c <= 'z')
            c = c - 32;
        else if (c >= 'A' && c <= 'Z')
            c = c + 32;

        c = c + CLAVE;

        checksum += (int)c;
        resultado += c;
    }

    return resultado;
}

string desencriptar(string texto, int& checksum) 
{
    string resultado = "";
    checksum = 0;

    for (int i = 0; i < texto.length(); i++)
    {
        char c = texto[i];
        checksum += (int)c;

        c = c - CLAVE;

        if (c >= 'a' && c <= 'z')
            c = c - 32;
        else if (c >= 'A' && c <= 'Z')
            c = c + 32;

        resultado += c;
    }

    return resultado;
}


bool cargarMensajes(vector<string>& mensajes) //Pregunta si quieres recuperar los mensajes de antes
{
    ifstream archivo("Encriptar.txt");

    if (!archivo.is_open())
        return false;

    int checksumGuardado;
    archivo >> checksumGuardado;
    archivo.ignore();

    char opcion;
    cout << "Quieres recuperar los mensajes? (s/n): ";
    cin >> opcion;
    cin.ignore();

    int checksumCalculado = 0;

    if (opcion == 's')
    {
        string linea;

        while (getline(archivo, linea))
        {
            int checksumTemp;
            string mensaje = desencriptar(linea, checksumTemp);
            checksumCalculado += checksumTemp;

            mensajes.push_back(mensaje);
            cout << mensaje << endl;
        }

        if (checksumCalculado != checksumGuardado)
        {
            cout << "El archivo ha sido alterado" << endl;
        }

        archivo.close();
        return true;
    }

    archivo.close();
    return false;
}


void guardarMensajes(const vector<string>& mensajes, bool recuperar) //Guarda los nuevos mensajes
{
    ofstream archivo("Encriptar.txt");

    if (!archivo.is_open())
    {
        cout << "Error al guardar el archivo." << endl;
        return;
    }

    int checksumTotal = 0;
    vector<string> cifrados;

    for (int i = 0; i < mensajes.size(); i++)
    {
        int checksumTemp;
        string cifrado = encriptar(mensajes[i], checksumTemp);

        checksumTotal += checksumTemp;
        cifrados.push_back(cifrado);
    }

    archivo << checksumTotal << endl;

    for (int i = 0; i < cifrados.size(); i++)
    {
        archivo << cifrados[i] << endl;
    }

    archivo.close();

    if (!recuperar)
        cout << "Se han eliminado los mensajes anteriores" << endl;
    else
        cout << "Mensajes guardados correctamente." << endl;
}
