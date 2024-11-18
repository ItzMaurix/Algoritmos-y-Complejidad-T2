Instrucciones para la Ejecución de los Archivos

Este proyecto contiene los siguientes archivos:
1. "generador.py": Genera un archivo "entrada.txt" con cadenas de texto que cubren tres casos:
   - Cadenas con caracteres repetidos.
   - Cadenas que benefician las transposiciones.
   - Cadenas completamente aleatorias.
2. "FuerzaBruta.cpp": Implementa la distancia mínima de edición utilizando el paradigma de Fuerza Bruta.
3. "ProgramacionDinamica.cpp": Implementa la distancia mínima de edición utilizando el paradigma de Programación Dinámica.

---

Requisitos Previos
1. Tener instalado Python3 para ejecutar el generador:
   sudo apt update
   sudo apt install python3

2. Tener un compilador de C++ como "g++":
   sudo apt install g++

---

Paso 1: Generar el Archivo de Entrada
Ejecuta el generador "generador.py" para crear el archivo "entrada.txt" con las cadenas de texto de prueba.

python3 generador.py

Esto generará un archivo "entrada.txt" con el formato:

n
cadena1 cadena2
...

Donde "n" es el número de pares de cadenas, y cada línea siguiente contiene dos cadenas: "cadena1" y "cadena2".

---

Paso 2: Compilar los Programas en C++
1. Compila el archivo "FuerzaBruta.cpp":
   g++ FuerzaBruta.cpp -o FuerzaBruta

2. Compila el archivo "ProgramacionDinamica.cpp":
   g++ ProgramacionDinamica.cpp -o ProgramacionDinamica

Esto generará los ejecutables "FuerzaBruta" y "ProgramacionDinamica".

---

Paso 3: Ejecutar los Programas
Ambos programas tienen dos modos de entrada:
1. Leer cadenas de texto desde el archivo "entrada.txt".
2. Introducir manualmente dos cadenas de texto "S1" y "S2".

3.1 Modo Archivo
Si deseas utilizar el archivo "entrada.txt" generado previamente, ejecuta los programas de la siguiente manera:

- Para "FuerzaBruta":
  ./FuerzaBruta
  Cuando el programa solicite, selecciona la opción "1" (Modo Archivo). A continuación, procesará las cadenas del archivo "entrada.txt" y mostrará los resultados para cada par.

- Para "ProgramacionDinamica":
  ./ProgramacionDinamica
  Igual que el programa anterior, selecciona la opción "1" para leer las cadenas desde el archivo.

3.2 Modo Manual
Si deseas introducir manualmente las cadenas "S1" y "S2", ejecuta:

- Para "FuerzaBruta":
  ./FuerzaBruta
  Selecciona la opción "0" (Modo Manual). Luego, el programa pedirá que introduzcas las dos cadenas "S1" y "S2".

- Para "ProgramacionDinamica":
  ./ProgramacionDinamica
  Igual que el programa anterior, selecciona la opción "0" e ingresa las cadenas manualmente.

---

Salida de los Programas
Ambos programas mostrarán:
1. Las cadenas procesadas ("S1" y "S2").
2. La distancia mínima de edición calculada.
3. El tiempo de ejecución.
4. La memoria utilizada por las estructuras del programa.

---

Ejemplo de Uso

1. Generar el archivo de entrada:
   python3 generador.py

   Archivo "entrada.txt" generado:
   3
   aaa aaaab
   abcde acbde
   random1 random2

2. Compilar los programas:
   g++ FuerzaBruta.cpp -o FuerzaBruta
   g++ ProgramacionDinamica.cpp -o ProgramacionDinamica

3. Ejecutar "FuerzaBruta" en modo archivo:
   ./FuerzaBruta
   Selecciona la opción "1". La salida mostrará:
   S1: aaa     S2: aaaab
   Distancia mínima de edición: 1
   Tiempo de ejecución: 0.002 segundos
   Memoria utilizada: 2.1 KB

4. Ejecutar "ProgramacionDinamica" en modo manual:
   ./ProgramacionDinamica
   Selecciona la opción "0" e introduce:
   Ingrese la primera cadena: hello
   Ingrese la segunda cadena: hola

   La salida mostrará:
   Distancia mínima de edición: 3
   Tiempo de ejecución: 0.001 nanosegundos
   Memoria utilizada: 1.5 KB

---

Notas Adicionales
- Asegúrate de que "entrada.txt" esté en el mismo directorio que los ejecutables.
- Si necesitas personalizar el número de casos o las longitudes de las cadenas, edita los parámetros en "generador.py".