#include <iostream>
#include "Image_Class.h"
using namespace std;

Image grayscale(const Image &image)
{
    Image res_img(image.width,image.height);
    for (int i = 0; i < image.width; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {

            unsigned int avg = 0; 

            for (int k = 0; k < 3; ++k) 
            {
                avg += image(i, j, k); 
            }

            avg /= 3; 

            for(int k = 0 ; k < 3 ; k++)
            {
                res_img(i,j,k) = avg ;
            }
        }
    }
    return res_img;
}
Image flip_horozontally(Image &image)
{
    Image res_img(image.width,image.height);
    for (int width = 0; width < image.width / 2; width++) 
    { // Iterate only half width
            for (int height = 0; height < image.height; height++) 
            {
                // Swap pixels horizontally
                for(int colour = 0; colour < 3; colour++) 
                {
                    int temp = image.getPixel(width, height, colour);
                    res_img.setPixel(width, height, colour, image.getPixel(image.width - 1 - width, height, colour));
                    res_img.setPixel(image.width - 1 - width, height, colour, temp);
                }}}
    return res_img ;
}
Image flip_vertically(Image &image)
{
    Image res_img(image.width,image.height);
    for(int i = 0 ; i<image.width ; i++)
    {
        for(int j = 0 ; j<image.height/2 ; j++)
        {
            for(int k = 0 ; k<3 ; k++)
            {

                    int temp = image.getPixel(i, j, k);

                    res_img.setPixel(i, j, k, image.getPixel(i, image.height - 1 - j, k));

                    res_img.setPixel(i, image.height - 1 - j, k , temp);
            }
        }
    }
    return res_img ;
}

int main()
{
    Image image1;
    //Image image2;
    if(image1.loadNewImage("building.jpg"))
    {
        cout << "loaded successfully" << endl ;
    }
    //     unsigned int min_width = std::min(image1.width, image2.width);

    //     unsigned int min_height = std::min(image1.height, image2.height);

    //     Image mergedImage(min_width, min_height);
        
    //     for (int i = 0; i < min_width; ++i) 
    //     {
    //         for (int j = 0; j < min_height; ++j) 
    //         {
    //             for (int k = 0; k < 3; ++k) 
    //             {
    //                 mergedImage(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
    //             }
    //         }
    //     }
      Image flip_photo = flip_vertically(image1); 
    int x = flip_photo.saveImage("new_photo.png") ;
    cout << x ;

    return 0;
}
