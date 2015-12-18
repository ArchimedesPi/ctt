#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include "../include/config.h"
#include "../include/wificonfig.h"

#include "server.h"

void wifiConnectOk();
void wifiConnectFail();

bool failBlinkState = false;

void init() {
	spiffs_mount(); // mount the flash fs to work with files

	Serial.begin(SERIAL_BAUD_RATE);
	Serial.systemDebugOutput(true);

	pinMode(TREE_PIN, OUTPUT);

	WifiStation.config(WIFI_SSID, WIFI_PASS);
	WifiStation.enable(true);
	WifiAccessPoint.enable(false);

	WifiStation.waitConnection(wifiConnectOk, 20, wifiConnectFail);
}

void wifiConnectOk() {
	debugf("connected to wifi, yay!");
	debugf("ssid: %s; ip: %s", WifiStation.getIP().toString().c_str(), WifiStation.getSSID().c_str());

	debugf("firing up server");
	startServer();
}

void failBlink() {
	digitalWrite(FAIL_BLINK_PIN, failBlinkState);
	failBlinkState = !failBlinkState;
}

void wifiConnectFail() {
	debugf("failed to connect to wifi!");
	Timer failBlinkTimer;
	pinMode(FAIL_BLINK_PIN, OUTPUT);
	failBlinkTimer.initializeMs(500, failBlink).start();
}