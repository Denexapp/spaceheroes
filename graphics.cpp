#include "stdafx.h"
#include "graphics.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#define RAND_MAX 255;

int graphics::GetRandomNumber() {
	return std::rand();
}