#include <vector>
#include <string>
#include <algorithm>
#include <numeric>

int bitwiseComplement(int N) {

	if (N == 0)
		return 1;

	int all_ones = 0;

	for (int i = 0; all_ones < N; ++i)
	{
		all_ones += std::pow(2, i);
	}

	return all_ones ^ N;
}

int largestSumAfterKNegations(std::vector<int>& A, int K) {
	std::sort(A.begin(), A.end());

	int index = 0;
	while (K > 0 && index < A.size())
	{
		if (A[index] < 0)
		{
			A[index] *= -1;
			++index;
			--K;
		}
		else
		{
			break;
		}
	}

	if (K == 0 || std::find(A.begin(), A.end(), 0) != A.end())
	{
	}
	else
	{
		K %= 2;
		if (K == 1 && index < A.size())
		{
			if (index > 0)
			{
				bool top = A[index] > A[index - 1];
				if (top)
				{
					A[index - 1] *= -1;
				}
				else
				{
					A[index] *= -1;
				}
			}
			else
			{
				A[index] *= -1;
			}
		}
		else if (K == 1)
		{
			A[0] *= -1;
		}

	}

	return std::accumulate(A.begin(), A.end(), 0);
}

int main(void)
{
	std::vector<int> t{ -8,-5,-5,-3,-2,3 };
	int z = largestSumAfterKNegations(t, 6);
	return 0;
}