/*This class will discrible the node of control flow chart(CFG)*/

//---------------------------------------------------------------------------
#ifndef controlflownodeH
#define controlflownodeH
//---------------------------------------------------------------------------


#include "token.h"
#include "mathlib.h"
#include <ostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>

class Scope;
class Type;
class Function;
class Variable;
class Settings;

//---------------------------------------------------------------------------

class CFnode {
public:
	enum Type {
		eFunction, eSwicth, eIf, eElse, eElseif, eWhile, eFor
	};
	const Token *tok;
	Type type;
	bool state;
	unsigned int id;//tok->varId();
	CFnode *root;//root of current node
	std::vector<CFnode*> branch;

	CFnode();
	CFnode(const Token *tok_, Type type_, bool state_, unsigned int id_, CFnode *root_)
		:tok(tok_), type(type_),state(state_), id(id_), root(root_){}
private:
	CFnode *rootback = nullptr;

};
//---------------------------------------------------------------------------

class CPPCHECKLIB ControlFlowTree{

public:

//---------------------------------------------------------------------------
public:
	void insert(CFnode *node);

	void post_recurs_render(CFnode* root);

	void pre_recurs_render(CFnode* root);

	void CFG_listCreat();

	void destroy(CFnode *root);
};

//---------------------------------------------------------------------------

#endif //controlflownodeH