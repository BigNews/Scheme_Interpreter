

#ifndef _OBJECT_H_
#define _OBJECT_H_

namespace ObjectDef
{
	enum ObjectType{
		OBJECT,		// default ObjectType
		BOOLEAN,	// boolean
		INTEGER,	// integer, included by Rational 
		RATIONAL, REAL, // rational number and real number are included by complex number.
		COMPLEX_RATIONAL,	COMPLEX_REAL, //numbers
		PRIMITIVE_PROCEDURE,	// primitive procedure
		COMPOUND_PROCEDURE,		// compound procedure
		PAIR,			// pair
		//LIST,			// list, included by Pair
		SYMBOL,			// symbol
		CHAR,			// character
		STRING,			// string
		//VECTOR,			// vector
		ENVIRONMENT,	// environment
		//PAIRDOT,		
		VOID,			// None
		UNDEFINED,		// Undefined Object
		NIL,			// For empty list

		//Bonus Part? ( Too hard too achieve them...
		CONTINUATION
	};

	class Object
	{
	public:
		ObjectType getType() {return objType; }
	protected:

		ObjectType objType;
	};
}

#endif