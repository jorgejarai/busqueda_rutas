# Búsqueda de ruta en C++

Este programa implementa distintos algoritmos de búsqueda de ruta para grafos no dirigidos y ponderados, como A*, búsqueda en profundidad al azar, búsqueda de costo uniforme y búsqueda *greedy*.

## Compilación

Para compilar el programa, se requiere CMake 3.10 o superior y un compilador compatible con C++17. Para compilar el programa, ejecute:

```console
$ mkdir build
$ cd build
$ cmake ..
$ make
```

El ejecutable del programa se va a encontrar en `build/tarea1`.

## Ejecución

El programa se ejecuta de la siguiente manera:

```console
$ ./tarea1 <algoritmo> <grafo>
```

Donde `<algoritmo>` puede tomar uno de los siguientes valores:

- `a-star`: algoritmo A*
- `dfs`: búsqueda en profundidad al azar
- `ucs`: búsqueda de costo uniforme
- `greedy`: búsqueda *greedy*

Y `<grafo>` es la ruta archivo de entrada que contiene el grafo a analizar. El formato del archivo de entrada es el siguiente:

```text
Init: <nodo_inicial>
Goal: <nodo_meta>
<nodo_1> <heurística>
<nodo_2> <heurística>
...
<nodo_n> <heurística>
<nodo_origen>, <nodo_destino>, <costo>
<nodo_origen>, <nodo_destino>, <costo>
...
<nodo_origen>, <nodo_destino>, <costo>
```

Al encontrar una ruta válida, el programa imprime la ruta encontrada en la salida estándar, acompañada de su costo y el número de veces que se expandió cada nodo de la solución, en el siguiente formato:

```text
<nodo_inicial> -> <nodo_1> -> <nodo_2> -> ... -> <nodo_meta>
Costo: <costo total>
<nodo_1>: <expansiones>
<nodo_2>: <expansiones>
...
<nodo_n>: <expansiones>
```
