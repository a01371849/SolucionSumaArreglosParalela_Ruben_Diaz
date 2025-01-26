#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define N 55555
#define chunk 100
#define mostrar 10

void imprimeArreglo(float *d);
void checkOpenMP();

int main()
{
	// Revisar si OpenMP está disponible para utilizar en el proyecto
	checkOpenMP();
	// Inicializar la semilla para generar números aleatorios
	srand(time(0));

	std::cout << "Sumando Arreglos en Paralelo!\n\n";
	float a[N], b[N], c[N], c1[N];
	int i;

	for (i = 0; i < N; i++)
	{
		a[i] = rand() % 101;
		b[i] = rand() % 101;
	}

	int pedazos = chunk;

    clock_t start = clock();
	#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
	
	clock_t end = clock();
    std::cout << "start: " << start << " - end " << end << std::endl;

    clock_t start1 = clock();
    int j = 0;
    for (j = 0; j < N; j++)
        c1[j] = a[j] + b[j];
    clock_t end1 = clock();
    std::cout << "start: " << start1 << " - end " << end1 << std::endl;

	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
	imprimeArreglo(a);
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
	imprimeArreglo(b);
	std::cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
	imprimeArreglo(c);

	// Calculate execution time in seconds
	double executionTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
	// Print the execution time
	std::cout << "Time taken to execute in parallel: " << executionTime << " seconds" << std::endl;

    // Calculate execution time in seconds
    double executionTime1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC;
    // Print the execution time
    std::cout << "Time taken to execute without parallel: " << executionTime1 << " seconds" << std::endl;
}

void imprimeArreglo(float* d) {
	for (int x = 0; x < mostrar; x++)
		std::cout << d[x] << " - ";
		std::cout << std::endl;
}

void checkOpenMP() {

	# ifdef _OPENMP
		std::cout << "OMP disponible y funcionando\n" << std::endl;
	# endif
}


/*
#include "pch.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define N 1000000
#define chunk 10
#define mostrar 10

void imprimeArreglo(const vector<float>& d);
void checkOpenMP();

int main() {
    // Check OpenMP availability
    checkOpenMP();

    // Seed the random number generator
    srand(static_cast<unsigned>(time(NULL)));

    cout << "Sumando Arreglos en Paralelo!\n\n";

    vector<float> a(N), b(N), c(N);
    int pedazos = chunk;
    int i;


    // Fill arrays with random numbers
    for (int i = 0; i < N; ++i) {
        a[i] = rand() % 101;
        b[i] = rand() % 101;
    }

    // Start timing
    clock_t start = clock();

    // Parallel addition
#pragma omp parallel for shared(a, b, c, pedazos) private(i) schedule(static, pedazos)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // End timing
    clock_t end = clock();

    int j = 0;

    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }


    // Print arrays
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo a: " << endl;
    imprimeArreglo(a);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo b: " << endl;
    imprimeArreglo(b);
    cout << "Imprimiendo los primeros " << mostrar << " valores del arreglo c: " << endl;
    imprimeArreglo(c);

    // Calculate and print execution time
    double executionTime = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    cout << "Time taken to execute: " << executionTime << " seconds" << endl;

    return 0;
}

void imprimeArreglo(const vector<float>& d) {
    for (int x = 0; x < mostrar; ++x) {
        cout << d[x] << " - ";
    }
    cout << endl;
}

void checkOpenMP() {
#ifdef _OPENMP
    cout << "OMP disponible y funcionando\n" << endl;
#else
    cout << "OMP no está disponible. Por favor, habilite OpenMP.\n" << endl;
#endif
}
*/