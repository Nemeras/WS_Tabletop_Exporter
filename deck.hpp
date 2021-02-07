#include <stdio.h>
#include <iostream>
#include <vector>
#include "CImg.h"
#include "card.hpp"
#include <unordered_map>
#include <sstream>
#include <string>
#include <curl/curl.h>

void download_image(std::string url, std::string filename);

class Deck {
    protected :
        std::vector<Card> cards;

    public :
        void generate_image(std::string output_name);
        void add_card(Card card);
        void add_card(Card card, int number);
        void generate_json(std::string name);
        void generate_deck_json(std::string deck_name, std::string cards_url, std::string sleeves_url);
        void import_encoredeck(std::string name);

        Deck(std::string filename){
            std::ifstream file;
            file.open(filename);
            for (int i = 1; i <= 50; i++){
                std::string card_name;
                if(!std::getline(file,card_name)){
                    std::cout << "The deck file doesn't have 50 lines !" << std::endl;
                    return;
                }
                add_card(Card(card_name));
            }
        }

        Deck(){
        }

};