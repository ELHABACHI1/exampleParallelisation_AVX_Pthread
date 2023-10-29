#include <stdio.h>
#include "projet.h"
#define NUM_THREADS 4





int main() {
    /*===================== Génération des vecteurs ===========================*/
    int N = 8;                                                                  /**/
    int MIN = 0; // Valeur minimale (0)                                         /**/
    int MAX = 100; // Valeur maximale (100)                                     /**/
    /**/
    srand(time(NULL));
                                                                                 /**/
    float U[N];                                                                 /**/
    float V[N];
    // les vecteurs avec des valeurs aléatoires entre 0 et 100
    for (int i = 0; i < N; i++) {
        U[i] = (float)rand() / RAND_MAX * (MAX - MIN) + MIN;
        V[i] = (float)rand() / RAND_MAX * (MAX - MIN) + MIN;
    }                                                                            /**/
                                                                                 /**/
/*===============================================================================*/
/*================ Version ( scalaire ) =========================================*/

    double result = dist(U, V, N);
    printf("\n1- Version scalaire {sans avx & sans threads} :    ");
    printf("Distance: %.2f \n", result);

/*==========================================================================*/
/*================ Version utilisant les threads ( scalaire ) ================*/
/*
    pthread_t THREADS[NUM_THREADS] = {0};
    pthread_t threadsID[NUM_THREADS] = {0};
    double globalResult = 0;
    double partialResult[NUM_THREADS] = {0};

    // Création des threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadsID[i] = i;
        if (pthread_create(&THREADS[i], NULL, routine, &threadsID[i]) != 0) {
            // ERROR;
            perror("Thread creation failed");
            return 1;
        }
    }

    // appel des joins :
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(THREADS[i], NULL)!=0) {
            // ERROR :
            perror("Thread Join Failed\n");
            return 1;
        }
    }

    // Calcul du résultat global :
    for (int i = 0; i < NUM_THREADS; i++) {
        globalResult += partialResult[i];
    }

    printf("\n2- Version Pthreads { %d Threads }             :    ",NUM_THREADS);
    printf("Distance: %.2f \n", globalResult);
*/
    /*==========================================================================*/
    /*========================== Version  AVX } ========================*/
    double resultat = vect_dist(U, V, N);
    printf("\n3- Version AVX ne tenant pas align & N%8         :    ");
    printf("Distance: %.2f \n", resultat);

    /*==========================================================================*/
    /*========================== Version  AVX Générale ========================*/
    double res = vect_dist_gen(U, V, N);
    printf("\n4- Version AVX  tenant pas align & N%8 (generale)      :    ");
    printf("Distance: %.2f \n", res);

    /*==========================================================================*/
    /*========================== Version  (AVX & Scalaire)+Multithreads ========================*/


    /*==========================================================================*/

    return 0;
}