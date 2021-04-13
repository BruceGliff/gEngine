#include "logger.h"

#include <typeinfo>
#include <fstream>

Debug::DebugInfo::DebugInfo(std::string const& file, int line, std::string const& explanation) :
	file_place{ file },
	line_place{ line },
	explain{ explanation }
{}

void Debug::DebugInfo::print(std::ostream& os) const
{
	os << "\tFILE:: " << file_place << "\n\tLINE:: " << line_place;
}

void Debug::Warning::Dump(std::ostream& os) const
{
	if (typeid(os) == typeid(std::cout))
		os << warnFormat << "WARN:: " << Format::SingleCode{ Format::TextFMT::StyleCode::BOLD_OFF } << explain << Format::SingleCode{} << "\n";
	else
		os << "WARN:: " << explain << "\n";

	print(os);
	os << std::endl;
}

Debug::Warning::Warning(std::string const& file, int line, std::string const& explanation) : 
	DebugInfo{ file, line, explanation }
{
	warnFormat.setCode(Format::TextFMT::ColorCode::YELLOW).setCode(Format::TextFMT::StyleCode::BOLD);
}
Debug::Message::Message(std::string const& file, int line, std::string const& explanation) : 
	DebugInfo{ file, line, explanation }
{
	warnFormat.setCode(Format::TextFMT::ColorCode::CYAN).setCode(Format::TextFMT::StyleCode::BOLD);
}
void Debug::Message::Dump(std::ostream& os) const
{
	if (typeid(os) == typeid(std::cout))
		os << warnFormat << "DMSG:: " << Format::SingleCode{ Format::TextFMT::StyleCode::BOLD_OFF } << explain << Format::SingleCode{} << "\n";
	else
		os << "DMSG:: " << explain << "\n";

	print(os);
	os << std::endl;
}

void Debug::Error::Dump(std::ostream& os) const
{
	if (typeid(os) == typeid(std::cerr))
		os << errFormat << "ERR::  " << Format::SingleCode{ Format::TextFMT::StyleCode::BOLD_OFF } << explain << Format::SingleCode{} << "\n";
	else
		os << "ERR::  " << explain << "\n";
	print(os);
	os << std::endl;
}

Debug::Error::Error(std::string const& file, int line, std::string const& explanation) : 
	DebugInfo{ file, line, explanation }
{
	errFormat.setCode(Format::TextFMT::ColorCode::RED).setCode(Format::TextFMT::StyleCode::BOLD);
}

Debug::Logger const& Debug::Logger::DumpWarnings(std::ostream& os) const
{
	for (auto&& log : logs)
	{
		if (typeid(*log) == typeid(Warning))
			log->Dump(os);
	}
	return *this;
}

Debug::Logger const& Debug::Logger::DumpErrors(std::ostream& os) const
{
	for (auto&& log : logs)
	{
		if (typeid(*log) == typeid(Error))
		{
			log->Dump(os);
		}
	}
	return *this;
}

Debug::Logger const& Debug::Logger::Dump(std::ostream& os) const
{
	for (auto&& log : logs)
		log->Dump(os);

	return *this;
}

Debug::Logger const& Debug::Logger::Dump() const
{
	for (auto&& log : logs)
		log->Dump();

	return *this;
}

Debug::Logger& Debug::Logger::AddLog(DebugInfo const* log)
{
	logs.push_back(log);
	#ifdef gDEBUG
		log->Dump();
	#endif //gDEBUG

	return *this;
}

Debug::Logger const& Debug::Logger::DumpToFile() const
{
	std::ofstream outfile{ "dump.log" };
	if (outfile.is_open())
		Dump(outfile);

	return *this;
}

Debug::Logger::~Logger()
{
	try {
#ifdef gDEBUG
		DumpToFile();
#endif //gDEBUG

	}
	catch (...)
	{
		// silence death
	}

	for (auto&& x : logs)
		delete x;
}
