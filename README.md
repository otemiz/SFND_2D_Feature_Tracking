# SFND 2D Feature Tracking

<img src="images/keypoints.png" width="820" height="248" />

The idea of the camera course is to build a collision detection system - that's the overall goal for the Final Project. As a preparation for this, you will now build the feature tracking part and test various detector / descriptor combinations to see which ones perform best. This mid-term project consists of four parts:

* First, you will focus on loading images, setting up data structures and putting everything into a ring buffer to optimize memory load. 
* Then, you will integrate several keypoint detectors such as HARRIS, FAST, BRISK and SIFT and compare them with regard to number of keypoints and speed. 
* In the next part, you will then focus on descriptor extraction and matching using brute force and also the FLANN approach we discussed in the previous lesson. 
* In the last part, once the code framework is complete, you will test the various algorithms in different combinations and compare them with regard to some performance measures. 

See the classroom instruction and code comments for more details on each of these parts. Once you are finished with this project, the keypoint matching part will be set up and you can proceed to the next lesson, where the focus is on integrating Lidar points and on object detection using deep-learning. 

## Performance Evaluation

### Detector Comparison - Task 7

In the following table number of detected keypoints on the preceding vehicle is compared

| Detector | Total Keypoints |
|:---:|:----:|
| AKAZE | 1655 |
|:---:|:----:|
| BRISK | 2713 |
|:---:|:----:|
| FAST | 4094 |
|:---:|:----:|
| HARRIS | 560 |
|:---:|:----:|
| ORB | 1150 |
|:---:|:----:|
| SIFT | 1371 |
|:---:|:----:|
| SHITOMASI | 1491 |
|:---:|:----:|

### Overall System Comparison - Task 8,9

For this task an bash script is adapted to my code for parametric simulation. And it creates the following table. Some combinations are not available therefore they are removed manually.

For fair comparison same match selection is used. The used algorithm is KNN match selection with ratio filtering set to 0.8.

********************1********************

SHITOMASI-BRISK-DES_BINARY-0-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SHITOMASI + BRISK |1491 |899 |392.902 |0.00022881 |

********************2********************


SHITOMASI-BRIEF-DES_BINARY-0-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SHITOMASI + BRIEF |1491 |1099 |3.13827 |0.0350193 |

********************3********************


SHITOMASI-ORB-DES_BINARY-0-2.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SHITOMASI + ORB |1491 |1071 |3.02653 |0.035387 |

********************4********************


SHITOMASI-FREAK-DES_BINARY-0-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SHITOMASI + FREAK |1491 |878 |50.9257 |0.00172408 |

********************5********************


HARRIS-BRISK-DES_BINARY-1-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| HARRIS + BRISK |560 |393 |447.746 |8.77729e-05 |

********************6********************


HARRIS-BRIEF-DES_BINARY-1-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| HARRIS + BRIEF |560 |460 |18.1841 |0.00252968 |

********************7********************


HARRIS-ORB-DES_BINARY-1-2.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| HARRIS + ORB |560 |451 |18.6401 |0.00241952 |

********************8********************


HARRIS-FREAK-DES_BINARY-1-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| HARRIS + FREAK |560 |396 |58.5679 |0.000676138 |

********************9********************


FAST-BRISK-DES_BINARY-2-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| FAST + BRISK |4094 |2183 |395.157 |0.000552438 |

********************10********************


FAST-BRIEF-DES_BINARY-2-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| FAST + BRIEF |4094 |2831 |8.87619 |0.0318943 |

********************11********************


FAST-ORB-DES_BINARY-2-2.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| FAST + ORB |4094 |2768 |8.258 |0.033519 |

********************12********************


FAST-FREAK-DES_BINARY-2-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| FAST + FREAK |4094 |2233 |56.7426 |0.00393531 |

********************13********************


BRISK-BRISK-DES_BINARY-3-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| BRISK + BRISK |2713 |1544 |823.66 |0.000187456 |

********************14********************


BRISK-BRIEF-DES_BINARY-3-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| BRISK + BRIEF |2713 |1675 |435.591 |0.000384535 |

********************15********************


BRISK-ORB-DES_BINARY-3-2.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| BRISK + ORB |2713 |1479 |438.817 |0.000337043 |

********************16********************


BRISK-FREAK-DES_BINARY-3-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| BRISK + FREAK |2713 |1495 |482.24 |0.000310012 |

********************17********************


ORB-BRISK-DES_BINARY-4-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| ORB + BRISK |1150 |744 |394.873 |0.000188415 |

********************18********************


ORB-BRIEF-DES_BINARY-4-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| ORB + BRIEF |1150 |540 |9.35322 |0.00577341 |

********************19********************


ORB-ORB-DES_BINARY-4-2.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| ORB + ORB |1150 |755 |13.4672 |0.00560621 |

********************20********************


ORB-FREAK-DES_BINARY-4-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| ORB + FREAK |1150 |416 |54.9768 |0.000756683 |

********************21********************


AKAZE-BRISK-DES_BINARY-5-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| AKAZE + BRISK |1655 |1204 |500.112 |0.000240746 |

********************22********************


AKAZE-BRIEF-DES_BINARY-5-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| AKAZE + BRIEF |1655 |1257 |113.247 |0.00110996 |

********************23********************


AKAZE-ORB-DES_BINARY-5-2.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| AKAZE + ORB |1655 |1175 |119.215 |0.000985616 |

********************24********************


AKAZE-FREAK-DES_BINARY-5-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| AKAZE + FREAK |1655 |1179 |159.382 |0.000739732 |

********************25********************


AKAZE-AKAZE-DES_BINARY-5-4.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| AKAZE + AKAZE |1655 |1249 |202.68 |0.000616243 |

********************26********************


SIFT-BRISK-DES_BINARY-6-0.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SIFT + BRISK |1371 |586 |536.119 |0.000109304 |

********************27********************


SIFT-BRIEF-DES_BINARY-6-1.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SIFT + BRIEF |1371 |693 |164.235 |0.000421956 |

********************28********************


SIFT-FREAK-DES_BINARY-6-3.txt

| Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:----:|:-----:|:-----:|:-----:|
| SIFT + FREAK |1371 |588 |207.167 |0.000283829 |

## Chosen detector/ descriptor pairs

When we evaluate the feature detection algorithms only, the FAST algorithm comes at top by finding most keypoints in least time. And this result continues when we compare all combinations as well. 

Focusing on the descriptors we can see that BRIEF and ORB are very close. BRIEF is able to match more features at the cost of computation time. And when we compare the unit time for matches FAST + ORB combination comes at top.

Therefore my preference as follows:

|Sr. No. | Detector + Descriptor |Total Keypoints |Total Matches |Average Time (ms) |Matches/Time) |
|:---:|:---:|:----:|:-----:|:-----:|:-----:|
|1 | FAST + ORB |4094 |2768 |8.258 |0.033519 |
|2 | FAST + BRIEF |4094 |2831 |8.87619 |0.0318943 |
|3 | FAST + BRISK |4094 |2183 |395.157 |0.000552438 |




## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* OpenCV >= 4.1
  * This must be compiled from source using the `-D OPENCV_ENABLE_NONFREE=ON` cmake flag for testing the SIFT and SURF detectors.
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./2D_feature_tracking`.