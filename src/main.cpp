#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <cmath>

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

void rotation(sil::Image &image) // Rotation de 90]
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
}