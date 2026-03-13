#include "AuxPort.h"

int main(int argc, char*argv[])
{
	if (argc != 5)
	{
		AuxPort::Logger::Log("Usage : ./AuxImpulse <impulse_file> <output_folder> <vstPluginWithPath> iterations",AuxPort::LogType::Error,AuxPort::ColourType::Red);
		return 0;
	}
	std::string impulseFile = argv[1];
	std::string outputFolder = argv[2];
	std::string vstPluginWithPath = argv[3];
	std::string iterations = argv[4];

	if (impulseFile.find(".wav") < 0)
	{
		AuxPort::Logger::Log("Can only process .wav files",AuxPort::LogType::Error,AuxPort::ColourType::Red);
		return 0;
	}

	if (!std::filesystem::exists(outputFolder))
	{
		AuxPort::Logger::Log("Folder does not exist, Attempting to create directory", AuxPort::LogType::Warning, AuxPort::ColourType::Yellow);
		if (!std::filesystem::create_directory(outputFolder))
		{
			AuxPort::Logger::Log("Invalid Directory", AuxPort::LogType::Error, AuxPort::ColourType::Red);
			return 0;
		}
		AuxPort::Logger::Log("Directory Created",AuxPort::LogType::Success,AuxPort::ColourType::Green);
	}

	try
	{
		auto i = std::stoi(iterations);
	}
	catch (std::exception& ex)
	{
		AuxPort::Logger::Log("iterations has to be a valid number",AuxPort::LogType::Error,AuxPort::ColourType::Red);
		return 0;
	}
	



}
