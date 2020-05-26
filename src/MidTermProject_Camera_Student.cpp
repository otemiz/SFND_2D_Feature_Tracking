/* INCLUDES FOR THIS PROJECT */
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <limits>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/xfeatures2d.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

#include "dataStructures.h"
#include "matching2D.hpp"

//using namespace std;

/* MAIN PROGRAM */
int main(int argc, const char *argv[])
{

    /* INIT VARIABLES AND DATA STRUCTURES */

    // data location
    std::string dataPath = "../";

    // camera
    std::string imgBasePath = dataPath + "images/";
    std::string imgPrefix = "KITTI/2011_09_26/image_00/data/000000"; // left camera, color
    std::string imgFileType = ".png";
    int imgStartIndex = 0; // first file index to load (assumes Lidar and camera names have identical naming convention)
    int imgEndIndex = 9;   // last file index to load
    int imgFillWidth = 4;  // no. of digits which make up the file index (e.g. img-0001.png)

    // misc
    int dataBufferSize = 2;       // no. of images which are held in memory (ring buffer) at the same time
    std::vector<DataFrame> dataBuffer; // list of data frames which are held in memory at the same time
    bool bVis = false;            // visualize results
  	double totalmatches;
  	double totalkeypoints;
  	double averagetime;
    std::string detectorType = "SHITOMASI "; // HARRIS, FAST, BRISK, ORB, AKAZE, SIFT
  	std::string descriptorType = "FREAK"; // BRIEF, ORB, FREAK, AKAZE, SIFT
  	std::string descriptorType4match = "DES_BINARY"; // DES_BINARY, DES_HOG
  	std::string matcherType = "MAT_BF";        // MAT_BF, MAT_FLANN
    std::string selectorType = "SEL_KNN";       // SEL_NN, SEL_KNN


    /* MAIN LOOP OVER ALL IMAGES */

    for (size_t imgIndex = 0; imgIndex <= imgEndIndex - imgStartIndex; imgIndex++)
    {
        /* LOAD IMAGE INTO BUFFER */

        // assemble filenames for current index
        std::ostringstream imgNumber;
        imgNumber << std::setfill('0') << std::setw(imgFillWidth) << imgStartIndex + imgIndex;
        std::string imgFullFilename = imgBasePath + imgPrefix + imgNumber.str() + imgFileType;

        // load image from file and convert to grayscale
        cv::Mat img, imgGray;
        img = cv::imread(imgFullFilename);
        cv::cvtColor(img, imgGray, cv::COLOR_BGR2GRAY);

        //// STUDENT ASSIGNMENT
        //// TASK MP.1 -> replace the following code with ring buffer of size dataBufferSize

        // push image into data frame buffer
        DataFrame frame;
        frame.cameraImg = imgGray;
        dataBuffer.push_back(frame);
        if (dataBuffer.size() > dataBufferSize)
        {
            dataBuffer.erase(dataBuffer.begin());
        }

        //// EOF STUDENT ASSIGNMENT

        /* DETECT IMAGE KEYPOINTS */

        // extract 2D keypoints from current image
        std::vector<cv::KeyPoint> initialkeypoints; // create empty feature list for current image

        //// STUDENT ASSIGNMENT
        //// TASK MP.2 -> add the following keypoint detectors in file matching2D.cpp and enable string-based selection based on detectorType
        //// 
      	double cycletime = (double)cv::getTickCount();
      
        if (detectorType.compare("SHITOMASI") == 0)
        {
            detKeypointsShiTomasi(initialkeypoints, imgGray, false);
        }
        else if (detectorType.compare("HARRIS") == 0)
        {
            detKeypointsHarris(initialkeypoints, imgGray, false);
        }
        else
        {
            detKeypointsModern(initialkeypoints, imgGray, detectorType, false);
        }

        //// STUDENT ASSIGNMENT
        //// TASK MP.3 -> only keep keypoints on the preceding vehicle

        // only keep keypoints on the preceding vehicle
        bool bFocusOnVehicle = true;
        cv::Rect vehicleRect(535, 180, 180, 150);
      	std::vector<cv::KeyPoint> keypoints;
        if (bFocusOnVehicle)
        {
            for (auto it = initialkeypoints.begin(); it != initialkeypoints.end(); ++it)
            {
                cv::Rect keypointRect(it->pt.x, it->pt.y, 1, 1);
                bool intersects = ((vehicleRect & keypointRect).area() > 0);
                if (intersects == true)
                {
                    keypoints.push_back(*it);
                }
            }
        }
      	totalkeypoints += keypoints.size();
        //cout << "Resulting number of keypoints = " << keypoints.size() << endl;

        //// EOF STUDENT ASSIGNMENT

        // optional : limit number of keypoints (helpful for debugging and learning)
        bool bLimitKpts = false;
        if (bLimitKpts)
        {
            int maxKeypoints = 50;

            if (detectorType.compare("SHITOMASI") == 0)
            { // there is no response info, so keep the first 50 as they are sorted in descending quality order
                keypoints.erase(keypoints.begin() + maxKeypoints, keypoints.end());
            }
            cv::KeyPointsFilter::retainBest(keypoints, maxKeypoints);
        }

        // push keypoints and descriptor for current frame to end of data buffer
        (dataBuffer.end() - 1)->keypoints = keypoints;

        /* EXTRACT KEYPOINT DESCRIPTORS */

        //// STUDENT ASSIGNMENT
        //// TASK MP.4 -> add the following descriptors in file matching2D.cpp and enable string-based selection based on descriptorType
        //// -> BRIEF, ORB, FREAK, AKAZE, SIFT
        cv::Mat descriptors;
        descKeypoints((dataBuffer.end() - 1)->keypoints, (dataBuffer.end() - 1)->cameraImg, descriptors, descriptorType);
        //// EOF STUDENT ASSIGNMENT

        // push descriptors for current frame to end of data buffer
        (dataBuffer.end() - 1)->descriptors = descriptors;

        if (dataBuffer.size() > 1) // wait until at least two images have been processed
        {
            /* MATCH KEYPOINT DESCRIPTORS */
            std::vector<cv::DMatch> matches;

            //// STUDENT ASSIGNMENT
            //// TASK MP.5 -> add FLANN matching in file matching2D.cpp
            //// TASK MP.6 -> add KNN match selection and perform descriptor distance ratio filtering with t=0.8 in file matching2D.cpp
            matchDescriptors((dataBuffer.end() - 2)->keypoints, (dataBuffer.end() - 1)->keypoints,
                             (dataBuffer.end() - 2)->descriptors, (dataBuffer.end() - 1)->descriptors,
                             matches, descriptorType4match, matcherType, selectorType);
          
          	//cout << "Number of matches are: " << matches.size() << endl;
          	totalmatches += matches.size();

            //// EOF STUDENT ASSIGNMENT

            // store matches in current data frame
            (dataBuffer.end() - 1)->kptMatches = matches;

            // visualize matches between current and previous image
            bVis = false;
            if (bVis)
            {
                cv::Mat matchImg = ((dataBuffer.end() - 1)->cameraImg).clone();
                cv::drawMatches((dataBuffer.end() - 2)->cameraImg, (dataBuffer.end() - 2)->keypoints,
                                (dataBuffer.end() - 1)->cameraImg, (dataBuffer.end() - 1)->keypoints,
                                matches, matchImg,
                                cv::Scalar::all(-1), cv::Scalar::all(-1),
                                std::vector<char>(), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

                std::string windowName = "Matching keypoints between two camera images";
                cv::namedWindow(windowName, 7);
                cv::imshow(windowName, matchImg);
                //cout << "Press key to continue to next image" << endl;
                //cv::waitKey(0); // wait for key to be pressed
            }
            bVis = false;
        }
      cycletime = 1000 * ((double)cv::getTickCount() - cycletime) / cv::getTickFrequency();
      averagetime += cycletime/10;
    } // eof loop over all images

  	std::cout << "| Detector + Descriptor |" << "Total Keypoints |" << "Total Matches |" << "Average Time (ms) |" << "Matches/Time) |" << "\n";
    std::cout << "|:---:|:----:|:-----:|:-----:|:-----:|\n";
    std::cout << "| " << detectorType << " + " << descriptorType << " |" << totalkeypoints << " |" << totalmatches << " |" << averagetime << " |" << totalmatches / (averagetime * 10000.0) << " |"<< "\n";
    return 0;
}
