#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <fstream>

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
		DebugInfo(std::string const& file, int line, std::string const& explanation) : 
			file_place{ file }, 
			line_place{ line },
			explain{explanation}
		{}

		virtual void Dump(std::ostream& os = std::cout) const = 0;
		void print(std::ostream& os) const
		{
			os << "\tFILE:: " << file_place << "\n\tLINE:: " << line_place;
		}
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


		void Dump(std::ostream& os = std::cout) const override
		{
			if (typeid(os) == typeid(std::cout))
				os << warnFormat << "WARN:: " << Format::SingleCode{Format::TextFMT::BOLD_OFF} << explain << Format::SingleCode{} << "\n";
			else
				os << "WARN:: " << explain << "\n";
				
			print(os);
			os << std::endl;
		}
		Warning(std::string const & file, int line, std::string const & explanation) : DebugInfo{file, line, explanation}
		{
			warnFormat.setCode(Format::TextFMT::ColorCode::YELLOW).setCode(Format::TextFMT::StyleCode::BOLD);			
		}
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


		void Dump(std::ostream& os = std::cerr) const override
		{
			if (typeid(os) == typeid(std::cerr))
				os << errFormat << "ERR::  " << Format::SingleCode{Format::TextFMT::BOLD_OFF} << explain << Format::SingleCode{} << "\n";
			else
				os << "ERR::  " << explain << "\n";
			print(os);
			os << std::endl;
		}
		Error(std::string const & file, int line, std::string const & explanation) : DebugInfo{file, line, explanation}
		{
			errFormat.setCode(Format::TextFMT::ColorCode::RED).setCode(Format::TextFMT::StyleCode::BOLD);			
		}
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

		Logger const & DumpWarnings(std::ostream& os = std::cout) const
		{
			for (auto && log : logs)
			{
				if (typeid(*log) == typeid(Warning))
					log->Dump(os);
			}
			return *this;
		}
		Logger const & DumpErrors(std::ostream& os = std::cerr) const
		{
			for (auto && log : logs)
			{
				if (typeid(*log) == typeid(Error))
				{
					log->Dump(os);
				}
			}
			return *this;
		}
		Logger const & Dump(std::ostream& os) const
		{
			for (auto && log : logs)
				log->Dump(os);

			return *this;
		}
		Logger const & Dump() const
		{
			for (auto && log : logs)
				log->Dump();

			return *this;
		}

		Logger & AddLog(DebugInfo const * log)
		{
			logs.push_back(log);

			#ifdef gDEBUG
				log->Dump();
			#endif //gDEBUG

			return *this;
		}
		Logger const & DumpToFile() const
		{
			std::ofstream outfile{"dump.log"};
				if (outfile.is_open())
					Dump(outfile);

			return *this;
		}

		~Logger()
		{
			try{
				#ifdef gDEBUG
					DumpToFile();
				#endif //gDEBUG
				
			}
			catch (...)
			{
				// silence death
			}	

			for (auto && x : logs)
				delete x;
		}

	};
}