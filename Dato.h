#ifndef DATO_H
#define DATO_H

#include <string>

class Dato{
private:

    std::string nombre;
    int id;

public: 
    Dato(const std::string& nombre = "", int id = 0);

    std::string obtenerNombre() const;
    void establecerNombre(const std::string& nuevoNombre);

    int obtenerId() const;
    void establecerId(int nuevoId);

    // Compara dos personas por edad y luego por nombre si las edades son iguales.
    bool operator<(const Dato &other) const;

    bool operator>(const Dato &other) const;

    // Comprueba si dos personas son iguales en términos de edad y nombre.
    bool operator==(const Dato &other) const;
};

#endif 