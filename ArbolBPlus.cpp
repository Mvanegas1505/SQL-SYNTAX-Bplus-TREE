#include <iomanip>
#include "ArbolBPlus.h"
#include "Dato.h"

// Implementación del método insertar
// Muestra en la consola el comando simulado de inserción con columnas y valores dados
// Implementación del método insertar
// Muestra en la consola el comando simulado de inserción con columnas y valores dados
void ArbolBPlus::insertar(const std::string& tabla, std::vector<std::string> columnas, std::vector<std::string> valores) {
    std::cout << "Ejecutando: INSERT INTO " << tabla << " (";

    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }

    std::cout << ") VALUES (";
    for (size_t i = 0; i < valores.size(); ++i) {
        std::cout << valores[i];
        if (i < valores.size() - 1) std::cout << ", ";
    }
    std::cout << ")\n";

    // Verificar que las columnas y valores coincidan
    if (columnas.size() != valores.size()) {
        std::cerr << "Error: El número de columnas y valores no coincide.\n";
        return;
    }

    // Crear un nuevo Dato a partir de las columnas y valores
    std::string nombre;
    int id = 0;
    for (size_t i = 0; i < columnas.size(); ++i) {
        if (columnas[i] == "nombre") {
            nombre = valores[i];
        } else if (columnas[i] == "id") {
            try {
                id = std::stoi(valores[i]);
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: El valor de id no es un número válido.\n";
                return;
            }
        }
    }

    Dato* nuevoDato = new Dato(nombre, id);
    if (!root) {
        root = new BpNode(true);
        root->isLeaf = true;
    }

    if (root->key.size() == static_cast<size_t>(maxKeys)) {
        BpNode* nuevoRoot = new BpNode(false);
        nuevoRoot->isLeaf = false;
        nuevoRoot->child_ptrs.push_back(root);
        splitChild(nuevoRoot, 0);
        root = nuevoRoot;
    }

    insertNonFull(root, nuevoDato);
}

// Implementación del método seleccionar
// Muestra en la consola el comando simulado de selección con columnas especificadas
void ArbolBPlus::seleccionar(const std::string& tabla, const std::vector<std::string>& columnas) {
    std::cout << "Ejecutando: SELECT ";
    // Itera y muestra cada columna seleccionada
    for (size_t i = 0; i < columnas.size(); ++i) {
        std::cout << columnas[i];
        if (i < columnas.size() - 1) std::cout << ", ";
    }
    std::cout << " FROM " << tabla << std::endl;

    if (!root) {
        std::cout << "Tabla vacía" << std::endl;
        return;
    }

    // Mostrar datos de la raíz
    BpNode* nodo_actual = root;
    for (auto& dato : nodo_actual->key) {
        for (const auto& columna : columnas) {
            if (columna == "nombre") {
                std::cout << dato->obtenerNombre() << "\t";
            } else if (columna == "id") {
                std::cout << dato->obtenerId() << "\t";
            }
        }
        std::cout << std::endl;
    }

    // Recorrer todas las ramas del árbol usando un stack
    std::vector<BpNode*> nodos; // Stack de nodos
    nodos.push_back(root);

    while (!nodos.empty()) {
        nodo_actual = nodos.back();
        nodos.pop_back();

        if (!nodo_actual->isLeaf) {
            for (auto it = nodo_actual->child_ptrs.rbegin(); it != nodo_actual->child_ptrs.rend(); ++it) {
                if (*it) {
                    nodos.push_back(*it);
                }
            }
        } else {
            // Iterar sobre todas las hojas
            while (nodo_actual) {
                for (auto& dato : nodo_actual->key) {
                    for (const auto& columna : columnas) {
                        if (columna == "nombre") {
                            std::cout << dato->obtenerNombre() << "\t";
                        } else if (columna == "id") {
                            std::cout << dato->obtenerId() << "\t";
                        }
                    }
                    std::cout << std::endl;
                }
                nodo_actual = nodo_actual->nextLeaf;
            }
        }
    }
}

