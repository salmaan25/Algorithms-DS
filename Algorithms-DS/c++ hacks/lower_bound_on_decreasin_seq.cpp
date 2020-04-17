// For array sorted in non-increasing array, lower_bound() finds iterator to first element that does not compare greater than to given element. 
// upper_bound() finds iterator to first element that is smaller than given element. We use grater() for this purpose.
int main(void) {
	int unsorted[10] = { 3, 3, 2, 1, 5, 5, 4, 3, 7, 8 }; 
	std::vector<int> v(unsorted, unsorted + 10); 

    // sorting vector in non increasing order. Vector 
    // becomes {8, 7, 5, 5, 4, 3, 3, 3, 2, 1} 
	std::sort(v.begin(), v.end(), std::greater<int>()); 

	std::vector<int>::iterator low, up; 
	low = std::lower_bound(v.begin(), v.end(), 3, std::greater<int>());          
	up = std::upper_bound(v.begin(), v.end(), 5, std::greater<int>());
}