
# Proyecto: Simulador de Comandos SQL con Árbol B+

Este proyecto implementa un simulador básico de comandos SQL (`INSERT`, `SELECT`, `UPDATE`, `DELETE`) 
utilizando un árbol B+ para almacenar y gestionar datos de manera estructurada. 
Cada comando es procesado por un analizador SQL, que extrae la información de los parámetros
y llama a las funciones del árbol B+ para simular las operaciones solicitadas.

## Estructura del Proyecto

El proyecto se divide en los siguientes archivos:

- `ArbolBPlus.h` y `ArbolBPlus.cpp`: Definen y implementan la clase `ArbolBPlus`, que simula un árbol B+ con operaciones
  básicas de inserción, selección, actualización y eliminación.
- `AnalizadorSQL.h` y `AnalizadorSQL.cpp`: Contienen la clase `AnalizadorSQL`, que interpreta los comandos SQL y llama
  a los métodos de `ArbolBPlus`.
- `main.cpp`: Archivo principal que inicia el programa y permite al usuario ingresar comandos SQL.
- `Makefile`: Archivo para automatizar la compilación y ejecución del proyecto.

## Algoritmos y Pseudocódigo

### Algoritmo General

1. Leer el comando SQL ingresado por el usuario.
2. Identificar el tipo de comando (`INSERT`, `SELECT`, `UPDATE`, `DELETE`).
3. Llamar a la función correspondiente en `AnalizadorSQL` para extraer los parámetros y procesarlos.
4. Ejecutar el comando llamando al método correspondiente en `ArbolBPlus`.
5. Mostrar en pantalla el comando ejecutado y sus detalles.

### Pseudocódigo

```pseudo
INICIAR el programa
MIENTRAS (verdadero)
    MOSTRAR "SQL> "
    LEER comando SQL ingresado por el usuario
    SI comando == "exit"
        TERMINAR el programa
    FIN SI
    ANALIZAR el comando
    SI es INSERTAR
        PROCESAR columnas y valores
        EJECUTAR en ArbolBPlus
    SI es SELECCIONAR
        PROCESAR columnas
        EJECUTAR en ArbolBPlus
    SI es ACTUALIZAR
        PROCESAR asignaciones y condiciones
        EJECUTAR en ArbolBPlus
    SI es ELIMINAR
        PROCESAR condiciones
        EJECUTAR en ArbolBPlus
FIN MIENTRAS
```

## Explicación de las Funciones

- `ArbolBPlus::insertar`: Muestra un mensaje de inserción con el formato `INSERT INTO tabla (columnas) VALUES (valores)`.
- `ArbolBPlus::seleccionar`: Muestra un mensaje de selección con el formato `SELECT columnas FROM tabla`.
- `ArbolBPlus::actualizar`: Muestra un mensaje de actualización con el formato `UPDATE tabla SET asignaciones WHERE condicion`.
- `ArbolBPlus::eliminar`: Muestra un mensaje de eliminación con el formato `DELETE FROM tabla WHERE condicion`.
- `AnalizadorSQL::analizar`: Interpreta el comando y llama a la función adecuada según el tipo de operación.

## Compilación y Ejecución

1. Para compilar el proyecto, ejecuta en la terminal:

    ```bash
    make
    ```

2. Para ejecutar el programa, usa:

    ```bash
    make run
    ```

3. Ingresa comandos SQL en el siguiente formato:

    ```sql
    INSERT INTO clientes (nombre, edad) VALUES ("Juan", 30)
    SELECT (nombre, edad) FROM clientes
    UPDATE clientes SET edad=31 WHERE nombre="Juan"
    DELETE FROM clientes WHERE nombre="Juan"
    ```

4. Para salir del programa, escribe `exit`.

## Ejemplos de Uso

Aquí algunos ejemplos de cómo interactuar con el programa:

```bash
SQL> INSERT INTO clientes (nombre, edad) VALUES ("Juan", 30)
Ejecutando: INSERT INTO clientes (nombre, edad) VALUES ("Juan", 30)

SQL> SELECT (nombre, edad) FROM clientes
Ejecutando: SELECT nombre, edad FROM clientes

SQL> UPDATE clientes SET edad=31 WHERE nombre="Juan"
Ejecutando: UPDATE clientes SET edad = 31 WHERE nombre="Juan"

SQL> DELETE FROM clientes WHERE nombre="Juan"
Ejecutando: DELETE FROM clientes WHERE nombre="Juan"

SQL> exit
```

## Requisitos

- Compilador compatible con C++11 o superior
- Makefile para automatizar la compilación (incluido en el proyecto)

## Limpieza de Archivos Generados

Para eliminar archivos generados por la compilación, puedes utilizar el siguiente comando:

```bash
make clean
```
