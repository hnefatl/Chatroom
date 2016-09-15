#include "Data/Statement.h"

#include <Log.h>

namespace Data
{
	Statement::Statement()
	{
		Inner = nullptr;
	}
	Statement::~Statement()
	{
		Finalise();
	}

	bool Statement::Prepare(sqlite3 * const Database, const std::string &Query)
	{
		Inner = nullptr;
		int Err = sqlite3_prepare_v2(Database, Query.c_str(), -1, &Inner, nullptr);
		if (Err != SQLITE_OK)
		{
			Finalise();
			LogError("Failed to prepare statement with query \"" + Query + "\".");
			LogError(sqlite3_errstr(Err), false);
			return false;
		}
		return true;
	}

	bool Statement::Bind(const std::string &Name, const std::string &Value)
	{
		if (Inner == nullptr)
			return false;

		int Err = sqlite3_bind_text(Inner, sqlite3_bind_parameter_index(Inner, Name.c_str()), Value.c_str(), -1, nullptr);
		if (Err != SQLITE_OK)
		{
			Finalise();
			LogError("Failed to bind value \"" + Value + "\" to statement variable \"" + Name + "\".");
			return LogError(sqlite3_errstr(Err), false);
		}
		return true;
	}
	bool Statement::Bind(const std::string &Name, const int Value)
	{
		if (Inner == nullptr)
			return false;

		int Err = sqlite3_bind_int(Inner, sqlite3_bind_parameter_index(Inner, Name.c_str()), Value);
		if (Err != SQLITE_OK)
		{
			Finalise();
			LogError("Failed to bind value \"" + std::to_string(Value) + "\" to statement variable \"" + Name + "\".");
			return LogError(sqlite3_errstr(Err), false);
		}
		return true;
	}
	bool Statement::BindNull(const std::string &Name)
	{
		if (Inner == nullptr)
			return false;

		int Err = sqlite3_bind_null(Inner, sqlite3_bind_parameter_index(Inner, Name.c_str()));
		if (Err != SQLITE_OK)
		{
			Finalise();
			LogError("Failed to bind NULL value to statement variable \"" + Name + "\".");
			return LogError(sqlite3_errstr(Err), false);
		}
		return true;
	}

	bool Statement::Execute()
	{
		int Err = sqlite3_step(Inner);
		if (Err != SQLITE_DONE && Err != SQLITE_ROW)
		{
			Finalise();
			return LogError(sqlite3_errstr(Err), false);
		}

		return true;
	}
	bool Statement::Step(bool &MoreData)
	{
		int Err = sqlite3_step(Inner);
		if (Err == SQLITE_ROW)
		{
			MoreData = true;
			return true;
		}
		else if (Err == SQLITE_DONE)
		{
			MoreData = false;
			return true;
		}
		else
			return false;
	}

	bool Statement::GetString(unsigned int Column, Nullable<std::string> &Out)
	{
		if (Inner == nullptr)
			return false;

		if (sqlite3_column_type(Inner, Column) == SQLITE_NULL)
		{
			Out = Nullable<std::string>();
			return true;
		}

		Out = Nullable<std::string>(std::string(reinterpret_cast<const char *>(sqlite3_column_text(Inner, Column))));
		return true;
	}
	bool Statement::GetString(const std::string &ColumnHeader, Nullable<std::string> &Out)
	{
		unsigned int ColumnIndex;
		if (!GetColumnIndex(ColumnHeader, ColumnIndex))
			return false;

		return GetString(ColumnIndex, Out);
	}

	bool Statement::GetInt(unsigned int Column, Nullable<int> &Out)
	{
		if (Inner == nullptr)
			return false;

		if (sqlite3_column_type(Inner, Column) == SQLITE_NULL)
		{
			Out = Nullable<int>();
			return true;
		}

		Out = Nullable<int>(sqlite3_column_int(Inner, Column));
		return true;
	}
	bool Statement::GetInt(const std::string &ColumnHeader, Nullable<int> &Out)
	{
		unsigned int ColumnIndex;
		if (!GetColumnIndex(ColumnHeader, ColumnIndex))
			return false;

		return GetInt(ColumnIndex, Out);
	}

	bool Statement::GetColumns(std::vector<std::string> &Out)
	{
		if (Inner == nullptr)
			return false;

		Out.resize(sqlite3_column_count(Inner));
		for (unsigned int x = 0; x < Out.size(); x++)
			Out[x] = std::string(sqlite3_column_name(Inner, x));

		return true;
	}
	bool Statement::GetColumnIndex(const std::string &ColumnName, unsigned int &Out)
	{
		std::vector<std::string> Columns;
		if (!GetColumns(Columns))
			return false;

		for (unsigned int x = 0; x < Columns.size(); x++)
		{
			if (Columns[x] == ColumnName)
			{
				Out = x;
				return true;
			}
		}

		LogError("Could not find column with name \"" + ColumnName + "\".");
		return false;
	}

	bool Statement::Finalise()
	{
		int Err = sqlite3_finalize(Inner);
		if (Err != SQLITE_OK)
		{
			LogError("Failed to finalise statement.");
			return LogError(sqlite3_errstr(Err), false);
		}
		Inner = nullptr;
		return true;
	}
	bool Statement::Reset()
	{
		int Err = sqlite3_reset(Inner);
		if (Err != SQLITE_OK)
		{
			LogError("Failed to reset statement.");
			return LogError(sqlite3_errstr(Err), false);
		}
		Err = sqlite3_clear_bindings(Inner);
		if (Err != SQLITE_OK)
		{
			LogError("Failed to clear bindings.");
			return LogError(sqlite3_errstr(Err), false);
		}
		return true;
	}
}
