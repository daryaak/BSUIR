#include "FileExeption.h"

bool check_file(string name_file)
{
    ifstream filee(name_file, ios::in);
    try
    {
        if (!filee)
            throw (FileExeption(1, "Ошибка открытия файла", "Данного файла не существует"));
        if (!filee.is_open())
            throw (FileExeption(3, "Ошибка открытия файла", "Данный файл не открылся"));

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
