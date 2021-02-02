#pragma once

#include <ostream>
#include <string>
#include <vector>

#include "formater.h"

namespace Debug
{
	// contains plain info: file and line
	class DebugInfo
	{
		std::string const file_place;
		int			const line_place;
	public:
		DebugInfo()								= delete;
		DebugInfo(DebugInfo const&)				= delete;
		DebugInfo(DebugInfo&&)					= delete;
		DebugInfo& operator= (DebugInfo const&) = delete;
		DebugInfo& operator= (DebugInfo&&)		= delete;
		DebugInfo(std::string const& file, int line) : 
			file_place{ file }, 
			line_place{ line } 
		{}

		void print(std::ostream& os) const
		{

		}
		virtual ~DebugInfo() {};
	};
	class Warning final : public DebugInfo
	{
		Format::Formater warnFormat;
		std::string const explain;
	public:
		Warning() 							= delete;
		Warning(Warning const&)				= delete;
		Warning(Warning&&) 					= delete;
		Warning& operator= (Warning const&) = delete;
		Warning& operator= (Warning&&) 		= delete;


		void Dump(std::ostream& os) const
		{
			os << warnFormat << "WARN:: " << explain << Format::Reset << "\n{";
			print(os);
			os << "}" << std::endl;
		}
		void Dump() const
		{
			Dump(std::cout);
		}
		Warning(std::string const & file, int line, std::string const & explanation) : DebugInfo{file, line}, explain{explanation}
		{
			warnFormat.setCode(Format::TextFMT::ColorCode::YELLOW).setCode(Format::TextFMT::StyleCode::BOLD);			
		}
	};

	class Logger
	{
		std::vector<Warning *> warnings;
	};
}