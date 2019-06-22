#include <iostream>
#include "runTEST.h"
#include "../lib/gtest/gtest.h"
int runTest(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}