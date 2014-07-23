
// A simple VC++ code that
// opens a serial port and write Binary commands to Zaber devices.
//
// NOTE: CLR support is required (compile with /clr option)
//
// For full Binary protocol specification,
// see http://www.zaber.com/wiki/Manuals/Binary_Protocol_Manual
//
// Prepared 8 Nov 2013 by AAL
 
#include "StdAfx.h"
#using <System.dll>
 
// Sets duration to wait for when polling for available bytes to read
#define SLEEP_DURATION_MS	1
 
// Some Binary message command numbers
#define CMD_HOME	 	 	 	 	 1
#define CMD_LIMIT_ACTIVE	 	 	 9
#define CMD_MOVE_ABSOLUTE	 	 	 20
#define CMD_MOVE_RELATIVE			 21
#define CMD_UNEXPECTED_POS	 	 	 13
#define CMD_RETURN_CURRENT_POSITION	 60
#define CMD_ERROR	 	 	 	 	 255
#define CMD_RETURN_STATUS			 54

using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace System::Text;
 /*
void SendCommand(SerialPort^ port, Byte unit, Byte command, Int32 data);
void ReceiveReply(SerialPort^ port, Byte& unit, Byte& command, Int32& data);
void WaitForReply(SerialPort^ port, Byte expectUnit, Byte expectCommand, Byte& unit, Byte& command, Int32& data);
 */

/*
//int _tmain(int argc, _TCHAR* argv[])
int test(void)
{
 SerialPort^ port;
 Byte unit;
 Byte command;
 Int32 data;
 
 // Set up serial port
 port = gcnew SerialPort();
 port->PortName = "COM6";
 port->BaudRate = 9600;
 port->DataBits = 8;
 port->Parity = Parity::None;
 port->StopBits = StopBits::One;
 port->Handshake = Handshake::None;
 
 // Open port
 port->Open();
 
 // Home device 1
 SendCommand(port, 1, CMD_HOME, 0);
 WaitForReply(port, 1, CMD_HOME, unit, command, data);

  SendCommand(port, 2, CMD_HOME, 0);
 WaitForReply(port, 2, CMD_HOME, unit, command, data);
 
 // Move device 1 to position 1000
 SendCommand(port, 1, CMD_MOVE_ABSOLUTE, 50000);
 WaitForReply(port, 1, CMD_MOVE_ABSOLUTE, unit, command, data);
 
 SendCommand(port, 2, CMD_MOVE_ABSOLUTE, 90000);
 WaitForReply(port, 2, CMD_MOVE_ABSOLUTE, unit, command, data);

 // Query position of device 1
 SendCommand(port, 1, CMD_RETURN_CURRENT_POSITION, 0);
 WaitForReply(port, 1, CMD_RETURN_CURRENT_POSITION, unit, command, data);
 
 Console::WriteLine("Current position is " + data);
 
 // Close port
 port->Close();
 
 return 0;
}
*/

Zaber::Zaber()
{
	// Set up serial port
	 port = gcnew SerialPort();
	 port->PortName = "COM6";
	 port->BaudRate = 9600;
	 port->DataBits = 8;
	 port->Parity = Parity::None;
	 port->StopBits = StopBits::One;
	 port->Handshake = Handshake::None;

	 unitMove = "microsteps";
	
}

int Zaber::openPort(void)
{
	// if the port is closed, open. If it's already open, return -1.
	if(!port->IsOpen)
	{ 
		// Open port
		port->Open();
		return 0;
	}
	else
	{
		return -1;
	}
}

int Zaber::closePort(void)
{
	//If the port is open, close it. If not, return -1
	if(port->IsOpen)
	{
		//close port
		port->Close();
		return 0;
	}
	else
	{	
		return -1;
	}
}

void Zaber::moveStageAbsolute(double distanceX, double distanceY)
{

	if(distanceX<0 || distanceY<0)
	{
		//printf("%i < 0, Zaber cannot move to a negative absolute position\n", distance);
		return;
	}

	microstepsX = (unsigned int) convertToMicrosteps(distanceX, unitMove);
	microstepsY = (unsigned int) convertToMicrosteps(distanceY, unitMove);
	
	//Send command to move in X direction
	device = 1;
	command = CMD_MOVE_ABSOLUTE;
	data = microstepsX;
	SendCommand();
	WaitForReply(1, CMD_MOVE_ABSOLUTE);

	//Send command to move in Y direction
	device = 2;
	command = CMD_MOVE_ABSOLUTE;
	data = microstepsY;
	SendCommand();
	WaitForReply(2, CMD_MOVE_ABSOLUTE);

	//Report stage position:
	getStagePosition();
}

