#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <gdiplus.h>


int GetEncoderClsid(const WCHAR* format, CLSID* pClsid); //Helper function
void convert_to_jpg (std::string input_name, std::string output_name); //Use gdi+ to convert an image into a jpg