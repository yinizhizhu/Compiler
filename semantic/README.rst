* Semantic Analyzer: 

		功能：判断源码中的语义是否符合实际要求（eg.无法int和string进行乘法操作），并输出中间代码。
		
		语义分析器的实现简单的通过产生式的结构进行解析，然后根据规则编写程序。

* Note:
		
		source.txt：存放的源码
		
		syntaxResult：存放的词法分析器的输出结果
		
		result.txt：存放的中间代码