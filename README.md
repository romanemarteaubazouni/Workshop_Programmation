# S1 | Prog&Algo: Workshop

**Workshop de ProgAlgo, IMAC2028 S1**

Tous les exercices ont été réalisés sous forme de fonctions individuelles, puis la création des images a été faite dans le main, sous la forme suivante :

```cpp
int main()
{
    {
        sil::Image image{"images/logo.png"}; // Lis l'image
        green(image); // Utilise la fonction pour modifier l'image
        image.save("output/green_imac.png"); // Sauvegarde l'image
    }
    {
        sil::Image image{"images/logo.png"};
        swapRedBlue(image);
        image.save("output/swaped_imac.png");
    }
}
```

Pour alléger le code, j'ai décidé de ne pas garder l'entièreté du main, une fois les images créées. Ainsi, j'ai laissé quelques exemples (ci-dessus), ainsi que le code pour l'animation du disque (car différent des autres).

*RMQ : L'aspect mathématique des exercices m'a facilité la vie (vive la prépa) et j'ai pu avancé rapidement sur les rosaces et rotations !*

# Images de référence
![image](./images/logo.png)
<img src="./images/photo.jpg" alt="image" width="300">
<img src="./images/photo_faible_contraste.jpg" alt="image" width="300">

# Exercices réalisés
## ⭐ Nuances de vert
![image](./output/green_imac.png)

## ⭐ Inversion de couleur (bleu <--> rouge)
![image](./output/swaped_imac.png)

## ⭐ Noir et blanc
![image](./output/n&b_imac.png)

## ⭐ Négatif
![image](./output/negatif_imac.png)

## ⭐ Dégradé de noir et blanc
Le pourcentage de noir varie en fonction de la coordonnée x.

![image](./output/degrade_n&b.png)

## ⭐⭐ Miroir
![image](./output/miroir_imac.png)

## ⭐⭐ Bruit aléatoire
L'aléatoire est utilisé pour la position (x, y) des pixels et pour leur couleur (aléatoire pour chaque composante).

![image](./output/bruit_imac.png)

## ⭐⭐ Rotation 90°
Pour chaque pixel, on remplace ses coordonnées par ses nouvelles :
```cpp
x' = image.height() - 1 - y
y' = x
```
![image](./output/rotation90_imac.png)

## ⭐⭐ RGB Split
<u>Utilisation de l'indice :</u> pour chaque pixel, on prend un peu du rouge et du vert des pixels voisins.
![image](./output/rgb_split_imac.png)

## ⭐⭐ Différentes luminosités
<img src="./output/high_lum_imac.png" alt="image" width="300">
<img src="./output/low_lum_imac.png" alt="image" width="300">

## ⭐⭐(⭐) Disque, cercle, rosace
<img src="./output/disque.png" alt="image" width="300">
<img src="./output/cercle.png" alt="image" width="300">

Pour l'animation, une boucle a été réalisée dans le main pour générer les images successives. Pour faciliter cette animation, des paramètres ont été ajoutés dans la fonction `disk` (et circle d'ailleurs pour faciliter la rosace).

<img src="./output/animation/disque_animation.gif" alt="gif" width="300">
<img src="./output/rosace.png" alt="image" width="300">

## ⭐⭐ (⭐⭐⭐⭐) Mosaïques
J'ai laissé une fonction différente par étape de mosaïques afin de laisser mon chemin de pensée (d'abord trouver comment réaliser la mosaïque, puis retourner une image sur 2 puis une ligne sur 2)

![image](./output/mosaique_imac.png)
![image](./output/mosaique_miroir_imac.png)
![image](./output/mosaique_double_miroir_imac.png)

## ⭐⭐⭐ Glitch
![image](./output/glitch.png)

## ⭐⭐⭐ Tri de pixels
Le tri a été fait à l'aide du code Processing présenté dans la vidéo YouTube. On génère aléatoire la position et la taille d'une ligne de pixels, puis on la tri par luminosité de pixels.

![image](./output/tri_de_pixels.png)

## ⭐⭐⭐(⭐) Fractale
Cette fractale avait été réalisée, de mon côté, dans le workshop d'Anthony. J'ai donc repris mon code Processing et je l'ai adapté.

<img src="./output/fractale.png" alt="image" width="300">

## ⭐⭐⭐(⭐) Dégradé de couleur
![image](./output/degrade_couleur.png)
![image](./output/degrade_couleur_ameliore.png)

## ⭐⭐⭐(⭐) Tramage
<img src="./output/tramage/tramage_basic.png" alt="image" width="300">
<img src="./output/tramage/tramage_random_noise.png" alt="image" width="300">

___

<u>*Ordered dithering* avec une matrice de Bayer 4x4 :</u>

<u>Principe du code :</u> au lieu de se limiter à tester la luminosité d'un pixel par rapport à 0.5, on lui ajoute un facteur dépendant de sa position et de la matrice de Bayer, puis on compare cette luminosité par rapport à 0.5 (principe de base).
L'algorithme codé est celui du site internet (C), traduit en C++.
```c
for (int sy = 0; sy < viewport.height; sy++) {
        float orig_color = get_screen_gradient(sy);
        for (int sx = 0; sx < viewport.width; sx++) {
            int color_result = BLACK;
            float bayer_value = bayer_matrix_4x4[sy % bayer_n][sx % bayer_n];
            float output_color = orig_color + (bayer_r * bayer_value);
            // Color screen blue to white
            if (output_color < (NUM_VALUES / 2)) {
                color_result = WHITE;
            }
            *PIXEL_PTR((&screen), sx, sy, 1) = color_result;
        }
    }
```

