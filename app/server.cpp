#include <user_config.h>
#include <SmingCore/SmingCore.h>

#include "../include/config.h"

HttpServer server;

bool serverRunning = false;

bool treeState = false; // start off

void setTreeState(bool state);

#include "routes.h"

void startServer() {
	if (serverRunning) return;

	server.listen(80);
	registerRoutes(server);
	
	serverRunning = true;
}

void setTreeState(bool state) {
	treeState = state;
	digitalWrite(TREE_PIN, treeState);
}