#include "Parser.h"
#include "../standard.h"

#ifndef __PARSER_DEBUGGER_
//#define __PARSER_DEBUGGER_
#endif

namespace Parser
{
	using namespace ObjectDef;
	using namespace buildin;

	shared_ptr<Object> LoadAndParseBlockFromToken(Tokens &token, int &index, int depth)
	{
		if (index == token.size) throw Debugger::DebugMessage("Expected a ')' to close '('.\n");

		//Special Symbol
		if (token.element[index] == "(")
		{
			++index;
			return LoadAndParseSequenceFromToken(token, index, depth + 1);
		}
		else
		if (token.element[index] == ")")
		{
			if (depth == 0) throw Debugger::DebugMessage("Unexpected ')'\n");

			++index;
			return shared_ptr<Null>(new Null(1));
		}
		if (token.element[index] == "'")
		{
			++index;
			return _cons(shared_ptr<Symbol>(new Symbol("quote")),
				_cons(LoadAndParseBlockFromToken(token, index, depth),
				     shared_ptr<Null>(new Null())));
		}
		else
		if (token.element[index] == "`")
		{
			++index;
			return _cons(shared_ptr<Symbol>(new Symbol("quasiquote")),
				_cons(LoadAndParseBlockFromToken(token, index, depth),
				     shared_ptr<Null>(new Null())));
		}
		else
		if (token.element[index] == ",")
		{
			++index;
			return _cons(shared_ptr<Symbol>(new Symbol("unquote")),
				_cons(LoadAndParseBlockFromToken(token, index, depth),
				     shared_ptr<Null>(new Null())));
		}
		else
		if (TokenIsNumber(token.element[index]))
		{
			return TokenToNumber(token.element[index++]);
		}
		else
		if (TokenIsString(token.element[index]))
		{
			return TokenToString(token.element[index++]);
		}
		else
		if (TokenIsBoolean(token.element[index]))
		{
			return TokenToBoolean(token.element[index++]);
		}
		if (TokenIsSymbol(token.element[index]))
		{
			return TokenToSymbol(token.element[index++]);
		}

		throw Debugger::DebugMessage("In LoadAndParseBlockFromToken,\nGet unexpected type of tokens.\n");
	}

	shared_ptr<Object> LoadAndParseSequenceFromToken(Tokens &token, int &index, int depth)
	{
		if (index == token.size) throw Debugger::DebugMessage("Expected a ')' to close '('.\n");

		shared_ptr<Object> exv = LoadAndParseBlockFromToken(token, index, depth);
		if (exv -> getType() == NIL)
		{
			if (std::static_pointer_cast<Null>(exv) -> nullType) return shared_ptr<Null>(new Null());
		}

		if (exv -> getType() == SYMBOL)
		{
			if (std::static_pointer_cast<Symbol>(exv) -> value == ".")
			{
				exv = LoadAndParseBlockFromToken(token, index, depth);

				shared_ptr<Object> tt = LoadAndParseBlockFromToken(token, index, depth);
				if (tt -> getType() != NIL || !std::static_pointer_cast<Null>(tt) -> nullType)
					throw Debugger::DebugMessage("Illegal use of '.'\n");
				return exv;
			}
		}
		
		return (_cons(exv, LoadAndParseSequenceFromToken(token, index, depth)));
	}

	bool TaggedList(shared_ptr<Object> x, std::string y)
	{
		if (x -> getType() != PAIR) return false;

		shared_ptr<Object> tmp = static_pointer_cast<Pair>(x) -> car();
		if (tmp -> getType() != SYMBOL) return false;
		if (static_pointer_cast<Symbol>(tmp) -> value != y) return false;

		return true;
	}

	//Eval a self-evaluating element
	bool _SelfEvaluating(shared_ptr<Object> x)
	{
		if (x -> getType() == SYMBOL) return false;
		if (x -> getType() == PAIR) return false;
		return true;
	}

	//Eval a variable
	bool _IsVariable(shared_ptr<Object> x)
	{
		if (x -> getType() == SYMBOL) return true;
		return false;
	}

