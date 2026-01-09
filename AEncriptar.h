#pragma once

#include <vector>
#include <string>

bool cargarMensajes(std::vector<std::string>& mensajes); //Cargar los mensajes 
void guardarMensajes(const std::vector<std::string>& mensajes, bool recuperar); //Guardar los mensajes

std::string encriptar(std::string texto, int& checksum); //Funcion de encriptar
std::string desencriptar(std::string texto, int& checksum); //Funcion desencriptar


