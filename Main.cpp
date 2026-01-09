#include <iostream>
#include <vector>
#include <string>
#include "AEncriptar.h"

using namespace std;

int main()
{
    vector<string> mensajes;
    string texto;

    bool recuperados = cargarMensajes(mensajes);

    cout << "Escribe mensajes (exit para acabar):" << endl;

    while (true)
    {
        getline(cin, texto);

        if (texto == "exit")
            break;

        mensajes.push_back(texto);
    }

    char guardar;
    cout << "Guardar? (s/n): ";
    cin >> guardar;

    if (guardar == 's')
        guardarMensajes(mensajes, recuperados);
    else if (!recuperados)
        cout << "Se han eliminado los mensajes anteriores" << endl;

    return 0;
}
