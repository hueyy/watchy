#include "../../Watchy_Custom.h"

#define SERVICE_UUID_DATA "86b12870-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_BATTERY "86b12871-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_TIME "86b12872-4b70-4893-8ce6-9864fc00374d"

CustomBLEStatus status = CUSTOMBLE_DISCONNECTED;

class CustomBLEServerCallbacks : public BLEServerCallbacks
{
public:
  void onConnect(BLEServer *pServer)
  {
    if (DEBUG_MODE)
      Serial.println("BLE connected");
    status = CUSTOMBLE_CONNECTED;
  };

  void onDisconnect(BLEServer *pServer)
  {
    if (DEBUG_MODE)
      Serial.println("BLE disconnected");
    status = CUSTOMBLE_DISCONNECTED;
  };
};

class BLETimeCallbacks : public BLECharacteristicCallbacks
{
public:
  tmElements_t cTime;
  BLETimeCallbacks(tmElements_t &curTime)
  {
    cTime = curTime;
  };
  void onWrite(BLECharacteristic *RAW_DATA);
  void onRead(BLECharacteristic *pTime);
};

void BLETimeCallbacks::onWrite(BLECharacteristic *RAW_DATA)
{
  // String epochString = ;
  // HOUR.toInt();
  unsigned long epochTime = atol(RAW_DATA->getValue().c_str());
  tmElements_t tm;
  breakTime((time_t)epochTime, tm);
  Watchy::RTC.set(tm);
};

void BLETimeCallbacks::onRead(BLECharacteristic *pTime)
{
  Watchy::RTC.read(cTime);
  unsigned long epochTime = makeTime(cTime);
  pTime->setValue(epochTime.c_str());
};

CustomBLEStatus WatchyCustom::bleStatus()
{
  return status;
};

void WatchyCustom::bleBegin()
{
  if (DEBUG_MODE)
    Serial.println("bleBegin");
  BLEDevice::init(BLE_DEVICE_NAME);

  BLEServer *pServer = NULL;
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new CustomBLEServerCallbacks());

  BLEService *pDataService = NULL;
  pDataService = pServer->createService(SERVICE_UUID_DATA);

  BLECharacteristic *pBatteryCharacteristic = NULL;
  pBatteryCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_UUID_BATTERY, BLECharacteristic::PROPERTY_READ);
  float voltage = getBatteryVoltage();
  pBatteryCharacteristic->setValue(voltage);

  BLECharacteristic *pTimeCharacteristic = NULL;
  pTimeCharacteristic = pDataService->createCharacteristic(
      CHARACTERISTIC_UUID_TIME, BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pTimeCharacteristic->addDescriptor(new BLE2902());
  pTimeCharacteristic->setCallbacks(new BLETimeCallbacks(currentTime));

  pDataService->start();

  pServer->getAdvertising()->addServiceUUID(SERVICE_UUID_DATA);
  pServer->getAdvertising()->start();
  status = CUSTOMBLE_READY;
};