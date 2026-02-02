#include <sil/sil.hpp>
#include <iostream>

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
    {
        sil::Image image{"images/logo.png"};
        blackAndWhite(image);
        image.save("output/n&b_imac.png");
    }
}