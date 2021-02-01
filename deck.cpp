#include "convert.hpp"
#include "deck.hpp"

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
    convert_to_jpg("temp.png", output_name+".jpg"); //Using GDI+ to convert the temporary file.
    remove( "temp.png");
}

void Deck::generate_json(std::string name){
    std::string filename = name + ".json";
    std::ofstream file(filename.c_str());
    bool fst = true;
    std::ifstream part1("part1.json");
    file << part1.rdbuf();
     part1.close();
    file << '"' << "[";
    for (auto &c : cards){
        c.reference_slash();
        if (!fst)
            file << ",";
        fst = false;
        file << "\\\\\\" << '"' << c.get_reference() << "\\\\\\" << '"';
    }
    file << "]\\" << '"' << "\\r\\nserialInfoJSON = \\" << '"' << "{";

    std::unordered_map<std::string,Card> card_map;
        
    for (auto &c : cards){
        std::pair<std::string,Card> temp_card (c.get_reference(),c);
        card_map.insert(temp_card);
    }
    fst = true;
    for (auto &c : card_map){
        if (fst != true)
            file << ",";
        fst = false;
        Card card = c.second;
        card.reference_slash();
        card.effect_line_break();
        file << "\\\\\\" << '"' << card.get_reference() << "\\\\\\" << '"' << ":{\\\\\\" << '"' << "Name\\\\\\" << '"' << ":\\\\\\" << '"' << card.get_name();
        file << " [" << card.get_reference() << "][" << card.get_type() << "]\\\\\\" << '"' << ",\\\\\\" << '"' << "Description\\\\\\" << '"';
        file << ":\\\\\\" << '"' << "Type: " << card.get_type() << "\\\\\\\\nTraits: " << card.get_traits() << " \\\\\\\\nP/S: " << card.get_power();
        file << "P/" << card.get_soul() << "S " << '|' << '|' << " Lv/Co: " << card.get_level() << "/" << card.get_cost() << "\\\\\\\\nEffect: " << card.get_effect();
        file << "\\\\\\" << '"' << "}";
    }
    file << "}\\" << '"' << "\\r\\n\\r\\n-- "; 

    std::ifstream part2("part2.json");
    file << part2.rdbuf();
    part2.close();

    file.close();
}