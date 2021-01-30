#include <stdio.h>
#include <iostream>

class Card {
    protected :
        std::string reference;
        std::string name;
        std::string trait1;
        std::string trait2;
        std::string effect;
        std::string image_name;
        int power;
        int cost;
        int level;
        int soul;

    public:
        std::string get_image_name();
        std::string generate_card();
        
    Card(){
        name = "Miku";
        image_name="weiss4.jpg";
        power = 0;
        cost = 0;
        level = 0;
        soul = 0;
        trait1 = "";
        trait2 = "";
        effect = "";

    }
};