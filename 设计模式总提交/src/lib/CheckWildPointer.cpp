//---------------------------------------------------------------------------
#include "checkwildpointer.h"
#include "mathlib.h"
#include "symboldatabase.h"
#include "valueflow.h"
#include <cctype>

#include <set>
//---------------------------------------------------------------------------

// Register this check class (by creating a static instance of it)
namespace {
	CheckWildPointer instance;
}

void CheckWildPointer::wildPointer()
{
	for (const Token* tok = _tokenizer->tokens(); tok; tok = tok->next())
	{
		const Token *wildUse = nullptr;
		//find the use of the wildPointer
		if (Token::Match(tok, "* %var%") && tok->astOperand2() == nullptr)
		{
			wildUse = tok->tokAt(1);
		}
		else if (Token::Match(tok, "%var% ."))
		{
			wildUse = tok;
		}

		if (wildUse)
		{
			if (wildUse->tokType() == Token::eVariable && wildUse->variable()->isPointer())
			{
				for (auto& value : wildUse->values)
				{
					if (value.varvalue == ValueFlow::deletedVarId)
					{
						wildPointerError(wildUse, wildUse->str());
						break;
					}
				}
			}
		}
	}
}

void CheckWildPointer::wildPointerError(const Token *tok, const std::string strValue)
{
	reportError(tok, Severity::error, "This wildpointer",
		"Violate rule R-1-6-16: Using pointer " + strValue + " of released resource");
}
//---------------------------------------------------------------------------

