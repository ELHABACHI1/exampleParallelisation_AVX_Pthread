

#ifndef PROJETVERSION2_PROJET_H
#define PROJETVERSION2_PROJET_H
#include <immintrin.h>  // Inclure la bibliothèque AVX
#include "math.h"
#include <pthread.h>

// Mutex pour gérer la somme
extern pthread_mutex_t mutex;

// déclaration des fonctions
double dist(float *U, float *V, int n); // scalaire

double vect_dist(float *U, float *V, int n);  // vecto normale

double vect_dist_gen(float *U, float *V, int n);  // vecto_générale

void *threadRoutine(void *threadData);     // la routine du thread

double distPar(float *U, float *V, int n, int nb_threads, int mode);    // la fonction générale donnant le choix du mode

// ====================================== déclaration de la structure =============================
struct ThreadData {
    float *U;
    float *V;
    int n;
    int mode;
    double result;
};





#endif //PROJETVERSION2_PROJET_H