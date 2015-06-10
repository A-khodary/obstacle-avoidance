//
// Created by paul on 07/06/15.
//

#include "ValueSmootherTest.h"

TEST_F(ValueSmootherTest, singleValue) {
    ValueSmoother v(1);
    EXPECT_EQ(10, v.calculateSmoothedValue(10));
}

TEST_F(ValueSmootherTest, underCapacity) {
    int bufferSize = 10;
    ValueSmoother v(bufferSize);

    int n, result;

    for (n = 1; n <= bufferSize; n++) {
        result = v.calculateSmoothedValue(n);
        EXPECT_EQ((n + 1) / 2, result);
    }
}

TEST_F(ValueSmootherTest, simpleSmoothing) {
    int bufferSize = 10;

    /*
     * We provide a few different contiguous test values
     *  to allow for the possibility that our tests could
     *  erroneously pass in spite of off-by-one errors
     *  because of rounding due to integer division.
     */
    ValueSmootherTest::testSimpleSmoothing(bufferSize, 100);
    ValueSmootherTest::testSimpleSmoothing(bufferSize, 99);
    ValueSmootherTest::testSimpleSmoothing(bufferSize, 98);
    ValueSmootherTest::testSimpleSmoothing(bufferSize, 97);

}

TEST_F(ValueSmootherTest, noSmoothing) {

    int bufferSize = 10;
    ValueSmoother v(bufferSize);

    int constantValue = 42;

    for (int i=0; i < bufferSize * 100; i++) {
        v.calculateSmoothedValue(constantValue);
    }

    EXPECT_EQ( constantValue, v.calculateSmoothedValue(constantValue));

}

void ValueSmootherTest::testSimpleSmoothing(int bufferSize, int outlier) {
    ValueSmoother v(bufferSize);

    int n;

    for (n = 1; n <= bufferSize; n++) {
        v.calculateSmoothedValue(n);
    }
    n--; // to counteract the last n++ of the for loop

    int result = v.calculateSmoothedValue(outlier);
    EXPECT_EQ( (int) ((float) (n + 1)/2 + (float) (outlier - 1)/n ), result);
}