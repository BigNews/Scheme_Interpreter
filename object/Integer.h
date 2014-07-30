#include "object.h"
#include "..\debugger\Debugger.h"
#include <memory>

#ifndef _INTEGER_H_
#define _INTEGER_H_

namespace ObjectDef
{
	class Integer : public Object
	{
	private:
		friend Integer IntPlus(const Integer&, const Integer&);	// a + b
		friend Integer _IntPlus(const Integer&, const Integer&);	// a + b (a >= 0 && b>= 0)
		friend Integer IntMinus(const Integer&, const Integer&);   // a - b (a >= b >= 0)
		friend Integer _IntMinus(const Integer&, const Integer&);  // a - b
		friend Integer IntMult(const Integer&, const Integer&);   // a * b
		friend Integer IntDiv(Integer, Integer);    // a / b
		friend Integer IntMod(const Integer&, const Integer&);	// a % b
		friend Integer IntModulo(const Integer&, const Integer&);	// a module b
		friend Integer IntGcd(Integer, Integer);	// (a, b)

		friend Integer IntAbs(const Integer&);					// absolute value

		friend bool IntEqual(const Integer&, const Integer&);	// a =? b
		friend bool IntBigger(const Integer&, const Integer&);	// a >? b		
		friend bool IntSmaller(const Integer&, const Integer&);	// a <? b

		friend bool IntBiggerOrEqual(const Integer&, const Integer&);	// a >=? b
		friend bool IntSmallerOrEqual(const Integer&, const Integer&);	// a <=? b

		friend void WriteInteger(const Integer&);// cout << Integer

	public:

		Integer();						//normal constructor   0
		Integer(const char *);			//converting string into number, throw "Error"
		Integer(const int);			//Allow 0-f(16)
		Integer(const Integer &);		//copy-constructor
		
		Integer operator=(const Integer &tmp);
		//constructor

		~Integer();						//destructor

		int Size() const;
		int StorageNum(int) const;
		bool IsNonnegative() const;

		//bool GetExactness();			// get exactness(obsoleted)

	private:

		const static int modv = 10000;		//	compress four digit into one datum<int>.

		int capacity, size;					//	related to length of Integers.
		bool nonnegative;					//	suggest that Integer is nonnegative or not.

		int* num;							//	Integer data

		void assignSpace(int);					//	call this method to get a specific capacity

		//bool exactness;						// exact or inexact number; already obsoleted.

		//--------------------------------------------------------------------------------
		//**********inherit from class Object**********

		//int refered;			//How many points have pointed to this object.
								//This Object will be deleted when refered's value is zero;

		//int garbagePos;			//Garbage Index (class Gabage) [obsolete]

		//ObjectType objType;

		//**********inherit from class Number**********
		//bool exactness
	};

	bool IntStrCheck(const char *str);

	Integer IntPlus(const Integer&, const Integer&);			// a + b
	Integer _IntPlus(const Integer&, const Integer&);			// a + b  (a >= 0 && b >= 0)
	Integer IntMinus(const Integer&, const Integer&);		// a - b
	Integer _IntMinus(const Integer&, const Integer&);		// a - b  (a >= b >= 0)
	Integer IntMult(const Integer&, const Integer&);			// a * b
	Integer IntDiv( Integer, Integer);			// a / b
	Integer IntMod(const Integer&, const Integer&);		// a % b
	Integer IntModulo(const Integer&, const Integer&);
	Integer IntGcd(Integer, Integer);		// (a, b)

	Integer IntAbs(const Integer&);				//absolute value

	bool IntEqual(const Integer&, const Integer&);	// a =? b
	bool IntBigger(const Integer&, const Integer&);	// a >? b		
	bool IntSmaller(const Integer&, const Integer&);	// a <? b

	bool IntBiggerOrEqual(const Integer&, const Integer&);	// a >=? b
	bool IntSmallerOrEqual(const Integer&, const Integer&);	// a <=? b

	void WriteInteger(const Integer&);// cout << Integer

	bool IntegerSqrt(Integer &, Integer &);

	const Integer IntZero("0");
	const Integer IntOne("1");
	const Integer IntTen("10");
	const Integer IntMinusOne("-1");
	const Integer IntTwo("2");
}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;

	void _DisplayInteger(shared_ptr<Object>);
}

#endif

