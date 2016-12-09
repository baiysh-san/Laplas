#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv.h>
using namespace cv;
using namespace std;
/*Реализуйте маску Лапласа 3X3 [1  1  1 ;  1  -8  1 ; 1  1  1]  с=-1
 * 1)По пиксельно
 * 2) Готовыми функциями OpenCV.
 * Перевести изображение 8 битный монохром*/


void myLaplas(const Mat& myImage, Mat& Result)//Моя функция
{
    CV_Assert(myImage.depth() == CV_8U);

    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    for(int j = 1; j < myImage.rows - 1; ++j)
    {
        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current  = myImage.ptr<uchar>(j    );
        const uchar* next     = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j);

        for(int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
            *output++ = saturate_cast<uchar>(-8 * current[i]
                                             +current[i - nChannels] + current[i + nChannels] + previous[i] + next[i]+
                                             previous[i+nChannels]+previous[i-nChannels]+next[i+nChannels]+next[i-nChannels]);
        }
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
}


int main() {
    Mat src;
    src = imread("/home/baiysh/ClionProjects/Laplas/lena.jpg",CV_8U);
    imshow("lena_8bit",src);
    Mat out;
    Laplacian( src, out, CV_8U,3,1,0,BORDER_DEFAULT);// Готовая функция OpenCV
    imshow("openCv",out);
    myLaplas(src,out);// моя функция
    imshow("My_Laplas",out);
    waitKey(0);
    return(0);
}