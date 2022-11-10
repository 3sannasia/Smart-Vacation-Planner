/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <iostream>
#include <vector>
namespace cs225 {
    class StickerSheet{
        public:
        StickerSheet (const Image &picture, unsigned max);
        void Clear();
        ~StickerSheet ();
        StickerSheet (const StickerSheet &other);
        const StickerSheet & 	operator= (const StickerSheet &other);
        void changeMaxStickers (unsigned max);
        int addSticker (Image &sticker, unsigned x, unsigned y);
        bool translate (unsigned index, unsigned x, unsigned y);
        void 	removeSticker (unsigned index);
        Image * 	getSticker (unsigned index);
        Image 	render () const;
        //Image drawer (Image* &current, Image* to_add);

        private:
        Image* base;
        std::vector<Image*> images;
        size_t max_;
        std::vector<std::pair<int, int>> coor;
    
    };

};