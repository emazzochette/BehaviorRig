#pragma once


using namespace System;
using namespace System::IO::Ports;
using namespace System::Threading;
using namespace System::Text;


public ref class Zaber{
	public:
		double posX; // reports x-axis stage position in "unitMove" units.
		double posY; // reports y-axis stage position in "unitMove" units.
		double posZ; // reports z-axis position
		char* unitMove; // user specified unit of movement and reporting. Options are: "centimeter", "millimeter", "micrometer", "microsteps"
		SerialPort^ port; // uses .NET 3.5 Serial port communication tool

	private:
		//Information to be sent and received over the serial port
		Byte device; // 1 = x-axis, 2 = y-axis
		Byte command; // command to be sent to device (i.e. move absolute)
		Int32 data; // data associated with the comment.

		unsigned int microstepsX, microstepsY, microstepsZ; // number of microsteps to be moved in specified direction.
		
	public:
		Zaber();
		int openPort(void);
		int closePort(void);
		void moveStageAbsolute(double distanceX, double distanceY);
		void moveStageRelative(double distanceX, double distanceY);
		void getStagePosition(void);
		void SetMoveUnit(System::String^ unitMoveString);
		int requestZaberStatus(void);

	private:
		void SendCommand(void);
		void ReceiveReply(void);
		void WaitForReply(Byte expectDevice, Byte expectCommand);
		int convertToMicrosteps(double distance, char* unit);
		double convertFromMicrosteps(int distance, char* unit);


	};
