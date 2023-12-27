package com.example.lab2;

import com.fazecast.jSerialComm.SerialPort;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.text.Text;
import javafx.scene.text.TextBoundsType;
import javafx.scene.text.TextFlow;
import java.util.Random;


import java.util.Random;
import java.util.concurrent.CompletableFuture;

public class Lab4Controller {
    @FXML
    private TextArea inputTextArea;
    @FXML
    private TextArea outputTextArea;
    @FXML
    private Text noAvailablePortsText;
    @FXML
    private MenuButton menuButton;
    @FXML
    private Text baudRate;
    @FXML
    private Text bytesSend;
    @FXML

    private TextArea bytesSend1;
    @FXML
    private TextArea currentPackage;
    @FXML
    private MenuButton bitsInByteMenu;
    private SerialPort serialPort;
    private boolean portsAvailable;

    public void initialize() {

        inputTextArea.addEventFilter(KeyEvent.KEY_PRESSED,event->{
            if(event.getCode() == KeyCode.ENTER) {
                writeData();
                event.consume();
            }
        });

        inputTextArea.addEventFilter(KeyEvent.KEY_TYPED, event -> {
            String allowedCharacters = "01\n";
            if (!allowedCharacters.contains(event.getCharacter()) || event.getCode() == KeyCode.BACK_SPACE) {
                event.consume();
            }
        });

        byteSizeHandle();
        updateMenu();
        findAvailablePorts();

    }

    public void findAvailablePorts() {
        CompletableFuture.runAsync(() -> {
            while (true) {
                SerialPort[] serialPorts = SerialPort.getCommPorts();
                if (serialPorts.length == 0) {
                    menuButton.setVisible(false);
                    noAvailablePortsText.setVisible(true);
                    portsAvailable=false;
                } else {
                    menuButton.setVisible(true);
                    noAvailablePortsText.setVisible(false);
                    if (portsAvailable == false){
                        for(int i = 0; i < serialPorts.length;i++){
                            if(setPort(serialPorts[i])) break;
                        }
                    }
                    portsAvailable = true;
                }
            }
        });
    }
    public void updateMenu() {
        menuButton.setOnMouseEntered(event->{
            SerialPort[] serialPorts = SerialPort.getCommPorts();
            menuButton.getItems().clear();
            for(int i = 0; i<serialPorts.length;i++){
                MenuItem menuItem = new MenuItem(serialPorts[i].getSystemPortName().substring(3));
                menuItem.setOnAction(actionEvent -> {
                    if(Integer.parseInt(menuItem.getText())>15){
                        Alert alert = new Alert(Alert.AlertType.WARNING);
                        alert.setTitle("Предупреждение");
                        alert.setHeaderText(null);
                        alert.setContentText("Выберите порт с номером меньше 16!");
                        alert.show();
                        actionEvent.consume();
                    }else {
                        if (setPort(SerialPort.getCommPort("COM" + menuItem.getText())) == false) {
                            Alert alert = new Alert(Alert.AlertType.WARNING);
                            alert.setTitle("Предупреждение");
                            alert.setHeaderText(null);
                            alert.setContentText("Выбранный порт уже используется другим приложением!");
                            alert.show();
                        }
                    }
                });
                menuButton.getItems().add(menuItem);
            }
        });
    }

    public boolean setPort(SerialPort chosenPort){
        if(serialPort != null && serialPort.getSystemPortName().equals(chosenPort.getSystemPortName())) return true;

        if(chosenPort.openPort()){
            if(serialPort!= null && serialPort.isOpen()) serialPort.closePort();

            serialPort = chosenPort;
            outputTextArea.clear();
            inputTextArea.clear();
            String numberBytes = bitsInByteMenu.getText();
            int byteNumber = Integer.parseInt(numberBytes);
            serialPort.setComPortParameters(9600, byteNumber, 1, 0);
            Platform.runLater(() -> menuButton.setText(serialPort.getSystemPortName().substring(3)));
            Integer baudRate1 = serialPort.getBaudRate();
            String rate = baudRate1.toString();
            baudRate.setText(rate);
            readData();
            return true;
        }

        return false;
    }

