#include "kstsp.h"
#include <stdio.h>



int main(void){
	int **candidates; // �����ƂȂ�o�H�̔z��
	int candNum;
	KsTSP kstsp(4);
	int left, right, mid, ansID;

	kstsp.PrintInfo();
	/*--------------
	   ��ԊȒP�Ȏ���
	   -------------*/
	candNum = (1 << kstsp.GetCNum()) - 1;
	candidates = new int *[candNum];
	for (int i = 0; i < candNum; i++){
		candidates[i] = new int[kstsp.GetCNum()];
		for (int j = 0; j < kstsp.GetCNum(); j++){
			candidates[i][j] = (i + 1)&(1 << j) ? 1 : -1;
		}
	}
	/*��ԒP���Ȑ헪�����@(�Ƃ肠�������������)
		����s�s�̑g�ݍ��킹��S�p�^�[���񋓁i���Ԃ͖��Ȃ��j
		�@��
		���l���ɍ~���\�[�g
		�@��
		���l�̍���������R�X�g�ȓ��ŏ���邩�`�F�b�N

		---���_-----------------------------------------
		�E���̏W�����傫������
		�@�s�s��N�̂Ƃ��W���̑傫����
		    N
			��  nCk�@=�@2^N-1
		   k=1
		�@�ɂȂ�
		 ���Ȃ킿��Ԍv�Z�ʂ�O(exp(n))
	*/
	// sort subsets
	// �Ƃ肠�����o�u��
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

