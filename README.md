#Scheme_Interpreter <Basic Edition>

Introduction:

	Scheme�������������棩
	ʵ����Scheme�Ļ������ܡ�
	
	ջ�ռ�������ٶ�����ÿ��5000��ָ�

How to build it?

	����Visual Studio 2010�³ɹ����벢��ͨ�����ԡ�
	
	���뻷����
		�뱣֤����128MB�Ķѿռ��ջ�ռ䡣		
			��Visual Studio�����öѱ����ռ��ջ�����ռ�Ϊ33554432
			����룺 /HEAP:"33554432" /STACK:"33554432"
		��VS2010����ʹ��Releaseģʽ����ʹ��������ʽ���룬�뾡���ܵĴ��Ż���

	�����ڲ�DEBUG���֣�
		debugger\debugger.h��       ����#define __DEBUG_MODE_ON_  		�����ڴ󲿷ֺ��������ü�顣���ٶȻ������½���
		parser\parser.cpp			����#define __PARSER_DEBUGGER_		��������Ļ�������������ִ�в��衣������ʹ�õ���cout������ᵼ���ٶ��쳣����
		
How to use it?

	��ȷ��library.scm��Scheme_Interpreter��ͬһ��Ŀ¼�¡�
	�ļ�����������SchemeInterpreter.log�ڲ���

	Usage: Scheme_Interpreter <filename>
	
Test performance
	
	no_side_effect.scm		Accepted! 		19 min 30 s
		
	side_effect.scm			Accepted!		< 1 s
		
	deep_tree.scm			Accepted!		2 min 20 s
	
Postscript.
	
	���������һ�㡣����
		
	
	