    public void writeData(){
        new Thread(() -> {
            if (portsAvailable) {
                String writeBytes = inputTextArea.getText();
                bytesSend1.setText("");
                inputTextArea.clear();
                String pack = formPackage(writeBytes);

                StringBuilder dataToSend = new StringBuilder();

                int counter = 0;
                char ch;
                int firstIndex = 0;
                int secondIndex = 0;
                String flag = "00001100";
                String cadre;

                while (true) {
                    firstIndex = pack.indexOf(flag,firstIndex);
                    if (firstIndex == -1) {
                        break;
                    }
                    secondIndex = firstIndex + 1;
                    secondIndex = pack.indexOf(flag, secondIndex);
                    if (secondIndex == -1) {
                        secondIndex = pack.length();
                    }
                    cadre = pack.substring(firstIndex, secondIndex); //пакет без флага
                    for (int i = 0; i < cadre.length(); i++) {
                        counter = 0;
                        ch = cadre.charAt(i);
                        bytesSend1.setText(bytesSend1.getText() + " ");

                        while (counter < 16) {
                            while (!generateBusyChannel()) {
                                //wait for free chanel
                            }
                            sleepDuringCollisionWindow();
                            dataToSend.append(ch);
                            if (generateCollision()) {
                                counter++;
                                if(counter==16) break;
                                generateBackOff(counter);
                               // dataToSend.append("0");
                                dataToSend.setCharAt(dataToSend.length()-1,'0');
                                bytesSend1.setText(bytesSend1.getText() + "+");

                            } else {
                                bytesSend1.setText(bytesSend1.getText() + "-");
                                break;
                            }
                        }
                    }
                    bytesSend1.appendText("\n");
                    firstIndex = secondIndex;
                }
                serialPort.writeBytes(dataToSend.toString().getBytes(), dataToSend.toString().length());
                Integer writeToStatus = writeBytes.length();
                bytesSend.setText(writeToStatus.toString());
            }
        }).start();
    }

    public void readData(){
        CompletableFuture.runAsync(() -> {
            while (true) {
                SerialPort tempPort = serialPort;
                byte[] byteBuffer = new byte[9999];
                String tempPortName = tempPort.getSystemPortName();
                String serialPortName = serialPort.getSystemPortName();
                while(tempPortName.equals(serialPortName)){
                    while(tempPort.bytesAvailable()>0){

                        int readBytes = tempPort.readBytes(byteBuffer,9999);
                        currentPackage.clear();
                        String rawData = new String(byteBuffer,0,readBytes);
                        String flag = "00001100";
                        String text = "";
                        int begin = 0;
                        int end = 0;

                            String data = rawData; //пакет без флага

                            String destuffeddata = data;
                            destuffeddata = destuffeddata.replace("00001101", "0000110");

                            String showFCS = getHammingCode(destuffeddata.replace("~",""));
                            String showData = destuffeddata;
                            destuffeddata = destuffeddata.replace("~","");
                            currentPackage.appendText(rawData.substring(0, 8) + showData + " " + showFCS + "\n");
                            outputTextArea.setText(destuffeddata);
                    }
                }
            }
        });
    }

