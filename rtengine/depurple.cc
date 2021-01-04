#include "depurple.h"
#include "labimage.h"
#include "improccoordinator.h"
#include "imageio.h"
#include "image8.h"
#include "improcfun.h"

namespace rtengine
{
    void rgb2LabImage(unsigned char *dst, LabImage *src, const double rgb_xyz[3][3])
    {

    }

    void DAGE_DepurpleAPI(std::string filePath, std::string resultPath)
    {
        cv::Mat monitorRgb = cv::imread(filePath);

        cv::cvtColor(monitorRgb, monitorRgb, CV_BGR2Lab);

        monitorRgb.convertTo(monitorRgb, CV_32FC3);

        LabImage*    laboCrop;
        Image8*      cropImg;

        int w = monitorRgb.cols;
        int h = monitorRgb.rows;

        laboCrop = new LabImage(w, h);
        cropImg = new Image8(w, h);

        //monitorRgb -> LabImage
        laboCrop->CopyFromMat(monitorRgb);

        ImProcFunctions ipf;

        ipf.PF_correct_RT(laboCrop, 5, 1);

        cv::Mat dst;

        laboCrop->getLabImg(dst);

        dst.convertTo(dst, CV_8UC3);
        cv::cvtColor(dst, dst, CV_Lab2BGR);

        cv::imwrite(resultPath, dst);

        delete laboCrop;
        delete cropImg;
    }
}

