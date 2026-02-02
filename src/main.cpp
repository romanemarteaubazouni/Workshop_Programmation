#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"

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

void rotation(sil::Image &image)
{
    sil::Image new_image{image.height(), image.width()};
    
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
    //     image.save("output/mirroir_imac.png");
    // }
    // {
    //     sil::Image image{"images/logo.png"};
    //     noise(image);
    //     image.save("output/bruit_imac.png");
    // }
    {
        sil::Image image{"images/logo.png"};
        rotation(image);
        image.save("output/rotation90_imac.png");
    }
}