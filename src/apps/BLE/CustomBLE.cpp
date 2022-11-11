#include "../../Watchy_Custom.h"

#define SERVICE_UUID_DATA "86b12870-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_BATTERY "86b12871-4b70-4893-8ce6-9864fc00374d"
#define CHARACTERISTIC_UUID_TIME "86b12872-4b70-4893-8ce6-9864fc00374d"

<<<<<<< HEAD
CustomBLEStatus CUSTOM_BLE_STATUS = CUSTOMBLE_DISCONNECTED;
=======
CustomBLEStatus custom_status = CUSTOMBLE_DISCONNECTED;
>>>>>>> 6ce9113 (chore: update watchy library)

class CustomBLEServerCallbacks : public BLEServerCallbacks
{
public:
  void onConnect(BLEServer *pServer)
  {
    if (DEBUG_MODE)
      Serial.println("BLE connected");
<<<<<<< HEAD
    CUSTOM_BLE_STATUS = CUSTOMBLE_CONNECTED;
=======
      custom_status = CUSTOMBLE_CONNECTED;
>>>>>>> 6ce9113 (chore: update watchy library)
  };

  void onDisconnect(BLEServer *pServer)
  {
    if (DEBUG_MODE)
      Serial.println("BLE disconnected");
<<<<<<< HEAD
    CUSTOM_BLE_STATUS = CUSTOMBLE_DISCONNECTED;
=======
      custom_status = CUSTOMBLE_DISCONNECTED;
>>>>>>> 6ce9113 (chore: update watchy library)
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
  std::string rawData = RAW_DATA->getValue();
  char *endptr;
  unsigned long epochTime = strtoul(rawData.c_str(), &endptr, 10);
  tmElements_t tm;
  breakTime((time_t)epochTime, tm);
  Watchy::RTC.set(tm);
};

void BLETimeCallbacks::onRead(BLECharacteristic *pTime)
{
  Watchy::RTC.read(cTime);
  unsigned long epochTime = makeTime(cTime);
  // pTime->setValue(epochTime.c_str());
};

CustomBLEStatus WatchyCustom::bleStatus()
{
  return custom_status;
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
<<<<<<< HEAD
  CUSTOM_BLE_STATUS = CUSTOMBLE_READY;
=======
  custom_status = CUSTOMBLE_READY;
>>>>>>> 6ce9113 (chore: update watchy library)
};