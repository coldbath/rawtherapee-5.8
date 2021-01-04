/*
 *  This file is part of RawTherapee.
 *
 *  Copyright (c) 2004-2017 Gabor Horvath <hgabor@rawtherapee.com>
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

#include <memory>

#include "labimage.h"

namespace rtengine
{

LabImage::LabImage (int w, int h) : W(w), H(h)
{
    allocLab(w, h);
}

LabImage::~LabImage ()
{
    deleteLab();
}

void LabImage::CopyFrom(LabImage *Img)
{
    memcpy(data, Img->data, W * H * 3 * sizeof(float));
}

void LabImage::CopyFromMat(cv::Mat src)
{
    // memcpy(data, src.data, W * H * 3 * sizeof(float));
    
    for (size_t i = 0; i < H; i++)
    {
        for (size_t j = 0; j < W; j++)
        {
            L[j][i] = src.at<cv::Vec3f>(j, i)[0];
            a[j][i] = src.at<cv::Vec3f>(j, i)[1];
            b[j][i] = src.at<cv::Vec3f>(j, i)[2];
        }
        
    }
    
}

void LabImage::loadLabImg(std::string filePath, int w, int h)
{
    FILE *fp;

    fp = fopen(filePath.c_str(), "rb");

    if(fp == NULL)
        return ;

    fread(data, 1, w * h * 3 * sizeof(float), fp);

    fclose(fp);
}

void LabImage::getLabImg(cv::Mat &dst)
{
    dst.create(H, W, CV_32FC3);
    dst.setTo(0);

    for(int j = 0; j < H; j++)
    {
        for(int i = 0; i < W; i++)
        {
            dst.at<cv::Vec3f>(j, i)[0] = L[j][i]; 
        }
    }

    for(int j = 0; j < H; j++)
    {
        for(int i = 0; i < W; i++)
        {
            dst.at<cv::Vec3f>(j, i)[1] = a[j][i];
        }
    }

    for(int j = 0; j < H; j++)
    {
        for(int i = 0; i < W; i++)
        {
            dst.at<cv::Vec3f>(j, i)[2] = b[j][i]; 
        }
    }
}

void LabImage::getPipetteData (float &v1, float &v2, float &v3, int posX, int posY, int squareSize)
{
    float accumulator_L = 0.f;
    float accumulator_a = 0.f;
    float accumulator_b = 0.f;
    unsigned long int n = 0;
    int halfSquare = squareSize / 2;

    for (int iy = posY - halfSquare; iy < posY - halfSquare + squareSize; ++iy) {
        for (int ix = posX - halfSquare; ix < posX - halfSquare + squareSize; ++ix) {
            if (ix >= 0 && iy >= 0 && ix < W && iy < H) {
                accumulator_L += L[iy][ix];
                accumulator_a += a[iy][ix];
                accumulator_b += b[iy][ix];
                ++n;
            }
        }
    }

    v1 = n ? accumulator_L / float(n) : 0.f;
    v2 = n ? accumulator_a / float(n) : 0.f;
    v3 = n ? accumulator_b / float(n) : 0.f;
}

void LabImage::allocLab(size_t w, size_t h)
{
    L = new float*[h];
    a = new float*[h];
    b = new float*[h];

    data = new float [w * h * 3];
    float * index = data;

    for (size_t i = 0; i < h; i++) {
        L[i] = index + i * w;
    }

    index += w * h;

    for (size_t i = 0; i < h; i++) {
        a[i] = index + i * w;
    }

    index += w * h;

    for (size_t i = 0; i < h; i++) {
        b[i] = index + i * w;
    }
}

void LabImage::deleteLab()
{
    delete [] L;
    delete [] a;
    delete [] b;
    delete [] data;
}

void LabImage::reallocLab()
{
    allocLab(W, H);
}

}
