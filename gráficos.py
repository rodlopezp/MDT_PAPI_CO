#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Created on Tue Nov 03 19:57:21 2015

@author: Rodrigo
"""

import numbers
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.lines import Line2D

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
sizes = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
sizesCO = [16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192]
leafSizes = [1, 2, 4, 8, 16]

###Por ahora, estoy copiando los datos a mano.
avgTimeSpent = [7.88436e-05, 8.9211e-05, 0.000102676, 0.000176059, 0.000744781, 0.00332708, 0.0232231, 0.0989751, 0.407999, 1.17362]
avgL1CacheMisses = [102, 214, 717, 17478, 69870, 279689, 1171448, 5460881, 26329426, 138829049]
avgL2CacheMisses = [52, 94, 248, 446, 46359, 278852, 1126486, 4565911, 19692982, 92017065]

avgTimeSpentCO = [[4.85182e-05, 6.71148e-05, 0.000132084, 0.000409365, 0.00141287, 0.00582588, 0.0219198, 0.101418, 0.424301, 1.52329],
                  [4.86374e-05, 5.65052e-05, 8.13007e-05, 0.000181913, 0.000561237, 0.00208259, 0.00875354, 0.0330107, 0.133875, 0.561498],
                  [4.673e-05, 5.10216e-05, 6.58035e-05, 0.000120163, 0.000325203, 0.00115728, 0.00451517, 0.0181251, 0.0879035, 0.29718], 
                  [4.76837e-05, 5.10216e-05, 6.19888e-05, 0.000114441, 0.000270367, 0.000905037, 0.00352764, 0.0137944, 0.0571127, 0.251437],
                  [4.43459e-05, 4.91142e-05, 5.8651e-05, 9.67979e-05, 0.00025177, 0.000841618, 0.00333452, 0.0132799, 0.0525389, 0.208555]]
avgL1CacheMissesCO = [[64, 75, 88, 165, 235, 2318, 1786, 40352, 234080, 509836],
                      [71, 82, 106, 150, 232, 420, 4796, 7000, 41850, 219836],
                      [66, 83, 110, 165, 252, 496, 1311, 5764, 94798, 155716], 
                      [71, 96, 139, 284, 466, 932, 3126, 11794, 61379, 405427],
                      [87, 123, 201, 350, 806, 2455, 10997, 43044, 161738, 644556]]
avgL2CacheMissesCO = [[9, 15, 18, 42, 63, 365, 370, 7259, 38643, 77475],
                      [17, 20, 27, 32, 44, 77, 761, 1181, 6540, 39140],
                      [10, 17, 22, 28, 30, 72, 206, 916, 18698, 26016], 
                      [13, 18, 25, 58, 60, 95, 264, 980, 6902, 59650],
                      [12, 15, 24, 35, 76, 154, 556, 2945, 9835, 35723]]

''' ###Parsing###
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
 '''

###Gráfico###
index = np.arange(len(sizes))
width = 0.2
data_index = np.arange(len(leafSizes))

fig, ax = plt.subplots()
fig.set_size_inches(20.0, 10.0)

#Marcadores para los puntos.
markers = []
for m in Line2D.markers:
    try:
        if len(m) == 1 and m != ' ':
            markers.append(m)
    except TypeError:
        pass

ax.clear()
fig.canvas.draw()
ax.set_xticks(sizes)
ax.set_xticklabels(sizes)
ax.set_yscale("log")
ax.grid(True)
ax.set_xscale("log")
ax.set_ylabel("Tiempo[s]")
ax.set_xlabel(u"Tamaño de la matriz")
ax.set_title(u"Transposición de matrices (tiempo de ejecución)")

curves = []
curves.append(ax.plot(sizes, avgTimeSpent, linestyle = '--', color = 'k', label = 'Naive', marker = 'x'))
for i in data_index:
    curves.append(ax.plot(sizes, avgTimeSpentCO[i], linestyle = '--', marker = markers[i], color = 'k', 
                  label = ("Cache-Oblivious (submatriz " + str(leafSizes[i]) + "x" + str(leafSizes[i])+ ")")))
ax.legend(loc = 4)
plt.savefig("resultadosTiempo.svg", bbox = 'Tight')

ax.clear()
fig.canvas.draw()
ax.set_xticks(sizes)
ax.set_xticklabels(sizes)
ax.grid(True)
ax.set_yscale("log")
ax.set_xscale("log")
ax.set_ylabel("Fallas de cache L1")
ax.set_xlabel(u"Tamaño de la matriz")
ax.set_title(u"Transposición de matrices (fallas de cache L1)")
curves = []
curves.append(ax.plot(sizes, avgL1CacheMisses, linestyle = '--', color = 'k', label = 'Naive', marker = 'x'))
for i in data_index:
    curves.append(ax.plot(sizes, avgL1CacheMissesCO[i], linestyle = '--', marker = markers[i], color = 'k', 
                  label = ("Cache-Oblivious (submatriz " + str(leafSizes[i]) + "x" + str(leafSizes[i])+ ")")))
ax.legend(loc = 4)
plt.savefig("resultadosL1.svg", bbox = 'Tight')

ax.clear()
fig.canvas.draw()
ax.set_xticks(sizes)
ax.set_xticklabels(sizes)
ax.set_yscale("log")
ax.set_xscale("log")
ax.grid(True)
ax.set_ylabel("Fallas de cache L2")
ax.set_xlabel(u"Tamaño de la matriz")
ax.set_title(u"Transposición de matrices (fallas de cache L2)")
curves = []
curves.append(ax.plot(sizes, avgL2CacheMisses, linestyle = '--', color = 'k', label = 'Naive', marker = 'x'))
for i in data_index:
    curves.append(ax.plot(sizes, avgL2CacheMissesCO[i], linestyle = '--', marker = markers[i], color = 'k', 
                  label = ("Cache-Oblivious (submatriz " + str(leafSizes[i]) + "x" + str(leafSizes[i])+ ")")))
ax.legend(loc = 4)
plt.savefig("resultadosL2.svg", bbox = 'Tight')
