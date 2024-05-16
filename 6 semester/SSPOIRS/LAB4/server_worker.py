import socket
import time
import os
import sys
import signal

OPT_INTERVAL = 5
OPT_COUNT = 2
FRAME_SIZE = 1024

def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    clientSocket.setsockopt(socket.SOL_TCP, socket.TCP_USER_TIMEOUT, 30000)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket

# def reconnect(serverSocket, clientSocket):
#     print("Соединение разорвано.")
#     clientSocket.close()
#     clientSocket, clientAddr = serverSocket.accept()

#     global lastClientAddr
#     if clientAddr[0] == lastClientAddr[0]:
#         print("Соединение восстановлено.\n")
#     else:
#         print("Обнаружено подключение\n"
#               "Адрес:", clientAddr[0], "\n")
#     connected = True

#     lastClientAddr = clientAddr

#     return clientSocket

def download(fileName):
    if not os.path.exists(fileName):
        clientSocket.send("0".encode())
        return "Файл \"" + fileName + "\" не найден."
    
    clientSocket.send("1".encode())

    printStartFileLoading(fileName, False)
    
    downloadFile(fileName)
    return "Файл передан успешно."

def downloadFile(fileName):
    offset = 0

    with open(fileName, 'rb') as file:
        offset = int(clientSocket.recv(FRAME_SIZE).decode())
        clientSocket.send(str(os.path.getsize(fileName)).encode())
        file.seek(offset, 0)

        while True:
            data = file.read(FRAME_SIZE)
            if not data:
                break
            clientSocket.send(data)

    file.close()

def upload(fileName):
    clientHasFile = clientSocket.recv(1).decode()
    if clientHasFile == "0":
        return clientSocket.recv(FRAME_SIZE).decode()

    printStartFileLoading(fileName, True)

    uploadFile(fileName)
    return "Файл загружен успешно."

def uploadFile(fileName):
    mode = 'ab' if os.path.exists(fileName) else 'wb+'

    with open(fileName, mode) as file:
        fileSize = int(clientSocket.recv(FRAME_SIZE).decode())
        clientSocket.send(str(os.path.getsize(fileName)).encode())
        offset = os.path.getsize(fileName)
        file.seek(0, os.SEEK_END)
        
        while fileSize > offset:
            data = clientSocket.recv(FRAME_SIZE)
            fileSize -= len(data)
            file.write(data)

    file.close()

def echo(data):
    return data 

def _time():
    currentTime = time.asctime(time.localtime())
    return "Время сервера: " + currentTime

def _exit():
    global connected
    connected = False
    return "Отключение от сервера..."

def handleCommand(clientInput):
    command, argument = clientInput.partition(" ")[::2]

    match (command.lower()):
        case "echo":
            response = echo(argument)

        case "time":
            response = _time()

        case "download":
            response = download(argument)

        case "upload":
            response = upload(argument)

        case "exit":
            response = _exit()

        case _:
            response = "Такой команды не существует!"

    return response

def printStartFileLoading(fileName, dir):
    if dir:
        wrapPrint(f"Начат приём файла {fileName}\n"
                  f"Отправитель: {clientAddr[0]}")
    else:
        wrapPrint(f"Начата передача файла {fileName}\n"
                  f"Получатель: {clientAddr[0]}")

def printLog(clientInput, response):
    if clientInput:
        wrapPrint(f"Команда пользователя {clientAddr[0]}\n"
                  f"Содержание: {clientInput}\n"
                  f"Ответ: {response}")

def wrapPrint(*args, **kwargs):
    print(f"PID: {os.getpid()}")
    print("==============")
    print(*args, **kwargs)
    print()

def termHandler(*args):
    if clientSocket and clientSocket.fileno() != -1:
        clientSocket.close()
    os.close(pipe)
    exit()

def timeoutHandler(*args):
    os.write(pipe, "T".encode())

#------------

try:
    serverSocket = socket.fromfd(int(sys.argv[1]), socket.AF_INET, socket.SOCK_STREAM)
    clientSocket = None
    clientAddr = None
    connected = False

    timeout = int(sys.argv[2])
    pipe = int(sys.argv[3])

    signal.signal(signal.SIGTERM, termHandler)
    signal.signal(signal.SIGALRM, timeoutHandler)

    while True:
        signal.alarm(timeout)
        clientSocket, clientAddr = serverSocket.accept()
        signal.alarm(0)
        connected = True

        wrapPrint("Обнаружено подключение\n" + "Адрес:", clientAddr[0])
        os.write(pipe, "A".encode())

        clientSocket = setOptions(clientSocket)
        clientSocket.send("1".encode())
        
        while connected:
            try:
                clientInput = clientSocket.recv(FRAME_SIZE).decode()
                response = handleCommand(clientInput)
                clientSocket.send(response.encode())
                printLog(clientInput, response)
            
            except socket.error:
                wrapPrint(f"Обрыв соединения с {clientAddr[0]}")
                clientSocket.close()
                break
        os.write(pipe, "F".encode())

except KeyboardInterrupt:
    pass