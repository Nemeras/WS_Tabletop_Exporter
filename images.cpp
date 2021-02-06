#include "images.hpp"

using namespace cimg_library; 

bool dirExists(const std::string& dirName_in){
  DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return true;   // this is a directory!

  return false;    // this is not a directory!
}

bool fileExists(const std::string& fileName_in){
  DWORD ftyp = GetFileAttributesA(fileName_in.c_str());
  if (ftyp == INVALID_FILE_ATTRIBUTES)
    return false;  //something is wrong with your path!

  if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
    return false;   // this is a directory!

  return true;    // this is not a directory!
}

void add_image(std::string image_filename, std::string reference){

  CImg<unsigned char> image(image_filename.c_str());
  if (image.width()/image.height() != 5/7){
      std::cout << "Image is not of the correct ratio !" << std::endl;
      return;
  }

  image.resize(500,700);
  std::string filename = "images\\"+ reference + ".png";
  std::replace(filename.begin(),filename.end(),'/','\\');
  std::string translation_filename = ".\\translations\\"+ reference + ".txt";
  std::replace(translation_filename.begin(),translation_filename.end(),'/','\\');
  if (access( translation_filename.c_str(), F_OK ) == -1){
      std::cout << "I don't have any translation for this card !" << std::endl;
      return;
  }
  if(dirExists("images") == false)
      CreateDirectoryA("images", NULL);
  int cnt=0;
  while(reference[cnt] != '/')
      cnt++;
  std::string dir_name = "images\\" + reference.substr(0,cnt);
  LPSTR lpstr_dir_name = const_cast<char *>(dir_name.c_str());
  if(dirExists(dir_name) == false)
      CreateDirectoryA(lpstr_dir_name, NULL); 

  image.save(filename.c_str()); 
}