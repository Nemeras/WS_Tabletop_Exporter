#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>

class Card {
    protected :
        std::string name;
        std::string reference;
        std::string color;
        std::string type;
        std::string traits;
        std::string effect;
        std::string image_name;
        std::string triggers;
        std::string traduction_file_path;
        int power;
        int cost;
        int level;
        int soul;

    public:
        std::string get_image_name();
        std::string generate_card();
        void to_file(std::string filename);
        void to_file_ref();
        void from_traduction_file(std::string filename);
        void parse_traduction(std::ifstream&& stream);
        std::string get_reference();
        void check_path();

        Card(){
        }

        Card(std::string card_name){
            std::string filename = ".\\traductions\\" + card_name + ".txt";
            std::replace(filename.begin(),filename.end(),'/','\\');
            std::ifstream file;
            file.open(filename);
            if (file.is_open() == false){
                std::cout << "FILE NOT OPENED (card declaration)" << std::endl;
                return;
            }
            std::getline(file,name,'\n');
            std::getline(file,reference,'\n');
            std::getline(file,color,'\n');
            std::getline(file,type,'\n');
            std::getline(file,traits,'\n');
            std::getline(file,image_name,'\n');
            std::getline(file,triggers,'\n');
            std::getline(file,traduction_file_path,'\n');
            file >> power;
            file >> cost;
            file >> level;
            file >> soul;
            std::string buffer;
            while(std::getline(file,buffer))
                effect.append(buffer + "\n");
            effect = effect.substr(1,effect.length()-2);
            file.close();
        }

};

void parse_hotc_file(std::string filename);
/*void use_ofstream(std::ofstream &&stream);
void send_stream();*/