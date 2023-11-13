#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <windows.h>
#include <devguid.h>
#include <setupapi.h>
#include "deviceInfo.h"
#include <cstdlib>
#include <ctime>
#pragma comment(lib, "setupapi.lib")

using namespace cv;
using namespace std;

void hideConsoleWindow();
void takeHiddenPhoto();
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
string generateFileName();

HHOOK keyboardHook;
bool flafIsHidden = false;
bool flagReadyToPicture = true;

int main()
{
    setlocale(LC_ALL, "Russian");
    
    ShowWindow(GetForegroundWindow(), SW_SHOW);

    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc, NULL ,0);

    if (keyboardHook == NULL){
        cerr << "Не удалось установить хук клавиатуры." << endl;
        return 1;
    }

    deviceInfo data;
    data.initialize();
    wcout << data;

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) != 0){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    UnhookWindowsHookEx(keyboardHook);
    
    return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

    KBDLLHOOKSTRUCT* keyCode = (KBDLLHOOKSTRUCT*)lParam;

    if (nCode >= 0) {
        if (keyCode->vkCode == VK_CAPITAL) {
            hideConsoleWindow();
            if(flagReadyToPicture)
            takeHiddenPhoto();
        }

        if (keyCode->vkCode == VK_ESCAPE) {
            exit(0);
        }
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

void hideConsoleWindow(){
    HWND console = GetConsoleWindow();
    SetForegroundWindow(console);

    if (flafIsHidden == false){
        ShowWindow(GetForegroundWindow(), SW_HIDE);
        flafIsHidden = true;
    }
}

void takeHiddenPhoto(){
    flagReadyToPicture = false;
    VideoCapture camera(0);
    Mat image;

    if (!camera.isOpened()){
        return;
    }

    camera >> image;
    if (image.empty()){
        flagReadyToPicture = true;
        return;
    }

    imwrite(generateFileName(), image);

    camera.release();
    flagReadyToPicture = true;
}

string generateFileName(){

    srand(static_cast<unsigned>(time(nullptr)));

    int randomNumber1 = rand() % 1000;
    string randomString1 = to_string(randomNumber1);

    int randomNumber2 = rand() % 1000;
    string randomString2 = to_string(randomNumber2);

    string fileName = "D:/5 сем/ИиУВМ/" + randomString1 + "hiddenPhoto" + randomString2 + ".jpg";

    return fileName;
}