// Implementación del método actualizar
// Muestra en la consola el comando simulado de actualización con asignaciones y condición
void ArbolBPlus::actualizar(const std::string& tabla, const std::map<std::string, std::string>& asignaciones, const std::map<std::string, std::string>& condicion) {
    std::cout << "Ejecutando: UPDATE " << tabla << " SET ";
    for (const auto& asignacion : asignaciones) {
        std::cout << asignacion.first << " = " << asignacion.second;
    }
    std::cout << " WHERE ";
    for (const auto& con : condicion) {
        std::cout << con.first << " = " << con.second << std::endl; 
    }

    std::string keyAsignacion = asignaciones.begin()->first;
    std::string valueAsignacion = asignaciones.begin()->second;

    std::string keyCondicion = condicion.begin()->first;
    std::string valueCondicion = condicion.begin()->second;

    std::transform(keyCondicion.begin(), keyCondicion.end(), keyCondicion.begin(), ::toupper);
    std::transform(keyAsignacion.begin(), keyAsignacion.end(), keyAsignacion.begin(), ::toupper);

    if (keyCondicion == "NOMBRE"){
        
        std::vector<BpNode*> nodosObjetivo = buscarNodo(root, valueCondicion);
            
        if (!nodosObjetivo.empty()){
            for (size_t i = 0; i < nodosObjetivo.size(); i++){
                for (size_t j = 0; j < nodosObjetivo[i]->key.size(); j++) {

                    Dato* dato = nodosObjetivo[i]->key[j];
                    std::string datoNombre = dato->obtenerNombre(); 
                    
                    std::transform(datoNombre.begin(), datoNombre.end(), datoNombre.begin(), ::toupper);
                    std::transform(valueCondicion.begin(), valueCondicion.end(), valueCondicion.begin(), ::toupper);

                    if (datoNombre == valueCondicion){
                        if (keyAsignacion == "NOMBRE"){
                            dato->establecerNombre(valueAsignacion);
                        } else {
                            dato->establecerId(std::stoi(valueAsignacion));
                        }
                    }
                }
            }
            std::cout << "Actualizacion realizada exitosamente.\n";
        } else {
            std::cout << "No se encontro el registro.\n";
        }
         
    } else {

        BpNode* nodoObjetivo = buscarNodo(root, std::stoi(valueCondicion));

        if (nodoObjetivo != nullptr){
            for (size_t i = 0; i < nodoObjetivo->key.size(); i++) {
                Dato* dato = nodoObjetivo->key[i];

                if (dato->obtenerId() == std::stoi(valueCondicion)){
                    if (keyAsignacion == "NOMBRE"){
                        dato->establecerNombre(valueAsignacion);
                    } else {
                        dato->establecerId(std::stoi(valueAsignacion));
                    }
                }
            }
            std::cout << "Actualizacion realizada exitosamente.\n";
        } else {
            std::cout << "No se encontro el registro.\n";
        }
    }

}

// Implementación del método eliminar
// Muestra en la consola el comando simulado de eliminación con la condición dada
void ArbolBPlus::eliminar(const std::string& tabla, const std::string& condicion) {
    std::cout << "Ejecutando: DELETE FROM " << tabla << " WHERE " << condicion << std::endl;

    if (!root) {
        std::cout << "El árbol está vacío. No hay nada que eliminar.\n";
        return;
    }

    Dato* claveEliminar;
    size_t pos = condicion.find('=');
    if (pos != std::string::npos) {
        std::string claveStr = condicion.substr(pos + 1);
        try {
            // Intenta convertir la clave a un número entero para eliminar por ID
            int claveId = std::stoi(claveStr);
            claveEliminar = new Dato("", claveId);  // Clave basada en ID
        } catch (const std::invalid_argument&) {
            // Si no es un número, tratamos la clave como un nombre para eliminar por nombre
            claveEliminar = new Dato(claveStr, 0); // Clave basada en nombre
        }
    } else {
        std::cout << "Condición inválida.\n";
        return;
    }

    eliminarClave(root, claveEliminar);
    delete claveEliminar;

    if (root->key.empty()) {
        root = root->isLeaf ? nullptr : root->child_ptrs[0];
    }
}

