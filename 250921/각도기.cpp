#include "pch.h"

//¿¹°¢(çåÊÇ) : Acute angle(0µµº¸´Ù Å©°í 90µµº¸´Ù ÀÛÀº °¢)
//Á÷°¢(òÁÊÇ) : Right angle(90µµÀÇ °¢)
//µÐ°¢(ÔïÊÇ) : Obtuse angle(90µµº¸´Ù Å©°í 180µµº¸´Ù ÀÛÀº °¢)
//Æò°¢(øÁÊÇ) : Straight angle(180µµÀÇ °¢)

#define AC_ANGLE 1
#define RI_ANGLE 2
#define OB_ANGLE 3
#define ST_ANGLE 4

int Solution(int angle)
{
	if (angle == 180)
		return ST_ANGLE;
	else if ((angle > 90) && (angle < 180))
		return OB_ANGLE;
	else if (angle == 90)
		return RI_ANGLE;
	else if ((angle > 0) && (angle < 90))
		return AC_ANGLE;
}


int main()
{
	cout << Solution(70);
	return 0;
}