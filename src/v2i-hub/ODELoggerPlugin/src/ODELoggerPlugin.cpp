
/**
 * Copyright (C) 2019 LEIDOS.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this plogFile except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */


#include "ODELoggerPlugin.h"

namespace ODELoggerPlugin
{

/**
 * Construct a new ODELoggerPlugin with the given name.
 *
 * @param name The name to give the plugin for identification purposes.
 */
ODELoggerPlugin::ODELoggerPlugin(string name): PluginClient(name)
{
	PLOG(logDEBUG)<< "In ODELoggerPlugin Constructor";
	// The log level can be changed from the default here.
	//FILELog::ReportingLevel() = FILELog::FromString("DEBUG");

	// Critical section
	std::lock_guard<mutex> lock(_cfgLock);
	GetConfigValue("schedule_frequency", _scheduleFrequency);
	GetConfigValue("ForwardBsm", _forwardBSM);
	GetConfigValue("BSMKafkaTopic", _BSMkafkaTopic);
	GetConfigValue("KafkaBrokerIp", _kafkaBrokerIp);
	GetConfigValue("KafkaBrokerPort", _kafkaBrokerPort);

	if(_forwardBSM == true)

		AddMessageFilter < BsmMessage > (this, &ODELoggerPlugin::HandleBasicSafetyMessage);

	// Subscribe to all messages specified by the filters above.
	SubscribeToMessages();

	PLOG(logDEBUG) << "Exit ODELoggerPlugin Constructor";
}

/**
 * Destructor
 */

ODELoggerPlugin::~ODELoggerPlugin()
{

}


/**
 * Updates configuration settings
 */
void ODELoggerPlugin::UpdateConfigSettings()
{
	// Configuration settings are retrieved from the API using the GetConfigValue template class.
	// This method does NOT execute in the main thread, so variables must be protected
	// (e.g. using std::atomic, std::mutex, etc.).

	int instance;
	GetConfigValue("Instance", instance);


	std::lock_guard<mutex> lock(_cfgLock);
	GetConfigValue("schedule_frequency", _scheduleFrequency);
	GetConfigValue("ForwardBsm", _forwardBSM);
	GetConfigValue("BSMKafkaTopic", _BSMkafkaTopic);
	GetConfigValue("KafkaBrokerIp", _kafkaBrokerIp);
	GetConfigValue("KafkaBrokerPort", _kafkaBrokerPort);

}

/**
 * Called when configuration is changed
 *
 * @param key Key of the configuration value changed
 * @param value Changed value
 */
void ODELoggerPlugin::OnConfigChanged(const char *key, const char *value)
{
	PluginClient::OnConfigChanged(key, value);
	UpdateConfigSettings();
}

/**
 * Called on plugin state change
 *
 * @para state New plugin state
 */
void ODELoggerPlugin::OnStateChange(IvpPluginState state)
{
	PluginClient::OnStateChange(state);

	if (state == IvpPluginState_registered)
	{
		UpdateConfigSettings();
		//SetStatus("ReceivedMaps", 0);
	}
}

/**
 * Method that's called to process a message that this plugin has
 * subscribed for.  This particular method decodes the BSM message and
 * logs selective fields to a log file.
 *
 * @param msg BSMMessage that is received
 * @routeable_message not used
 */
void ODELoggerPlugin::HandleRealTimePublish(BsmMessage &msg,
		routeable_message &routeableMsg) {

	PLOG(logDEBUG)<<"HandleBasicSafetyMessage";
	auto bsm = msg.get_j2735_data();

	float speed_mph;
	int32_t bsmTmpID;

	bool isSuccess = false;
	//asn_fprint(stdout, &asn_DEF_BasicSafetyMessage, bsm);
	int32_t latitude = bsm->coreData.lat;
	int32_t longitude = bsm->coreData.Long;
	int32_t longAcceleration = bsm->coreData.accelSet.Long;


	uint16_t rawSpeed = bsm->coreData.speed;
	uint16_t rawHeading = bsm->coreData.heading;
	GetInt32((unsigned char *)bsm->coreData.id.buf, &bsmTmpID);

	// Heading units are 0.0125 degrees.
	float heading = rawHeading / 80.0;

	// The speed is contained in bits 0-12.  Units are 0.02 meters/sec.
	// A value of 8191 is used when the speed is not known.
	if (rawSpeed != 8191)
	{
		// Convert from .02 meters/sec to mph.
		speed_mph = rawSpeed / 50 * 2.2369362920544;

		isSuccess = true;
	}
	else
		speed_mph = 8191;


	PLOG(logDEBUG)<<"Logging BasicSafetyMessage data";
	_logFile << DSRCmsgID_basicSafetyMessage << ",,"; // DSRC_MessageID,  vehicle_ID
	_logFile	<< bsmTmpID << "," << bsm->coreData.secMark  << ","; // BSM_tmp_ID, transtime
	_logFile << latitude << "," <<  longitude<< ","; //X,Y
	_logFile << speed_mph << ","; //speed
	_logFile	<< longAcceleration << ","; //Intant_acceleration
	_logFile	<< heading << ","; //Heading
	_logFile	<< "" << ","; //brakeStatus
	_logFile	<< "" << ","; //brakePressed
	_logFile	<< "" << ","; //hardBraking
	_logFile	<< "" << ","; //transTo
	_logFile	<< routeableMsg.get_millisecondsSinceEpoch()<<","; //transmission_received_time in milliseconds since epoch


	if(bsm->partII != NULL) {
		if (bsm->partII[0].list.count >= partII_Value_PR_SpecialVehicleExtensions ) {
			try
			{
				if(bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.trailers !=NULL){
					_logFile<<bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.trailers->connection.pivotOffset<<",";
					_logFile<<bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.trailers->units.list.array[0]->length<<",";
					_logFile<<bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.trailers->units.list.array[0]->height[0]<<",";
				}
				else 
				{
					_logFile<<",,,";
				}
			}
			catch(exception &e)
			{
				PLOG(logDEBUG)<<"Standard Exception:: Trailers unavailable "<<e.what();
			}
			try {
				if(bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.vehicleAlerts != NULL){
					_logFile<<bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.vehicleAlerts->sirenUse<<",";	
					_logFile<<bsm->partII[0].list.array[1]->partII_Value.choice.SpecialVehicleExtensions.vehicleAlerts->lightsUse<<",";
				}
				else
				{
					_logFile<<",,";
				}
				
			}
			catch(exception &e)
			{
				PLOG(logDEBUG)<<"Standard Exception:: VehicleAlerts unavailable "<<e.what();
			}
		}
		if(bsm->partII[0].list.count >= partII_Value_PR_SupplementalVehicleExtensions){
		try {
			if(bsm->partII[0].list.array[2]->partII_Value.choice.SupplementalVehicleExtensions.classDetails != NULL) {	
				_logFile<<bsm->partII[0].list.array[2]->partII_Value.choice.SupplementalVehicleExtensions.classDetails->role[0]<<",";
				_logFile<<bsm->partII[0].list.array[2]->partII_Value.choice.SupplementalVehicleExtensions.classDetails->keyType[0]<<",";
				_logFile<<bsm->partII[0].list.array[2]->partII_Value.choice.SupplementalVehicleExtensions.classDetails->responderType<<",";
			}
			else {
				_logFile<<",,,";
			}
		}			
		catch(exception &e)
			{
				PLOG(logDEBUG)<<"Standard Exception:: classDetails unavailable "<<e.what();
			}
		}
	}
	_logFile<< endl;


}



/**
 *  Opens a new log file in the directory specified of specified name for logging BSM messages and
 *  inserts a header row with names of fields that will be logged when data is received. If a log file
 *  with the same name already exists before opening a new file, it's renamed with current timestamp suffix.
 */
void ODELoggerPlugin::OpenBSMLogFile()
{
	PLOG(logDEBUG) << "BSM Log File: " << _curFilename << std::endl;;
	//rename logfile if one already exists
	std::string newFilename = _fileDirectory + "/" + _filename + GetCurDateTimeStr() + ".csv";
	std::rename(_curFilename.c_str(), newFilename.c_str());

	_logFile.open(_curFilename);
	if (!_logFile.is_open())
		std::cerr << "Could not open log : " << strerror(errno) <<  std::endl;
	else
	{
		_logFile << "DSRC_MessageID, "
				"Vehicle ID, "
				"BSM_tmp_ID, "
				"transtime, "
				"X, Y, "
				"Speed, "
				"Instant_Acceleration, "
				"Heading, "
				"brakeStatus, "
				"brakePressure, "
				"hardBraking,  "
				"transTo, "
				"transmission_received_time, "
				"trailerPivot, "
				"trailreLength, "
				"trailerHeight, "
				"vehicleRole, "
				"vehicletype, "
				"Respondertype, "
				"SirenState, "
				"LightState, "
				"VehicleDescription, " 
				"" << endl;

	}
}

/**
 * Checks the size of the logfile and opens a new file if it's size is greater
 * than the max size specified.
 */
void ODELoggerPlugin::CheckBSMLogFileSizeAndRename(bool createNewFile)
{
	if (_logFile.is_open())
	{
		std::lock_guard<mutex> lock(_cfgLock);
		_logFile.seekp( 0, std::ios::end );
		int curFilesizeInMB = _logFile.tellp()/BYTESTOMB;
		if (curFilesizeInMB > _maxFilesizeInMB || createNewFile)
		{
			_logFile.close();
			OpenBSMLogFile();
		}
	}
}

/**
 * Returns the current data time as string.
 * @return current time in ddmmyyhhmiss format.
 */
std::string ODELoggerPlugin::GetCurDateTimeStr()
{
	auto t = std::time(nullptr);
	auto tm = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&tm, "%d%m%Y%H%M%S");
	auto str = oss.str();
	return str;
}

// Override of main method of the plugin that should not return until the plugin exits.
// This method does not need to be overridden if the plugin does not want to use the main thread.
int ODELoggerPlugin::Main()
{
	PLOG(logDEBUG) << "Starting ODELoggerPlugin...";

	uint msCount = 0;
	while (_plugin->state != IvpPluginState_error)
	{
		PLOG(logDEBUG4) << "ODELoggerPlugin Sleeping 5 minutes" << endl;

		this_thread::sleep_for(chrono::milliseconds(300000));

		// check size of the log file and open new one if needed
		CheckBSMLogFileSizeAndRename(true);
	}

	PLOG(logDEBUG) << "ODELoggerPlugin terminating gracefully.";
	return EXIT_SUCCESS;
}

} /* namespace ODELoggerPlugin */


/**
 * Main method for running the plugin
 * @param argc number of arguments
 * @param argv array of arguments
 */
int main(int argc, char *argv[])
{
	return run_plugin<ODELoggerPlugin::ODELoggerPlugin>("ODELoggerPlugin", argc, argv);
}
