#include <bits/stdc++.h>
using namespace std;
#include "Image_Class.h"

// Name:Adham Amr Hassan 
// ID:20240070
// s8
// Filter 1,4,7,10


//Filter 1
Image grayscale(Image &image)
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

            avg /= 3; // avg = avg / 3

            for(int k = 0 ; k < 3 ; k++)
            {
                res_img(i,j,k) = avg ;
            }
        }
    }
    return res_img;
}
//Filter 4
Image make_brightness(Image &image , int percentage)  
{
Image res_image(image.width,image.height);

for(int i = 0 ; i<image.width ; i++)
{
    for(int j = 0 ; j<image.height ; j++)
    {
        for(int k = 0 ; k < 3 ; k++)
        {
            int val = image(i,j,k);

            int new_val = val + (val*percentage)/100 ;

            if(new_val > 255) new_val = 255; // positive

            if(new_val < 0) new_val = 0; // Negative

            res_image(i,j,k) = new_val ;
        }
    }
}
return res_image ;
}
// Filter 7
Image merge_image(Image &image1, Image &image2) 
  {
        unsigned int min_width = std::min(image1.width, image2.width);

        unsigned int min_height = std::min(image1.height, image2.height);

        Image mergedImage(min_width, min_height);
        
        for (int i = 0; i < min_width; ++i) 
        {
            for (int j = 0; j < min_height; ++j) 
            {
                for (int k = 0; k < 3; ++k) 
                {
                    mergedImage(i, j, k) = (image1(i, j, k) + image2(i, j, k)) / 2;
                }
            }
        }
        
        return mergedImage;
    }
// Filter 10
Image Edge_Detection(Image & image) 


    {
            Image grayImage = grayscale(image);
    
            Image edgeImage(grayImage.width, grayImage.height);
    
            //loop from 1 to width - 1 because Sobel needs neighbors around each pixel
    
            for (int i = 1; i < grayImage.width - 1; ++i) 
            {
                for (int j = 1; j < grayImage.height - 1; ++j) 
                {
                    // Apply Sobel operator on grayscale image
                    //     [ -1  0  1 ]                 [ -1  -2  -1 ]
                    //Gx = [ -2  0  2 ]         Gy =    [  0   0   0 ]
                    //     [ -1  0  1 ]                 [  1   2   1 ]
                    
                    for(int k = 0 ; k < 3 ; k++)
                    {
                        int gx = (grayImage(i+1, j-1, k) + 2*grayImage(i+1, j, k) + grayImage(i+1, j+1, k)) - (grayImage(i-1, j-1, k) + 2*grayImage(i-1, j, k) + grayImage(i-1, j+1, k));
        
                        int gy = (grayImage(i-1, j+1, k) + 2*grayImage(i, j+1, k) + grayImage(i+1, j+1, k)) - (grayImage(i-1, j-1, k) + 2*grayImage(i, j-1, k) + grayImage(i+1, j-1, k));
        
                        int magnitude = sqrt(gx*gx + gy*gy);
        
                        // Edge thresholding
        
                        if (magnitude > 128)
                        edgeImage(i, j, k) = 0; // Black
                        else
                        edgeImage(i, j, k) = 255; // White
                    }
                }
            }
            return edgeImage;
        }
// Filter 2
    Image applyInvert(Image &img) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            img(x,y,0) = 255 - img(x,y,0);
            img(x,y,1) = 255 - img(x,y,1);
            img(x,y,2) = 255 - img(x,y,2);
        }
    }
    return img;
}

Image Black_White(Image& image)
{    
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
            unsigned int color = 0;
            if(avg >= 128)
            {
                color = 0; 
            }
            else
            {
                color = 255;
            }
            image(i, j, 0) = color;
            image(i, j, 1) = color;
            image(i, j, 2) = color;
        }
    }
    return image ;
}
// Filter 5
Image Flip_Vertical(Image& image)
{
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height / 2; ++j) {
            for (int k = 0; k < 3; k++)
            {
                unsigned int tmp = image(i, j, k);
    
                image(i, j, k) = image(i, image.height - j - 1, k);
                image(i, image.height - j - 1, k) = tmp;
            }
            
    
        }
    }
    return image ;
}
Image Flip_Horizontal(Image& image)
{
    for (int i = 0; i < image.width/2; ++i) 
    {
        for (int j = 0; j < image.height; ++j) 
        {
            for (int k = 0; k < 3; k++)
            {
                unsigned int tmp = image(i, j, k);

                image(i, j, k) = image(image.width - i - 1, j, k);
                image(image.width - i - 1,j, k) = tmp;
            }
        }
    }
    return image ;
}
// Filter 8
Image Cropped(Image& image)
{
    int w = 0,h = 0;
    int lcorner = 0, rcorner = 0;
    cout << "Enter the start of top left corner of the cropped image: ";
    cin >> lcorner  >> rcorner;
    if(lcorner >= image.width || rcorner >= image.height)
    {
        throw std::runtime_error("Out of image size");
    }
    cout << "Enter the dimention of the cropped image: ";
    cin >> w  >> h;
    if(w + lcorner >= image.width ||h + rcorner >= image.height)
    {
         throw std::runtime_error("Out of image size");
    }
    
    Image cropped(w , h);
    
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            for (int k = 0; k < image.channels; k++) {
                cropped(i, j, k) = image(lcorner + i, rcorner + j, k);
            }
        }
    }
    // we will write cropped.SaveImage not image.SaveImage
    return cropped;
}

Image Resize(Image& image)

