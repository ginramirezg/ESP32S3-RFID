
#include <MFRC522v2.h>
#include <MFRC522DriverSPI.h>
//#include <MFRC522DriverI2C.h>
#include <MFRC522DriverPinSimple.h>
#include <MFRC522Debug.h>


MFRC522DriverPinSimple ss_pin(5);

MFRC522DriverSPI driver{ss_pin}; // Crear el controlador SPI
//MFRC522DriverI2C driver{};     // Crear el controlador I2C
MFRC522 mfrc522{driver};         // Crear la instancia MFRC522

MFRC522::MIFARE_Key key; // Clave de autenticación

byte blockAddress = 2; // Dirección del bloque de memoria donde escribir
byte newBlockData[17] = {"Equipo alpha"}; // Datos a escribir en la tarjeta
//byte newBlockData[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};   // Borrar datos
byte bufferblocksize = 18; // Tamaño del buffer de lectura
byte blockDataRead[18]; // Datos leídos del bloque

void setup() {
  Serial.begin(115200);  // Iniciar comunicación serie
  while (!Serial);       // Esperar hasta que el puerto serie esté listo
  
  mfrc522.PCD_Init();    // Inicializar el lector MFRC522
  Serial.println(F("Advertencia: este ejemplo sobrescribe un bloque en tu tarjeta, úsalo con precaución."));
 
  // Preparar clave de autenticación - por defecto todas están en FFFFFFFFFFFF desde fábrica.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void loop() {
  // Verificar si hay una nueva tarjeta presente
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(500);
    return;
  }

  // Mostrar el UID de la tarjeta
  Serial.print("----------------\nUID de la tarjeta: ");
  MFRC522Debug::PrintUID(Serial, (mfrc522.uid));
  Serial.println();

  // Autenticar el acceso al bloque especificado usando la clave KEY_A = 0x60
  if (mfrc522.PCD_Authenticate(0x60, blockAddress, &key, &(mfrc522.uid)) != 0) {
    Serial.println("Fallo en la autenticación.");
    return;
  }
  
  // Escribir datos en el bloque especificado
  if (mfrc522.MIFARE_Write(blockAddress, newBlockData, 16) != 0) {
    Serial.println("Fallo en la escritura.");
  } else {
    Serial.print("Datos escritos correctamente en el bloque: ");
    Serial.println(blockAddress);
  }

  // Autenticar nuevamente antes de leer los datos
  if (mfrc522.PCD_Authenticate(0x60, blockAddress, &key, &(mfrc522.uid)) != 0) {
    Serial.println("Fallo en la autenticación.");
    return;
  }

  // Leer datos del bloque especificado
  if (mfrc522.MIFARE_Read(blockAddress, blockDataRead, &bufferblocksize) != 0) {
    Serial.println("Fallo en la lectura.");
  } else {
    Serial.println("Lectura exitosa!");
    Serial.print("Datos en el bloque ");
    Serial.print(blockAddress);
    Serial.print(": ");
    for (byte i = 0; i < 16; i++) {
      Serial.print((char)blockDataRead[i]);  // Imprimir como caracteres
    }
    Serial.println();
  }
  
  // Detener la comunicación con la tarjeta
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  delay(2000);  // Retraso para facilitar la lectura
}
