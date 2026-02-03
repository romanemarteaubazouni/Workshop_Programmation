#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <cmath>
#include <complex>

void green(sil::Image& image) // Ne gardez que le vert
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

void swapRedBlue(sil::Image& image) // Echangez les canaux (rouge <--> bleu)
{
    for (glm::vec3& color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}

void blackAndWhite(sil::Image& image) // Image en N&B
{
    for (glm::vec3& color : image.pixels())
    {
        float grey = 0.3f * color.r + 0.59f * color.g + 0.11f * color.b;
        color = glm::vec3(grey);
    }
}

void negative(sil::Image& image) // Image en négatif
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
}

void fading(sil::Image& image) // Dégradé N&B
{
    for (int x {0}; x < image.width(); ++x)
    {
        for (int y {0}; y < image.height(); ++y)
        {
            float greyValue = static_cast<float>(x)/(image.width() - 1);
            image.pixel(x, y) = glm::vec3(greyValue);
        }
    }
}

void mirror(sil::Image &image) // Effet mirroir
{
    sil::Image copy = image; // On créé une copie pour ne pas écraser les nouveaux pixels
    for (int x {0}; x < image.width(); ++x)
    {
        for (int y {0}; y < image.height(); ++y)
        {
            int newX = image.width() - 1 - x;
            image.pixel(x, y) = copy.pixel(newX, y);
        }
    } 
}

void noise(sil::Image &image) // Effet bruité
{
    int numberOfPixels = random_int(0, image.width()*image.height()); // Nombre de pixels bruités
    
    for (int i {0}; i < numberOfPixels; ++i)
    {
        // On sélectionne nos pixels
        int x = random_int(0, image.width());
        int y = random_int(0, image.height());
        // Couleurs aléatoires
        float c1 = random_float(0.f, 1.f);
        float c2 = random_float(0.f, 1.f);
        float c3 = random_float(0.f, 1.f);

        image.pixel(x, y) = glm::vec3(c1, c2, c3);
    }
}

void rotation(sil::Image &image) // Rotation de 90°
{
    sil::Image new_image{image.height(), image.width()};

    for (int x {0}; x < image.width(); ++x)
    {
        for (int y {0}; y < image.height(); ++y)
        {
            int newX = image.height() - 1 - y;
            int newY = x;
            new_image.pixel(newX, newY) = image.pixel(x, y);
        }
    }
    image = new_image;
}

void rgb_split(sil::Image &image)
{
    sil::Image copie = image;

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            // Pour gérer les bords
            int x_left = std::max(x - 10, 0); // Si on arrive au bord gauche, x = 0
            int x_right = std::min(x + 10, image.width() - 1); // Si on arrive au bord droit, x = width - 1

            float c1 = copie.pixel(x_left, y).r; // Rouge d'un pixel à sa gauche
            float c2 = copie.pixel(x, y).g;
            float c3 = copie.pixel(x_right, y).b; // Bleu d'un pixel à sa droite

            image.pixel(x, y) = glm::vec3(c1, c2, c3);
        }
    }
}

void brightness(sil::Image &image) // Modifier la luminosité (ici, elle s'assombrit car exponent < 1)
{
    float exponent = 0.75;
    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            image.pixel(x, y) *= exponent;
        }
    }
}

void disk(sil::Image &image, float centerX, float centerY) // Mettre les coordonnées du centre en paramètres est pratique pour la suite (animation)
{
    int r = 150;

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            // Formule du disque
            float dx = x - centerX; // Distance au centre en x
            float dy = y - centerY; // Distance au centre en y

            if (dx*dx + dy*dy <= r*r)
            {
                image.pixel(x, y) = {1.f, 1.f, 1.f};
            }
        }
    }
}

void circle(sil::Image &image, float centerX, float centerY)
{
    // Rayon
    int r = 120;
    int thickness = 5;

    for (int x = 0; x < image.width(); ++x)
    {
        for (int y = 0; y < image.height(); ++y)
        {
            // Formule du disque
            float dx = x - centerX; // Distance au centre en x
            float dy = y - centerY; // Distance au centre en y

            if ((dx*dx + dy*dy <= r*r) && (dx*dx + dy*dy > (r-thickness)*(r-thickness)))
            {
                image.pixel(x, y) = {1.f, 1.f, 1.f};
            }
        }
    }
}

