# Los Desafios de James

Trabajo Práctico Grupal de Algoritmos y Programación 2 2c2023.

### Integrantes del grupo NOMBRE_GRUPO:

1. SCHWEITZER, Agustín  - Padron - aschweitzer@fi.uba.ar
2. MENEM, Eduardo Francisco - Padron - emenem@fi.uba.ar
3. GUERRA ECHENIQUE, Martin - Padron - mguerrae@fi.uba.ar
4. BONNEVAL, Julien - Padron - jbonneval.ext@fi.uba.ar

### Corrector asignado:

Julian Ruiz Diaz

## Compilación:

El programa se puede compilar utilizando el **CMakeLists.txt** que está en el repositorio o bien ejecutando por consola:

> g++ -I include src/*.cpp main.cpp -o main -Wall -Werror -Wconversion

Al compilar con **CMake**, se deben agregar todos los archivos **.cpp** en la línea:

> add_executable(ayp2_plantilla_tp_grupal_2c2023 main.cpp //otros archivos .cpp//)

## Tests:

Para ejecutar los tests, basta con cargar el **CMakeLists.txt** que se encuentra dentro de la carpeta tests/.

## Organización de archivos:

En la carpeta src/ van a encontrar los archivos .cpp del proyecto.<br>
En la carpeta include/ van a encontrar los headers del proyecto.<br>
