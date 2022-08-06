#include "./Watchy_Custom.h"

#define SERVICE_UUID_DATA "86b12870-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_BATTERY "86b12871-4b70-4893-8ce6-9864fc00374d"

CustomBLEStatus status = CUSTOMBLE_DISCONNECTED;

class CustomBLEServerCallbacks : public BLEServerCallbacks {
  public:
    void onConnect(BLEServer *pServer) {
      if(DEBUG_MODE) Serial.println("BLE connected");
      status = CUSTOMBLE_CONNECTED;
    };

    void onDisconnect(BLEServer *pServer) {
      if(DEBUG_MODE) Serial.println("BLE disconnected");
      status = CUSTOMBLE_DISCONNECTED;
    }
};

void WatchyCustom::bleBegin()
{
  if(DEBUG_MODE) Serial.println("bleBegin");
  BLEDevice::init(BLE_DEVICE_NAME);

  BLEServer *pServer = NULL;
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new CustomBLEServerCallbacks());

  BLEService *pDataService = NULL;
  pDataService = pServer->createService(SERVICE_UUID_DATA);

  BLECharacteristic *pBatteryCharacteristic = NULL;
  pBatteryCharacteristic = pDataService->createCharacteristic(
    CHARACTERISTIC_UUID_BATTERY, BLECharacteristic::PROPERTY_READ
  );
  float voltage = getBatteryVoltage();
  pBatteryCharacteristic->setValue(voltage);

  pDataService->start();

  pServer->getAdvertising()->addServiceUUID(SERVICE_UUID_DATA);
  pServer->getAdvertising()->start();
  status = CUSTOMBLE_READY;
}

CustomBLEStatus WatchyCustom::bleStatus(){
  return status;
}