# S1 | Prog&Algo: Workshop

Workshop de ProgAlgo, IMAC2028 S1

Tous les exercices ont été réalisés sous forme de fonctions individuelles, puis la création des images a été faite dans le main, sous la forme suivante :

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

Pour alléger le code, j'ai décidé de ne pas garder l'entièreté du main, une fois les images créées. Ainsi, j'ai laissé quelques exemples (ci-dessus), ainsi que le code pour l'animation du disque (car différent des autres).

RMQ : L'aspect mathématique des exercices m'a facilité la vie !

## Exercice 1 :
![alt text](./output/green_imac.png)

## Exercice 2 :
![alt text](./output/swaped_imac.png)

## Exercice 3 :
![alt text](./output/n&b_imac.png)

## Exercice 4 :
![alt text](./output/negatif_imac.png)

## Exercice 5 :
![alt text](./output/degrade_n&b.png)

## Exercice 6 :
![alt text](./output/miroir_imac.png)

## Exercice 7 :
![alt text](./output/bruit_imac.png)

## Exercice 8 :
![alt text](./output/rotation90_imac.png)

## Exercice 9 :
![alt text](./output/rgb_split_imac.png)

## Exercice 10 :
![alt text](./output/high_lum_imac.png)
![alt text](./output/low_lum_imac.png)

## Exercice 11 :
![alt text](./output/disque.png)
![alt text](./output/cercle.png)
![alt text](./output/animation/disque_animation.gif)
![alt text](./output/rosace.png)

## Exercice 12 :
J'ai laissé une fonction différente par étape de mosaïques afin de laisser mon chemin de pensée (d'abord trouver comment réaliser la mosaïque, puis retourner une ligne puis une colonne)
![alt text](./output/mosaique_imac.png)
![alt text](./output/mosaique_miroir_imac.png)
![alt text](./output/mosaique_double_miroir_imac.png)

## Exercice 13 :
![alt text](./output/glitch.png)

## Exercice 14 :
![alt text](./output/tri_de_pixels.png)

## Exercice 15 :
![alt text](./output/fractale.png)

## Exercice 16 :
![alt text](./output/degrade_couleur.png)