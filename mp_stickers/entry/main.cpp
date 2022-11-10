#include "Image.h"
#include "StickerSheet.h"

int main() {
  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  //Image alma; alma.readFromFile("../tests/alma.png");
   Image alma; alma.readFromFile("../tests/t.png");

  //Image i;    i.readFromFile("../tests/i.png");
 Image i;    i.readFromFile("../tests/flower.png");
  // Image b;    b.readFromFile("../tests/b.png");
  //  Image c;    c.readFromFile("../tests/h.png");

  cs225::StickerSheet sheet(alma, 5);
  // cs225:StickerSheet sheet(alma, 5);
  //sheet.addSticker(i, 20, 200);

  sheet.addSticker(i, 30, 800);
  sheet.addSticker(i, 0, 200);
  sheet.addSticker(i, 150, 700);


  sheet.render().writeToFile("../myImage.png");
  


  return 0;
}
