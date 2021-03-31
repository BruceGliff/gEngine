#pragma once

#include <string>
#include <vector>
#include <iostream>

#ifdef gWINDOWS
	#include "formater_WIN.h"
#endif // gWINDOWS
#ifndef gWINDOWS
	#include "formater_UNIX.h"
#endif // gWINDOWS

namespace Debug
{
	// contains plain info: file, line and what happened
	class DebugInfo
	{
		std::string const file_place;
		int			const line_place;
	protected:
		std::string const explain;
	public:
		DebugInfo()								= delete;
		DebugInfo(DebugInfo const&)				= delete;
		DebugInfo(DebugInfo&&)					= delete;
		DebugInfo& operator= (DebugInfo const&) = delete;
		DebugInfo& operator= (DebugInfo&&)		= delete;

		// only one constructor 
		DebugInfo(std::string const& file, int line, std::string const& explanation);

		// Function which called by Warning and Error class to dump DebugInfo
		virtual void Dump(std::ostream& os = std::cout) const = 0;
		// Dump DebugInfo without formating
		void print(std::ostream& os) const;
		virtual ~DebugInfo() {};
	};
	// class represent Warnings with specific formating
	class Warning final : public DebugInfo
	{
		Format::Formater warnFormat;
	public:
		Warning() 							= delete;
		Warning(Warning const&)				= delete;
		Warning(Warning&&) 					= delete;
		Warning& operator= (Warning const&) = delete;
		Warning& operator= (Warning&&) 		= delete;

		// only one constructor
		Warning(std::string const& file, int line, std::string const& explanation);
		// Dump DebugInfo woth formating to specific out stream
		void Dump(std::ostream& os = std::cout) const override;
	};
	// class represent debug messages
	class Message final : public DebugInfo
	{
		Format::Formater warnFormat;
	public:
		Message() 							= delete;
		Message(Message const&)				= delete;
		Message(Message&&) 					= delete;
		Message& operator= (Message const&) = delete;
		Message& operator= (Message&&) 		= delete;

		// only one constructor
		Message(std::string const& file, int line, std::string const& explanation);
		// Dump DebugInfo woth formating to specific out stream
		void Dump(std::ostream& os = std::cout) const override;
	};
	// class represent Errors with specific formating
	class Error final : public DebugInfo
	{
		Format::Formater errFormat;
	public:
		Error() 						= delete;
		Error(Error const&)				= delete;
		Error(Error&&) 					= delete;
		Error& operator= (Error const&) = delete;
		Error& operator= (Error&&) 		= delete;

		// only one constructor
		Error(std::string const& file, int line, std::string const& explanation);
		// Dump DebugInfo woth formating to specific out stream
		void Dump(std::ostream& os = std::cerr) const override;
	};

	// Class contains all logs due to runnig program
	class Logger
	{
		// vector of logs: Errors and Warnings
		std::vector<DebugInfo const *> logs;

	public:
		Logger() 							= default;
		Logger(Logger const&)				= delete;
		Logger(Logger&&) 					= delete;
		Logger& operator= (Logger const&) 	= delete;
		Logger& operator= (Logger&&) 		= delete;

		// Dump only Warnings to specific out stream (cout as default)
		Logger const& DumpWarnings(std::ostream& os = std::cout) const;
		// Dump only Errors to specific out stream (cerr as default)
		Logger const& DumpErrors(std::ostream& os = std::cerr) const;
		// Dump only Messages to specific out stream (cout as default)
		Logger const& DumpMessages(std::ostream& os = std::cerr) const;
		// Dump all logs to specific out stream
		Logger const& Dump(std::ostream& os) const;
		// Dump all logs to cout
		Logger const& Dump() const;

		// Add log
		Logger& AddLog(DebugInfo const* log);
		// Dump all logs to "dump.log" file
		Logger const& DumpToFile() const;

		~Logger();

	};
}