{    
    cout << "Enter newWidth and newHeight: ";
    unsigned int newWidth,newHeight;
    cin >> newWidth >> newHeight;
    Image resized(newWidth, newHeight);
    
    for (int i = 0; i < newWidth; i++) 
    {
        for (int j = 0; j < newHeight; j++) 
        {
            int x = i * image.width / newWidth;
            int y = j * image.height / newHeight;
            
            for (int k = 0; k < image.channels; k++) 
            {
                resized(i, j, k) = image(x, y, k);
            }
        }
    }
    // we will write resized.SaveImage not image.SaveImage
    return resized ;
}

//filter number 6: 
Image applyRotate(Image &img, int angle) {
    if (angle == 180) {
        // In-place 180 rotation
        for (int x = 0; x < img.width / 2; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int c = 0; c < 3; c++) {
                    swap(img(x, y, c),
                              img(img.width - 1 - x, img.height - 1 - y, c));
                }
            }
        }
        return img;
    }

    if (angle == 90) {
        // to rotate the photo 90 degrees.
        Image temp(img.height, img.width);
        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int c = 0; c < 3; c++) {
                    temp(img.height - 1 - y, x, c) = img(x, y, c);
                }
            }
        }
        img = temp; 
    } 
    else if (angle == 270) {
        // to rotate the photo 270 degree
        Image temp(img.height, img.width);
        for (int x = 0; x < img.width; x++) {
            for (int y = 0; y < img.height; y++) {
                for (int c = 0; c < 3; c++) {
                    temp(y, img.width - 1 - x, c) = img(x, y, c);
                }
            }
        }
        img = temp;
    }
    return img ;
}

//filter number 9:
Image applyFrame(Image &img, int thickness = 20) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            if (x < thickness || y < thickness ||
                x >= img.width - thickness || y >= img.height - thickness) {
                for (int c = 0; c < 3; c++) {
                    img(x, y, c) = 0;  // black border
                }
            }
        }
    }
    return img ;
}



//filter number 12:
Image applyBlur(Image &img) {
    Image temp(img.width, img.height);  // new blank image

    int k = 1; // matrix for area of pixels (3x3)
    for (int x = k; x < img.width - k; x++) {
        for (int y = k; y < img.height - k; y++) {
            int sum[3] = {0, 0, 0};

            // adding the matrix with each other. 
            for (int dx = -k; dx <= k; dx++) {
                for (int dy = -k; dy <= k; dy++) {
                    for (int c = 0; c < 3; c++) {
                        sum[c] += img(x + dx, y + dy, c);
                    }
                }
            }

            for (int c = 0; c < 3; c++) {
                temp(x, y, c) = sum[c] / 9; // we take the pixel itself, plus the 8 surrounding pixels.
            }
        }
    }

    img = temp; // the final result is to rotate the make the photo blur
    return img ;
}


int main() {

        cout << "Welcome to Photo Editor" << endl ;
        cout << "First we need to load an image" << endl ;
        cout << "Please make sure image has same directory as project file" << endl ; //Very important

    string filename;

    cout << "Please enter the image you want to edit.\n";

    cin >> filename;

    Image image(filename);
      
        cout << "1) Grayscale Filter" << endl;
        cout << "2) Black ans white filter" << endl ;
        cout << "3) Invert filter" << endl ;
        cout << "4) Merge two images "<< endl ;
        cout << "5) flip filter" << endl ;
        cout << "6) Rotate filter" << endl ;
        cout << "7) brightness Filter" << endl;
        cout << "8) crop filter" << endl ;
        cout << "9) Add frame filter" << endl ;
        cout << "10) Edge detection "<< endl;
        cout << "11) resize filter" << endl ;
        cout << "12) Blur filter" << endl ;

        int x ;
        cin >> x ;

        if(x==1)
        {
            image = grayscale(image);
        }
        else if (x==2)
        {
            image = Black_White(image);
        }
        else if(x==3)
        {
            image = applyInvert(image);
        }
        else if(x==4)
        {
            string file1 ;
            cout << "Please enter the image you want to merge with your image.\nbu";
            cin >> file1 ;
            Image img1(file1) ;
            Image img2(filename) ;
            image = merge_image(img1,img2); 
        }
        else if (x==5)
        {
            cout << "1) flip horozontally" << endl ;
            cout << "2) flip vertically" << endl ;
            int c ; 
            cin >> c ;
            if(c==1)
            {
                image = Flip_Horizontal(image);
            }
            else if(c==2)
            {
                image = Flip_Vertical(image);
            }
            else 
            {
            cout << "Invalid flip option please choose (1,2)\n";
            return 1;
        }

        }
        else if (x==6)
        {
            cout << "Please enter the rotation angle you want(90,180,270)" << endl ;
            int angle ;
            cin >> angle ;
            image = applyRotate(image,angle);

        }
        else if(x==7)
        {
            int percentage ;
            cout << "Please enter the brightness level you want.\n";
            cin >> percentage ;
            image = make_brightness(image,percentage);
        }
        else if(x==8)
        {
            image = Cropped(image);
        }
        else if(x==9)
        {
            image = applyFrame(image);
        }
        else if(x==10)
        {
            image = Edge_Detection(image);
        }
        else if(x==11)
        {
            image = Resize(image);
        }
        else if(x==12)
        {
            image = applyBlur(image);
        }
        else
        {
            cout << "invalid number please press number of (1,2,3,4,5,6,7,8,9,10,11,12)" ;
            return 1 ;
        }
        


    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga: ";

    cin >> filename;
    image.saveImage(filename);

    return 0;
}