void ArbolBPlus::eliminarClave(BpNode* nodo, Dato* clave) {
    size_t i = 0;
    bool esBusquedaPorId = (clave->obtenerId() != 0); // Si el ID es no nulo, es una eliminación por ID

    // Búsqueda inicial: determinar la posición de la clave en el nodo
    while (i < nodo->key.size() && 
          (esBusquedaPorId ? nodo->key[i]->obtenerId() < clave->obtenerId() : nodo->key[i]->obtenerNombre() != clave->obtenerNombre())) {
        i++;
    }

    if (nodo->isLeaf) {
        // En nodo hoja: verificar si la clave se encuentra en el índice correcto y eliminarla
        bool encontrada = (i < nodo->key.size()) &&
                          (esBusquedaPorId ? nodo->key[i]->obtenerId() == clave->obtenerId()
                                           : nodo->key[i]->obtenerNombre() == clave->obtenerNombre());
        if (encontrada) {
            nodo->key.erase(nodo->key.begin() + i);
            std::cout << "Clave eliminada: " << (esBusquedaPorId ? "ID " + std::to_string(clave->obtenerId())
                                                                 : "Nombre " + clave->obtenerNombre()) << "\n";
            if (nodo->key.empty()) rebalancearDespuesDeEliminar(nodo);
        } else {
            std::cout << "Clave no encontrada en el árbol.\n";
        }
    } else {
        // En nodo interno: recursivamente eliminar en el hijo correspondiente
        if (i < nodo->child_ptrs.size()) {
            eliminarClave(nodo->child_ptrs[i], clave);
            if (nodo->child_ptrs[i]->key.empty()) rebalancearDespuesDeEliminar(nodo->child_ptrs[i]);
        }
    }
}

void ArbolBPlus::rebalancearDespuesDeEliminar(BpNode* nodo) {
    if (!nodo || nodo == root) return; // No hay necesidad de rebalancear si el nodo es nulo o es la raíz

    BpNode* padre = encontrarPadre(root, nodo);
    if (!padre) return; // Si no se encuentra el padre, no se puede rebalancear

    size_t idx = std::find(padre->child_ptrs.begin(), padre->child_ptrs.end(), nodo) - padre->child_ptrs.begin();

    if (idx > 0 && !padre->child_ptrs[idx - 1]->key.empty()) {
        redistribuirIzq(padre, idx - 1);
    } else if (idx < padre->child_ptrs.size() - 1 && !padre->child_ptrs[idx + 1]->key.empty()) {
        redistribuirDer(padre, idx);
    } else {
        fusionarNodos(padre, idx > 0 ? idx - 1 : idx);
    }
}

void ArbolBPlus::redistribuirIzq(BpNode* padre, size_t idx) {
    BpNode* izq = padre->child_ptrs[idx];
    BpNode* der = padre->child_ptrs[idx + 1];
    if (!izq || !der) return; // Verificar que los nodos izquierdo y derecho no sean nulos

    der->key.insert(der->key.begin(), padre->key[idx]);
    padre->key[idx] = izq->key.back();
    izq->key.pop_back();
}

void ArbolBPlus::redistribuirDer(BpNode* padre, size_t idx) {
    BpNode* izq = padre->child_ptrs[idx];
    BpNode* der = padre->child_ptrs[idx + 1];
    if (!izq || !der) return; // Verificar que los nodos izquierdo y derecho no sean nulos

    izq->key.push_back(padre->key[idx]);
    padre->key[idx] = der->key.front();
    der->key.erase(der->key.begin());
}

void ArbolBPlus::fusionarNodos(BpNode* padre, size_t idx) {
    BpNode* izq = padre->child_ptrs[idx];
    BpNode* der = padre->child_ptrs[idx + 1];
    if (!izq || !der) return; // Verificar que los nodos izquierdo y derecho no sean nulos

    izq->key.push_back(padre->key[idx]);
    izq->key.insert(izq->key.end(), der->key.begin(), der->key.end());
    izq->child_ptrs.insert(izq->child_ptrs.end(), der->child_ptrs.begin(), der->child_ptrs.end());

    padre->key.erase(padre->key.begin() + idx);
    padre->child_ptrs.erase(padre->child_ptrs.begin() + idx + 1);

    delete der;
}

BpNode* ArbolBPlus::encontrarPadre(BpNode* nodoActual, BpNode* nodoHijo) {
    if (!nodoActual || nodoActual->isLeaf || nodoActual == nodoHijo) return nullptr;
    for (auto* child : nodoActual->child_ptrs) {
        if (child == nodoHijo) return nodoActual;
        BpNode* resultado = encontrarPadre(child, nodoHijo);
        if (resultado) return resultado;
    }
    return nullptr;
}

void ArbolBPlus::insertNonFull(BpNode* nodo, Dato* llave) {
    if (nodo->isLeaf) {
        nodo->key.push_back(llave);
        std::sort(nodo->key.begin(), nodo->key.end(), [](const Dato* a, const Dato* b) {
            return a->obtenerId() < b->obtenerId();
        });
        std::cout << "Inserted " << llave->obtenerId() << " into leaf node.\n";
    } else {
        size_t i = 0;
        while (i < nodo->key.size() && llave->obtenerId() > nodo->key[i]->obtenerId()) {
            i++;
        }
        if (nodo->child_ptrs[i]->key.size() == static_cast<size_t>(maxKeys)) {
            splitChild(nodo, i);
            if (llave->obtenerId() > nodo->key[i]->obtenerId()) {
                i++;
            }
        }
        insertNonFull(nodo->child_ptrs[i], llave);
    }
}

