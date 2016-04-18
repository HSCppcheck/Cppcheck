//---------------------------------------------------------------------------
#ifndef checkwildpointerH
#define checkwildpointerH
//---------------------------------------------------------------------------

#include "config.h"
#include "check.h"


/// @addtogroup Checks
/// @{


/** @brief check for wild pointer dereferencing */
class CPPCHECKLIB CheckWildPointer : public Check
{
public:
	/** @brief This constructor is used when registering the CheckNullPointer */
	CheckWildPointer() : Check(myName()) {
	}

	/** @brief This constructor is used when running checks. */
	CheckWildPointer(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger)
		: Check(myName(), tokenizer, settings, errorLogger) {
	}

	/** @brief Run checks against the normal token list */
	void runChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger) {
		CheckWildPointer checkWildPointer(tokenizer, settings, errorLogger);
		checkWildPointer.wildPointer();
		checkWildPointer.judgeDelete();
	}

	/** @brief Run checks against the simplified token list */
	void runSimplifiedChecks(const Tokenizer *tokenizer, const Settings *settings, ErrorLogger *errorLogger) {
		CheckWildPointer checkWildPointer(tokenizer, settings, errorLogger);
	}

	void wildPointer();
	
private:
	void wildPointerError(const Token *tok, const std::string strValue);
	
	/** Get error messages. Used by --errorlist */
	void getErrorMessages(ErrorLogger *errorLogger, const Settings *settings) const {
		CheckWildPointer c(0, settings, errorLogger);
		c.wildPointerError(0,0);
	}

	/** Name of check */
	static std::string myName() {
		return "Wild pointer";
	}

	/** class info in WIKI format. Used by --doc */
	std::string classInfo() const {
		return "Wild pointers\n"
			"- wild pointer dereferencing\n";
	}
};

#endif // checkwildpointerH