 #include <SoftwareSerial.h>
 #include <DFRobotDFPlayerMini.h>
 
 SoftwareSerial SoftSerial(19, 18); // RX, TX (conectar al controlador de servos)
 SoftwareSerial mySoftwareSerial(14, 15); // RX, TX (Conecta los pines RX y TX del módulo DFPlayer Mini a estos pines)
 DFRobotDFPlayerMini myDFPlayer;

String inputString = "";
boolean stringComplete = false;
unsigned long commandStartTime = 0;  // Variable para rastrear el tiempo de inicio del comando

void wait_serial_return_ok(unsigned long timeout) {
  int num = 0;
  char c[16];
  unsigned long timeoutMillis = millis() + timeout;  // Esperar el tiempo especificado para recibir "OK"
  bool okReceived = false;

  while (millis() < timeoutMillis) {
    while (SoftSerial.available() > 0) {
      char receivedChar = SoftSerial.read();
      c[num] = receivedChar;
      num++;
      if (num >= 15)
        num = 0;
      if (receivedChar == 'K' && c[num - 2] == 'O') {
        c[num] = '\0';  // Agregar el carácter nulo al final para convertirlo en una cadena
        Serial.println("Respuesta recibida: " + String(c));
        okReceived = true;
        break;  // Salir del bucle interno si se recibe "OK"
      }
    }

    if (okReceived) {
      break;  // Salir del bucle principal si se recibió "OK"
    }
  }

  if (!okReceived) {
    Serial.println("Tiempo de espera excedido para recibir 'OK', enviando comando para detener acciones");
    SoftSerial.print("~ST");  // Enviar comando para detener acciones
    delay(1000);  // Esperar 1 segundo antes de continuar
  }
}

