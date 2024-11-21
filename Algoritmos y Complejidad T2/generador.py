import random
import string
import math

def generar_caso_vacio():
    return "*", "*"

def generar_caso_s1_vacio(longitud):
    cadena2 = ''.join(random.choices(string.ascii_lowercase, k=longitud))
    return "*", cadena2

def generar_caso_s2_vacio(longitud):
    cadena1 = ''.join(random.choices(string.ascii_lowercase, k=longitud))
    return cadena1, "*"

def generar_caso_repetidos(max_longitud, cantidad):
    longitud = max_longitud
    S1 = ""
    S2 = ""

    i = 0
    while i < cantidad:
        if i%2 == 0:
            char = random.choice(string.ascii_lowercase)
            S1 += char * math.ceil(longitud/cantidad)
            char = random.choice(string.ascii_lowercase)
            S2 += char * math.ceil(longitud/cantidad)
        else:
            char = random.choice(string.ascii_lowercase)
            S1 += char * math.ceil(longitud/cantidad)
            S2 += char * math.ceil(longitud/cantidad)
        i += 1

    if len(S1) != max_longitud:
        S1 = S1[:max_longitud]
    if len(S2) != max_longitud:
        S2 = S2[:max_longitud]

    return [S1, S2]

def generar_caso_transposiciones(max_longitud):
    cadena = ''.join(random.choices(string.ascii_lowercase, k=max_longitud))

    i = random.randint(0, max_longitud - 2)
    j_actual = (i + 2)%max_longitud
    j_siguiente = (i + 3)%max_longitud
    k_actual = (j_actual + 2)%max_longitud
    k_siguiente = (j_actual + 3)%max_longitud

    transpuesta = list(cadena)
    transpuesta[i], transpuesta[i + 1] = transpuesta[i + 1], transpuesta[i]
    transpuesta[j_actual], transpuesta[j_siguiente] = transpuesta[j_siguiente], transpuesta[j_actual]
    transpuesta[k_actual], transpuesta[k_siguiente] = transpuesta[k_siguiente], transpuesta[k_actual]
    return [cadena, ''.join(transpuesta)]

def generar_caso_aleatorio(max_longitud):
    cadena1 = ''.join(random.choices(string.ascii_lowercase, k=max_longitud))
    cadena2 = ''.join(random.choices(string.ascii_lowercase, k=max_longitud))
    return [cadena1, cadena2]

def generar_dataset(max_longitud, total_casos, cantidad):
    casos = []

    j = 0
    while j < total_casos:
        casos.append(generar_caso_vacio())
        j += 1

    i = 6
    while i <= max_longitud:
        j = 0
        while j < total_casos:
            casos.append(generar_caso_s1_vacio(i))
            j += 1
        i += 1

    i = 6
    while i <= max_longitud:
        j = 0
        while j < total_casos:
            casos.append(generar_caso_s2_vacio(i))
            j += 1
        i += 1

    i = 6
    while i <= max_longitud:
        j = 0
        while j < total_casos:
            casos.append(generar_caso_repetidos(i, cantidad))
            j += 1
        i += 1

    i = 6
    while i <= max_longitud:
        j = 0
        while j < total_casos:
            casos.append(generar_caso_transposiciones(i))
            j += 1
        i += 1

    i = 6
    while i <= max_longitud:
        j = 0
        while j < total_casos:
            casos.append(generar_caso_aleatorio(i))
            j += 1
        i += 1

    return casos

def guardar_dataset(casos, nombre_archivo):
    archivo = open(nombre_archivo, "w")
    archivo.write(f"{len(casos)}\n")
    for cadena1, cadena2 in casos:
        archivo.write(f"{cadena1} {cadena2}\n")
    return 0

longitud_maxima = 18  # Longitud máxima variable
total_casos = 50     # Número total de casos
cantidad_repetidos = 5 #Número de caracteres que pueden estar repetidos

dataset = generar_dataset(longitud_maxima, total_casos, cantidad_repetidos)
guardar_dataset(dataset, "entrada.txt")
print(f"Archivo entrada.txt generado exitosamente con cadenas de longitud variable hasta {longitud_maxima}.")