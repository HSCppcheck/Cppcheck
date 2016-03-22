#include "controlflownode.h"
#include "symboldatabase.h"

std::stack<std::string> form_stack;
static ControlFlowTree CFTree;
Tokenizer * _tokenizer;
const Function *function;
static CFnode *root, *currentroot;
const Token* codeblock;
void ControlFlowTree::destroy(CFnode *root)
{
	if (root == nullptr)
		return;
	else if (root->branch.empty()){
		free(root);
		root = nullptr;
	}
	else{
		for (int i = 0; i < root->branch.size(); i++)
		{
			destroy(root->branch[i]);
		}
	}

}


void ControlFlowTree::insert(CFnode *root)
{


}

void ControlFlowTree::post_recurs_render(CFnode* root)
{

}

void ControlFlowTree::pre_recurs_render(CFnode* root)
{

}


void ControlFlowTree::CFG_listCreat(){
	const SymbolDatabase *symbolDatabase = _tokenizer->getSymbolDatabase();
	const std::size_t functions = symbolDatabase->functionScopes.size();
	for (std::size_t i = 0; i < functions; ++i) {
		function = symbolDatabase->functionScopes[i]->function;
		if (function){
			const Token *vtok = function->token;
			unsigned int varid = 0;
			if (Token::Match(vtok, "main (")) {				
				root = new CFnode(vtok, CFnode::eFunction, false, vtok->varId(), nullptr);
				currentroot = root;
				codeblock = vtok->link()->tokAt(2);
			}
		}
	}
	for (const Token *tok = codeblock; tok && tok != tok->link(); tok = tok->next()) {
		bool status = false;
		if (Token::Match(tok, "%name% (") && tok->tokType() == Token::eFunction){
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			CFTree.insert(node);
			currentroot = node;
			continue;
		}
		else if (Token::Match(tok, "if (")){			
			status = true;
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			currentroot = node;
			continue;
		}

		else if (Token::Match(tok, "else if (")){
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			continue;
		}
		else if (Token::Match(tok, "else (")){
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			continue;
		}
		else if (Token::Match(tok, "for (")){
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			currentroot = node;
			continue;
		}
		else if (Token::Match(tok, "while (")){
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			currentroot = node;
			continue;
		}
		else if (Token::Match(tok, "do {")){
			CFnode *node = new CFnode(tok, CFnode::eFunction, false, tok->varId(), currentroot);
			currentroot = node;
			continue;
		}
	}
}