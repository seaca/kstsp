#ifndef KSTSPH
#define KsTSPH

#include "city.h"
#define ENDOFROUTE -1

#define XXX 0

class KsTSP{
private:
	int cityNum;
	City *cities;
	int costLmt;
	double *costTable;
public:
	KsTSP(){}
	KsTSP(int n); // 都市数だけ決めて中身はランダム
//	KsTSP(char *fname);
	~KsTSP();
	void PrintInfo();
	int GetCNum(){ return cityNum; }
	int GetCost(int c1, int c2);
	int SumOfValue(int isIncludedFlgAry[]); // 全都市について 含まれる=1/含まれない=-1 の配列
	bool IsTravelable(int isIncludedFlgAry[]); // 同上
	double CalcRouteCost(int *isIncludedFlgAry);
private:
	void FullsetToSublist(int *cityIdxList, int *isIncludedFlgAry, int *listSize); // 1or-1の全体集合から部分都市の配列へ
	void SetCostTbl(); // とりあえず今は都市間のユークリッド距離とする
	int GetTblID(int c1, int c2);
};

#endif