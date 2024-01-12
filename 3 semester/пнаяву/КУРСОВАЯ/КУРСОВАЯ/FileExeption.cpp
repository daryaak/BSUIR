#include "FileExeption.h"

//�������� �����
bool exist_file(string name_file)
{
    ifstream in_test(name_file, ios::in);
    try
    {
        if (!in_test)
            throw (FileExeption(1, "������ �����", "���� �� ����������"));
        if (!in_test.is_open())
            throw (FileExeption(3, "������ �����", "���� �� ��������"));
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
    cout << "��� ������:" << Code << endl;
    cout << Type << endl;
    cout << Message << endl;
}