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
    std::cout << "Hello world" << std::endl;

    OptionParser op("Allowed options");
    auto deck_creating_option = op.add<Value<std::string>>("g", "generate", "generate a deck from a text file");
    auto file_parsing_option  = op.add<Value<std::string>>("p", "parse", "parse a translation file");
    auto image_adding_option  = op.add<Value<std::string>>("i","image", "adds an image");
    auto output_option        = op.add<Value<std::string>>("o", "output", "output");
    auto encoredeck_option    = op.add<Value<std::string>>("e", "encore", "generate a deck from an encoredeck exported text file.");

    op.parse(argc, argv);   
    int cnt = deck_creating_option->is_set() + file_parsing_option->is_set() + image_adding_option->is_set() + encoredeck_option->is_set();
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

    if(encoredeck_option->is_set()){
        Deck deck;
        std::string deck_name;
        std::ifstream file(encoredeck_option->value());
        std::getline(file,deck_name);
        file.close();
        deck.import_encoredeck(encoredeck_option->value());
        deck.generate_image(deck_name);
        deck.generate_json(deck_name);
    }

    return 1;
}