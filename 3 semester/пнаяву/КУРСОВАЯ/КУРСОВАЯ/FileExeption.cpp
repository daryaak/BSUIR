#include "FileExeption.h"

//проверка файла
bool exist_file(string name_file)
{
    ifstream in_test(name_file, ios::in);
    try
    {
        if (!in_test)
            throw (FileExeption(1, "ошибка файла", "файл не существует"));
        if (!in_test.is_open())
            throw (FileExeption(3, "ошибка файла", "файл не открылся"));
    }
    catch (FileExeption obj)
    {
        cin.clear();
        obj.ShowError();
        return 0;
    }
    return true;
}
void FileExeption::ShowError()
{
    cout << "Код ошибки:" << Code << endl;
    cout << Type << endl;
    cout << Message << endl;
}