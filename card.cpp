#include "card.hpp"

bool dirExists(const std::string& dirName_in)
{
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

void Card::check_path(){
    if(dirExists("traductions") == false)
        CreateDirectoryA("traductions", NULL);
    int cnt=0;
    while(reference[cnt] != '\\')
        cnt++;
    std::string dir_name = "traductions\\" + reference.substr(0,cnt);
    LPSTR lpstr_dir_name = const_cast<char *>(dir_name.c_str());
    if(dirExists(dir_name) == false)
        CreateDirectoryA(lpstr_dir_name, NULL);
}

std::string Card::get_image_name(){
    return image_name;
}

void Card::to_file(std::string filename){
    std::ofstream file;
    file.open(filename);
    if(file.is_open() == false){
        std::cout << "FILE IS NOT OPENED" << std::endl;
        return;
    }
    file << name << std::endl;
    file << reference << std::endl;
    file << color << std::endl;
    file << type << std::endl;
    file << traits << std::endl;
    file << image_name << std::endl;
    file << triggers << std::endl;
    file << traduction_file_path << std::endl;
    file << power << std::endl;
    file << cost << std::endl;
    file << level << std::endl;
    file << soul << std::endl;
    file << effect;
    file.close();
}

void Card::to_file_ref(){
    check_path();
    to_file(traduction_file_path);
}

void Card::from_traduction_file(std::string filename){
    try{
        std::ifstream file;
        file.open(filename);
        parse_traduction(std::move(file));
        file.close();
    }
    catch(std::string error){
        if (error == "INCORRECT FILE")
            std::cout << "INCORRECT FILE" << std::endl;
    }
}

void Card::parse_traduction(std::ifstream&& file){
    std::string garbage;
    
    std::string temp_type;
    std::getline(file,garbage,'=');
    std::getline(file,garbage,'\n');
    while(true){
        std::string garbage;
        char next_char = file.peek();
        if (next_char == EOF)
            throw std::string("INCORRECT FILE");
        if (next_char != '\n')
            break;
        std::getline(file,garbage,'\n');
    }
    std::getline(file,name,'\n');
    std::getline(file,garbage,'\n');
    std::getline(file,garbage,':');
    file >> reference;
    std::getline(file,garbage,'\n');
    std::getline(file,garbage,':');
    file >> color;
    std::getline(file,garbage,':');
    std::getline(file,temp_type,'\n');
    std::getline(file,garbage,':');
    file >> level;
    std::getline(file,garbage,':');
    file >> cost;
    std::getline(file,garbage,':');
    file >> power;
    std::getline(file,garbage,':');
    file >> soul;
    std::getline(file,garbage,':');
    std::getline(file,traits,'\n');
    std::getline(file,garbage,':');
    std::getline(file,triggers,'\n');
    std::getline(file,garbage,':');
    std::getline(file,garbage,':');
    std::getline(file,effect,'=');

    if(traits[0] == ' ')
        traits.erase(traits.begin(),traits.begin()+1);

    if(effect[0] == ' ')
        effect.erase(effect.begin(),effect.begin()+1);

    if(triggers[0] == ' ')
        triggers.erase(triggers.begin(),triggers.begin()+1);

    effect.erase(std::remove(effect.end()-4, effect.end(), '\n'),effect.end());

    reference.erase(std::remove(reference.begin(),reference.end(),' '),reference.end());

    if(temp_type.find("Char") != temp_type.npos){
        type = "CH";
    } else {
        if (temp_type.find("Cli") != temp_type.npos ){
        type = "CX";
        } else
        {
        type = "EV";
        }
    }

    std::replace(reference.begin(),reference.end(),'/','\\');
    image_name = ".\\images\\" + reference + ".jpg";
    traduction_file_path = ".\\traductions\\" + reference + ".txt";
}

std::string Card::get_reference(){
    return reference;
}

void parse_hotc_file(std::string filename){
    std::ifstream file;
    file.open(filename);
    while(true){
        try{
            Card temp_card;
            temp_card.parse_traduction(std::move(file));
            temp_card.to_file_ref();
        }
        catch(std::string exception){
            if (exception == "INCORRECT FILE")
                std::cout << "Finished !" << std::endl;
            break;
        }
    }
    file.close();
}