void Zaber::moveStageRelative(double distanceX, double distanceY)//, char* unit)
{

	int distance;

	//Convert absolute distance into microsteps
	//TICTOC::timer().tic("StageMovementConvertToMicroSteps");
	microstepsX = (unsigned int) convertToMicrosteps(distanceX, unitMove);
	microstepsY = (unsigned int) convertToMicrosteps(distanceY, unitMove);
	//TICTOC::timer().toc("StageMovementConvertToMicroSteps");

	//Send data to move in X direction
	
	device = 1;
	command = CMD_MOVE_RELATIVE;
	data = microstepsX;
	TICTOC::timer().tic("StageMovementSendXCommand");
	SendCommand();
	TICTOC::timer().toc("StageMovementSendXCommand");
	TICTOC::timer().tic("StageMovementWaitXCommand");
	//WaitForReply(1, CMD_MOVE_RELATIVE);
	TICTOC::timer().toc("StageMovementWaitXCommand");
	/*distance = data;
	posX = convertFromMicrosteps(distance, unitMove);*/
	
	//Send Data to move in Y direction
	
	device = 2;
	command = CMD_MOVE_RELATIVE;
	data = microstepsY;
	TICTOC::timer().tic("StageMovementSendYCommand");
	SendCommand();
	TICTOC::timer().toc("StageMovementSendYCommand");
	TICTOC::timer().tic("StageMovementWaitYCommand");
	//WaitForReply(2, CMD_MOVE_RELATIVE);
	TICTOC::timer().toc("StageMovementWaitYCommand");
	/*distance = data;
	posY = convertFromMicrosteps(distance, unitMove);
*/
	/*
	TICTOC::timer().tic("StageMovementWaitTwoDevicesCommand");
	 WaitForReplyEitherDevice(1, CMD_MOVE_RELATIVE, 2, CMD_MOVE_RELATIVE);  // wait for either reply
    distance = convertFromMicrosteps(data, unitMove);          // find final position
	if(device == 1)                                            // update relevant position
    {
        posX = distance;
    }
    else
    {
        posY = distance;
    }

    WaitForReplyEitherDevice(1, CMD_MOVE_RELATIVE, 2, CMD_MOVE_RELATIVE);
    distance = convertFromMicrosteps(data, unitMove);
    if(device == 1)
    {
        posX = distance;
    }
    else
    {
        posY = distance;
    }
	TICTOC::timer().toc("StageMovementWaitTwoDevicesCommand");
*/

	////Report stage position
	//TICTOC::timer().tic("StageMovementGetStagePosition");
	////getStagePosition();
	//TICTOC::timer().toc("StageMovementGetStagePosition");
	
}

void Zaber::getStagePosition(void)
{

	int distance;

	// Send command to request x position
	device = 1;
	command = CMD_RETURN_CURRENT_POSITION;
	data = 0;
	SendCommand();

	//Wait for device to reply with x position
	WaitForReply(1, CMD_RETURN_CURRENT_POSITION);
	distance = data;
	posX = convertFromMicrosteps(distance, unitMove);
	
	//Send command to request y position.
	device = 2;
	command = CMD_RETURN_CURRENT_POSITION;
	data = 0;
	SendCommand();

	//Wait for device to reply with y position
	WaitForReply(2, CMD_RETURN_CURRENT_POSITION);
	distance = data;
	posY = convertFromMicrosteps(distance, unitMove);
}
void Zaber::SetMoveUnit(System::String^ unitMoveString)
{
	//Sets move unit based on user input.
	if (!System::String::Compare(unitMoveString, "Centimeter"))
		unitMove = "centimeter";
	else if (!System::String::Compare(unitMoveString, "Millimeter"))
		unitMove = "millimeter";
	else if (!System::String::Compare(unitMoveString, "Micrometer"))
		unitMove = "micron";
	else if (!System::String::Compare(unitMoveString, "Microstep"))
		unitMove = "microstep";

}
int Zaber::requestZaberStatus(void)
{
	device = 1;
	command = CMD_RETURN_STATUS;
	data = 0;
	SendCommand();
	WaitForReply(1, CMD_RETURN_STATUS);
	if (data !=0)
	{
		return 1; //x-axis is moving
	}
	else
	{
		device = 2;
		command = CMD_RETURN_STATUS;
		data = 0;
		SendCommand();
		WaitForReply(2, CMD_RETURN_STATUS);
		if (data != 0)
		{
			return 2; //y-axis is moving
		}
		else 
		{
			return 0; //zaber is stable
		}
	}	
}

// BEGIN PRIVATE FUNCTIONS
 
/// <summary>
/// Format and send a Binary command
/// </summary>
/// <param name="port">Serial port where Zaber devices are attached to</param>
/// <param name="unit">Unit number of Zaber device to address command to</param>
/// <param name="command">Binary message command number</param>
/// <param name="data">Data value for Binary command</param>
void Zaber::SendCommand(void)
{
 array<Byte>^ packet = gcnew array<Byte>(6);
 
 packet[0] = device;
 packet[1] = command;
 
 packet[2] = data & 0xFF;
 packet[3] = (data >> 8) & 0xFF;
 packet[4] = (data >> 16) & 0xFF;
 packet[5] = (data >> 24) & 0xFF;
 
 port->Write(packet, 0, 6);
}
 
