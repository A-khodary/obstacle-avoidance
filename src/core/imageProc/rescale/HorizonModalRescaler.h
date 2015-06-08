//
// Created by paul on 23/05/15.
//

#ifndef OBSTACLE_AVOIDANCE_HORIZONMODALRESCALER_H
#define OBSTACLE_AVOIDANCE_HORIZONMODALRESCALER_H


#include <queue>

#include "geometry/Horizon.h"
#include "imageTypes/Image16bit.h"
#include "imageTypes/Image8bit.h"
#include "imageProc/histogram/ImageHistogram.h"
#include "imageProc/histogram/HorizonImageHistogram.h"
#include "EightBitWindowRescaler.h"
#include "ValueBuffer.h"

class HorizonModalRescaler : public EightBitWindowRescaler {

public:
    HorizonModalRescaler(int bufferSize = ValueBuffer::DEFAULT_BUFFER_SIZE);
    void scale16bitTo8bit(const Image16bit &src, const Horizon &horizon, Image8bit &dst);

protected:
    ValueBuffer valueBuffer;

};


#endif //OBSTACLE_AVOIDANCE_HORIZONMODALRESCALER_H
