#Scheme_Interpreter <Basic Edition>

Introduction:

	Scheme解释器（基础版）
	实现了Scheme的基础功能。
	
	栈空间需求大，速度慢（每秒5000条指令）

How to build it?

	已在Visual Studio 2010下成功编译并且通过测试。
	
	编译环境：
		请保证至少128MB的堆空间和栈空间。		
			在Visual Studio中设置堆保留空间和栈保留空间为33554432
			或加入： /HEAP:"33554432" /STACK:"33554432"
		在VS2010下请使用Release模式，如使用其它方式编译，请尽可能的打开优化。

	代码内部DEBUG部分：
		debugger\debugger.h：       启用#define __DEBUG_MODE_ON_  		可以在大部分函数中启用检查。但速度会有所下降。
		parser\parser.cpp			启用#define __PARSER_DEBUGGER_		可以在屏幕上输出解释器的执行步骤。但由于使用的是cout输出，会导致速度异常慢。
		
How to use it?

	请确保library.scm与Scheme_Interpreter在同一个目录下。
	文件的输出存放在SchemeInterpreter.log内部。

	Usage: Scheme_Interpreter <filename>
	
Test performance
	
	no_side_effect.scm		Accepted! 		19 min 30 s
		
	side_effect.scm			Accepted!		< 1 s
		
	deep_tree.scm			Accepted!		2 min 20 s
	
Postscript.
	
	请对它温柔一点。。。
		
	
	