	shared_ptr<Object> LookUpVariableValue(shared_ptr<Object> x, shared_ptr<Environment> y)
	{
		//buildin::_Display(x);

		if (x -> getType() != SYMBOL) throw Debugger::DebugMessage("In LookUpVariableValue(shared_ptr<Object>, shared_ptr<Environment>),\nx is not a Symbol!");

		while (y.use_count())
		{
			if (y -> SymbolExist(*static_pointer_cast<Symbol>(x)))
				return y -> LookUpSymbol(*static_pointer_cast<Symbol>(x));

			y = y -> GetFather();
		}

		throw Debugger::DebugMessage("Undefined,\nCannot reference undefined identifer.\n");
	}
	
	//Eval a quoted value
	bool _IsQuoted(shared_ptr<Object> x)
	{
		return (TaggedList(x, "quote") || TaggedList(x, "quasiquote"));
	}

	shared_ptr<Object> TextOfQuotation(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In TextOfQuotation(shared_ptr<Object>),\n1st: x is not a pair.\n");
		x = static_pointer_cast<Pair>(x) -> cdr();
		
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In TextOfQuotation(shared_ptr<Object>),\n2nd: x is not a pair.\n");
		x = static_pointer_cast<Pair>(x) -> car();

		return x;
	}

	//Eval an assignment.
	bool _IsAssignment(shared_ptr<Object> x)
	{
		return TaggedList(x, "set!");
	}

	shared_ptr<Object> EvalAssignment(shared_ptr<Object> x, shared_ptr<Environment> y)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In EvalAssignment,\nx is not a pair.\n");
		
		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("set!: Bad syntax!");
		shared_ptr<Object> setSymbol = static_pointer_cast<Pair>(x) -> car();
		shared_ptr<Object> setValue = static_pointer_cast<Pair>(x) -> cdr();
		
		if (setValue -> getType() != PAIR) throw Debugger::DebugMessage("set!: Bad syntax!");
		setValue = static_pointer_cast<Pair>(setValue) -> car();
		setValue = Eval(setValue, y);

		if (setSymbol -> getType() != SYMBOL) throw Debugger::DebugMessage("set!: No an identifier.");

		while (y.use_count())
		{
			if (y -> SymbolExist(*static_pointer_cast<Symbol>(setSymbol)))
			{
				y -> SetSymbol(*static_pointer_cast<Symbol>(setSymbol), setValue);
				
				return shared_ptr<Void>(new Void());
			}
			y = y -> GetFather();
		}