void setup() {
  Serial2.begin(2400); // Inicializa Serial2 a 2400 baudios para recibir comandos
  Serial.begin(9600); // Inicializa el Monitor Serial a 9600 baudios
  SoftSerial.begin(9600); // baudios controladora servos
  mySoftwareSerial.begin(9600); // baudios dfplayer probar con 2400
  Serial.println("Comunicación serial inicializada");

   if (!myDFPlayer.begin(mySoftwareSerial)) {  // Inicializa el reproductor
    Serial.println(F("Error DFPlayer Mini"));
    while (true);
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(20); // Establece el volumen (0-30)
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.play(64);
}

void loop() {
 
  if (stringComplete) {
    Serial.print("Datos recibidos: ");
    Serial.println(inputString);

    if (inputString == ":CL00") {
      Serial.println("Inicio de G0F1");
      SoftSerial.print("G0F1\r\n");
      commandStartTime = millis(); 
      wait_serial_return_ok(1500);
      Serial.println("Fin de G0F1");
    } else if (inputString == ":OP00") {
      Serial.println("Inicio de G2F1");
      SoftSerial.print("G2F1\r\n");
      commandStartTime = millis(); 
      wait_serial_return_ok(1500);
      Serial.println("Fin de G2F1");
    } else if (inputString == ":SE03") {
      Serial.println("Inicio de G3F1");
      SoftSerial.print("G3F1\r\n");
      commandStartTime = millis(); 
      wait_serial_return_ok(7000);
      Serial.println("Fin de G4F2");
    } else if (inputString == ":SE05") {
      Serial.println("Inicio de G4F2");
      SoftSerial.print("G4F2\r\n"); //F2 para que se repita dos veces
      commandStartTime = millis(); 
      wait_serial_return_ok(16000);
      Serial.println("Fin de G4F2");
    } else if (inputString == ":SE06") {
      Serial.println("Inicio de G5F1");
      SoftSerial.print("G5F1\r\n"); 
      commandStartTime = millis(); 
      wait_serial_return_ok(20000);
      Serial.println("Fin de G5F1");
    } else if (inputString == ":SE01") {
      Serial.println("Inicio de G6F1");
      SoftSerial.print("G6F1\r\n"); 
      commandStartTime = millis(); 
      wait_serial_return_ok(5000);
      Serial.println("Fin de G6F1");
    } else if (inputString == ":PINZA") {
      Serial.println("Inicio de G7F1");
      SoftSerial.print("G7F1\r\n"); 
      commandStartTime = millis(); 
      wait_serial_return_ok(8000);
      Serial.println("Fin de G7F1");
    } else if (inputString == ":Sierra") {
      Serial.println("Inicio de G8F1");
      SoftSerial.print("G8F1\r\n"); 
      commandStartTime = millis(); 
      wait_serial_return_ok(22000);
      Serial.println("Fin de G8F1");
    } else if (inputString == "$11") { myDFPlayer.play(1);      
    } else if (inputString == "$12") { myDFPlayer.play(2);
    } else if (inputString == "$13") { myDFPlayer.play(3);      
    } else if (inputString == "$14") { myDFPlayer.play(4);     
    } else if (inputString == "$15") { myDFPlayer.play(5);      
    } else if (inputString == "$16") { myDFPlayer.play(6);     
    } else if (inputString == "$17") { myDFPlayer.play(7);     
    } else if (inputString == "$18") { myDFPlayer.play(8);    
    } else if (inputString == "$19") { myDFPlayer.play(9);     
    } else if (inputString == "$110") { myDFPlayer.play(10);    
    } else if (inputString == "$111") { myDFPlayer.play(11);     
    } else if (inputString == "$112") { myDFPlayer.play(12);     
    } else if (inputString == "$113") { myDFPlayer.play(13);    
    } else if (inputString == "$114") { myDFPlayer.play(14);     
    } else if (inputString == "$115") { myDFPlayer.play(15);     
    } else if (inputString == "$116") { myDFPlayer.play(16);    
    } else if (inputString == "$117") { myDFPlayer.play(17);    
    } else if (inputString == "$118") { myDFPlayer.play(18);    
    } else if (inputString == "$119") { myDFPlayer.play(19);          
    } else if (inputString == "$21") { myDFPlayer.play(20);    
    } else if (inputString == "$22") { myDFPlayer.play(21);    
    } else if (inputString == "$23") { myDFPlayer.play(22);      
    } else if (inputString == "$24") { myDFPlayer.play(23);    
    } else if (inputString == "$25") { myDFPlayer.play(24);    
    } else if (inputString == "$26") { myDFPlayer.play(25);    
    } else if (inputString == "$27") { myDFPlayer.play(26);    
    } else if (inputString == "$28") { myDFPlayer.play(27);   
    } else if (inputString == "$29") { myDFPlayer.play(28);  
    } else if (inputString == "$210") { myDFPlayer.play(29);   
    } else if (inputString == "$211") { myDFPlayer.play(30);     
    } else if (inputString == "$212") { myDFPlayer.play(31);      
    } else if (inputString == "$213") { myDFPlayer.play(32);   
    } else if (inputString == "$214") { myDFPlayer.play(33);    
    } else if (inputString == "$215") { myDFPlayer.play(34);    
    } else if (inputString == "$216") { myDFPlayer.play(35);   
    } else if (inputString == "$217") { myDFPlayer.play(36);     
    } else if (inputString == "$218") { myDFPlayer.play(37);     
    } else if (inputString == "$31") { myDFPlayer.play(38);      
    } else if (inputString == "$32") { myDFPlayer.play(39);     
    } else if (inputString == "$33") { myDFPlayer.play(40);    
    } else if (inputString == "$34") { myDFPlayer.play(41);     
    } else if (inputString == "$35") { myDFPlayer.play(42);     
    } else if (inputString == "$36") { myDFPlayer.play(43);    
    } else if (inputString == "$37") { myDFPlayer.play(44);    
    } else if (inputString == "$41") { myDFPlayer.play(45);    
    } else if (inputString == "$42") { myDFPlayer.play(46);    
    } else if (inputString == "$43") { myDFPlayer.play(47);     
    } else if (inputString == "$44") { myDFPlayer.play(48);    
    } else if (inputString == "$51") { myDFPlayer.play(49);     
    } else if (inputString == "$52") { myDFPlayer.play(50);   
    } else if (inputString == "$53") { myDFPlayer.play(51);    
    } else if (inputString == "$61") { myDFPlayer.play(52);   
    } else if (inputString == "$62") { myDFPlayer.play(53);    
    } else if (inputString == "$63") { myDFPlayer.play(54);     
    } else if (inputString == "$71") { myDFPlayer.play(55);     
    } else if (inputString == "$72") { myDFPlayer.play(56);     
    } else if (inputString == "$73") { myDFPlayer.play(57);    
    } else if (inputString == "$81") { myDFPlayer.play(58);     
    } else if (inputString == "$82") { myDFPlayer.play(59);     
    } else if (inputString == "$83") { myDFPlayer.play(60);      
    } else if (inputString == "$84") { myDFPlayer.play(61);    
    } else if (inputString == "$85") { myDFPlayer.play(62);     
    } else if (inputString == "$86") { myDFPlayer.play(63);     
    } else if (inputString == "$001") { myDFPlayer.play(64);      
    }
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent2() {
  while (Serial2.available()) {
    char inChar = (char)Serial2.read();
    if (inChar == '\r' || inChar == '\n') {
      stringComplete = true;
      break;
    } else {
      inputString += inChar;
    }
  }
}

void serialEvent3() {
  while (Serial3.available()) {
    char inChar = (char)Serial3.read();
    if (inChar == '\r' || inChar == '\n') {
      stringComplete = true;
      break;
    } else {
      inputString += inChar;
    }
  }
}
