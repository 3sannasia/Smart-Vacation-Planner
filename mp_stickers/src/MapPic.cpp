#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <cmath>


    void Image::lighten () {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                if (!(getPixel(w,h).l + 0.1 > 1)) {
                    getPixel(w,h).l =  getPixel(w,h).l + 0.1;
                } 
                else {
                    getPixel(w,h).l = 1;
                }
                
            }
        }
    }
    void Image::lighten (double amount) {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                if (!(getPixel(w,h).l + amount  > 1)) {
                    getPixel(w,h).l =  getPixel(w,h).l + 0.1;
                } 
                else {
                    getPixel(w,h).l = 1;
                } 
            }
        }
    }

    void Image::darken() {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
              
                // get pixel at coordinate
                // HSLAPixel& p = getPixel(w,h); 
                // p.l = p.l + amount;
                // change pixel
                if (!(getPixel(w,h).l - 0.1 < 0)) {
                    getPixel(w,h).l =  getPixel(w,h).l - 0.1;
                } 
                else {
                    getPixel(w,h).l =  0;
                }
            
            }
        }
    }

    void Image::darken(double amount) {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
              
    
                if (!(getPixel(w,h).l - amount < 0)) {
                    getPixel(w,h).l =  getPixel(w,h).l - amount;
                } 
                else {
                    getPixel(w,h).l =  0;
                }
            
            }
        }
    }
    void Image::saturate() {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                // get pixel at coordinate
                // HSLAPixel& p = getPixel(w,h); 
                // p.s = p.s + 0.1;
                getPixel(w,h).s =  getPixel(w,h).s + 0.1;
                // change pixel
            }
        }
    }

    void Image::saturate(double amount) {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                // get pixel at coordinate
                // HSLAPixel& p = getPixel(w,h); 
                // p.s = p.s + amount;
                getPixel(w,h).s =  getPixel(w,h).s + amount;
                // change pixel
            }
        }
    }

    void Image::rotateColor(double degrees) {
        if (degrees >= 0) {
            for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {  
                if ((getPixel(w,h).h + degrees) < 360) {
                    getPixel(w,h).h =  getPixel(w,h).h + degrees;
                }  
                else {
                    int s = (degrees)/360;
                    int rotate_by = degrees - (360*s);
                    getPixel(w,h).h = rotate_by - (360 - getPixel(w,h).h);
                }

            }
        }
        }
        else if (degrees < 0){
            std::cout << "degrees is" << degrees << std::endl;
            std::cout << "current hue is" << getPixel(0,0).h << std::endl;
            //std::cout << "here"<< std::endl;
            for (unsigned int w = 0; w < width(); w++) {
                for (unsigned int h = 0; h < height(); h++) {
                   if ((getPixel(w,h).h + degrees) < 360) {
                        getPixel(w,h).h = getPixel(w,h).h + degrees + 360;
                    
                    }  
                    else {
                        getPixel(w,h).h = getPixel(w,h).h + degrees;
                    } 
                    
                    
                }

            }
        }
    }
        
    

    void Image::grayscale () {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                // get pixel at coordinate
                // HSLAPixel& p = getPixel(w,h); 
                // p.s = 0;
                getPixel(w,h).s =  0;
                // change pixel
            }
        }
    }

    void Image::scale(double factor) { // - works 
    std::cout << "og w and h" << width() << "  " << height();
        double new_width = width() * factor;
        double new_height = height() * factor;
        Image* temp = new Image(*this);
        this->resize(new_width, new_height);
    
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
               // temp->getPixel(w,h) = getPixel((w*factor), (h*factor));
               this->getPixel(w,h) = temp->getPixel((w/factor), (h/factor));
            }
        }

        delete temp;
    }
    //this
    void Image::scale(unsigned w,unsigned h ) {
       float factor = std::min((float)w/width(),(float) h/height());
       scale(factor);
        //std::cout << "factor is " << factor << "  " << height();
    }

    void Image::desaturate() {
         for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                // get pixel at coordinate
                // HSLAPixel& p = getPixel(w,h); 
                // p.s = p.s + amount;
                getPixel(w,h).s =  getPixel(w,h).s - 0.1;
                // change pixel
            }
        }
    }
    void Image::desaturate(double amount) {
         for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                // get pixel at coordinate
                // HSLAPixel& p = getPixel(w,h); 
                // p.s = p.s + amount;
                getPixel(w,h).s =  getPixel(w,h).s - amount;
                // change pixel
            }
        }
    }

    void Image::illinify () {
        for (unsigned int w = 0; w < width(); w++) {
            for (unsigned int h = 0; h < height(); h++) {
                
                if (getPixel(w,h).h >= 11 &&  getPixel(w,h).h <= 102.5) {
                    getPixel(w,h).h = 11; 
                } 
                else if (getPixel(w,h).h <= 216 &&  getPixel(w,h).h > 102.5) {
                    getPixel(w,h).h = 216; 
                }
                else if (getPixel(w,h).h > 216 &&  getPixel(w,h).h < 293.5) {
                    getPixel(w,h).h = 216; 
                }
                else {
                    getPixel(w,h).h = 11;
                }
                
            }
        }
    }