		throw Debugger::DebugMessage("set!: assignment disallowed:\ncannot set undefined\n");
	}

	//Eval a definition
	bool _IsDefinition(shared_ptr<Object> x)
	{
		return TaggedList(x, "define");
	}

	shared_ptr<Object> EvalDefinition(shared_ptr<Object> x, shared_ptr<Environment> y)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In LookUpVariableValue(shared_ptr<Object>,shared_ptr<Environment>),\nx is not a pair\n");

		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("define: Bad syntax!\n");
		shared_ptr<Object> setSymbol = static_pointer_cast<Pair>(x) -> car();
		shared_ptr<Object> setValue = static_pointer_cast<Pair>(x) -> cdr();

		//(define variable expression)
		if (setSymbol -> getType() == SYMBOL)
		{
			if (setValue -> getType() != PAIR) throw Debugger::DebugMessage("define: Bad syntax!\n");
			if (static_pointer_cast<Pair>(setValue) -> cdr() -> getType() != NIL) throw Debugger::DebugMessage("define: Multiple Expression after identifier\n");
			setValue = static_pointer_cast<Pair>(setValue) -> car();
			setValue = Eval(setValue, y);
			y -> DefineSymbol(*static_pointer_cast<Symbol>(setSymbol), setValue);

			return shared_ptr<Void>(new Void());
		}
		else
		if (setSymbol -> getType() == PAIR)
		{
			shared_ptr<Object> lambdaParameter;
			lambdaParameter = static_pointer_cast<Pair>(setSymbol) -> cdr();
			setSymbol = static_pointer_cast<Pair>(setSymbol) -> car();
			if (setSymbol -> getType() != SYMBOL) throw Debugger::DebugMessage("define: bad syntax!\n");
			
			if (setValue -> getType() != PAIR) throw Debugger::DebugMessage("r5rs body: no expression in body\n");
			
			/*buildin::_Display(lambdaParameter);
			std::cout << std::endl;
			buildin::_Display(setSymbol);
			std::cout << std::endl;
			buildin::_Display(setValue);
			std::cout << std::endl;*/

			//y -> DefineSymbol(*static_pointer_cast<Symbol>(setSymbol), shared_ptr<Procedure>());
			shared_ptr<Procedure> newProc(new Procedure(lambdaParameter, setValue, y));
			//newProc.reset();
			//y -> DefineSymbol(*static_pointer_cast<Symbol>(setSymbol), newProc);
			y -> DefineSymbol(*static_pointer_cast<Symbol>(setSymbol), newProc);
			//newProc.reset();
			//y -> DefineSymbol(*static_pointer_cast<Symbol>(setSymbol), shared_ptr<Procedure>(new Procedure(lambdaParameter, setValue, y)));

			return shared_ptr<Void>(new Void());
		}

		throw Debugger::DebugMessage("define: bad syntax!\n");
	}

	//Eval an if-predicate
	bool _IsIfPredicate(shared_ptr<Object> x)
	{
		return TaggedList(x, "if");
	}

	shared_ptr<Object> IfPredicate(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In IfPredicate(shared_ptr<Object>),\nx is not a pair");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("If : bad syntax!\n");

		x = static_pointer_cast<Pair>(x) -> car();

		return x;
	}

	shared_ptr<Object> IfConsequent(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In IfConsequent(shared_ptr<Object>),\nx is not a pair");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("If : bad syntax!\n");
		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("If : bad syntax!\n");
		x = static_pointer_cast<Pair>(x) -> car();

		return x;
	}

	shared_ptr<Object> IfAlternative(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In IfAlternative(shared_ptr<Object>),\nx is not a pair");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("If : bad syntax!\n");
		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("If : bad syntax!\n");
		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) return shared_ptr<Void>(new Void());
		x = static_pointer_cast<Pair>(x) -> car();

		return x;
	}

	shared_ptr<Object> EvalIf(shared_ptr<Object> x, shared_ptr<Environment> y)
	{
		/*buildin::_Display(IfPredicate(x));
		std::cout << "  ";
		buildin::_Display(IfConsequent(x));
		std::cout << "  ";
		buildin::_Display(IfAlternative(x));
		std::cout << "  ";*/

		if (_IsTrue(Eval(IfPredicate(x), y)) -> getValue())
			return Eval(IfConsequent(x), y);
		return Eval(IfAlternative(x), y);
	}

	//Eval a lambda expression
	bool _IsLambda(shared_ptr<Object> x)
	{
		return TaggedList(x, "lambda");
	}

	shared_ptr<Object> LambdaParameters(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In LambdaParameter(shared_ptr<Object>),\nx is not a pair.");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("lambda : bad syntax!\n");

		x = static_pointer_cast<Pair>(x) -> car();

		return x;
	}

	shared_ptr<Object> LambdaBody(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In LambdaParameter(shared_ptr<Object>),\nx is not a pair.");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		if (x -> getType() != PAIR) throw Debugger::DebugMessage("lambda : bad syntax!\n");

		x = static_pointer_cast<Pair>(x) -> cdr();

		return x;
	}

	shared_ptr<Object> MakeProcedure(shared_ptr<Object> para, shared_ptr<Object> body, shared_ptr<Environment> envi)
	{
		/*buildin::_Display(para);
		std::cout << std::endl;
		buildin::_Display(body);
		std::cout << std::endl;*/

		return shared_ptr<Procedure>(new Procedure(para, body, envi));
	}

	// Eval a begin sequence
	bool _IsBegin(shared_ptr<Object> x)
	{
		return TaggedList(x, "begin");
	}

	shared_ptr<Object> BeginActions(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In BeginActions,\nx is not a pair\n");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		return x;
	}

	shared_ptr<Object> EvalSequence(shared_ptr<Object> x, shared_ptr<Environment> envi)
	{
		shared_ptr<Object> exv;

		#ifdef __PARSER_DEBUGGER_
		std::cout << "Eval-sequence processing...   :";
		buildin::_Display(x);
		std::cout << std::endl;
		#endif

		while (x -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (x -> getType() != PAIR) throw Debugger::DebugMessage("In Eval Sequence(shared_ptr<Object>, shared_ptr<Environment>),\nx is not a pair.");
			#endif
			exv = Eval(static_pointer_cast<Pair>(x) -> car(), envi);

			x = static_pointer_cast<Pair>(x) -> cdr();
		}

		return exv;
	}

	//Eval a let-binding.
	bool _IsLet(shared_ptr<Object> x)
	{
		return TaggedList(x, "let");
	}

	shared_ptr<Object> LetParameters(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In LetParameters(shared_ptr<Object>),\nx is not a pair.");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("let: bad syntax in: (let)\n");
		
		x = static_pointer_cast<Pair>(x) -> car();
		return x;
	}

	shared_ptr<Object> LetBody(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In LetParameters(shared_ptr<Object>),\nx is not a pair.");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("let: bad syntax in: (let)\n");
		
		x = static_pointer_cast<Pair>(x) -> cdr();
		return x;
	}

	shared_ptr<Object> EvalLet(shared_ptr<Object> para, shared_ptr<Object> body, shared_ptr<Environment> envi)
	{
		shared_ptr<Environment> env(new Environment(envi));

		shared_ptr<Object> x;
		shared_ptr<Object> symb;
		shared_ptr<Object> expr;

		while (para -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (para -> getType() != PAIR) throw Debugger::DebugMessage("In EvalLet(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Environment>),\npara is not a pair.");
			#endif
			x = static_pointer_cast<Pair>(para) -> car();

			if (x -> getType() != PAIR) throw Debugger::DebugMessage("let: bad syntax (not an identifier and expression for a binding)\n");
			symb = static_pointer_cast<Pair>(x) -> car();
			if (symb -> getType() != SYMBOL) throw Debugger::DebugMessage("let: bad syntax (not an identifier and expression for a binding)\n");

			expr = static_pointer_cast<Pair>(x) -> cdr();
			if (expr -> getType() != PAIR) throw Debugger::DebugMessage("let: bad syntax (not an identifier and expression for a binding)\n");
			expr = static_pointer_cast<Pair>(expr) -> car();

			env -> DefineSymbol(static_pointer_cast<Symbol>(symb) -> value, Eval(expr, envi));

			para = static_pointer_cast<Pair>(para) -> cdr();
		}

		return EvalSequence(body, env);
	}

	//Eval a cond-predicate
	bool _IsCondition(shared_ptr<Object> x)
	{
		return TaggedList(x, "cond");
	}

	shared_ptr<Object> CondSequence(shared_ptr<Object> x)
	{
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In CondSequence(shared_ptr<Object>), x is not a pair.");

		return (static_pointer_cast<Pair>(x) -> cdr());
	}

	shared_ptr<Object> EvalCond(shared_ptr<Object> x, shared_ptr<Environment> envi)
	{
		shared_ptr<Object> exv(new Void());
		
		shared_ptr<Object> y;
		shared_ptr<Object> predicate;

		#ifdef __PARSER_DEBUGGER_
		std::cout << "EvalCond Processing ... :";
		buildin::_Display(x);
		std::cout << std::endl;
		#endif

		while (x -> getType() != NIL)
		{
			#ifdef __DEBUG_MODE_ON_
			if (x -> getType() != PAIR) throw Debugger::DebugMessage("In EvalCond(shared_ptr<Object>, shared_ptr<Environment>):\nx is not a pair.\n");
			#endif

			y = static_pointer_cast<Pair>(x) -> car();

			if (y -> getType() != PAIR) throw Debugger::DebugMessage("Cond : Bad syntax!\n");
			predicate = static_pointer_cast<Pair>(y) -> car();
			
			if (predicate -> getType() == SYMBOL &&
				static_pointer_cast<Symbol>(predicate) -> value == "else")
			{
				#ifdef __PARSER_DEBUGGER_
				std::cout << "In EvalCond, Got 'else' clause, and evaluating... : ";
				buildin::_Display(x);
				//std::cout << "     ";
				//buildin::_Display(static_pointer_cast<Pair>(x) -> cdr());
				std::cout << std::endl; 
				#endif
				if (static_pointer_cast<Pair>(x) -> cdr() -> getType() != NIL)
					throw Debugger::DebugMessage("cond: bad syntax (`else' clause must be last)\n");

				exv = EvalSequence(static_pointer_cast<Pair>(y) -> cdr(), envi);
				return exv;
			}
			else
			if (_IsTrue(Eval(predicate, envi)) -> getValue())
			{
				exv = EvalSequence(y, envi);
				return exv;
			}

			x = static_pointer_cast<Pair>(x) -> cdr();
		}

		return exv;
	}

	//Eval an application

	bool _IsApplication(shared_ptr<Object> x)
	{
		if (x -> getType() == PAIR) return true;
		return false;
	}

	shared_ptr<Object> Eval(shared_ptr<Object> expr, shared_ptr<Environment> envi)
	{
		#ifdef __PARSER_DEBUGGER_
		std::cout << "Eval processing...   :";
		buildin::_Display(expr);
		std::cout << std::endl;
		#endif

		if (_SelfEvaluating(expr)) return expr;
		if (_IsVariable(expr)) return LookUpVariableValue(static_pointer_cast<Symbol>(expr), envi);
		if (_IsQuoted(expr)) return TextOfQuotation(expr);
		if (_IsAssignment(expr)) return EvalAssignment(expr, envi);
		if (_IsDefinition(expr)) return EvalDefinition(expr, envi);
		if (_IsIfPredicate(expr)) return EvalIf(expr, envi);
		if (_IsLambda(expr)) return MakeProcedure(LambdaParameters(expr), LambdaBody(expr), envi);
		if (_IsBegin(expr)) return EvalSequence(BeginActions(expr), envi);
		if (_IsLet(expr)) return EvalLet(LetParameters(expr), LetBody(expr), envi);
		if (_IsCondition(expr)) return EvalCond(CondSequence(expr), envi);
		if (_IsApplication(expr)) 
		{
			//buildin::_Display(ListOfValue(Operands(expr), envi));
			return Apply(Eval(Operator(expr), envi),
												ListOfValue(Operands(expr), envi));
		}
	
		throw Debugger::DebugMessage("Error: Unknown expression type -- EVAL\n");
	}

	shared_ptr<Object> Operator(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In Operator(shared_ptr<Object>),\nx is not a pair");
		#endif

		x = static_pointer_cast<Pair>(x) -> car();

		return x;
	}

	shared_ptr<Object> Operands(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In Operands(shared_ptr<Object>),\nx is not a pair");
		#endif

		x = static_pointer_cast<Pair>(x) -> cdr();

		return x;
	}

	shared_ptr<Object> ListOfValue(shared_ptr<Object> x, shared_ptr<Environment> envi)
	{
		if (x -> getType() == NIL) return shared_ptr<Null>(new Null());

		#ifdef __DEBUG_MODE_ON_
		if (x -> getType() != PAIR) throw Debugger::DebugMessage("In ListOfValue(shared_ptr<Object>),\nx is not a pair.");
		#endif

		shared_ptr<Object> t1 = Eval(static_pointer_cast<Pair>(x) -> car(), envi);
		shared_ptr<Object> t2 = ListOfValue(static_pointer_cast<Pair>(x) -> cdr(), envi);

		return _cons(t1, t2);
	}

	shared_ptr<Object> Apply(shared_ptr<Object> procedure, shared_ptr<Object> arguments)
	{
		#ifdef __PARSER_DEBUGGER_
		std::cout << "Applying Procedure && arguments...  ";
		buildin::_Display(arguments);
		std::cout << std::endl;
		#endif

		if (procedure -> getType() == PRIMITIVE_PROCEDURE)
		{
			return ApplyPrimitiveProcedure(procedure, arguments);
		}
		else
		if (procedure -> getType() == COMPOUND_PROCEDURE)
		{
			return EvalSequence(ProcedureBody(procedure) 
						       ,static_pointer_cast<Environment>
							   (static_pointer_cast<Procedure>(procedure)
							   -> ExtendEnvironment(arguments)));
												
		}

		throw Debugger::DebugMessage("Unknown procedure type -- APPLY\n");
	}

	shared_ptr<Object> ApplyPrimitiveProcedure(shared_ptr<Object> procedure, shared_ptr<Object> arguments)
	{
		#ifdef __DEBUG_MODE_ON_
		if (procedure -> getType() != PRIMITIVE_PROCEDURE) throw Debugger::DebugMessage("In ApplyPrimitiveProcedure,\nprocedure is not a primitive procedure.\n");
		#endif

		if (static_pointer_cast<Primitive>(procedure) -> CheckPrimitive(arguments)) throw Debugger::DebugMessage("arity mismatch;\nthe expected number of arguments does not match the given number");

		return static_pointer_cast<Primitive>(procedure) -> CallPrimitive(arguments);
	}

	shared_ptr<Object> ProcedureBody(shared_ptr<Object> x)
	{
		return static_pointer_cast<Procedure>(x) -> GetProcedureBody();
	}
}


