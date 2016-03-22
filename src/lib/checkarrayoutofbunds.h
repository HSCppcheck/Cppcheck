/*
* Cppcheck - A tool for static C/C++ code analysis
* Copyright (C) 2007-2015 Daniel Marjamäki and Cppcheck team.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


//---------------------------------------------------------------------------
#ifndef checkarrayoutofbundsH
#define checkarrayoutofbundsH
//---------------------------------------------------------------------------

#include "config.h"
#include "check.h"
#include "mathlib.h"
#include <list>
#include <vector>
#include <string>
#include  <map>

class Variable;
class Function;

class CPPCHECKLIB CheckArrayOutOfBounds : public Check {
public:

	/** This constructor is used when registering the CheckClass */
	CheckArrayOutOfBounds() : Check(myName()) {
	}

	/** This constructor is used when running checks. */
	CheckArrayOutOfBounds(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
		: Check(myName(), tokenizer, settings, errorLogger) {
	}

	void runSimplifiedChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger) {
		CheckArrayOutOfBounds checkBufferOverrun(tokenizer, settings, errorLogger);
		checkBufferOverrun.bufferOverrun();
		checkBufferOverrun.bufferOverrun2();
		checkBufferOverrun.arrayIndexThenCheck();
		checkBufferOverrun.negativeArraySize();
		checkBufferOverrun.bufferOverrun3();
	}

#endif // checkarrayoutofbundsH