void rosace(sil::Image &image)
{
    circle(image, 250.f, 250.f); // Cercle central

    int r = 120; // Rayon du cercle central

    for (float teta{0}; teta <= 2*M_PI; teta += M_PI/3) // Les 6 cercles
    {
        circle(image, 250.f + r * cos(teta), 250.f + r * sin(teta)); // Passage cartésiennes --> polaires
    }
}
/*********************** MOSAIQUES (en plusieurs étapes) *************************/
void mosaique(sil::Image &image)
{
    sil::Image mosaique {image.width(), image.height()};

    // On parcourt l'image d'arrivée
    for (int x {0}; x < image.width(); ++x)
    {
        for (int y {0}; y < image.height(); ++y)
        {
            mosaique.pixel(x, y) = image.pixel((x * 5) % image.width(), (y * 5) % image.height()); // On reboucle quand l'image IMAC se répète
            // Rmq : si on augmente le facteur (ici 5), on a une mosaique avec plus de répétition
        }
    }
    image = mosaique;
}

/*Idée pour la mosaïque miroir : on reprend le code précédent, puis dès q'uon boucle on inverse l'image (cad dès que x * 5 % image.width passe à 0)*/

void mosaique_mirror(sil::Image &image)
{
    sil::Image mosaique {image.width(), image.height()};
    // On initalise un compteur pour repérer le bloc "impair" (miroir) et des blocs "pairs" (normaux)
    int compteur = 0;
    int previous_pixel_x = -1;

    for (int x = 0; x < image.width(); ++x)
    {
        // Si rebouclage, alors (x * 5) % image.width() repart de 0
        if ((x * 5) % image.width() < previous_pixel_x)
        {
            compteur++; // On est passé à un autre bloc
        }
        previous_pixel_x = (x * 5) % image.width();

        for (int y = 0; y < image.height(); ++y)
        {
            int x_final{};
            if (compteur % 2 == 1)
            {
                x_final = image.width() - 1 - (x * 5) % image.width(); // Si bloc impair, on applique l'effet miroir
            }
            else
            {
                x_final = (x * 5) % image.width();
            }
            mosaique.pixel(x, y) = image.pixel(x_final, (y * 5) % image.height());
        }
    }
    image = mosaique;
}

/*Pour faire comme dans l'énoncé, il faut aussi qu'ule ligne sur deux soit retournée*/

void mosaique_double_mirror(sil::Image &image)
{
    sil::Image mosaique {image.width(), image.height()};
    // On initalise un compteur pour repérer le bloc "impair" (miroir) et des blocs "pairs" (normaux) et les lignes "paires" et "impaires"
    int compteur_columns = 0;
    int compteur_lines = 0;

    int previous_pixel_x = -1;
    int previous_pixel_y = -1;

    for (int x = 0; x < image.width(); ++x)
    {
        // Si rebouclage, alors (x * 5) % image.width() repart de 0
        if ((x * 5) % image.width() < previous_pixel_x)
        {
            compteur_columns++; // On est passé à un autre bloc
        }
        previous_pixel_x = (x * 5) % image.width();

        // On remet à jour pour chaque nouvelle colonne
        compteur_lines = 0;
        previous_pixel_y = -1;

        for (int y = 0; y < image.height(); ++y)
        {
            // Si saut de ligne, alors (y * 5) % image.height() repart de 0
            if ((y * 5) % image.height() < previous_pixel_y)
            {
                compteur_lines++; // On est passé à une autre ligne
            }
            previous_pixel_y = (y * 5) % image.height();
            
            int x_final{};
            int y_final{};
            if (compteur_columns % 2 == 1)
            {
                x_final = image.width() - 1 - (x * 5) % image.width(); // Si bloc impair, on applique l'effet miroir
            }
            else
            {
                x_final = (x * 5) % image.width();
            }

            if (compteur_lines % 2 == 1)
            {
                y_final = image.height() - 1 - (y * 5) % image.height(); // Si bloc impair, on applique l'effet miroir
            }
            else
            {
                y_final = (y * 5) % image.height();
            }
            mosaique.pixel(x, y) = image.pixel(x_final, y_final);
        }
    }
    image = mosaique;
}

