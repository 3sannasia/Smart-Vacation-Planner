#include "StickerSheet.h"

#include "Image.h"

using namespace cs225;
StickerSheet::StickerSheet (const Image &picture, unsigned max) {
    // Image* copy = new Image(picture);
    // images.push_back(copy);
    // coor.push_back(std::make_pair(0,0));
    //base = picture;
    base = new Image(picture);
    max_ = max;
   // std::cout << "in constuctor" << images.size() << std::endl;
    for (size_t i = 0; i < max; i++) {
        images.push_back(nullptr);
        coor.push_back(std::make_pair(0,0));
    }
   // std::cout << "in constuctor" << images.size() << std::endl;
    

}

void StickerSheet::Clear() {
    // for (size_t i = 0; i < images.size(); i++) {
    //    // images[i] = nullptr;
    //     delete images[i];
        
    // }
   delete base;
   base = nullptr;
   images.clear();
}

StickerSheet::~StickerSheet () {
    Clear();

}
StickerSheet::StickerSheet (const StickerSheet &other) {
    base = new Image(*other.base);
    coor = other.coor;
    max_ = other.max_;
    for (size_t i = 0; i < other.images.size(); i++) {
        if (other.images.at(i) == nullptr) {
           images.push_back(nullptr); 
        }
        else {
            Image* copy = other.images.at(i);
            images.push_back(copy);
        }
    }
}
const StickerSheet & StickerSheet:: operator= (const StickerSheet &other) {
    if (this != &other) {
       Clear();
       
       base = new Image(*other.base);
        coor = other.coor;
        max_ = other.max_;
        for (size_t i = 0; i < other.images.size(); i++) {
            if (other.images.at(i) == nullptr) {
            images.push_back(nullptr); 
            }
            else {
                //Image* copy = new Image(*(other.images.at(i)));
                Image* copy = other.images.at(i);
                images.push_back(copy);
            }
        }
    }
    return *this;

}
void StickerSheet::changeMaxStickers (unsigned max) {
   // std::cout << "entered change" << images.size() <<std::endl;
    if (max >= max_) {   
        for (size_t i = max_; i < max; i++) {
            images.push_back(nullptr);
            coor.push_back(std::make_pair(0,0));
        }
        max_ = max;
       // std::cout << "after" << images.size() <<std::endl;
        //std::cout << "new max is " << max_ <<std::endl;
        return;
    }
    else {
        for (size_t i = max ; i < images.size(); i++) {
           // delete images.at(i);
            images.at(i) = nullptr;
            // possible memory leak
            
            coor.at(i) = std::make_pair(0,0);

        }
    }
   

}
int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y) {
 
    if (images.size() > max_) {
        //std::cout << "added" << std::endl;
        return -1;
    }
    for (size_t i = 0; i < images.size(); i++) {
        if (images.at(i) == nullptr) {
            //std::cout << "i is " << i << std::endl;
            images.at(i) = &sticker;
            coor.at(i) = std::make_pair(x,y);
            //std::cout << "added" << std::endl;
            return i;
        } 

    }
     return -1;
     //std::cout << "added" << std::endl;

}
bool StickerSheet::translate (unsigned index, unsigned x, unsigned y) {
    if (index > max_ || images.at(index) == nullptr) {
        return false;
    }
    coor.at(index) = std::make_pair(x,y);
    return true;
}
 void StickerSheet::removeSticker (unsigned index) {
    // delete images.at(index);
     // possible memory leak 
     images.at(index) = nullptr;
   
 }
Image * StickerSheet::getSticker (unsigned index) {
    if (index > images.size()) {
        return nullptr;
    }
    else {
        return images.at(index);
    }

}
Image StickerSheet::render () const {
    //std::cout << "entered render" << std::endl;
    Image* current = base;
   //Image current = base;
    for (size_t i = 0; i < images.size(); i++) {
       // std::cout << images.size() << std::endl;
        if (images.at(i) == nullptr) {
                    continue;
        }

        if (images.at(i)->height() + coor.at(i).second > current->height() || images.at(i)->width() + coor.at(i).first > current->width()) {
            current->resize(std::max(current->width(), images.at(i)->width() + coor.at(i).first), std::max(current->height(), images.at(i)->height() + coor.at(i).second));
        }
        // size_t x = 0;
        // size_t y = 0;
       // std::cout << images.size() << std::endl;
        // for (size_t w = coor.at(i).first; w < coor.at(i).first + images.at(i)->width(); w++, x++) {
        //     for (size_t h = coor.at(i).second; h <  coor.at(i).second + images.at(i)->height(); h++, y++) {
                
        //         if (images.at(i)->getPixel(x,y).a != 0) {
        //             current->getPixel(w,h) = images.at(i)->getPixel(x, y);
                   
        //         }
                
        //     }
        // }
        for (size_t w = 0; w < images.at(i)->width(); w++) {
            for (size_t h = 0; h < images.at(i)->height(); h++) {
                if (images.at(i)->getPixel(w,h).a != 0) {
                    current->getPixel(w + coor.at(i).first, h + coor.at(i).second) = images.at(i)->getPixel(w,h);
                }
                
            }
        }
   }
   // std::cout << "done with render" << std::endl;
    return *current;
}


