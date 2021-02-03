#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "formater.h"

namespace Debug
{
	// contains plain info: file and line
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
		DebugInfo(std::string const& file, int line, std::string const& explanation);

		virtual void Dump(std::ostream& os = std::cout) const = 0;
		void print(std::ostream& os) const;
		virtual ~DebugInfo() {};
	};
	class Warning final : public DebugInfo
	{
		Format::Formater warnFormat;
	public:
		Warning() 							= delete;
		Warning(Warning const&)				= delete;
		Warning(Warning&&) 					= delete;
		Warning& operator= (Warning const&) = delete;
		Warning& operator= (Warning&&) 		= delete;

		Warning(std::string const& file, int line, std::string const& explanation);
		void Dump(std::ostream& os = std::cout) const override;
	};
	class Error final : public DebugInfo
	{
		Format::Formater errFormat;
	public:
		Error() 						= delete;
		Error(Error const&)				= delete;
		Error(Error&&) 					= delete;
		Error& operator= (Error const&) = delete;
		Error& operator= (Error&&) 		= delete;

		Error(std::string const& file, int line, std::string const& explanation);
		void Dump(std::ostream& os = std::cerr) const override;
	};

	class Logger
	{
		std::vector<DebugInfo const *> logs;

	public:
		Logger() 							= default;
		Logger(Logger const&)				= delete;
		Logger(Logger&&) 					= delete;
		Logger& operator= (Logger const&) 	= delete;
		Logger& operator= (Logger&&) 		= delete;

		Logger const& DumpWarnings(std::ostream& os = std::cout) const;
		Logger const& DumpErrors(std::ostream& os = std::cerr) const;
		Logger const& Dump(std::ostream& os) const;
		Logger const& Dump() const;

		Logger& AddLog(DebugInfo const* log);
		Logger const& DumpToFile() const;

		~Logger();

	};
}