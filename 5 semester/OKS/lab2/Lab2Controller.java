package com.example.lab2;

import com.fazecast.jSerialComm.*;
import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.MenuButton;
import javafx.scene.control.MenuItem;
import javafx.scene.control.TextArea;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.text.Text;

import java.nio.charset.StandardCharsets;
import java.util.concurrent.CompletableFuture;

public class Lab2Controller {
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
                            String data = rawData.substring(begin + flag.length(), end);

                            String destuffeddata = data;
                            destuffeddata = destuffeddata.replace("~", "");
                            String showData = data;
                            destuffeddata = destuffeddata.replace("00001101", "0000110");
                            showData = showData.replace("00001101", "0000110{1}");

                            text += destuffeddata.substring(8, destuffeddata.length() - 1);
                            currentPackage.appendText(rawData.substring(0, 8) + showData + "\n");
                            begin = end;
                        }
                        outputTextArea.setText(text);
                    }
                }
            }
        });
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

    public String formPackage(String text) {

        String flag = "00001100";
        String packageStr = "";
        String portName = serialPort.getSystemPortName();
        int portNum = Integer.parseInt(portName.replaceAll(".*?(\\d+)$", "$1"));
        String portNumBinary = Integer.toBinaryString(portNum);

        while (portNumBinary.length() < 4) {
            portNumBinary = "0" + portNumBinary;
        }

        while (text.length() > 12) {
            String frame = text.substring(0, 12);
            text = text.substring(12);
            frame = "0000" + portNumBinary + frame + "0";
            frame = bitStuffing(frame);
            frame = flag + frame;
            packageStr += frame;
        }

        if (text.length() > 0) {
            while (text.length() < 12) {
                text += "~";
            }
            text = "0000" + portNumBinary + text + "0";
            text = bitStuffing(text);
            packageStr += flag + text;
        }

        return packageStr;
    }
}