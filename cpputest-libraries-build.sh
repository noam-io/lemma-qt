#! /bin/sh
cd CppUTest
CC=/home/dariusz/opt/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf-gcc CXX=/home/dariusz/opt/gcc-4.7-linaro-rpi-gnueabihf/bin/arm-linux-gnueabihf-gcc CPPUTEST_LIB_DIR=arm/lib CPPUTEST_OBJS_DIR=arm/objs TEST_TARGET=arm/cpputest_test make
make

