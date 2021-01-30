#include "deck.hpp"
#include "CImg.h"
#include "convert.hpp"

using namespace cimg_library; 

void Deck::add_card(Card card){
    cards.push_back(card);
}

void Deck::generate_image(std::string output_name){

    using Vector = typename std::vector<Card>;
    using Iterator = typename Vector::const_iterator;

    if (cards.size() != 50)
        std::cout << "Deck is not of the correct size !" << std::endl;

    Iterator it = cards.cbegin();
    const Iterator end = cards.cend();
    std::vector<Vector> cards_tbl;

    while (it != end) {
        Vector temp;
        std::back_insert_iterator<Vector> inserter(temp);
        std::copy(it, it+10, inserter);
        cards_tbl.push_back(std::move(temp));
        std::advance(it,10);
    } //separating the vector representing the deck between 5 vectors containing each 10 cards.

    CImg<unsigned char> deck_image;

    for(auto& v : cards_tbl){
        CImg<unsigned char> card_row;
        for(Card& c : v){
            std::string image_name = c.get_image_name();
            CImg<unsigned char> card_image(image_name.c_str());
            card_row.append(card_image,'x');
        } //creating the deck image, one row at a time.
        deck_image.append(card_row,'y');
    }

    deck_image.save("temp.png"); //I need to use a temporary png file because CImg doesn't seem to like saving jpgs.
    convert_to_jpg("temp.png", output_name); //Using GDI+ to convert the temporary file.
    remove( "temp.png");
}