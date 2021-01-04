#include "depurple.h"
#include "labimage.h"
#include "improccoordinator.h"
#include "imageio.h"
#include "image8.h"
#include "improcfun.h"

namespace rtengine
{
    void DAGE_DepurpleAPI(std::string filePath, std::string resultPath)
    {
        cv::Mat monitorRgb = cv::imread(filePath);

        cv::cvtColor(monitorRgb, monitorRgb, CV_BGR2RGB);

        LabImage*    laboCrop;
        Image8*      cropImg;

        int w = monitorRgb.cols;
        int h = monitorRgb.rows;

        laboCrop = new LabImage(w, h);
        cropImg = new Image8(w, h);

        //monitorRgb -> LabImage

        ImProcFunctions ipf;

        ipf.PF_correct_RT(laboCrop, 5, 1);

        ipf.lab2monitorRgb(laboCrop, cropImg);

        cropImg->saveAsJPEG (resultPath);

        delete laboCrop;
        delete cropImg;
    }
}

