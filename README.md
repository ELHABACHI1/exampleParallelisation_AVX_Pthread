# Projet : Parallélisaton avec Pthreads et AVX  (langage C)

Dans ce projet j'ai essayé de traité le calcul de la distance euclidienne entre deux vectuers U et V par trois méthodes : la méthode scalaire classique, la méthode de parallélisation par Pthreads et par AVX ( vectorisation), en utilisant le langage C.
 On utilise la formule : $$\sum_{i=start}^{end} \sqrt{U[i]^2 + V[i]^2}$$

 - J'ai travaillé avec les intrinsics de AVX en supposant que les données ne sont pas forcement alignées ( sur 8 bits ).
 - J'ai travaillé aussi avec Pthreads en choisissant un nombre de threads qui n'est pas forcément un diviseur de la taille des vecteurs.
 - J'ai aussi ajouté une fonction de calcul du temps d


## Cemment compiler & Exécuter le fichier ? 

* Si vous êtes sur MAC / Windows vous pouvez utiliser l'IDE Clion : Il vous facilite la vie !
* Si vous voulez pas l'utilier, pensez à installer CMAKE !
* Si vous êtes ami de la ligne de commande voilà les étapes à suivre :



