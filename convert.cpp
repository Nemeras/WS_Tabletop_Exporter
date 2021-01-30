#include "convert.hpp"

using namespace Gdiplus;

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
   UINT  num = 0;          // number of image encoders
   UINT  size = 0;         // size of the image encoder array in bytes

   ImageCodecInfo* pImageCodecInfo = NULL;

   GetImageEncodersSize(&num, &size);
   if(size == 0)
      return -1;  // Failure

   pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
   if(pImageCodecInfo == NULL)
      return -1;  // Failure

   GetImageEncoders(num, size, pImageCodecInfo);

   for(UINT j = 0; j < num; ++j)
   {
      if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
      {
         *pClsid = pImageCodecInfo[j].Clsid;
         free(pImageCodecInfo);
         return j;  // Success
      }    
   }

   free(pImageCodecInfo);
   return -1;  // Failure
}

void convert_to_jpg (std::string input_name, std::string output_name){
//convert the names
std::wstring in_name = std::wstring(input_name.begin(), input_name.end());
std::wstring out_name = std::wstring(output_name.begin(),output_name.end());

// Initialize GDI+.
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR gdiplusToken;
GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

CLSID encoderClsid;
Status stat;
Image* image = new Image(in_name.c_str());

// Get the CLSID of the PNG encoder.

GetEncoderClsid(L"image/jpeg", &encoderClsid);

stat = image->Save(out_name.c_str(), &encoderClsid, NULL);

if(stat == Ok)
   std::cout << input_name << " was successfully converted into " << output_name << std::endl;
else
   std::cout << "Failure: stat = " << stat << std::endl;

delete image;
GdiplusShutdown(gdiplusToken);

}