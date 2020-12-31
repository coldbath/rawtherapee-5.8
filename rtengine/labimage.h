/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2010 Gabor Horvath <hgabor@rawtherapee.com>
 *
 *  RawTherapee is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  RawTherapee is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RawTherapee.  If not, see <https://www.gnu.org/licenses/>.
 */
#pragma once

#include <cstring>

#include "opencv2/opencv.hpp"

namespace rtengine
{

class LabImage
{
private:
    void allocLab(size_t w, size_t h);

public:
    int W, H;
    float * data;
    float** L;
    float** a;
    float** b;

    cv::Mat labImg;

    LabImage (int w, int h);
    ~LabImage ();

    //Copies image data in Img into this instance.
    void CopyFrom(LabImage *Img);
    void CopyFromMat(cv::Mat src);

    void getLabImg(cv::Mat &dst);

    void getPipetteData (float &L, float &a, float &b, int posX, int posY, int squareSize);
    void deleteLab();
    void reallocLab();
};

}
