#include "Integer.h"
#include "..\debugger\Debugger.h"
#include <iostream>
#include <memory>

namespace ObjectDef
{
	Integer::Integer()
	{
		//construct an Integer with value 0.
		capacity = 1; size = 1;
		nonnegative = true;

		
		num = new int[capacity];
		num[0] = 0;

		objType = INTEGER;

		//exactness = true;
	}

	bool Integer::IsNonnegative() const
	{
		return nonnegative;
	}

	Integer::Integer(const char *str)
	{
		int len = strlen(str);

		//exactness = true;

		size = len / 4 + 1;
		capacity = size + 1;
		//while (capacity < size) capacity *= size + 1;	//Set size and capacity;

		num = new int[capacity];
		for (int i = 0; i < capacity; ++i) num[i] = 0;	//apply memory

		int i = 0;
		nonnegative = true;
		if (str[0] == '+') i = 1;
		if (str[0] == '-') 
		{ 
			nonnegative = false; i = 1;

			#ifdef __DEBUG_MODE_ON_

			if (i == len) throw Debugger::DebugMessage("In Integer constructor.\nIllegal String, only with '-'.");
		
			#endif

		}	//check str if it is negative

		int k = 0, count = 0, now = 0, powe = 1;
		for (int j = len - 1; j >= i; --j)
		{
			if (k == 4) 
			{ 
				num[now] = count; ++now; 
				count = 0; k = 0; powe = 1;
			}

			#ifdef __DEBUG_MODE_ON_

			if ((str[j] < '0' || str[j] > '9')) throw Debugger::DebugMessage("In Integer constructor.\nIllegal String, Expect Number, got something else.");

			#endif

			int tmp = str[j];
			//if (tmp == '#') tmp = '0', exactness = false;
			count = count + powe * (str[j] - '0');
			powe *= 10;
			++k;
		}
		num[now] = count;

		while (size > 1 && num[size - 1] == 0) --size;		//delete leading zero
		
		if (size == 1 && num[0] == 0) nonnegative = true;

		objType = INTEGER;
	}

	Integer::Integer(const Integer &tmp)
	{
		if (&tmp == this) return;

		capacity = tmp.capacity;
		size = tmp.size;

		nonnegative = tmp.nonnegative;

		//exactness = tmp.exactness;

		num = new int[capacity];

		for (int i = 0; i < size; ++i)
			num[i] = tmp.num[i];

		if (size == 1 && num[0] == 0) nonnegative = true;

		objType = INTEGER;
	}

	Integer Integer::operator=(const Integer &tmp)
	{
		if (&tmp == this) return(*this);

		delete num;

		capacity = tmp.capacity;
		size = tmp.size;
		nonnegative = tmp.nonnegative;

		//exactness = tmp.exactness;

		num = new int[capacity];

		for (int i = 0; i < size; ++i)
			num[i] = tmp.num[i];

		if (size == 1 && num[0] == 0) nonnegative = true;

		return (*this);
	}

	Integer::Integer(const int x)
	{
		capacity = 1; size = 1;
		nonnegative = true;

		
		num = new int[capacity];
		num[0] = x;

		objType = INTEGER;
	}

	Integer::~Integer()
	{
		delete [] num;
	}

	void Integer::assignSpace(int space)
	{
		int *tmp = num;

		capacity = space;
		size = space;
		
		num = new int[capacity];

		for (int i = 0; i < capacity; ++i) num[i] = 0;

		delete tmp;
	}

	Integer _IntPlus(const Integer &a, const Integer &b)
	{
		Integer exv;

		int maxlen = a.size; 
		if (b.size > maxlen) maxlen = b.size;	// the longest integer
		maxlen += 1;

		exv.nonnegative = true;

		exv.assignSpace(maxlen);

		int t1, t2;

		int temp;
		for (int i = 0; i < maxlen; ++i)
		{
			if (i >= a.size) t1 = 0; else t1 = a.num[i];
			if (i >= b.size) t2 = 0; else t2 = b.num[i];
			temp = exv.num[i] + t1 + t2;
			//if (exv.num[i] +)
			if (temp >= 10000) ++exv.num[i + 1], temp -= 10000;
			if (temp >= 10000) ++exv.num[i + 1], temp -= 10000;
			//exv.num[i + 1] += (exv.num[i] + t1 + t2) / 10000;		//isopsephy
			exv.num[i] = temp;			
		}

		while (exv.size > 1 && exv.num[exv.size - 1] == 0) --exv.size;	//delete leading zero

		if (exv.size == 1 && exv.num[0] == 0) exv.nonnegative = true;

		//exv.exactness = a.exactness && b.exactness; 

		return exv;
	}