void glitch(sil::Image &image)
{
    int numberOfRect = random_int(0, 100); // Nombre de rectangles
    
    for (int r {0}; r < numberOfRect; ++r)
    {
        // Tailles des rectangles
        int w = random_int(1, 50);
        int h = random_int(1, 10);

        // Positions aléatoires (départ)
        int x1 = random_int(0, image.width() - w); // Ne dépassera pas les bornes
        int y1 = random_int(0, image.height() - h);

        // Positions aléatoires (arrivée)
        int x2 = random_int(0, image.width() - w);
        int y2 = random_int(0, image.height() - h);

        for (int i {}; i < w; ++i)
        {
            for (int j {}; j < h; ++j)
            {
                // Interpolation des pixels
                glm::vec3 save = image.pixel(i + x1,j + y1);
                image.pixel(i + x1,j + y1) = image.pixel(i + x2, j + y2);
                image.pixel(i + x2, j + y2) = save;
            }
        }
    }
}

void fractals(sil::Image &image)
{
    for (int x {0}; x < image.width(); ++x)
    {
        for (int y {0}; y < image.height(); ++y)
        {
            float r = (x / 500.f) * 3.f - 2.f; // Conversion de x entre 0 et 500 --> -2 et 1
            float im = (y / 500.f) * 3.f - 1.5; // Conversion de x entre 0 et 500 --> -1.5 et 1.5
            std::complex<float> c{r, im};
            std::complex<float> z{0, 0};

            int compteur{};

            for (int i{}; i < 200; ++i)
            {
                z = z*z + c;
                
                if (std::abs(z) > 2)
                {
                    float grey = i / 200.f;
                    image.pixel(x, y) = glm::vec3(grey*10);
                    break;
                }
                ++compteur;
            }

            if (compteur == 200)
            {
                image.pixel(x, y) = glm::vec3(1.f);
            }
        }
    }
}

void fading_color(sil::Image& image) // Dégradé de couleurs
{
    glm::vec3 a(1.f, 0.f, 0.f); // Rouge
    glm::vec3 b(0.f, 1.f, 0.f); // Vert
    for (int x {0}; x < image.width(); ++x)
    {
        float t = x / 300.f; // Pourcentage de mélange entre les deux couleurs

        for (int y {0}; y < image.height(); ++y)
        {
            image.pixel(x, y) = glm::mix(a, b, t); // Colonne de pixels de même couleur (mélange de rouge et vert)
        }
    }
}

int main()
{
    // {
    //     sil::Image image{"images/logo.png"}; // Lis l'image
    //     green(image); // Utilise la fonction pour modifier l'image
    //     image.save("output/green_imac.png"); // Sauvegarde l'image
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     swapRedBlue(image);
    //     image.save("output/swaped_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     blackAndWhite(image);
    //     image.save("output/n&b_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     negative(image);
    //     image.save("output/negatif_imac.png");
    // }
    // {
    //     sil::Image image{300/*width*/, 200/*height*/};
    //     fading(image);
    //     image.save("output/degrade_n&b.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mirror(image);
    //     image.save("output/miroir_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     noise(image);
    //     image.save("output/bruit_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     rotation(image);
    //     image.save("output/rotation90_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     rgb_split(image);
    //     image.save("output/rgb_split_imac.png");
    // }
    // {
    //     sil::Image image{"images/photo.jpg"};
    //     brightness(image);
    //     image.save("output/low_lum_imac.png");
    // } 
    // {
    //     sil::Image image{500/*width*/, 500/*height*/};
    //     disk(image, 250.f, 250.f);
    //     image.save("output/disque.png");
    // }
    // {
    //     sil::Image image{500/*width*/, 500/*height*/};
    //     circle(image, 250.f, 250.f);
    //     image.save("output/cercle.png");
    // }

/**************** Animation disque ******************/
    // {
    //     int numberOfImages = 11; // Nombre d'images pour l'animation
        
    //     for (int i = 0; i < numberOfImages; ++i)
    //     {
    //         sil::Image image{500, 500};

    //         disk(image, i * 50.f, image.height()/2.f);

    //         image.save("output/animation/animation_" + std::to_string(i) + ".png");
    //     }
    // }

    // {
    //     sil::Image image{500/*width*/, 500/*height*/};
    //     rosace(image);
    //     image.save("output/rosace.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique(image);
    //     image.save("output/mosaique_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique_mirror(image);
    //     image.save("output/mosaique_miroir_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     mosaique_double_mirror(image);
    //     image.save("output/mosaique_double_miroir_imac.png");
    // }
    // {
    //     sil::Image image{500, 500};
    //     fractals(image);
    //     image.save("output/fractale.png");
    // }
    // {
    //     sil::Image image{300, 200};
    //     fading_color(image);
    //     image.save("output/degrade_couleur.png");
    // }
    {
        sil::Image image{"images/logo.png"};
        glitch(image);
        image.save("output/glitch.png");
    }
}