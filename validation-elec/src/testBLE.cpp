#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic *pCharacteristic;

void testBLE() {
  BLEDevice::init("ValidationElec"); // Nom du périphérique BLE

  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService("180A");  // UUID standard (service "Device Information")

  pCharacteristic = pService->createCharacteristic(
                      "2A29",                     // UUID caractéristique fabricant
                      BLECharacteristic::PROPERTY_READ
                    );

  pCharacteristic->setValue("ELEC_TEST");  // Valeur lue par le téléphone

  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->start();

  Serial.println("BLE actif. Connecte-toi via ton téléphone.");
}
