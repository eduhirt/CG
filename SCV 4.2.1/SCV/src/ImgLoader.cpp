#include "SCV/stdafx.h"
#include "SCV/ImgLoader.h"
#include "SCV/stb_image.h"

namespace scv {

unsigned char* loadImageToArray(const std::string &fileName, int *width, int *height) {
   int comp;
   unsigned char* data = stbi_load(fileName.c_str(), width, height, &comp, 4);

   /* NO VISUAL STUDIO ERA nullptr */
   if (data == NULL) {
      std::cerr << "ImageLoader: " << stbi_failure_reason() << std::endl;
   }

   return data;
}

void freeImageData(unsigned char* data) {
   stbi_image_free(data);
}

} // namespace scv