BpNode* ArbolBPlus::splitchild(BpNode* nodo, int indice) {

    BpNode* hijo = nodo->child_ptrs[indice];
    BpNode* nuevoNodo = new BpNode(hijo->isLeaf);

    int mitad = maxKeys / 2;
    nodo->key.insert(nodo->key.begin() + indice, hijo->key[mitad]);

    nuevoNodo->key.assign(hijo->key.begin() + mitad + 1, hijo->key.end());
    hijo->key.resize(mitad);

    if (!hijo->isLeaf) {
        nuevoNodo->child_ptrs.assign(hijo->child_ptrs.begin() + mitad + 1, hijo->child_ptrs.end());
        hijo->child_ptrs.resize(mitad + 1);
    }
    return nuevoNodo;
}

std::vector<BpNode*> matches;
std::vector<BpNode*> ArbolBPlus::buscarNodo(BpNode* nodo, std::string& nombre){
    buscarMatches(nodo, nombre);
    std::vector<BpNode*> aux = matches;
    matches.clear();

    return aux;
}

void ArbolBPlus::buscarMatches(BpNode* nodo, std::string& nombre){
    if (!nodo) return;

    for (size_t i = 0; i < nodo->key.size(); i++) {
        Dato* dato = nodo->key[i];
        std::string nombreDato = dato->obtenerNombre();

        std::transform(nombreDato.begin(), nombreDato.end(), nombreDato.begin(), ::toupper);
        std::transform(nombre.begin(), nombre.end(), nombre.begin(), ::toupper);

        if (nombreDato == nombre) {
            int count = std::count(matches.begin(), matches.end(), nodo);
            if (count <= 0){
                matches.emplace_back(nodo);
            }
        } 
    }
    
    for (size_t i = 0; i < nodo->child_ptrs.size(); i++) {
        buscarMatches(nodo->child_ptrs[i], nombre);    
    }
}

BpNode* ArbolBPlus::buscarNodo(BpNode* nodo, int id){
    if (!nodo) return nullptr;

    size_t i = 0;
    while (i < nodo->key.size() && id > nodo->key[i]->obtenerId()) i++;
    
    if (i < nodo->key.size() && id == nodo->key[i]->obtenerId()) {
        return nodo;
    }

    if (nodo->isLeaf) {
        return nullptr;
    } else {
        BpNode* resultado = buscarNodo(nodo->child_ptrs[i], id);
        return resultado;
    }
}

void ArbolBPlus::mostrarArbol() {
    printTreeAux(root, "", true);
}

void ArbolBPlus::printTreeAux(BpNode* nodo, std::string prefix, bool esUltimo) {
    if (!nodo) return;

    std::cout << prefix;
    std::cout << (esUltimo ? "└── " : "├── ");

    for (size_t i = 0; i < nodo->key.size(); i++) {
        std::cout << "Nodo: " << nodo->key[i]->obtenerNombre() << " (" << nodo->key[i]->obtenerId() << ")";
        if (i != nodo->key.size() - 1) {
            std::cout << " , ";
        }
    }
    std::cout << std::endl;

    prefix += (esUltimo ? "    " : "|   ");
    for (size_t i = 0; i < nodo->child_ptrs.size(); i++) {
        printTreeAux(nodo->child_ptrs[i], prefix, i == nodo->child_ptrs.size() - 1);
    }
}

void ArbolBPlus::splitChild(BpNode* padre, size_t i) {
    BpNode* hijo = padre->child_ptrs[i];
    BpNode* nuevoHijo = new BpNode(hijo->isLeaf);
    nuevoHijo->isLeaf = hijo->isLeaf;

    size_t t = maxKeys / 2;
    for (size_t j = 0; j < t; ++j) {
        nuevoHijo->key.push_back(hijo->key[j + t + 1]);
    }

    if (!hijo->isLeaf) {
        for (size_t j = 0; j <= t; ++j) {
            nuevoHijo->child_ptrs.push_back(hijo->child_ptrs[j + t + 1]);
        }
    }

    hijo->key.resize(t);
    hijo->child_ptrs.resize(t + 1);

    padre->child_ptrs.insert(padre->child_ptrs.begin() + i + 1, nuevoHijo);
    padre->key.insert(padre->key.begin() + i, hijo->key[t]);
}
