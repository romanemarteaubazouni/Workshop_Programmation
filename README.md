# S1 | Prog&Algo: Workshop

Workshop de ProgAlgo, IMAC2028 S1

Tous les exercices ont été réalisés sous forme de fonctions individuelles, puis la création des images a été faite dans le main, sous la forme suivante :

```
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

RMQ : L'aspect mathématique des exercices m'a facilité la vie (vive la prépa) et j'ai pu avancé rapidement sur les rosaces et rotations !

# Images de référence
![alt text](./images/logo.png)
![alt text](./images/photo.jpg)
![alt text](./images/photo_faible_contraste.jpg)

# Exercices réalisés
## Nuances de vert
![alt text](./output/green_imac.png)

## Inversion de couleur (bleu <--> rouge)
![alt text](./output/swaped_imac.png)

## Noir et blanc
![alt text](./output/n&b_imac.png)

## Négatif
![alt text](./output/negatif_imac.png)

## Dégradé de noir et blanc
Le pourcentage de noir varie en fonction de la coordonnée x.

![alt text](./output/degrade_n&b.png)

## Mirroir
![alt text](./output/miroir_imac.png)

## Bruit aléatoire
L'aléatoire est utilisé pour la position (x, y) des pixels et pour leur couleur (aléatoire pour chaque composante).

![alt text](./output/bruit_imac.png)

## Rotation 90°
Pour chaque pixel, on remplace ses coordonnées par ses nouvelles :
```
x' = image.height() - 1 - y
y' = x
```
![alt text](./output/rotation90_imac.png)

## RGB Split
Utilisation de l'indice : pour chaque pixel, on prend un peu du rouge et du vert des pixels voisins.
![alt text](./output/rgb_split_imac.png)

## Différentes luminosités
![alt text](./output/high_lum_imac.png)
![alt text](./output/low_lum_imac.png)

## Disque, cercle, rosace
![alt text](./output/disque.png)
![alt text](./output/cercle.png)

Pour l'animation, une boucle a été réalisée dans le main pour générer les images successives. Pour faciliter cette animation, des paramètres ont été ajoutés dans la fonction disk (et circle d'ailleurs pour faciliter la rosace).

![alt text](./output/animation/disque_animation.gif)
![alt text](./output/rosace.png)

## Mosaïques
J'ai laissé une fonction différente par étape de mosaïques afin de laisser mon chemin de pensée (d'abord trouver comment réaliser la mosaïque, puis retourner une image sur 2 puis une ligne sur 2)

![alt text](./output/mosaique_imac.png)
![alt text](./output/mosaique_miroir_imac.png)
![alt text](./output/mosaique_double_miroir_imac.png)

## Glitch
![alt text](./output/glitch.png)

## Tri de pixels
Le tri a été fait à l'aide du code Processing présenté dans la vidéo YouTube. On génère aléatoire la position et la taille d'une ligne de pixels, puis on la tri par luminosité de pixels.

![alt text](./output/tri_de_pixels.png)

## Fractale
Cette fractale avait été réalisée, de mon côté, dans le workshop d'Anthony. J'ai donc repris mon code Processing et je l'ai adapté.

![alt text](./output/fractale.png)

## Dégradé de couleur
![alt text](./output/degrade_couleur.png)
![alt text](./output/degrade_couleur_ameliore.png)

## Tramage
![alt text](./output/tramage/tramage_basic.png)
![alt text](./output/tramage/tramage_random_noise.png)

Ordered dithering avec matrice de Bayer 4x4 :
Principe du code : au lieu de se limiter à tester la luminosité d'un pixel par rapport à 0.5, on lui ajoute un facteur dépendant de sa position et de la matrice de Bayer, puis on compare cette luminosité par rapport à 0.5 (principe de base).

![alt text](./output/tramage/ordered_tramage.png)

## Normalisation d'histogramme
Au début, j'avais la logique suivante :
```
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

![alt text](./output/normalisation_de_histogramme.png)

## Vortex
![alt text](./output/vortex.png)

## Convolution
Principe de l'algo général (vidéo) :
Pour chaque pixel :
- on centre le kernel sur le pixel
- on additionne les couleurs voisines pondérées par la valeur du kernel sur ce pixel
- on applique le résultat au pixel

Le plus compliqué était de trouver les formules de pixelX et pixelY car il fallait parcourir un vecteur de vecteur donc trouver les indices a été long.

![alt text](./output/convolution/convolution_emboss.png)
![alt text](./output/convolution/convolution_outline.png)
![alt text](./output/convolution/convolution_sharpen.png)

### Blur naïf
![alt text](./output/convolution/convolution_blur_naif.png)
### Blur séparé
Le principe est de passer deux kernels 1D l'un après l'autre, un kernel horizontal puis un kernel vertical.

![alt text](./output/convolution/convolution_blur_1D.png)

J'ai ainsi créé deux fonctions qui utilisent les kernels 1D, horizontalement puis verticalement.