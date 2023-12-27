package com.example.demo;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import com.fazecast.jSerialComm.*;
import javafx.scene.input.*;
import javafx.scene.text.Text;

import java.util.concurrent.CompletableFuture;

public class Lab1Controller {
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
    private MenuButton bitsInByteMenu;
    private SerialPort serialPort;
    private boolean portsAvailable;

    public void initialize() {

        writeData(); ////!!!!
        byteSizeHandle();
        updateMenu(); ///!!!
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
                //String numberOfPort = serialPorts[i].getSystemPortName();
                MenuItem menuItem = new MenuItem(serialPorts[i].getSystemPortName().substring(3));
                menuItem.setOnAction(actionEvent -> {
                   if(setPort(SerialPort.getCommPort(menuItem.getText()))==false){
                       Alert alert = new Alert(Alert.AlertType.WARNING);
                       alert.setTitle("Предупреждение");
                       alert.setHeaderText(null);
                       alert.setContentText("Выбранный порт уже используется другим приложением!");
                       alert.show();
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
        inputTextArea.addEventFilter(KeyEvent.KEY_PRESSED,event->{
            if(event.getCode() == KeyCode.ENTER) {
                if(portsAvailable) {
                    byte[] writeBytes = inputTextArea.getText().getBytes();
                    inputTextArea.clear();
                    serialPort.writeBytes(writeBytes, writeBytes.length);
                    Integer writeToStatus = writeBytes.length;
                    bytesSend.setText(writeToStatus.toString());
                }
                event.consume();
            }
        });
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
                    if(readBytes!=-1){
                        String bytesString = new String(byteBuffer,0,readBytes);
                        outputTextArea.setText(bytesString);
                    }
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
    }