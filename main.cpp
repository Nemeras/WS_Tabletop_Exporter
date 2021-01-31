#include <windows.h>
#include <iostream>
#include <stdio.h> 
#include "CImg.h"
#include "convert.hpp"
#include "deck.hpp"
#include <string>
#include <popl.hpp>

using namespace cimg_library; 
int main(){
    std::cout << "test !" << std::endl;
    std::string deck_filename;
    std::string deck_output_name;

    /*options_description desc{"Options"};
    desc.add_options()
        ("parse", value<std::vector<std::string>>()->multitoken()->composing(),"Parse")
        ("unreg", "Unrecognized options");
        //("deck", value<std::string>)
    command_line_parser parser{argc, argv};
    parser.options(desc).allow_unregistered().style(
        command_line_style::default_style |
        command_line_style::allow_slash_for_short);
    parsed_options parsed_options = parser.run();

    variables_map vm;
    store(parsed_options, vm);
    notify(vm);

    if (vm.count("parse")){
        std::cout << "Hello world" << std::endl;
    }*/
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
    parse_hotc_file("test_hotc.txt");
    Card test("5HY/W83-003");
    test.to_file("checking.txt");
    Deck deck("deck.txt");
    deck.generate_image("Deck");
    //test2.to_file(".\\traductions\\test2.txt");
    //std::string temp = test2.get_reference() + ".txt";
    //std::cout << temp << std::endl;
    //test2.to_file(temp.c_str());
    //std::cout << name << std::endl << reference << std::endl << color << std::endl << "Bye bye" << std::endl;
    
    
    return 1;
}