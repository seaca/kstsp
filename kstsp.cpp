#include "kstsp.h"
#include <math.h>
#include <time.h>
#include <stdio.h>


KsTSP::KsTSP(int n){
	init_genrand((unsigned)time(NULL));
	this->cityNum = n;
	this->cities = new City[n];
	this->costLmt = genrand_real1()*100*n/2;
	this->costTable = new double[n*(n + 1) / 2];
	SetCostTbl();
}

KsTSP::~KsTSP(){
	if (cities){
		delete[] cities; cities = 0;
	}
	if (costTable){
		delete[] costTable;
		costTable = 0;
	}
}

void KsTSP::PrintInfo(){
	printf("---info-------------------\n");
	printf("cityNum:%d\n", this->cityNum);
	printf("cost limit: %d\n", this->costLmt);
	for (int i = 0; i < cityNum; i++){
		printf("x:%3d  y:%3d  val:%3d\n", cities[i].GetX(), cities[i].GetY(), cities[i].GetVal());
	}
	printf("--------------------------\n");
}
int KsTSP::GetTblID(int c1, int c2){
	return cityNum*c1 - c1*(c1 - 1) / 2 + (c2 - c1);
}

int KsTSP::GetCost(int c1, int c2){

	return c1==c2 ? 0 : c1 < c2 ? costTable[GetTblID(c1, c2)] : costTable[GetTblID(c2, c1)];
}

void KsTSP::SetCostTbl(){
	double dx, dy, cost;
	int idx;
	for (int j = 0; j < this->cityNum; j++){
		for (int i = 0; i <= j; i++){
			dx = cities[i].GetX() - cities[j].GetX();
			dy = cities[i].GetY() - cities[j].GetY();
			idx = GetTblID(i, j);
			cost = sqrt(dx*dx + dy*dy);
			costTable[idx] = cost;
		}
	}
}

int KsTSP::SumOfValue(int isIncludedFlgAry[]){
	int sov=0;

	for (int i = 0; i < cityNum; i++){
		if (isIncludedFlgAry[i] != -1) sov += cities[i].GetVal();
	}
	return sov;
}

bool KsTSP::IsTravelable(int isIncludedFlgAry[]){
	return CalcRouteCost(isIncludedFlgAry) < this->costLmt;
}

void KsTSP::FullsetToSublist(int *cityIdxList, int *isIncludedFlgAry, int *listSize){
	int i;

	for (i = 0, *listSize = 0; i < this->cityNum; i++){
		if (isIncludedFlgAry[i] != -1){
			cityIdxList[(*listSize)++] = i;
		}
	}

}

double KsTSP::CalcRouteCost(int *isIncludedFlgAry){
	double cost = 0;
	int *cityIdxList; // ルートに含まれる都市だけを抜き出した配列
	int cities = 0;

	cityIdxList = new int[this->cityNum];
	FullsetToSublist(cityIdxList, isIncludedFlgAry, &cities);
	// 都市数によってはTSPの求解が省略できる
	switch (cities){
	case 0: case 1:
		// そもそもコストが0
		cost = 0;
		break;
	case 2:
		// 総コストは2点間のコストの往復分
		cost = this->GetCost(cityIdxList[0], cityIdxList[1]) * 2;
		break;
	case 3:
		// 都市数が3なら経路は1通りなのでTSPを解く必要はない
		cost = this->GetCost(cityIdxList[0], cityIdxList[1]);
		cost += this->GetCost(cityIdxList[1], cityIdxList[2]);
		cost += this->GetCost(cityIdxList[2], cityIdxList[0]);
		break;
	default:
		// それ以上ならTSPを解く(とりあえず面倒だから常にfalseになるようにしておく)
		cost = 999.99;
	}
	return cost;

}