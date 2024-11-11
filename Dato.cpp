#include "Dato.h"

Dato::Dato(const std::string& nombre, int id) : nombre(nombre), id(id) {}

std::string Dato::obtenerNombre() const{
    return nombre;
}

void Dato::establecerNombre( const std::string& nuevoNombre){
    nombre = nuevoNombre;
}

int Dato::obtenerId() const{
    return id;
}

void Dato::establecerId(int nuevoId){
    id = nuevoId;
}

bool Dato::operator<(const Dato &other) const
{
    // Sobrecarga del operador de <= que para comparar objetos de tipo Dato
    if (id == other.id)
    {
        
            // Si las cédulas son iguales, compara los nombres
            return nombre < other.nombre;
    }
    // Si las cédulas son diferentes, compara las cédulas
    return id < other.id;
}

bool Dato::operator>(const Dato &other) const
{
    // Sobrecarga del operador > para comparar objetos de tipo Dato
    if (id == other.id)
    {
            // Si las cédulas son iguales, compara los nombres
            return nombre > other.nombre;
    }
    // Si las cédulas son diferentes, compara las cédulas
    return id > other.id;
}

bool Dato::operator==(const Dato &other) const
{
    // Sobrecarga del operador de igualdad para comparar objetos de tipo Dato
    return (id == other.id) && (nombre == other.nombre);
    // Devuelve verdadero si las cédulas y los nombres son iguales, de lo contrario, falso.
}
