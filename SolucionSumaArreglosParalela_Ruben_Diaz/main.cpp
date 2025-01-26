#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define N 55555		// Cantidad de elementos a manejar en los arreglos
#define chunk 100	// Tamaño que tendrán los pedazos de los arreglos para que cada hilo creado se encargue de esta cantidad de elementos
#define mostrar 10	// Cantidad de datos a imprimir

void imprimeArreglo(float *d);
void checkOpenMP();

int main()
{
	// Revisar si OpenMP está disponible para utilizar en el proyecto
	checkOpenMP();
	// Inicializar la semilla para generar números aleatorios
	srand(time(0));
	// Inicializar el programa, declara los arreglos y la variable iterativa
	std::cout << "Sumando Arreglos en Paralelo con los siguientes parametros:\n";
	std::cout << "N: " << N << std::endl;
	std::cout << "chunk: " << chunk << std::endl;
	std::cout << "mostrar: " << mostrar << "\n" << std::endl;
	float a[N], b[N], c[N], c1[N];
	int i;
	// LLenado de manera aleatoria de los 2 arreglos a sumarse
	for (i = 0; i < N; i++)
	{
		a[i] = rand() % 101;
		b[i] = rand() % 101;
	}

	int pedazos = chunk;
	// timer para medir el tiempo que tarda en ejecutarse el código en paralelo
    clock_t start = clock();
	// inicio del bloque de for parelelo
	#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
	clock_t end = clock();
    //std::cout << "start: " << start << " - end " << end << std::endl;

	// timer para medir el tiempo que tarda en ejecutarse el código en secuencial
    clock_t start1 = clock();
    int j = 0;
    for (j = 0; j < N; j++)
        c1[j] = a[j] + b[j];
    clock_t end1 = clock();
    //std::cout << "start: " << start1 << " - end " << end1 << std::endl;

	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
	imprimeArreglo(a);
	std::cout << "\nImprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
	imprimeArreglo(b);
	std::cout << "\nImprimiendo los primeros " << mostrar << " valores del arreglo c : " << std::endl;
	imprimeArreglo(c);

	// Calculate execution time in seconds
	double executionTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	// Print the execution time
	std::cout << "\nTiempo de ejecucion en paralelo: " << executionTime << " segundos" << std::endl;

    // Calculo del tiempo de ejecución en segundos
    double executionTime1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    // Print the execution time
    std::cout << "Tiempo de ejecucion en secuencial: " << executionTime1 << " segundos" << std::endl;
}

// Código de impresión de los arreglos para validar al final
void imprimeArreglo(float* d) {
	for (int x = 0; x < mostrar; x++) {
		std::cout << d[x];
		if (x<mostrar-1)
		{
			std::cout << " - \t";
		}
	}
	std::cout << std::endl;
}
// Código de verificación de que la librería OpenMP está disponible para su uso
void checkOpenMP() {

	# ifdef _OPENMP
		std::cout << "OMP disponible y funcionando\n" << std::endl;
	# endif
}
