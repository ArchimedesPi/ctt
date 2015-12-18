#ifndef __CTT_ROUTES__
#define __CTT_ROUTES__

#include <SmingCore/SmingCore.h>

void indexRoute(HttpRequest &request, HttpResponse &response) {
	response.sendFile("index.html");
}

void onFileRoute(HttpRequest &request, HttpResponse &response)
{
	String file = request.getPath();
	if (file[0] == '/')
		file = file.substring(1);

	if (file[0] == '.')
		response.forbidden();
	else
	{
		// response.setCache(86400, true); // It's important to use cache for better performance.
		response.sendFile(file);
	}
}
void apiTreeState(HttpRequest &request, HttpResponse &response) {
	if (request.getRequestMethod() == RequestMethod::GET) {
		JsonObjectStream *stream = new JsonObjectStream();
		JsonObject &json = stream->getRoot();
		json["on"] = treeState;
		response.sendJsonObject(stream);
	} else if (request.getRequestMethod() == RequestMethod::POST) {
		DynamicJsonBuffer jsonBuffer;
		JsonObject &json = jsonBuffer.parseObject(request.getBody());
		setTreeState(json["on"]);

		JsonObjectStream *stream = new JsonObjectStream();
		JsonObject &json_resp = stream->getRoot();
		json_resp["ok"] = true;
		response.sendJsonObject(stream);
	}
}

void registerRoutes(HttpServer &server) {
	server.addPath("/", indexRoute);
	// api
	server.addPath("/api/tree/state", apiTreeState);
	server.setDefaultHandler(onFileRoute);
}

#endif