    public static void sleepDuringCollisionWindow() {
        try {
            Thread.sleep(500L);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private String correctMistake(String corruptedFrame)
    {
        int i = 0;
        String data = corruptedFrame.replace("~", "");
        String correctFCS = corruptedFrame.substring(corruptedFrame.length()-4);
        String FCS = getHammingCode(data);

        if (FCS.equals(correctFCS))
            return data;

        int distortionPos = 0;
        for (i = 0; i < FCS.length(); i++)
            if (FCS.charAt(i) != correctFCS.charAt(i))
                distortionPos += (int) Math.pow(2,i);


        int numOfParityBits = 0;
        while (Math.pow(2,numOfParityBits) < distortionPos)
            numOfParityBits++;

        distortionPos -= numOfParityBits + 1;

        String inverted = data.charAt(distortionPos) == '1' ? "0" : "1";
        data = data.substring(0, distortionPos) + inverted + data.substring(distortionPos + 1);

        return data;
    }

    public void byteSizeHandle(){
        bitsInByteMenu.setOnMouseEntered(event ->{
            bitsInByteMenu.getItems().clear();
            for(Integer i = 8; i!=4;i--){
                String number = i.toString();
                MenuItem menuItem = new MenuItem(number);
                menuItem.setOnAction(event1 -> {
                    bitsInByteMenu.setText(number);
                    if (serialPort!=null) {
                        serialPort.setNumDataBits(Integer.parseInt(number));
                    }
                });
                bitsInByteMenu.getItems().add(menuItem);
            }
        });
    }

    public String bitStuffing(String data) {
        int begin = 0;
        String pattern = "0000110";

        while (begin < data.length()) {
            begin = data.indexOf(pattern, begin);
            if (begin == -1) {
                break;
            } else {
                data = data.substring(0, begin + pattern.length()) + "1" + data.substring(begin + pattern.length());
                begin += pattern.length();
            }
        }

        return data;
    }

    private String generateMistake(String data)
    {
        if (Math.random() <= 0.7)
        {
            int pos = (int) (Math.random() * (data.length() - 1));
            String inverted = data.charAt(pos) == '1' ? "0" : "1";
            data = data.substring(0, pos) + inverted + data.substring(pos + 1);
        }
        return data;
    }

    public boolean generateBusyChannel(){
        if (Math.random()<=0.7) return true;
        else return false;
    }

    public boolean generateCollision(){
        if (Math.random()<=0.3) return true;
        else return false;
    }

    public void generateBackOff(int counter){
        try {
            Random random = new Random();
           // long back = Math.min(counter, 10) * 100L;
            long back = (long)Math.pow(2, Math.min(counter, 10)) * 100L;
            long backOff = random.nextLong();
            backOff = Math.floorMod(backOff,back + 1);
            Thread.sleep(backOff);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public String formPackage(String text) {

        String flag = "00001100";
        String FCS;
        String packageStr = "";
        String portName = serialPort.getSystemPortName();
        int portNum = Integer.parseInt(portName.replaceAll(".*?(\\d+)$", "$1"));
        String portNumBinary = Integer.toBinaryString(portNum);

        while (portNumBinary.length() < 4) {
            portNumBinary = "0" + portNumBinary;
        }

        while (text.length() > 12) {
            String frame = text.substring(0, 12);
            String frameNew = generateMistake(frame);
            text = text.substring(12);
            FCS = getHammingCode(frame);
            frame = "0000" + portNumBinary + frameNew + FCS;
            frame = bitStuffing(frame);
            frame = flag + frame;
            packageStr += frame;
        }

        if (text.length() > 0) {
            String textNew = generateMistake(text);
            while (textNew.length() < 12) {
                textNew += "~";
            }
            FCS = getHammingCode(text);
            text = "0000" + portNumBinary + textNew + FCS;
            text = bitStuffing(text);
            packageStr += flag + text;
        }

        return packageStr;
    }

    private String getHammingCode(String data)
    {
        String code = "";
        int numOfParityBits = 0;
        int i = 0;

        while (Math.pow(2,numOfParityBits) <= data.length() + numOfParityBits)
            numOfParityBits++;

        for (i = 0; i < numOfParityBits; i++)
            data = data.substring(0, (int) Math.pow(2,i) - 1) + "0" + data.substring((int) Math.pow(2,i) - 1);

        for (i = 0; i < numOfParityBits; i++)
        {
            int parity = 0;
            int pos = (int) Math.pow(2,i) - 1;
            for (int j = pos; j < data.length(); j += (pos + 1) * 2)
                for (int k = j; k <= Math.min(j + pos, data.length() - 1); k++)
                    parity ^= Integer.parseInt(data.substring(k, k + 1));
            data = data.substring(0, pos) + Integer.toString(parity) + data.substring(pos + 1);
        }

        for (i = 0; i < numOfParityBits; i++)
            code += data.charAt((int) Math.pow(2,i) - 1);

        return code;
    }
}