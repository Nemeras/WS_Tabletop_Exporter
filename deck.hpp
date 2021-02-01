#include <stdio.h>
#include <iostream>
#include <vector>
#include "CImg.h"
#include "card.hpp"
#include <unordered_map>

class Deck {
    protected :
        std::vector<Card> cards;

    public :
        void generate_image(std::string output_name);
        void add_card(Card card);
        void generate_json(std::string name);

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

};