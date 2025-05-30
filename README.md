# Proyecto de Lectura y Escritura RFID con MFRC522

## Descripción
En este proyecto, utilizamos un lector RFID MFRC522 con una placa ESP32S3 para leer y escribir datos en tarjetas RFID. Autenticamos un bloque de memoria, escribimos datos y luego los leemos para verificar la escritura.

## Hardware Utilizado
- **Módulo RFID MFRC522**
- **Placa ESP32S3 (También podría utilizarse una placa Arduino)**
- **Tarjetas RFID MIFARE**
- **Cableado para conexión SPI**

## Archivos Utilizados
- **Código principal**: `rfid_rw.ino`
- **Bibliotecas necesarias**:
  - `MFRC522v2.h`
  - `MFRC522DriverSPI.h`
  - `MFRC522DriverPinSimple.h`
  - `MFRC522Debug.h`

##  Instalación y Uso
1. **Instalamos las bibliotecas:** Nos aseguramos de tener las bibliotecas necesarias en el gestor de Arduino.
2. **Conectamos el hardware:** Vinculamos el módulo MFRC522 correctamente a la placa mediante SPI.
3. **Cargamos el código:** Compilamos y subimos el código `rfid_rw.ino` a la placa.
4. **Ejecutamos el programa:** Abrimos el monitor serie para visualizar las lecturas y escrituras en la tarjeta RFID.
5. **Verificamos los resultados:** El código escribirá `"Equipo alpha"` en un bloque específico y luego lo leerá para asegurarnos de que la escritura se realizó correctamente.

## Advertencia
Este código sobrescribe datos en la tarjeta RFID, por lo que recomendamos utilizarlo con precaución en tarjetas de prueba.

<img src="https://github.com/ginramirezg/ESP32S3-RFID/blob/main/Imagen.jpg">
