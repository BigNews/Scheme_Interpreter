#include "recognizer.h"
#include "token.h"


#include "..\object\object.h"
#include "..\object\Integer.h"
#include "..\object\boolean.h"
#include "..\object\Rational.h"
#include "..\object\pair.h"
#include "..\object\list.h"
#include "..\object\null.h"
#include "..\object\Complex_rational.h"
#include "..\object\complex_real.h"
#include "..\object\primitive.h"
#include "..\object\symbol.h"
#include "..\object\environment.h"
#include "..\object\void.h"
#include "..\object\Real.h"
#include "..\object\procedure.h"
#include "..\buildin\NumberOperation.h"

#ifndef _PARSER_H_
#define _PARSER_H_

namespace Parser
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;

	int TryToParse(Tokens&);

	shared_ptr<Object> LoadAndParseBlockFromToken(Tokens&, int&, int);

		//Eval A parsing tree.
	shared_ptr<Object> Eval(shared_ptr<Object>, shared_ptr<Environment>);

		//Apply A procedure
	shared_ptr<Object> Apply(shared_ptr<Object>, shared_ptr<Object>);

		
	//**************************Useful tool ***************

	shared_ptr<Object> LoadAndParseSequenceFromToken(Tokens&, int&, int);


	//Eval a self-evaluating element.
	bool _SelfEvaluating(shared_ptr<Object>);
	
	//Eval a variable.
	bool _IsVariable(shared_ptr<Object>);
	shared_ptr<Object> LookUpVariableValue(shared_ptr<Object>, shared_ptr<Environment>);
	
	//Eval a quoted value
	bool _IsQuoted(shared_ptr<Object>);
	shared_ptr<Object> TextOfQuotation(shared_ptr<Object>);
	
	//Eval a set! assignment
	bool _IsSetAssignment(shared_ptr<Object>);
	shared_ptr<Object> EvalAssignment(shared_ptr<Object>, shared_ptr<Environment>);
	
	//Eval a definition
	bool _IsDefinition(shared_ptr<Object>);
	shared_ptr<Object> EvalDefinition(shared_ptr<Object>, shared_ptr<Environment>);
	
	//Eval a if-predicate
	bool _IsIfPredicate(shared_ptr<Object>);
	shared_ptr<Object> IfPredicate(shared_ptr<Object>);
	shared_ptr<Object> IfConsequent(shared_ptr<Object>);
	shared_ptr<Object> IfAlternative(shared_ptr<Object>);
	shared_ptr<Object> EvalIf(shared_ptr<Object>, shared_ptr<Environment>);
	
	//Eval a lambda expression : TODO
	bool _IsLambda(shared_ptr<Object>);
	shared_ptr<Object> LambdaParameters(shared_ptr<Object>);
	shared_ptr<Object> LambdaBody(shared_ptr<Object>);
	shared_ptr<Object> MakeProcedure(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Environment>);
	
	//Eval a begin sequence :
	bool _IsBegin(shared_ptr<Object> x);
	shared_ptr<Object> BeginActions(shared_ptr<Object>);
	shared_ptr<Object> EvalSequence(shared_ptr<Object>, shared_ptr<Environment>);

	//Eval a let-binding.
	bool _IsLet(shared_ptr<Object> x);
	shared_ptr<Object> LetParameters(shared_ptr<Object>);
	shared_ptr<Object> LetBody(shared_ptr<Object>);
	shared_ptr<Object> EvalLet(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Environment>);

	//Eval a let*-binding
	bool _IsLetStar(shared_ptr<Object> x);
	shared_ptr<Object> EvalLetStar(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Environment>);

	//Eval a letrec-binding
	bool _IsLetRec(shared_ptr<Object> x);
	shared_ptr<Object> EvalLetRec(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Environment>);

	//Eval a cond-predicate : 
	bool _IsCond(shared_ptr<Object>);
	shared_ptr<Object> CondSequence(shared_ptr<Object>);
	bool ContainProcedure(shared_ptr<Object> x);
	//shared_ptr<Object> CondToIf(shared_ptr<Object>);
	shared_ptr<Object> EvalCond(shared_ptr<Object>, shared_ptr<Environment>);
	
	//Eval an application : 
	bool _IsApplication(shared_ptr<Object>);
	shared_ptr<Object> Operator(shared_ptr<Object>);
	shared_ptr<Object> Operands(shared_ptr<Object>);
	shared_ptr<Object> ListOfValue(shared_ptr<Object>, shared_ptr<Environment>);
	//shared_ptr<Object> EvalApply(shared_ptr<Procedure>, shared_ptr<Pair>);
	
	//Eval a backquoted value && quasiquoted value
		
	shared_ptr<Object> EvalBackQuotation(shared_ptr<Pair>, int);

	bool TaggedList(shared_ptr<Object> x, std::string y);

	shared_ptr<Object> ApplyPrimitiveProcedure(shared_ptr<Object>, shared_ptr<Object>);
	//shared_ptr<Object> ProcedureParameter(shared_ptr<Object>);
	shared_ptr<Object> ProcedureBody(shared_ptr<Object>);
	//shared_ptr<Environment> ExtendedEnvironment(shared_ptr<Object>, shared_ptr<Object>, shared_ptr<Object>);


}

#endif
