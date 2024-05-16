import socket
import os
import time
import select

HOST_ADDRESS = "172.20.10.5"
HOST_PORT = 12345
OPT_INTERVAL = 5
OPT_COUNT = 3
FRAME_SIZE = 4096

exitFlag = False

def setOptions(clientSocket):
    clientSocket.setsockopt(socket.SOL_SOCKET, socket.SO_KEEPALIVE, 1)
    clientSocket.setsockopt(socket.SOL_TCP, socket.TCP_USER_TIMEOUT, 5000)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPIDLE, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPINTVL, OPT_INTERVAL)
    clientSocket.setsockopt(socket.IPPROTO_TCP, socket.TCP_KEEPCNT, OPT_COUNT)

    return clientSocket

def connect(clientSocket):
    clientSocket = setOptions(clientSocket)
    clientSocket.connect((HOST_ADDRESS, HOST_PORT))
    return clientSocket

def reconnectPrompt():
    print("Соединение разорвано.",
          "\nХотите попробовать восстановить соединение? [y/n]")
    
    answer = input()
    if (answer[0] == "Y") or (answer[0] == "y"):
        return True
    
    return False

def upload(filePath):
    if not os.path.exists(filePath):
        clientSocket.send("0".encode())
        clientSocket.send(("Файл \"" + filePath + "\" не найден.").encode())
        return clientSocket.recv(FRAME_SIZE).decode()

    clientSocket.send("1".encode())

    startTime = time.time()
    offset, fileSize = uploadFile(filePath)
    endTime = time.time()

    speed = "{:.2f}".format((fileSize - offset) / (endTime - startTime) / 1024)
    print("Скорость загрузки:", speed, "КБ/с")
    return clientSocket.recv(FRAME_SIZE).decode()

def uploadFile(filePath):
    with open(filePath, 'rb') as file:
        clientSocket.send(str(os.path.getsize(filePath)).encode())
        offset = int(clientSocket.recv(FRAME_SIZE).decode())
        file.seek(offset, 0)
        while True:
            data = file.read(FRAME_SIZE)
            if not data:
                break
            clientSocket.send(data)

    file.close()
    return (offset, os.path.getsize(filePath))

def download(filePath):
    serverHasFile = clientSocket.recv(1).decode()
    if serverHasFile == "0":
        return clientSocket.recv(FRAME_SIZE).decode()
    
    startTime = time.time()
    offset, fileSize = downloadFile(filePath)
    endTime = time.time()

    speed = "{:.2f}".format((fileSize - offset) / (endTime - startTime) / 1024)
    print("Скорость загрузки:", speed, "КБ/с")
    return clientSocket.recv(FRAME_SIZE).decode()
    

def downloadFile(fileName):
    mode = 'ab' if os.path.exists(fileName) else 'wb+'

    with open(fileName, mode) as file:
        offset = os.path.getsize(fileName)
        clientSocket.send(str(offset).encode())
        fileSize = int(clientSocket.recv(FRAME_SIZE).decode())
        file.seek(0, os.SEEK_END)

        while fileSize > offset:
            data = clientSocket.recv(FRAME_SIZE if FRAME_SIZE < fileSize - offset else fileSize - offset)
            fileSize -= len(data)
            file.write(data)

    file.close()
    return (offset, os.path.getsize(fileName))

def exit():
    global exitFlag
    exitFlag = True

def otherCommand(userInput):
    return clientSocket.recv(FRAME_SIZE).decode()

def handleCommand(userInput):
    command, argument = userInput.partition(" ")[::2]

    match (command.lower()):
        case "upload":
            response = upload(argument)
        
        case "download":
            response = download(argument)

        case _:
            response = otherCommand(userInput)

    if (userInput.lower() == "exit"):
        exit()

    return response

#------------

try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket = connect(clientSocket)

    print("Ожидание подключения...")

    clientSocket.recv(1)

    print("Соединение установлено.\n")

    while not exitFlag:
        try:
            userInput = input("> ")
            while userInput == "":
                userInput = input("> ")
            clientSocket.send(userInput.encode())
            response = handleCommand(userInput)
            print(response, "\n")
 
        except socket.error:
            clientSocket.close()
            try:
                result = reconnectPrompt()
                if (result):
                    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                    clientSocket = connect(clientSocket)
                    print("Соединение восстановлено.\n")
                else:
                    exitFlag = True
            except socket.error:
                print("Не удалось восстановить подключение.")
                exitFlag = True

except socket.error:
    print("Сервер недоступен.\n")
except KeyboardInterrupt:
    print("\nЗавершение работы.\n")
finally:
    clientSocket.close()
