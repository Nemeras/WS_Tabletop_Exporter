#include <stdio.h>
#include <iostream>
#include <vector>
#include "card.hpp"

class Deck {
    protected :
        std::vector<Card> cards;

    public :
        void add_card(Card card);
        void generate_image(std::string output_name);

        Deck(){
        };

};