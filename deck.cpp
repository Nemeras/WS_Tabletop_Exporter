#define _CRT_SECURE_NO_DEPRECATE
#include "convert.hpp"
#include "deck.hpp"
#include <windows.h>
#include <curl/curl.h>

using namespace cimg_library; 

void Deck::add_card(Card card){
    cards.push_back(card);
}

void Deck::add_card(Card card, int number){
    for (int i = 1; i <= number; i++)
        cards.push_back(card);
}
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void download_image(std::string url,std::string filename){
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(filename.c_str(),"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        // always cleanup 
        curl_easy_cleanup(curl);
        fclose(fp);
    }
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
        for (Card& c : v) {
            if (!fileExists(c.get_image_name())) {
                std::cout << "I don't have an image for " << c.get_reference() << " !" << std::endl;
                std::cout << "URL for an image ?" << std::endl;
                std::string url;
                std::cin >> url;
                int pos = url.find_last_of(".");
                std::string extension = url.substr(pos);
                std::string temp_filename = "temp" + extension;
                std::cout << "Downloading " << temp_filename << std::endl;
                download_image(url, temp_filename);
                add_image(temp_filename, c.get_reference());
                //remove(temp_filename.c_str());
            }
        
            std::cout << "Adding " << c.get_reference() << std::endl;
            std::string image_name = c.get_image_name();
            CImg<unsigned char> card_image(image_name.c_str());

            card_row.append(card_image,'x');
        } 
        deck_image.append(card_row,'y'); //creating the deck image, one row at a time.
    }

    deck_image.save("temp.png"); //I need to use a temporary png file because CImg doesn't seem to like saving jpgs.
    convert_to_jpg("temp.png", "Export\\" + output_name+".jpg"); //Using GDI+ to convert the temporary file.
    remove("temp.png");
}

void Deck::generate_json(std::string name){
    std::string filename = "Export\\" + name + ".json";
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

void Deck::import_encoredeck(std::string filename){
    std::ifstream file(filename.c_str());
    std::string garbage;
    std::string card_reference;
    std::string line;
    std::getline(file,garbage);
    std::getline(file,garbage);
    int number;
    while (std::getline(file,line)){
        std::cout << line << std::endl;
        if ((line.find("Climaxes") != std::string::npos) || (line.find("Events") != std::string::npos))
            continue;
        int pos = line.find('\t',0);
        std::cout << line.substr(0,pos) << "#" << std::endl;
        std::cout << line.substr(pos+1,pos+1) << "##" << std::endl;
        card_reference = line.substr(0,pos);
        number = std::stoi(line.substr(pos+1,pos+1));
        std::cout << card_reference << " " << number << std::endl;
        add_card(Card(card_reference), number);
    }
    file.close();
    if (cards.size() != 50)
        std::cout << "The deck doesn't have 50 cards !" << std::endl;
}