<img src="./output/tramage/ordered_tramage.png" alt="image" width="300">

## ⭐⭐⭐(⭐) Normalisation d'histogramme
Au début, j'avais la logique suivante :
```cpp
void normalisation(sil::Image& image)
{
    ...
    // Pour chaque pixel, on adapte la luminosité en fonction des extrêmes
    for (glm::vec3& pix : image.pixels())
    {
        float b = (pix.r + pix.g + pix.b) / 3.f; // Brightness
        float newLum = (b - recordDark)/(recordLight - recordDark);

        pix = glm::vec3(newLum);
    }
}
```
Je normalisais donc la luminorisité de toutes les composantes en même temps (et non pas chaque composante individuellement) ce qui me donnait un rendu en gris. Après plusieurs essais, j'ai donc séparé les composantes.

<img src="./output/normalisation_de_histogramme.png" alt="image" width="300">

## ⭐⭐⭐⭐ Vortex
![image](./output/vortex.png)

## ⭐⭐⭐⭐ Convolution
<u>Principe de l'algo général (vidéo) :</u>
Pour chaque pixel :
- on centre le kernel sur le pixel
- on additionne les couleurs voisines pondérées par la valeur du kernel sur ce pixel
- on applique le résultat au pixel

Le plus compliqué était de trouver les formules de `pixelX` et `pixelY` car il fallait parcourir un vecteur de vecteur donc trouver les indices a été long.

![image](./output/convolution/convolution_emboss.png)
![image](./output/convolution/convolution_outline.png)
![image](./output/convolution/convolution_sharpen.png)

#### Blur naïf
![image](./output/convolution/convolution_blur_naif.png)
#### Blur séparé
Le principe est de passer deux kernels 1D l'un après l'autre, un kernel horizontal puis un kernel vertical.

![image](./output/convolution/convolution_blur_1D.png)

J'ai ainsi créé deux fonctions qui utilisent les kernels 1D, horizontalement puis verticalement.

___

Le principe de la différence de gaussienne utilisé est celui de la vidéo YouTube (on fait une différence entre 2 flous, puis on fonce les contours).

<img src="./output/convolution/difference_de_gaussienne.png" alt="image" width="300">

## ⭐⭐⭐⭐⭐ K-means
<u>Principe du K-means, d'après la vidéo :</u>
On choisit k couleurs de départ au hasard.
Chaque pixel est assigné à la couleur la plus proche (groupes provisoires).
On remplace chaque couleur initiale par la moyenne réelle des pixels dans son groupe.
On répète jusqu’à ce que les groupes ne bougent plus.
Ainsi, pour chaque pixel :
- mesurer la distance (souvent euclidienne) entre sa couleur et chaque couleur centrale ;
- remplacer la couleur du pixel par celle du centre le plus proche.
Un fois les groupes bien fixes, on remplace la couleur de chaque pixel par sa nouvelle couleur.

Le plus long à trouver a été la condition booléenne `changed`. Aussi, il a été difficile de ne pas se perdre dans toutes les boucles/variables et d'être au clair sur le principe du code.

<img src="./output/k_means/k_means_2.png" alt="image" width="300">
<img src="./output/k_means/k_means_3.png" alt="image" width="300">
<img src="./output/k_means/k_means_16.png" alt="image" width="300">

Maintenant, peut-être que ce code pourrait être amélioré et optimisé.

## ⭐⭐⭐⭐⭐ Kuwahara
Pour chaque pixel, on calcule les couleurs moyennes de chaque zone (grâce à la fonction `moyInSquare`) de la grille voisine du pixel puis on calcule la variance de cette zone (grâce à la fonction `varInSquare`). On affecte au pixel la couleur de la zone ayant la variance la plus faible.

(Problème d'initialisation de variables : 1er fail)

<img src="./output/kuwahara_fail.png" alt="image" width="300">

___

**Résultat final**

<img src="./output/kuwahara.png" alt="image" width="300">

# Ce que j'en retient :
- TOUJOURS INITIALISER SES VARIABLES
Ici surtout, on travaille sur des couleurs, donc le résultat d'un code où l'on n'a pas initialisé toutes les variables peut rendre une image totalement aléatoire.
(cf [Kuwahara](#-kuwahara))
<br>
- Créer des fonctions annexes, hors du code principal, c'est quand même bien pratique, et beaucoup plus lisible !
(cf [Kuwahara](#-kuwahara) et [K-Means](#-k-means))
<br>
- Les fonctions `std::max() et std::min()` sont pratiques pour gérer les problèmes de bords.
(cf [Kuwahara](#-kuwahara) et [RGB Split](#-rgb-split))
<br>
- Il faut souvent faire une copie de l'image pour ne pas directement modifier notre image.
(beaucoup d'exemples ici, comme le [Vortex](#-vortex))