//
// Created by paul on 10/05/15.
//

#include "ParallelIMU.h"

ParallelIMU::ParallelIMU() {

    //  Using RTIMULib here allows it to use the .ini file generated by RTIMULibDemo.
    //  Or, you can create the .ini in some other directory by using:
    //      RTIMUSettings *settings = new RTIMUSettings("<directory path>", "RTIMULib");
    //  where <directory path> is the path to where the .ini file is to be loaded/saved
    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
    printf("No IMU found\n");
    exit(1);
    }

    //  This is an opportunity to manually override any settings before the call IMUInit

    //  set up IMU
    imu->IMUInit();

    //  this is a convenient place to change fusion parameters
    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    imu->setAccelEnable(true);
    imu->setCompassEnable(true);

    std::thread tempThread(&ParallelIMU::startCapture, this);
    std::swap(tempThread, imuThread);

}

ParallelIMU::~ParallelIMU() {

}

double ParallelIMU::getRollDeg() {
    return imuData.fusionPose.x() * RTMATH_RAD_TO_DEGREE;
}

double ParallelIMU::getPitchDeg() {
    return imuData.fusionPose.y() * RTMATH_RAD_TO_DEGREE;;
}

double ParallelIMU::getYawDeg() {
    return imuData.fusionPose.z() * RTMATH_RAD_TO_DEGREE;
}

void ParallelIMU::startCapture() {
    //  now just process data
    while (1) {
        //  poll at the rate recommended by the IMU
        usleep(imu->IMUGetPollInterval() * 1000);

        while (imu->IMURead()) {
            imuData = imu->getIMUData();
        }
    }
}
