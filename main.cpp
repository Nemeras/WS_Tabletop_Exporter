#include <windows.h>
#include <iostream>
#include <stdio.h> 
#include "CImg.h"
#include "convert.hpp"
#include "deck.hpp"
#include <string>
#include "popl.hpp"

using namespace cimg_library; 
using namespace popl;

int main(int argc, char* argv[]){
    std::cout << "test !" << std::endl;

    /*std::cout << "Hello World" << std::endl;
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

    CImg<unsigned char> image2("test.jpg");
    
    //CImg<unsigned char> test2("test2.png");
    CImg<unsigned char> test = image.append(image2,'x'); 
    CImg<unsigned char> image3("test.png");
    image3.resize(400,400,5);
    image3.save("resize.png");
    CImg<unsigned char> test2 = image3.append(image2,'x'); 
    //test.display();
    test.save("output.png");
    test2.save("output2.png");
    convert_to_jpg("output.png", "output.jpg");*/

    std::cout << "Hello world" << std::endl;
    /*parse_hotc_file("test_hotc.txt");
    Card test("5HY/W83-003");
    test.to_file("checking.txt");
    Deck deck("deck.txt");
    deck.generate_image("Deck");*/

    OptionParser op("Allowed options");
    auto deck_creating_option = op.add<Value<std::string>>("g", "generate", "generate a deck from a text file");
    auto file_parsing_option  = op.add<Value<std::string>>("p", "parse", "parse a translation file");
    auto image_adding_option  = op.add<Value<std::string>>("i","image", "adds an image");
    auto output_option        = op.add<Value<std::string>>("o", "output", "output");

    op.parse(argc, argv);   
    int cnt = deck_creating_option->is_set() + file_parsing_option->is_set() + image_adding_option->is_set();
    if(cnt > 1){
        std::cout << "Too many options !" << std::endl;
        return 0;
    }

    if(file_parsing_option->is_set())
        parse_hotc_file(file_parsing_option->value());
    
    if(deck_creating_option->is_set()){
        if (!output_option->is_set()){
            std::cout << "You have forgotten to indicate the output." << std::endl;
            return 0;
        }
        std::cout << "Generating " << output_option->value() << ".jpg from " << deck_creating_option->value() << std::endl;
        Deck deck(deck_creating_option->value());
        deck.generate_image(output_option->value());
        deck.generate_json(output_option->value());
    }

    if(image_adding_option->is_set()){
        if (!output_option->is_set()){
            std::cout << "You have forgotten to indicate the output." << std::endl;
            return 0;
        }
        std::cout << "Adding " << image_adding_option->value() << " as " << output_option->value() << std::endl;
        add_image(image_adding_option->value(),output_option->value());
    }

    //test2.to_file(".\\translations\\test2.txt");
    //std::string temp = test2.get_reference() + ".txt";
    //std::cout << temp << std::endl;
    //test2.to_file(temp.c_str());
    //std::cout << name << std::endl << reference << std::endl << color << std::endl << "Bye bye" << std::endl;

    //Deck deck("deck.txt");
    //deck.generate_json("test.json");
    return 1;
}