	Integer IntPlus(const Integer &a, const Integer &b)
	{
		Integer exv;

		if (a.nonnegative && b.nonnegative) 
		{ exv = _IntPlus(a, b); }		// a>=0 && b>=0 

		if (!a.nonnegative && !b.nonnegative) 
		{
			exv = _IntPlus(IntAbs(a), IntAbs(b)); 
			exv.nonnegative = false;				// a < 0 && b < 0
		}

		if (!a.nonnegative && b.nonnegative)
		{
			if (IntBigger(IntAbs(a), b))
			{
				exv = _IntMinus(IntAbs(a), b);
				exv.nonnegative = false;
			}
			else
			{
				exv = _IntMinus(b, IntAbs(a));
				exv.nonnegative = true;
			}
		}

		if (a.nonnegative && !b.nonnegative)
		{
			if (!IntSmaller(a, IntAbs(b)))
			{
				exv = _IntMinus(a, IntAbs(b));
				exv.nonnegative = true;
			}
			else
			{
				exv = _IntMinus(IntAbs(b), a);
				exv.nonnegative = false;
			}
		} 

		return exv;
	}

	Integer _IntMinus(const Integer &a, const Integer &b)
	{
		Integer exv;

		int maxlen = a.size;
		if (b.size > maxlen) maxlen = b.size;

		exv.assignSpace(maxlen);

		int t1, t2;

		for (int i = maxlen - 1; i >= 0; --i)
		{
			if (i >= a.size) t1 = 0; else t1 = a.num[i];
			if (i >= b.size) t2 = 0; else t2 = b.num[i];

			exv.num[i] = t1 - t2;
			int j = i;
			while (exv.num[j] < 0)
			{
				--exv.num[j + 1];
				exv.num[j] += 10000;
				++j;
			}
		}

		while (exv.size > 1 && exv.num[exv.size - 1] == 0) --exv.size;	//delete leading zero

		exv.nonnegative = true;

		//exv.exactness = a.exactness && b.exactness; 

		return exv;
	}

	Integer IntMinus(const Integer &a, const Integer &b)
	{
		Integer tmp(b);
		tmp.nonnegative = !tmp.nonnegative;
		if (tmp.size == 1 && tmp.num[0] == 0) tmp.nonnegative = true;

		return IntPlus(a, tmp);
	}

	bool IntBigger(const Integer &a, const Integer &b)
	{
		int maxlen = a.size;
		if (b.size > maxlen) maxlen = b.size;

		int f1, f2;
		if (a.nonnegative) f1 = 1; else f1 = -1;
		if (b.nonnegative) f2 = 1; else f2 = -1;
		int t1, t2;

		for (int i = maxlen - 1; i >= 0; --i)
		{
			if (i >= a.size) t1 = 0; else t1 = a.num[i] * f1;
			if (i >= b.size) t2 = 0; else t2 = b.num[i] * f2;
			if (t1 != t2) return (t1 > t2);
		}

		return false;
	}

	bool IntSmaller(const Integer &a, const Integer &b)
	{
		int maxlen = a.size;
		if (b.size > maxlen) maxlen = b.size;

		int f1, f2;
		if (a.nonnegative) f1 = 1; else f1 = -1;
		if (b.nonnegative) f2 = 1; else f2 = -1;
		int t1, t2;

		for (int i = maxlen - 1; i >= 0; --i)
		{
			if (i >= a.size) t1 = 0; else t1 = a.num[i] * f1;
			if (i >= b.size) t2 = 0; else t2 = b.num[i] * f2;
			if (t1 != t2) return (t1 < t2);
		}

		return false;
	}

	bool IntEqual(const Integer &a, const Integer &b)
	{
		if (IntSmaller(a, b) || IntBigger(a, b)) return false;
		return true;
	}

	bool IntBiggerOrEqual(const Integer &a, const Integer &b)
	{
		return !IntSmaller(a, b);
	}

	bool IntSmallerOrEqual(const Integer &a, const Integer &b)
	{
		return !IntBigger(a, b);
	}

	void WriteInteger(const Integer &a)
	{
		if (!a.nonnegative) std::cout << "-";
		std::cout << a.num[a.size - 1];
		for (int i = a.size - 2; i >= 0; --i)
		{
			if (a.num[i] < 1000) std::cout << "0";
			if (a.num[i] < 100)  std::cout << "0";
			if (a.num[i] < 10)   std::cout << "0";
			std::cout << a.num[i];
		}
	}

	Integer IntAbs(const Integer &a)
	{
		if (a.nonnegative) return a;

		Integer exv(a);
		exv.nonnegative = true;
		//exv.exactness = a.exactness;

		return exv;
	}

	Integer IntMult(const Integer &a, const Integer &b)
	{
		int maxlen = a.size + b.size + 1;

		Integer exv;
		exv.assignSpace(maxlen);

		for (int i = 0; i < a.size; ++i)
			for (int j = 0; j < b.size; ++j)
			{
				exv.num[i + j] = exv.num[i + j] + a.num[i] * b.num[j];
				exv.num[i + j + 1] = (exv.num[i + j] / 10000 + exv.num[i + j + 1]);
				exv.num[i + j] = exv.num[i + j] % 10000;
			}

		exv.nonnegative = !(a.nonnegative ^ b.nonnegative);
		//exv.exactness = a.exactness && b.exactness; 

		while (exv.size > 1 && exv.num[exv.size - 1] == 0) --exv.size;
		if (exv.size == 1 && exv.num[0] == 0) exv.nonnegative = true;

		return exv;
	}

