#ifndef _STATEMENT_H
#define _STATEMENT_H

#include <string>
#include <vector>

#include <sqlite3.h>

#include <Nullable.h>
#include <Core.h>

namespace Data
{
	class Statement
	{
	protected:
		sqlite3_stmt *Inner;

	public:
		CORE_API Statement();
		CORE_API ~Statement();

		CORE_API bool Prepare(sqlite3 *const Database, const std::string &Query);

		CORE_API bool Bind(const std::string &Name, const std::string &Value);
		CORE_API bool Bind(const std::string &Name, const int Value);
		CORE_API bool BindNull(const std::string &Name);

		CORE_API bool Execute();
		CORE_API bool Step();
		CORE_API bool Step(bool &MoreData);

		CORE_API bool GetString(unsigned int Column, Nullable<std::string> &Out);
		CORE_API bool GetString(const std::string &ColumnHeader, Nullable<std::string> &Out);
		CORE_API bool GetInt(const std::string &ColumnHeader, Nullable<int> &Out);
		CORE_API bool GetInt(unsigned int Column, Nullable<int> &Out);

		CORE_API bool GetColumns(std::vector<std::string> &Out);
		CORE_API bool GetColumnIndex(const std::string &ColumnName, unsigned int &Out);

		CORE_API bool Finalise();
		CORE_API bool Reset();
	};
}

#endif
