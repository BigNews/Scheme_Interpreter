#include "procedure.h"
#include "..\parser\Parser.h"
#include "..\standard.h"


namespace ObjectDef
{
	using std::shared_ptr;
	using std::static_pointer_cast;

	Procedure::Procedure(shared_ptr<Object> argu,
						 shared_ptr<Object> proc,
						 shared_ptr<Environment> fa)
	{
		objType = COMPOUND_PROCEDURE;

		shared_ptr<Environment> tester(new Environment());
		shared_ptr<Object> nargu = argu;
		shared_ptr<Object> single;

		while (nargu -> getType() == PAIR)
		{
			single = static_pointer_cast<Pair>(nargu) -> car();
			if (single -> getType() != SYMBOL) throw Debugger::DebugMessage("#%plain-lambda: not an identifier\n");
			if (tester -> SymbolExist(*static_pointer_cast<Symbol>(single))) throw Debugger::DebugMessage("#%plain-lambda: duplicate argument name.\n");
			tester -> DefineSymbol(*static_pointer_cast<Symbol>(single), proc);

			nargu = static_pointer_cast<Pair>(nargu) -> cdr();
		}
		
		if (nargu -> getType() != NIL)
		{
			single = nargu;
			if (single -> getType() != SYMBOL) throw Debugger::DebugMessage("#%plain-lambda: not an identifier\n");
			if (tester -> SymbolExist(*static_pointer_cast<Symbol>(single))) throw Debugger::DebugMessage("#%plain-lambda: duplicate argument name.\n");
			tester -> DefineSymbol(*static_pointer_cast<Symbol>(single), proc);
		}

		//tester.reset();

		argument = argu;
		process = proc;
		father = fa;
	}

	/*bool Procedure::CheckArgument(shared_ptr<Object> argu)
	{

		if (argu -> getType() != PAIR) return false;

		shared_ptr<Object> x(argu);
		shared_ptr<Object> y(argument);

		while (y -> getType() != SYMBOL && y -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_

			if (y -> getType() != SYMBOL && y -> getType() != NIL && y -> getType() != PAIR)
				throw Debugger::DebugMessage("In CheckArgument, Unknown Type y found!\n");

			if (x -> getType() != PAIR && x -> getType() != NULL)
				throw Debugger::DebugMessage("In CheckArgument, Unknown Type x found!\n");
			
			#endif

			if (x -> getType() == NIL) return false;
			
			x = static_pointer_cast<Object>(static_pointer_cast<Pair>(x) -> cdr());
			y = static_pointer_cast<Object>(static_pointer_cast<Pair>(y) -> cdr());
		}

		if (y -> getType() == SYMBOL) return true;
		if (y -> getType() == NIL && x -> getType() != NIL) return false;
		return true;
	}*/

	/*shared_ptr<Object> Procedure::ApplyProcedure(shared_ptr<Object> x)
	{
		shared_ptr<Object> nargu = argument;
		shared_ptr<Object> single;
		shared_ptr<Environment> current(new Environment(father));

		while (nargu -> getType() == PAIR)
		{
			single = static_pointer_cast<Pair>(nargu) -> car();

			if (x -> getType() != PAIR) throw Debugger::DebugMessage("arity mismatch;\n the expected number of arguments does not match the given number\n");

			current -> SetSymbol(*static_pointer_cast<Symbol>(single), static_pointer_cast<Pair>(x) -> car());

			nargu = static_pointer_cast<Pair>(nargu) -> cdr();
			x = static_pointer_cast<Pair>(x) -> cdr();
		}
		if (nargu -> getType() == NIL)
		{
			if (x -> getType() != NIL) throw Debugger::DebugMessage("arity mismatch;\n the expected number of arguments does not match the given number\n");
		}
		else
		{
			if (nargu -> getType() != SYMBOL) throw Debugger::DebugMessage("#%plain-lambda: not an identifier\n");
			current -> SetSymbol(*static_pointer_cast<Symbol>(nargu), x);
		}

		return Parser::Eval(process, current);
	}*/

	void Procedure::SetFather(shared_ptr<Environment> fa)
	{
		father = fa;
	}

	shared_ptr<Environment> Procedure::ExtendEnvironment(shared_ptr<Object> x)
	{
		shared_ptr<Object> nargu = argument;
		shared_ptr<Object> single;
		shared_ptr<Environment> exv(new Environment(father));

		while (nargu -> getType() == PAIR)
		{
			single = static_pointer_cast<Pair>(nargu) -> car();

			if (x -> getType() != PAIR) throw Debugger::DebugMessage("arity mismatch;\n the expected number of arguments does not match the given number\n");

			exv -> DefineSymbol(*static_pointer_cast<Symbol>(single), static_pointer_cast<Pair>(x) -> car());

			nargu = static_pointer_cast<Pair>(nargu) -> cdr();
			x = static_pointer_cast<Pair>(x) -> cdr();
		}
		if (nargu -> getType() == NIL)
		{
			if (x -> getType() != NIL) throw Debugger::DebugMessage("arity mismatch;\n the expected number of arguments does not match the given number\n");
		}
		else
		{
			if (nargu -> getType() != SYMBOL) throw Debugger::DebugMessage("#%plain-lambda: not an identifier\n");
			exv -> DefineSymbol(*static_pointer_cast<Symbol>(nargu), x);
		}

		return exv;
	}

	shared_ptr<Object> Procedure::GetProcedureBody()
	{
		return process;
	}

}
