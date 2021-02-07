#include <windows.h>
#include <iostream>
#include <stdio.h> 

#include "CImg.h"
#include "convert.hpp"
#include "deck.hpp"
#include <string>
#include "popl.hpp"
#include <time.h>

using namespace cimg_library; 
using namespace popl;

int main(int argc, char* argv[]){
    srand(time(NULL));
    std::cout << "test !" << std::endl;
    std::cout << "Hello world" << std::endl;
    /*CImg<unsigned char> test1("W83-001.png");
    test1.display();
    CImg<unsigned char> image("Kaleidoscope.jpg");
    image.display();*/

    OptionParser op("Allowed options");
    auto deck_creating_option = op.add<Value<std::string>>("g", "generate", "generate a deck from a text file");
    auto file_parsing_option  = op.add<Value<std::string>>("p", "parse", "parse a translation file");
    auto image_adding_option  = op.add<Value<std::string>>("i","image", "adds an image");
    auto output_option        = op.add<Value<std::string>>("o", "output", "output");
    auto encoredeck_option    = op.add<Value<std::string>>("e", "encore", "generate a deck from an encoredeck exported text file.");
    auto all_option           = op.add<Value<std::string>>("a", "all", "generates a deck from an encoredeck exported text file, downloads the sleeves and puts everything in tts");
    auto sharex_option        = op.add<Switch>("s", "sharex", "export to encoreX");
    auto tts_option           = op.add<Switch>("t", "tts", "saves to the TTS folder");
    

    op.parse(argc, argv);   
    int cnt = deck_creating_option->is_set() + file_parsing_option->is_set() + image_adding_option->is_set() + encoredeck_option->is_set() + all_option->is_set();
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
        if (sharex_option->is_set()) {
            std::cout << "Exporting to sharex !" << std::endl;
            std::string cmd = "C:\\Program^ Files\\ShareX\\ShareX.exe Export\\" + output_option->value() + ".jpg";
            int a = system(cmd.c_str());
        }
        if (tts_option->is_set()) {
            std::string homepath = getenv("HOMEPATH");
            std::string out_path = "C:" + homepath + "\\Documents\\My Games\\TableTop Simulator\\Saves\\Saved Objects\\" + output_option->value() + ".json";
            std::string out_path_logo = "C:" + homepath + "\\Documents\\My Games\\TableTop Simulator\\Saves\\Saved Objects\\" + output_option->value() + ".png";
            std::string file_path = "Export\\" + output_option->value() + ".json";
            std::cout << "Copying " << file_path << " to" << std::endl;
            std::cout << out_path << std::endl;
            CopyFile(file_path.c_str(), out_path.c_str(), TRUE);
            CopyFile("logo.png", out_path_logo.c_str(), TRUE);
        }
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
        std::replace(deck_name.begin(), deck_name.end(), ' ', '_');
        file.close();
        deck.import_encoredeck(encoredeck_option->value());
        deck.generate_image(deck_name);
        deck.generate_json(deck_name);
        if (sharex_option->is_set()) {
            std::cout << "Exporting to sharex !" << std::endl;
            std::string cmd = "C:\\Program^ Files\\ShareX\\ShareX.exe Export\\" + deck_name + ".jpg";
            int a = system(cmd.c_str());
        }
        if (tts_option->is_set()) {
            std::string homepath = getenv("HOMEPATH");
            std::string out_path = "C:" + homepath + "\\Documents\\My Games\\TableTop Simulator\\Saves\\Saved Objects\\" + deck_name + ".json";
            std::string out_path_logo = "C:" + homepath + "\\Documents\\My Games\\TableTop Simulator\\Saves\\Saved Objects\\" + deck_name + ".png";
            std::string file_path = "Export\\" + deck_name + ".json";
            std::cout << "Copying " << file_path << " to" << std::endl;
            std::cout << out_path << std::endl;
            CopyFile(file_path.c_str(), out_path.c_str(), TRUE);
            CopyFile("logo.png", out_path_logo.c_str(), TRUE);
        }
    }

    if (all_option->is_set()) {
        Deck deck;
        std::string deck_name;
        std::ifstream file(all_option->value());
        std::getline(file, deck_name);
        std::replace(deck_name.begin(), deck_name.end(), ' ', '_');
        file.close();
        deck.import_encoredeck(all_option->value());
        deck.generate_image(deck_name);
        deck.generate_json(deck_name);
        std::cout << "Exporting to sharex !" << std::endl;
        std::string cmd = "C:\\Program^ Files\\ShareX\\ShareX.exe Export\\" + deck_name + ".jpg";
        int a = system(cmd.c_str());
        std::string sleeves_url;
        std::cout << "URL of the sleeves ?" << std::endl;
        std::cin >> sleeves_url;
        int pos = sleeves_url.find_last_of(".");
        std::string extension = sleeves_url.substr(pos);
        std::string sleeves_filename = "sleeves" + extension;
        download_image(sleeves_url, sleeves_filename);
        CImg<unsigned char> image(sleeves_filename.c_str());
        image.save("sleeves.png");
        std::cout << "URL of the cards I exported to ShareX ?" << std::endl;
        std::string url;
        std::cin >> url;
        deck.generate_deck_json(deck_name, url.c_str(), sleeves_url.c_str());
        std::string homepath = getenv("HOMEPATH");
        std::string out_path = "C:" + homepath + "\\Documents\\My Games\\TableTop Simulator\\Saves\\Saved Objects\\" + deck_name + ".json";
        std::string out_path_logo = "C:" + homepath + "\\Documents\\My Games\\TableTop Simulator\\Saves\\Saved Objects\\" + deck_name + ".png";
        std::string file_path = deck_name + ".json";
        CopyFile(file_path.c_str(), out_path.c_str(), TRUE);
        CopyFile("sleeves.png", out_path_logo.c_str(), TRUE);
        remove(sleeves_filename.c_str());
        remove(file_path.c_str());
    }
    
    return 1;
}