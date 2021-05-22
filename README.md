# Grafos
**Jacobo Soffer A01028653**
Almacena un grafo leído de un archivo en una lista o matriz de adyecencia. Para usar redirección de stdin en lugar de lectura del archivo, cambiar el constructor usado en `main.cpp`.

## Formato de archivo de entrada
* Los valores son separados por espacios y una linea nueva entre cada par/triplete de valores.
* La primera linea esta reservada para un comentario o titulo del grafo. Esta es ignorada por el programa.
* En la segunda linea el primer valor indica el maximo número de nodo y el segundo el número de vertices.
* Todos los valores a continuación son las relaciones entre los nodos, el primero siendo el nodo origen y el segundo el nodo destino.
* Para grafos con pesos, el primer valor indica el nodo de origen, el segundo el peso, y el tercero el nodo de destino.