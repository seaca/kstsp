#ifndef CITYH
#define CITYH

#include "mt19937ar.h"

class City{
private:
	int x;
	int y;
	int val;
public:
	City(){ x = genrand_int32()%100; y = genrand_int32()%100; val = genrand_int32()%100; }
	City(int inX, int inY, int inVal){
		x = inX; y = inY; val = inVal;
	}
	int GetX(){	return x; }
	int GetY(){ return y; }
	int GetVal(){ return val; }
};

#endif