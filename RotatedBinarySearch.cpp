
#include <vector>

int RotatedBinarySearch(std::vector<int>& arr, int low, int high, int target)
{
	if (high < low)
		return -1;

	int mid = low + (high - low) / 2;

	if (arr[mid] == target)
		return mid;

	//if first half is sorted
	if (arr[low] <= arr[mid])
	{
		if (target >= arr[low] && target <= arr[mid])
		{
			return RotatedBinarySearch(arr, low, mid - 1, target);
		}
		else //in upper half
		{
			return RotatedBinarySearch(arr, mid + 1, high, target);
		}


	}


	if (target >= arr[mid] && target <= arr[high])
	{
		return RotatedBinarySearch(arr, mid + 1, high, target);
	}

	return RotatedBinarySearch(arr, low, mid - 1, target);
}

int main(void)
{


}