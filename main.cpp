#include <windows.h>
#include <iostream>
#include <stdio.h> 
#include "CImg.h"
#include "convert.hpp"

using namespace cimg_library; 

int main(){
    std::cout << "Hello World" << std::endl;
    CImg<unsigned char> image("weiss4.jpg");
    //image.resize(250,350);
    //image.display();
    //image.save_png("weissoutput.png");   
    //CImg<unsigned char> image2("weissoutput.png");
    image.resize(500,700);
    CImg<unsigned char> image3;
    for(int i = 1; i <= 5; i++)
        image3.append(image,'y');
    CImg<unsigned char> image4;
    for(int i = 1; i <=10; i++)
        image4.append(image3,'x');     
    image4.save_png("output.png"); 

    /*CImg<unsigned char> image2("test.jpg");
    
    //CImg<unsigned char> test2("test2.png");
    CImg<unsigned char> test = image.append(image2,'x'); 
    CImg<unsigned char> image3("test.png");
    image3.resize(400,400,5);
    image3.save("resize.png");
    CImg<unsigned char> test2 = image3.append(image2,'x'); 
    //test.display();
    test.save("output.png");
    test2.save("output2.png");*/
    convert_to_jpg("output.png", "output.jpg");
    std::cout << "Hello world" << std::endl;
    return 1;
}