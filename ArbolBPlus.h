#ifndef ARBOL_BPLUS_H
#define ARBOL_BPLUS_H

#include <string>    // Biblioteca para manejar cadenas de texto (std::string)
#include <vector>    // Biblioteca para manejar listas de elementos (std::vector)
#include <map>       // Biblioteca para manejar pares clave-valor (std::map)
#include <iostream>  // Biblioteca para operaciones de entrada y salida (std::cout)
#include "BpNode.h"
#include <algorithm>

// Clase ArbolBPlus simula un árbol B+ con métodos básicos para las operaciones de SQL.
class ArbolBPlus {
public:

    BpNode* root; // Puntero a la raíz del árbol B+
    int maxKeys;  // Máximo número de llaves permitidas por nodo

    ArbolBPlus(int maxK) : root(nullptr), maxKeys(maxK) {}

    // Método para simular la inserción en el árbol B+
    // Recibe el nombre de la tabla, una lista de columnas y una lista de valores
    void insertar(const std::string& tabla, const std::vector<std::string> columnas, const std::vector<std::string> valores);

    // Método para simular la selección de datos en el árbol B+
    // Recibe el nombre de la tabla y una lista de columnas
    void seleccionar(const std::string& tabla, const std::vector<std::string>& columnas);

    // Método para simular la actualización de datos en el árbol B+
    // Recibe el nombre de la tabla, un mapa de asignaciones (columna=valor), y una condición
    void actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::map<std::string, std::string>& condicion);

    // Método para simular la eliminación de datos en el árbol B+
    // Recibe el nombre de la tabla y una condición para eliminar filas que la cumplan
    void eliminar(const std::string& tabla, const std::string& condicion);

    void eliminarClave(BpNode* nodo, Dato* clave);

    void rebalancearDespuesDeEliminar(BpNode* nodo);

    void redistribuirIzq(BpNode* padre, size_t idx);
     
    void redistribuirDer(BpNode* padre, size_t idx);

    void fusionarNodos(BpNode* padre, size_t idx);

    BpNode* encontrarPadre(BpNode* nodoActual, BpNode* nodoHijo);

    void splitChild(BpNode* padre, size_t i);

    void mostrarArbol();

    private:

    // Inserta una llave en un nodo que no está lleno
    void insertNonFull(BpNode* node, Dato* llave);

    // Divide un nodo cuando está lleno
    BpNode* splitchild(BpNode* node, int indice);

    // Función auxiliar para recorrer a partir de un nodo específico
    void GoThroughNode(BpNode* node);

    // Función auxiliar para mostrar el árbol desde un nodo específico
    void printTreeAux(BpNode* node, std::string prefix, bool isLast);
    
    std::vector<BpNode*> buscarNodo(BpNode* nodo, std::string& nombre);

    void buscarMatches(BpNode* nodo, std::string& nombre);

    BpNode* buscarNodo(BpNode* nodo, int id);
};

#endif