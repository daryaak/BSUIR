package com.example.lab2;

import com.fazecast.jSerialComm.SerialPort;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextArea;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.text.Text;

import java.util.concurrent.CompletableFuture;
import java.util.zip.CRC32;
public class Lab3Controller {
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
    private TextArea currentPackage;
    @FXML
    private MenuButton bitsInByteMenu;
    private SerialPort serialPort;
    private boolean portsAvailable;

    private int controlBits;

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
                if(portsAvailable) {
                    String writeBytes = inputTextArea.getText();
                    inputTextArea.clear();
                    String pack = formPackage(writeBytes);
                    serialPort.writeBytes(pack.getBytes(), pack.length());
                    Integer writeToStatus = writeBytes.length();
                    bytesSend.setText(writeToStatus.toString());
                }
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

                        while (true) {
                            begin = rawData.indexOf(flag, begin);
                            if (begin == -1) {
                                break;
                            }
                            end = begin + 1;
                            end = rawData.indexOf(flag, end);
                            if (end == -1) {
                                end = rawData.length();
                            }
                            String data = rawData.substring(begin + flag.length(), end); //пакет без флага

                            String destuffeddata = data;
                            destuffeddata = destuffeddata.replace("00001101", "0000110");

                            String showFCS = getHammingCode(destuffeddata.substring(8,20).replace("~",""));
                            String showData = destuffeddata.substring(0,20);
                            String correctedData = correctMistake(destuffeddata);
                            text += correctedData;
                            currentPackage.appendText(rawData.substring(0, 8) + showData + " " + showFCS + "\n");
                            begin = end;
                        }
                        outputTextArea.setText(text);
                    }
                }
            }
        });
    }

    private String correctMistake(String corruptedFrame)
    {
        int i = 0;
        String data = corruptedFrame.substring(8, 20).replace("~", "");
        String correctFCS = corruptedFrame.substring(20);
        String FCS = getHammingCode(data);

        if (FCS.equals(correctFCS))
            return data;

        int wrongPosition = 0;
        for (i = 0; i < FCS.length(); i++)
            if (FCS.charAt(i) != correctFCS.charAt(i))
                wrongPosition += (int) Math.pow(2,i);


        int numOfControlBits = 0;
        while (Math.pow(2,numOfControlBits) < wrongPosition)
            numOfControlBits++;

        wrongPosition -= numOfControlBits + 1;

        String inverted = data.charAt(wrongPosition) == '1' ? "0" : "1";
        data = data.substring(0, wrongPosition) + inverted + data.substring(wrongPosition + 1);

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
        String hamCode = "";
        int numOfControlBits = 0;
        int i = 0;

        while (Math.pow(2,numOfControlBits) <= data.length() + numOfControlBits)
            numOfControlBits++;

        for (i = 0; i < numOfControlBits; i++)
            data = data.substring(0, (int) Math.pow(2,i) - 1) + "0" + data.substring((int) Math.pow(2,i) - 1);

        for (i = 0; i < numOfControlBits; i++)
        {
            int parity = 0;
            int pos = (int) Math.pow(2,i) - 1;
            for (int j = pos; j < data.length(); j += (pos + 1) * 2)
                for (int k = j; k <= Math.min(j + pos, data.length() - 1); k++)
                    parity ^= Integer.parseInt(data.substring(k, k + 1));
            data = data.substring(0, pos) + Integer.toString(parity) + data.substring(pos + 1);
        }

        for (i = 0; i < numOfControlBits; i++)
            hamCode += data.charAt((int) Math.pow(2,i) - 1);

        return hamCode;
    }
}