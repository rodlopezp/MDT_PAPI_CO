#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 03 19:57:21 2015

@author: Rodrigo
"""

import numbers
import numpy as np
from matplotlib import pyplot as plt

###Script para graficar a partir de archivo de texto###

###Funciones###
"""Etiqueta las barras del gráfico."""
def autolabel(rects):
    # attach some text labels
    for rect in rects:
        height = rect.get_height()
        if height < 1e-6:
            ax.text(rect.get_x()+rect.get_width()/2., height, u'<1 µs',
                    ha='center', va='bottom', rotation = "vertical")
        elif isinstance(height, float):
            ax.text(rect.get_x()+rect.get_width()/2, 1.05*height, 
                    '%.2e'%height, ha='center', va='bottom')
        elif isinstance(height, numbers.Real):
            ax.text(rect.get_x()+rect.get_width()/2, 1.05*height, 
                    height, ha='center', va='bottom')

"""Lee líneas de un archivo, y devuelve una lista con las líneas."""
def readLinesFromFile(filename):
	file = open(filename, 'r')
	readLines = file.readlines()
	file.close()
	return readLines

###Abrir archivos y guardar lineas en una lista###
naiveResults = readLinesFromFile('test_results_naive.txt')
coResults = readLinesFromFile('test_results_co.txt')

###Filtrar saltos de linea###
naiveResults = map(lambda s: s.strip(), naiveResults) #Remueve '\n' de las líneas
naiveResults = filter(None, naiveResults)  #Remueve lineas vacías

coResults = map(lambda s: s.strip(), coResults) #Remueve '\n' de todas las lines
coResults = filter(None, coResults)  #Remueve lineas vacías

###Listas para guardar resultados
sizes = []
sizesCO = []

avgTimeSpent = []
avgTimeSpentCO = []

avgL1CacheMisses = []
avgL1CacheMissesCO = []

avgL2CacheMisses = []
avgL2CacheMissesCO = []

leafSizes = []

###Parsing###
for line in naiveResults:
    if "Tamaño de matriz" in line:
        sizes.append(int(line.strip("Tamaño de matriz: ")))
    elif "Tiempo" in line:
        line = line.strip("Tiempo de ejecución promedio: ")
        avgTimeSpent.append(float(line.rstrip(" s")))
    elif "cache L1" in line:
        line = line.replace("Promedio de fallas de cache L1 totales: ", "")
        avgL1CacheMisses.append(int(line))
    elif "cache L2" in line:
        line = line.replace("Promedio de fallas de cache L2 totales: ", "")
        avgL2CacheMisses.append(int(line))

for line in coResults:
    if "Tamaño de matriz" in line:
        sizesCO.append(int(line.strip("Tamaño de matriz: ")))
    elif "submatriz" in line:
        leafSizes.append(int(line.strip("Tamaño mínimo de submatriz: ")))
    elif "Tiempo" in line:
        line = line.strip("Tiempo de ejecución promedio: ")
        avgTimeSpentCO.append(float(line.rstrip(" s")))
    elif "cache L1" in line:
        line = line.replace("Promedio de fallas de cache L1 totales: ", "")
        avgL1CacheMissesCO.append(int(line))
    elif "cache L2" in line:
        line = line.replace("Promedio de fallas de cache L2 totales: ", "")
        avgL2CacheMissesCO.append(int(line))        

###Gráfico###
index = np.arange(len(sizes))
width = 0.2

fig, ax = plt.subplots()
fig.set_size_inches(20.0, 10.0)
plt.yscale('log')

ax.set_xticks(index + 1.25 * width)
ax.set_xticklabels(sizes)

ax.set_ylabel("Tiempo[s]")
ax.set_xlabel(u"Tamaño de la matriz")
ax.set_title(u"Transposición de matrices (tiempo de ejecución)")
rects1 = ax.bar(index, avgTimeSpent, 2 * width, color = 'r', log = True)
rects2 = ax.bar(index+ 2.5 * width, avgTimeSpentCO[0:len(sizes)], 2 * width, color = 'y', log = True)
ax.legend((rects1[0], rects2[0]),("Naive", "Cache-oblivious"), loc=2)
autolabel(rects1)
autolabel(rects2)
plt.savefig("resultadosTiempo.png", bbox = 'Tight')

ax.set_ylabel("Fallas de cache L1")
ax.set_xlabel(u"Tamaño de la matriz")
ax.set_title(u"Transposición de matrices (fallas de cache L1)")
rects1 = ax.bar(index, avgL1CacheMisses, 2 * width, color = 'r', log = True)
rects2 = ax.bar(index+ 2.5 * width, avgL1CacheMissesCO[0:len(sizes)], 2 * width, color = 'y', log = True)
autolabel(rects1)
autolabel(rects2)
plt.savefig("resultadosL1.png", bbox = 'Tight')

ax.clear()
fig.canvas.draw()
ax.legend((rects1[0], rects2[0]),("Naive", "Cache-oblivious"), loc=2)
ax.set_ylabel("Fallas de cache L2")
ax.set_xlabel(u"Tamaño de la matriz")
ax.set_title(u"Transposición de matrices (fallas de cache L2)")
rects1 = ax.bar(index, avgL2CacheMisses, 2 * width, color = 'r', log = True)
rects2 = ax.bar(index+ 2.5 * width, avgL2CacheMissesCO[0:len(sizes)], 2 * width, color = 'y', log = True)
autolabel(rects1)
autolabel(rects2)
plt.savefig("resultadosL2.png", bbox = 'Tight')