/// <summary>
/// Wait and return the first incoming Binary reply message
/// </summary>
/// <param name="port">Serial port where Zaber devices are attached to</param>
/// <param name="unit">Unit number in the reply message</param>
/// <param name="command">Command number in the reply message</param>
/// <param name="data">Data value in the reply message</param>
void Zaber::ReceiveReply(void)
{
 while(port->BytesToRead < 6)
 {
 	 Thread::Sleep(SLEEP_DURATION_MS);
 }
 
 array<Byte>^ packet = gcnew array<Byte>(6);
 port->Read(packet, 0, 6);
 
 device = packet[0];
 command = packet[1];
 data = packet[2]
 	 	 + (packet[3] << 8)
 	 	 + (packet[4] << 16)
 	 	 + (packet[5] << 24);
}
 
/// <summary>
/// Wait until an expected Binary reply message arrives.
///
/// All other incoming replies are ignored.
///
/// This function returns when a reply message arrives
/// with matching unit number and command number. The function
/// also returns if the command number indicates other conditions
/// that affect the device operation.
///
/// Error logging and handling can be added to this function.
/// </summary>
/// <param name="port">Serial port where Zaber devices are attached to</param>
/// <param name="unit">Unit number in the reply message</param>
/// <param name="command">Command number in the reply message</param>
/// <param name="data">Data value in the reply message</param>
void Zaber::WaitForReply(Byte expectDevice, Byte expectCommand)
{
 do
 {
 	 //ReceiveReply(port, device, command, data);
	 ReceiveReply();
 } while( ! (device == expectDevice
 	 	 	 && (command == expectCommand
 	 	 	 	 || command == CMD_HOME	 	 	 	 // Auto-home routine has been triggered
 	 	 	 	 || command == CMD_LIMIT_ACTIVE	 	 // Device has reached its travel limit
 	 	 	 	 || command == CMD_UNEXPECTED_POS	 // Device has recently stalled or displaced
 	 	 	 	 || command == CMD_ERROR) ) );	 	 // Device is sending an error reply
}


void Zaber::WaitForReplyEitherDevice(Byte expectDevice1, Byte expectCommand1, Byte expectDevice2, Byte expectCommand2)
{
 do
 {
     //ReceiveReply(port, device, command, data);
     ReceiveReply();
 } while( !( (device == expectDevice1)  
			&& (command == expectCommand1               // Reply matches device and command 1
                 || command == CMD_HOME              // Auto-home routinehas been triggered
                 || command == CMD_LIMIT_ACTIVE      // Device has reached its travel limit
                 || command == CMD_UNEXPECTED_POS    // Device has recently stalled or displaced
                 || command == CMD_ERROR))           // Device is sending an error reply
          || (device == expectDevice2                // OR reply matches device and command 2
			&& (command == expectCommand2
                 || command == CMD_HOME              // Auto-home routine has been triggered
                 || command == CMD_LIMIT_ACTIVE      // Device has reached its travel limit
                 || command == CMD_UNEXPECTED_POS    // Device has recently stalled or displaced
                 || command == CMD_ERROR)) );      // Device is sending an error reply
}


int Zaber::convertToMicrosteps(double distance, char* unit){
	int out = 0;
	double conversion = 0.15625e-6; // specific to stage "Microstep Size (Device Resolution)"
	if(strcmp(unit,"centimeter") == 0)
	{
		  out = (distance*(1e-2)*(1/conversion));
		  distance = 1e2*out*conversion +.5;
	}
	else if(strcmp(unit,"millimeter") == 0)
	{
		  out = (distance*(1e-3)*(1/conversion));
		  distance = 1e3*out*conversion +.5;
	}
	else if(strcmp(unit,"micron") == 0)
	{
		  out = (distance*(1e-6)*(1/conversion));
		  distance = 1e6*out*conversion +.5;
	}
	else if(strcmp(unit,"microstep") == 0)
	{
		  out = (distance);
	}
	else
	{
		//printf("**Error: \"%s\" is an unknown unit of measurment used**\n", unit);
 		distance = 0;
	}
	return out;
}

double Zaber::convertFromMicrosteps(int distance, char* unit){
	double out = 0;
	double conversion = 0.15625e-6;
	if(strcmp(unit,"centimeter") == 0)
	{
		  out = (double)(distance*(1e2)*(conversion));
		  distance = 1e-2*out*(1/conversion) +.5;
	}
	else if(strcmp(unit,"millimeter") == 0)
	{
		  out = (double)(distance*(1e3)*(conversion));
		  distance = 1e-3*out*(1/conversion) +.5;
	}
	else if(strcmp(unit,"micron") == 0)
	{
		  out = (double)(distance*(1e6)*(conversion));
		  distance = 1e-6*out*(1/conversion) +.5;
	}
	else if(strcmp(unit,"microstep") == 0)
	{
		  out = (double)(distance);
	}  
	else
	{
		//printf("**Error (Convert from Microsteps): \"%s\" is an unknown unit of measurment used**\n", unit);
 		distance = 0;
	}
	return out;
}



