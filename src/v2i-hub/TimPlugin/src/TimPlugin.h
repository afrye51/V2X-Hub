/*
 * TimPlugin.h
 *
 *  Created on: October 25, 2017
 *      Author: zinkg
 */

#ifndef TIMPLUGIN_H_
#define TIMPLUGIN_H_

#include <iostream>
#include <map>
#include <mutex>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <thread>
#include <time.h>
#include <sys/time.h>
#include <atomic>
#include <tmx/tmx.h>
#include <tmx/IvpPlugin.h>
#include <tmx/messages/IvpJ2735.h>
#include <GeoVector.h>
#include <boost/date_time.hpp>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>


#include "PluginUtil.h"


#include "PluginClient.h"

#include <ApplicationMessage.h>
#include <ApplicationDataMessage.h>

#include <tmx/messages/auto_message.hpp>


#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QCoreApplication>
#include <QHostAddress>
#include <QRegExp>
#include <QStringList>
#include <QSharedPointer>
#include <QObject>

#ifdef __linux__
#include <signal.h>
#include <unistd.h>
#endif
#include <qhttpengine/server.h>
#include <qserverPedestrian/OAIApiRouter.h>
#include <qserverPedestrian/OAIPSM.h>






using namespace std;

using namespace tmx;
using namespace tmx::utils;
using namespace tmx::messages;


#define INPUTSREADY "Have Map/Spat/Veh"
#define INGRESSREGION "Ingress Region"
#define EGRESSREGION "Egress Region"



namespace TimPlugin {


class TimPlugin: public PluginClient {
public:
	TimPlugin(std::string);
	virtual ~TimPlugin();
	int Main();

protected:

	void UpdateConfigSettings();

	// Virtual method overrides.
	void OnConfigChanged(const char *key, const char *value);
	//void OnMessageReceived(IvpMessage *msg);
	void OnStateChange(IvpPluginState state);

	bool TimDuration();
	bool LoadTim(TravelerInformation *tim, const char *mapFile);
	int  StartWebService();
	void TimRequestHandler(QHttpEngine::Socket *socket);
	//void BroadCastTIM();


private:

	pthread_mutex_t _settingsMutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_t _timMutex = PTHREAD_MUTEX_INITIALIZER;

	uint64_t _frequency = 0;

	std::string _startDate;
	std::string _stopDate;
	std::string _startTime;
	std::string _stopTime;
	std::string _timupdate; 
	uint16_t webport;
	std::string webip; 

	TravelerInformation _tim;

	mutex _mapFileLock;
	string _mapFile;
	std::ofstream tmpTIM;
	atomic<bool> _isMapFileNew{false};
	atomic<bool> _isTimFileNew{false};
	bool _isTimLoaded = false;
	unsigned int _speedLimit = 0;
	int _lastMsgIdSent = -1;

};
std::mutex _cfgLock;
}
#endif
