/**
*
* Solution to course project # 7
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Mihail Dimitrov
* @idnumber 3MI0600472
* @compiler VC
*
* <file with util functions>
*
*/

bool compareStrings(const char* str1, const char* str2) {
	if (str1 == nullptr || str2 == nullptr)
	{
		return false;
	}

	while (*str1 != '\0') {
		if (*str1 != *str2)
		{
			return false;
		}
		str1++;
		str2++;
	}
	return *str2 == '\0';
}