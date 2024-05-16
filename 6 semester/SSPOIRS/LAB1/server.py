import socket
import time
import os

BIND_ADDRESS = "192.168.0.101"
BIND_PORT = 12345
OPT_INTERVAL = 5
OPT_COUNT = 3
FRAME_SIZE = 1024

def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    clientSocket.setsockopt(socket.SOL_TCP, socket.TCP_USER_TIMEOUT, 30000)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket

def reconnect(serverSocket, clientSocket):
    print("Соединение разорвано.")
    clientSocket.close()
    clientSocket, clientAddr = serverSocket.accept()

    global lastClientAddr
    if clientAddr[0] == lastClientAddr[0]:
        print("Соединение восстановлено.\n")
    else:
        print("Обнаружено подключение\n"
              "Адрес:", clientAddr[0], "\n")
    connected = True

    lastClientAddr = clientAddr

    return clientSocket

def download(fileName):
    if not os.path.exists(fileName):
        clientSocket.send("0".encode("utf-8"))
        return "Файл \"" + fileName + "\" не найден."
    
    clientSocket.send("1".encode("utf-8"))
    
    downloadFile(fileName)
    return "Файл передан успешно."

def downloadFile(fileName):
    offset = 0

    with open(fileName, 'rb') as file:
        offset = int(clientSocket.recv(FRAME_SIZE).decode("utf-8"))
        clientSocket.send(str(os.path.getsize(fileName)).encode("utf-8"))
        file.seek(offset, 0)

        while True:
            data = file.read(FRAME_SIZE)
            if not data:
                break
            clientSocket.send(data)

    file.close()

def upload(fileName):
    clientHasFile = clientSocket.recv(1).decode("utf-8")
    if clientHasFile == "0":
        return clientSocket.recv(FRAME_SIZE).decode("utf-8")

    uploadFile(fileName)
    return "Файл загружен успешно."

def uploadFile(fileName):
    mode = 'ab' if os.path.exists(fileName) else 'wb+'

    with open(fileName, mode) as file:
        fileSize = int(clientSocket.recv(FRAME_SIZE).decode("utf-8"))
        clientSocket.send(str(os.path.getsize(fileName)).encode("utf-8"))
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

def exit():
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
            response = exit()

        case _:
            response = "Такой команды не существует!"

    return response

def printLog(clientInput, response):
    print("Команда пользователя:", clientInput)
    print("Ответ:", response, "\n")
    
#------------
try:
    connected = False
    lastClientAddr = 0

    print("Сервер начал работу.\n")

    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket = setOptions(serverSocket)
    serverSocket.bind((BIND_ADDRESS, BIND_PORT))
    serverSocket.listen()

    while(True):
        clientSocket, clientAddr = serverSocket.accept()
        print("Обнаружено подключение\n"
            "Адрес:", clientAddr[0], "\n")
        connected = True
        lastClientAddr = clientAddr

        clientSocket = setOptions(clientSocket)
        
        while(connected):
            try:
                clientInput = clientSocket.recv(FRAME_SIZE).decode("utf-8")
                response = handleCommand(clientInput)
                clientSocket.send(response.encode("utf-8"))
                printLog(clientInput, response)
            
            except socket.error:
                clientSocket = reconnect(serverSocket, clientSocket)
except KeyboardInterrupt:
    print("\nЗавершение работы.\n")