#include "hlab1.h"

int main()
{
	rewind(stdin);
	setlocale(LC_ALL, "ru");
	system("cls");
	int repeat;                                                //переменна€ дл€ зацикливани€ программы
	do
	{
		int size1, size2;
		cout << "¬ведите размер первого массива" << endl;
		cin >> size1;
		array1 arr1(size1);                                     //объ€вление первого массива
		cout << "¬ведите первый массив" << endl;           
		arr1.input();                                           //ввод первого массива
		cout << "ѕервый массив:" << endl;
		arr1.output();                                          //вывод первого массива

		cout << "¬ведите размер второго массива" << endl;
		cin >> size2;
		array1 arr2(size2);                                     //объ€вление второго массива
		cout << "¬ведите второй массив" << endl;
		arr2.input();                                           //ввод второго массива
		cout << "¬торой массив:" << endl;
		arr2.output();                                          //вывод второго массива
		cout << "–езультат объединени€ двух массивов" << endl;
		//array1 result = arr1.concatenation(arr2);               //объединение с помощью отдельного метода
		//array1 result = arr1 + arr2+ arr1 + arr2+ arr1 + arr2;                          //объединение с помощью перегрузки оператора

		arr1 + arr2;
		arr2.output();
		arr1 + arr2 + arr1;
		

		cout << "∆елаете продолжить?1-да" << endl;              //запрос на повтор программы
		cin >> repeat;
		if (repeat != 1)return 0;
	} while (repeat == 1);
}