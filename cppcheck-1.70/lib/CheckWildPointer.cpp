//---------------------------------------------------------------------------
#include "checkwildpointer.h"
#include "mathlib.h"
#include "symboldatabase.h"
#include <cctype>
//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace {
	CheckWildPointer instance;
}

void CheckWildPointer::wildPointer()
{
	int flag = 0;
	std::string isWildPointer;
	for (const Token* tok = _tokenizer->tokens(); tok; tok = tok->next())
	{
		if (Token::Match(tok, "delete|free"))
		{
			const Token *cutPointer = tok->tokAt(1);
			//The value of isWildPointe is p1 in this judge
			isWildPointer = cutPointer->str(); 
			//wildPointerError(tok, store);
		}
		//find the use of the wildPointer
		if (Token::Match(tok, "* %var%"))
		{
			//find the use of p1
			const Token *wildUse = tok->tokAt(1);
			std::string store = wildUse->str();
			if (store == isWildPointer)
			{
				if (wildUse->next()->str() == "=")
				{
					wildPointerError(wildUse, store);
				}
			}
		}
	}
}

void CheckWildPointer::wildPointerError(const Token *tok, const std::string strValue)
{
	reportError(tok, Severity::error, "This wildpointer",
		"Violate rule R-1-6-xx: " + strValue + " Wrong p1");
}
//---------------------------------------------------------------------------

