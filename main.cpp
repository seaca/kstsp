#include "kstsp.h"
#include <stdio.h>



int main(void){
	int **candidates; // 解候補となる経路の配列
	int candNum;
	KsTSP kstsp(4);
	int left, right, mid, ansID;

	kstsp.PrintInfo();
	/*--------------
	   一番簡単な実装
	   -------------*/
	candNum = (1 << kstsp.GetCNum()) - 1;
	candidates = new int *[candNum];
	for (int i = 0; i < candNum; i++){
		candidates[i] = new int[kstsp.GetCNum()];
		for (int j = 0; j < kstsp.GetCNum(); j++){
			candidates[i][j] = (i + 1)&(1 << j) ? 1 : -1;
		}
	}
	/*一番単純な戦略メモ　(とりあえずこれを実装)
		巡る都市の組み合わせを全パターン列挙（順番は問わない）
		　↓
		価値順に降順ソート
		　↓
		価値の高い方からコスト以内で巡れるかチェック

		---問題点-----------------------------------------
		・候補の集合が大きすぎる
		　都市数Nのとき集合の大きさは
		    N
			Σ  nCk　=　2^N-1
		   k=1
		　になる
		 すなわち空間計算量がO(exp(n))
	*/
	// sort subsets
	// とりあえずバブル
	for (int i = candNum-1; i >= 0; i--){
		for (int j = 0; j < i; j++){
			if (kstsp.SumOfValue(candidates[j]) > kstsp.SumOfValue(candidates[j+1])){
				for (int k = 0; k < kstsp.GetCNum(); k++){
					int tmp;
					tmp = candidates[j][k];
					candidates[j][k] = candidates[j + 1][k];
					candidates[j + 1][k] = tmp;
				}
			}
		}
	}

	printf("--------------------------------------------------------\n");
	for (int i = 0; i < candNum; i++){
		printf("subset%02d : ", i);
		for (int j = 0; j < kstsp.GetCNum(); j++){
			printf("%+d, ", candidates[i][j]);
		}
		printf("val:%3d ", kstsp.SumOfValue(candidates[i]));
		printf("cost:%6.2f ", kstsp.CalcRouteCost(candidates[i]));
		printf("(%s)\n", kstsp.IsTravelable(candidates[i])?"OK":"NG");
	}
	printf("--------------------------------------------------------\n");
	// bin search
	// sorted by value ---regard---|> sorted by cost
	for (left = 0, right = candNum - 1;;){
		if (right - left == 1){
			ansID = kstsp.IsTravelable(candidates[right]) ? right : left;
			break;
		}
		else if (left == right){
			ansID = left;
			break;
		}
		else{
			mid = left + (right - left) / 2;
			if (kstsp.IsTravelable(candidates[mid])){
				left = mid;
			}
			else{
				right = mid - 1;
			}
		}
	}
	printf("answer : subset%02d\n", ansID);
	for (int i = 0; i < kstsp.GetCNum(); i++){
		printf("%+d, ", candidates[ansID][i]);
	}
	printf("%3d\n", kstsp.SumOfValue(candidates[ansID]));


	// wait to check
	{
		int i;
		scanf_s("%d", &i);
	}
	// post prosess
	for (int i = 0; i < candNum; i++){
		delete[] candidates[i];
	}
	delete[] candidates;
	return 0;
}

