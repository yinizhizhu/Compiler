* 哈尔滨工业大学（HIT）计算机科学与技术 	《编译原理》(Compiler)

		The Implementation of Pascal Compiler with C Language.

* Lexical Analyzer:
		
		功能：用于对源码进行分词，识别种类后将结果输出。

		词法分析器比较简单，直接通过易懂的if语句进行分类识别

* Syntax Analyzer:

		功能：判断源码中的语法是否符合Pascal语言的语法规则。

		语法分析器的实现需要利用编译工作台 CWB_ 获得LR(1)表，然后写一个总控程序即解决（需要留意Lex和Syn的连接）

* Semantic Analyzer: 

		功能：判断源码中的语义是否符合实际要求（eg.无法int和string进行乘法操作），并输出中间代码。
		
		语义分析器的实现简单的通过产生式的结构进行解析，然后根据规则编写程序。


.. _CWB: http://pan.baidu.com/s/1skBbiR7#0-tsina-1-31651-397232819ff9a47a7b7e80a40613cfe1