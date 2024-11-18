import random
import string

def generar_caso_repetidos(max_longitud):
    longitud = random.randint(1, max_longitud)
    char = random.choice(string.ascii_lowercase)
    return [char * longitud, char * (longitud + random.randint(0, 2))]

def generar_caso_transposiciones(max_longitud):
    longitud = random.randint(2, max_longitud)
    cadena = ''.join(random.choices(string.ascii_lowercase, k=longitud))
    i = random.randint(0, longitud - 2)
    transpuesta = list(cadena)
    transpuesta[i], transpuesta[i + 1] = transpuesta[i + 1], transpuesta[i]
    return [cadena, ''.join(transpuesta)]

def generar_caso_aleatorio(max_longitud):
    longitud1 = random.randint(1, max_longitud)
    longitud2 = random.randint(1, max_longitud)
    cadena1 = ''.join(random.choices(string.ascii_lowercase, k=longitud1))
    cadena2 = ''.join(random.choices(string.ascii_lowercase, k=longitud2))
    return [cadena1, cadena2]

def generar_dataset(max_longitud, total_casos):
    casos = []
    
    i = 0
    while i < 3:
        j = 0
        if i == 0:
            while j < total_casos:
                casos.append(generar_caso_repetidos(max_longitud))
                j += 1
        elif i == 1:
            while j < total_casos:
                casos.append(generar_caso_transposiciones(max_longitud))
                j += 1
        else:
            while j < total_casos:
                casos.append(generar_caso_aleatorio(max_longitud))
                j += 1
        i += 1
    return casos

def guardar_dataset(casos, nombre_archivo):
    with open(nombre_archivo, "w") as archivo:
        archivo.write(f"{len(casos)}\n")
        for cadena1, cadena2 in casos:
            archivo.write(f"{cadena1} {cadena2}\n")
    return 0

longitud_maxima = 20  # Longitud máxima variable
total_casos = 100     # Número total de casos

dataset = generar_dataset(longitud_maxima, total_casos)
guardar_dataset(dataset, "entrada.txt")
print(f"Archivo entrada.txt generado exitosamente con cadenas de longitud variable hasta {longitud_maxima}.")