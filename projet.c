//
// Created by salah.elhabachi on 29/10/2023.
//

#include <immintrin.h>
#include "math.h"
#include "projet.h"
#include <pthread.h>
#define NUM_THREADS 2
double partialResult[NUM_THREADS] ;
float U[8];
float V[8];
int n=8;



/*================ Version scalaire { sans pthread ni AVX } ================*/
double dist(float *U, float *V, int n) {
    double distance = 0.;
    for(int i = 0; i < n; i++) {
        distance += sqrt(pow(U[i], 2) + pow(V[i], 2));
    }
    return distance;
}

/*================ Version utilisant les threads ( scalaire ) ================*/
/*
void *routine(void *threadID) {
    long tid;
    int startLoop, endLoop;
    tid = *(long*)threadID;
    startLoop = tid * (n / NUM_THREADS);
    endLoop = (tid == NUM_THREADS - 1) ? n : (tid + 1) * (n / NUM_THREADS);  // Correction de la division des données
    printf("%d",startLoop);
    // calcul du résultat local pour chaque thread
    partialResult[tid] = dist(U + startLoop, V + startLoop, endLoop - startLoop); // appel de la fonctin du calcul de la distnace par la forume demandée
    pthread_exit(NULL);
}
*/
/*================ Version  AVX en supposant N%8=0 et données alignées ================*/
double vect_dist(float *U, float *V, int n) {
    double result = 0.0;
    int numVectors = n / 8;  // Chaque vecteur AVX traite 8 éléments

    for (int i = 0; i < numVectors; i++) {
        // Charger 8 éléments de U et V dans des registres AVX
        __m256 u = _mm256_load_ps(U + (i * 8));
        __m256 v = _mm256_load_ps(V + (i * 8));

        // Élever au carré les éléments de U et V
        __m256 u_squared = _mm256_mul_ps(u, u);
        __m256 v_squared = _mm256_mul_ps(v, v);

        // Ajouter les éléments de U et V élevés au carré
        __m256 sum_squared = _mm256_add_ps(u_squared, v_squared);

        // Calculer la racine carrée des sommes
        __m256 sqrt_sum = _mm256_sqrt_ps(sum_squared);

        // Somme des valeurs de sqrt_sum
        float sum_values[8];

        _mm256_storeu_ps(sum_values, sqrt_sum);

        for (int j = 0; j < 8; j++) {
            result += sum_values[j];
        }
    }

    return result;
}
/*================ Version AVX prenant en considération N%8!=0 & alignement  ================*/
double vect_dist_gen(float *U, float *V, int n) {
    double result = 0.0;
    int numVectors = n / 8;  // Nombre de vecteurs AVX complets
    int r =n % 8 ;  // Nombre d'éléments restants

    for (int i = 0; i < numVectors; i++) {
        // Charger 8 éléments de U et V dans des registres AVX
        __m256 u = _mm256_loadu_ps(U + (i * 8));
        __m256 v = _mm256_loadu_ps(V + (i * 8));

        // Élever au carré les éléments de U et V
        __m256 u_squared = _mm256_mul_ps(u, u);
        __m256 v_squared = _mm256_mul_ps(v, v);

        // Ajouter les éléments de U et V élevés au carré
        __m256 sum_squared = _mm256_add_ps(u_squared, v_squared);

        // Calculer la racine carrée des sommes
        __m256 sqrt_sum = _mm256_sqrt_ps(sum_squared);

        // Somme des valeurs de sqrt_sum
        float sum_values[8];
        _mm256_storeu_ps(sum_values, sqrt_sum);

        for (int j = 0; j < 8; j++) {
            result += sum_values[j];
        }
    }
    // Traitement scalaire des éléments restants
    if (r!=0) {
        for (int i = numVectors * 8; i < n; i++) {
            float u = U[i];
            float v = V[i];
            result += sqrt(u * u + v * v);
        }
    }
    return result;
}
/*================ Version distPar MT donnant le choix du mode {0:scalaire , 1:AVX} ================*/

// Fonction exécutée par chaque thread
void *threadRoutine(void *threadData) {
    struct ThreadData *data = (struct ThreadData *)threadData;
    if (data->mode == 0) {
        // Calcul scalaire
        data->result = distScalar(data->U, data->V, data->n);
    } else {
        // Calcul vectoriel
        data->result = distVector(data->U, data->V, data->n);
    }
    pthread_exit(NULL);
}

//