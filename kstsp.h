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
	KsTSP(int n); // �s�s���������߂Ē��g�̓����_��
//	KsTSP(char *fname);
	~KsTSP();
	void PrintInfo();
	int GetCNum(){ return cityNum; }
	int GetCost(int c1, int c2);
	int SumOfValue(int isIncludedFlgAry[]); // �S�s�s�ɂ��� �܂܂��=1/�܂܂�Ȃ�=-1 �̔z��
	bool IsTravelable(int isIncludedFlgAry[]); // ����
	double CalcRouteCost(int *isIncludedFlgAry);
private:
	void FullsetToSublist(int *cityIdxList, int *isIncludedFlgAry, int *listSize); // 1or-1�̑S�̏W�����畔���s�s�̔z���
	void SetCostTbl(); // �Ƃ肠�������͓s�s�Ԃ̃��[�N���b�h�����Ƃ���
	int GetTblID(int c1, int c2);
};

#endif