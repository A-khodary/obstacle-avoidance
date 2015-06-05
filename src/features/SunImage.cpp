#include "SunImage.h"
#include "lepton/LeptonCameraDimensions.h"
#include <iostream>
#include <stack>

SunImage::SunImage(const Horizon &horizon, const cv::Mat &frame, unsigned int minSunPixelValue, int margin) : horizon(horizon), frame(frame), minSunPixelValue(minSunPixelValue), margin(margin) {
}

SunImage::~SunImage() {
}

void SunImage::findSun() {
    for (int row = 0; row < frame.rows; row++) {
        for (int col = 0; col < frame.cols; col++) {
            unsigned int value = frame.at<uint16_t>(row, col);
            //std::cout << "value is " << value << std::endl;

            if (value >= minSunPixelValue) {
            	if (row > sunBottom)
            		sunBottom = row;
            	else if (row < sunTop)
            		sunTop = row;
            	if (col < sunLeft)
            		sunLeft = col;
            	else if (col > sunRight)
            		sunRight = col;
            }
        }
    }
}

void SunImage::debugMessage() {
    std::cout << "sunBottom is " << sunBottom << std::endl;
    std::cout << "sunTop is " << sunTop << std::endl;
    std::cout << "sunLeft is " << sunLeft << std::endl;
    std::cout << "sunRight is " << sunRight << std::endl;
}

void SunImage::findSunColumn() {
    int offset = horizon.getHeightLeft();
    float y = static_cast<float>((horizon.getHeightRight() - horizon.getHeightLeft()));
    float x = VIEWPORT_WIDTH_PIX;
    float magnitude = pow((VIEWPORT_WIDTH_PIX*2 + y*2), 0.5);
    x = x / magnitude;
    y = y / magnitude;

    unsigned int totalPix;
    float mean = 0.0, variance = 0.0, totalSum = 0.0;
    std::stack<float> tempResults;

    //calculate dot product
    for (int row = 0; row < frame.rows; row++) {
        for (int col = 0; col < frame.cols; col++) {
            if (minSunPixelValue <= frame.at<uint16_t>(row, col)) {
                float tempValue = (row - offset) * x + col * y;
                totalSum += tempValue;
                tempResults.push(tempValue);
            }
        }
    }

    //calculate mean
    totalPix = tempResults.size();
    mean = totalSum / static_cast<float>(totalPix);
    std::cout << "totalSum is " << totalSum << std::endl;
    std::cout << "totalPix is " << totalPix << std::endl;
    std::cout << " mean is " << mean << std::endl;

    //calculate variance
    while (!tempResults.empty()) {
        float tempResult = static_cast<float>(tempResults.top());
        tempResults.pop();
        variance += pow((tempResult - mean), 2);
    }
    
    variance = variance/static_cast<float>(totalPix);
    std::cout << "variance is " << variance << std::endl;
}