	Integer IntDiv(Integer a, Integer b)
	{
		Integer exv;

		bool nega = !(a.nonnegative ^ b.nonnegative);
		b.nonnegative = a.nonnegative = true;

		#ifdef __DEBUG_MODE_ON_

		if (b.size == 1 && b.num[0] == 0) throw Debugger::DebugMessage("In builtin function IntDiv,\nDivided By zero without checking,\nmodify it in 'Integer.cpp'");

		#endif

		Integer temp("1");

		while (IntSmallerOrEqual(IntMult(b, temp), a))
		{
			temp = IntMult(temp, IntTen);
		}

		Integer tmp;

		while (IntBigger(temp, IntZero))
		{
			tmp = IntMult(b, temp);
			while (IntBiggerOrEqual(a, tmp))
			{
				a = IntMinus(a, tmp);
				exv = IntPlus(exv, temp);
			}
			if (temp.num[temp.size - 1] > 1) temp.num[temp.size - 1] /= 10; 
			else
			{
				temp.num[temp.size - 1] = 0;
				if (temp.size > 1)
				{
					--temp.size;
					temp.num[temp.size - 1] = 1000; 
				}
			}
		}

		exv.nonnegative = nega;

		while (exv.size > 1 && exv.num[exv.size - 1] == 0) --exv.size;		//Normalize exv
		if (exv.size == 1 && exv.num[0] == 0) exv.nonnegative = true;		// 0 equals -0

		return exv;
	}

	Integer IntMod(const Integer &a, const Integer &b)
	{

		#ifdef __DEBUG_MODE_ON_

		if (b.size == 1 && b.num[0] == 0) throw Debugger::DebugMessage("In builtin function IntMod,\nDivided By zero without checking,\ntry to modify it in 'Integer.cpp'");

		#endif

		//Integer exv;
		//exv = ;

		return IntMinus(a, IntMult(b, IntDiv(a, b)));
	}

	Integer IntModulo(const Integer &a, const Integer &b)
	{
		#ifdef __DEBUG_MODE_ON_

		if (b.size == 1 && b.num[0] == 0) throw Debugger::DebugMessage("In buildin function IntModule,\nDivided By zero.\n");

		#endif

		Integer exv(IntMod(a, b));
		if (IntBiggerOrEqual(exv, IntZero)) return exv;
		return IntPlus(exv, b);
	}

	Integer IntGcd(Integer a, Integer b)
	{
		#ifdef __DEBUG_MODE_ON_

		if (a.size == 1 && a.num[0] == 0 && b.size == 1 && b.num[0] == 0)
			throw Debugger::DebugMessage("In function IntGcd,\nGet Two Zero!\n");

		#endif

		Integer t;
		while (!IntEqual(b, IntZero))
		{
			t = IntMod(a, b);
			a = b;
			b = t;
		}

		return a;
	}

	bool IntStrCheck(const char *str)
	{
		int len = strlen(str);

		if (len == 0) return false; //empty string, not a integer;

		int i = 0;
		if (str[0] == '-' || str[0] == '+') ++i;

		if (len <= i) return false; //a symbol '-' is insignificant. 

		for (;i<len; ++i)
			if (!(str[i] >= '0' && str[i] <= '9')) break;
		if (i < len) return false;

		return true;
	}

	int Integer::Size() const{ return size; }
	int Integer::StorageNum (int index) const
	{
		#ifdef __DEBUG_MODE_ON_

		if (index < 0 || index >= size)
			throw Debugger::DebugMessage("In Integer::StorageNum,\nIndex Out of Bound!\n");

		#endif

		return num[index];
	}

	bool IntegerSqrt(Integer &x, Integer &exv)
	{
		if (IntSmaller(x, IntZero)) return false;
		Integer l = IntZero, r = x;
		Integer mid;

		while (IntBigger(IntMinus(r, l), IntOne))
		{
			mid = IntDiv(IntPlus(l, r), IntTwo);

			if (IntBigger(IntMult(mid, mid), x))
				r = mid;
			else
				l = mid;
		}

		if (IntEqual(IntMult(l, l), x))
		{
			exv = l;
			return true;
		}
		if (IntEqual(IntMult(r, r), x))
		{
			exv = r;
			return true;
		}

		return false;
	}

}

namespace buildin
{
	using namespace ObjectDef;
	using std::shared_ptr;
	using std::static_pointer_cast;
	
	void _DisplayInteger(shared_ptr<Object> x)
	{
		#ifdef __DEBUG_MODE_ON_

		if ((*x).getType() != INTEGER)
			throw Debugger::DebugMessage("In _DisplayInteger,\nx is not a Integer");

		#endif

		WriteInteger(*static_pointer_cast<Integer>(x));
	}
}