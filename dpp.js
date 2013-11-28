{
	"Token" : [
		{ "Name" : "Var", "Regex" : "var", "ConvertFunction" : "void" },
		{ "Name" : "Int", "Regex" : "int", "ConvertFunction" : "void" },
		{ "Name" : "Uint", "Regex" : "uint", "ConvertFunction" : "void" },
		{ "Name" : "Short", "Regex" : "short", "ConvertFunction" : "void" },
		{ "Name" : "Ushort", "Regex" : "ushort", "ConvertFunction" : "void" },
		{ "Name" : "Byte", "Regex" : "byte", "ConvertFunction" : "void" },
		{ "Name" : "Ubyte", "Regex" : "ubyte", "ConvertFunction" : "void" },
		{ "Name" : "Long", "Regex" : "long", "ConvertFunction" : "void" },
		{ "Name" : "Ulong", "Regex" : "ulong", "ConvertFunction" : "void" },
		{ "Name" : "Const", "Regex" : "const", "ConvertFunction" : "void" },
		{ "Name" : "Int_Value", "Regex" : "[0-9]+", 
			"ConvertFunction" : "void" },
		{ "Name" : "Identifier", "Regex" : "", "ConvertFunction" : "void" },
		{ "Name" : "Float", "Regex" : "float", "ConvertFunction" : "void" },
		{ "Name" : "Lparen", "Regex" : "(", "ConvertFunction" : "void" },
		{ "Name" : "Rparen", "Regex" : ")", "ConvertFunction" : "void" },
		{ "Name" : "Lbrack", "Regex" : "[", "ConvertFunction" : "void" },
		{ "Name" : "Rbrack", "Regex" : "]", "ConvertFunction" : "void" },
		{ "Name" : "Lcurly", "Regex" : "{", "ConvertFunction" : "void" },
		{ "Name" : "Rcurly", "Regex" : "}", "ConvertFunction" : "void" },
		{ "Name" : "Dot", "Regex" : ".", "ConvertFunction" : "void" },
		{ "Name" : "Plusplus", "Regex" : "++", "ConvertFunction" : "void" },
		{ "Name" : "Minusminux", "Regex" : "--", "ConvertFunction" : "void" },
		{ "Name" : "Cast", "Regex" : "cast", "ConvertFunction" : "void" },
		{ "Name" : "Star", "Regex" : "*", "ConvertFunction" : "void" },
		{ "Name" : "Div", "Regex" : "/", "ConvertFunction" : "void" },
		{ "Name" : "Modulo", "Regex" : "%", "ConvertFunction" : "void" }
		{ "Name" : "Minus", "Regex" : "-", "ConvertFunction" : "void" }
		{ "Name" : "Plus", "Regex" : "+", "ConvertFunction" : "void" }
		{ "Name" : "Concat", "Regex" : "~", "ConvertFunction" : "void" }
		{ "Name" : "Star", "Regex" : "*", "ConvertFunction" : "void" }
		{ "Name" : "Bang", "Regex" : "~", "ConvertFunction" : "void" }
		{ "Name" : "And", "Regex" : "&", "ConvertFunction" : "void" }
		{ "Name" : "Leftshift", "Regex" : "<<", "ConvertFunction" : "void" }
		{ "Name" : "Rightshift", "Regex" : ">>", "ConvertFunction" : "void" }
		{ "Name" : "Less", "Regex" : "<", "ConvertFunction" : "void" }
		{ "Name" : "Lessequal", "Regex" : "<=", "ConvertFunction" : "void" }
		{ "Name" : "Greater", "Regex" : ">", "ConvertFunction" : "void" }
		{ "Name" : "Greaterequal", "Regex" : ">=", "ConvertFunction" : "void" }
		{ "Name" : "Equal", "Regex" : "==", "ConvertFunction" : "void" }
		{ "Name" : "Notequal", "Regex" : "!=", "ConvertFunction" : "void" }
		{ "Name" : "Is", "Regex" : "is", "ConvertFunction" : "void" }
		{ "Name" : "Bangis", "Regex" : "!is", "ConvertFunction" : "void" }
		{ "Name" : "And", "Regex" : "&", "ConvertFunction" : "void" }
		{ "Name" : "Logicaland", "Regex" : "&&", "ConvertFunction" : "void" }
		{ "Name" : "Or", "Regex" : "|", "ConvertFunction" : "void" }
		{ "Name" : "Logicalor", "Regex" : "||", "ConvertFunction" : "void" }
		{ "Name" : "Xor", "Regex" : "^", "ConvertFunction" : "void" }
		{ "Name" : "Questionmark", "Regex" : "?", "ConvertFunction" : "void" }
		{ "Name" : "Colon", "Regex" : ":", "ConvertFunction" : "void" }
		{ "Name" : "Comma", "Regex" : ",", "ConvertFunction" : "void" }
		{ "Name" : "Assign", "Regex" : "=", "ConvertFunction" : "void" }
		{ "Name" : "Var", "Regex" : "var", "ConvertFunction" : "void" }
		{ "Name" : "While", "Regex" : "while", "ConvertFunction" : "void" }
		{ "Name" : "For", "Regex" : "for", "ConvertFunction" : "void" }
		{ "Name" : "Foreach", "Regex" : "foreach", "ConvertFunction" : "void" }
		{ "Name" : "Do", "Regex" : "do", "ConvertFunction" : "void" }
		{ "Name" : "Def", "Regex" : "def", "ConvertFunction" : "void" }
		{ "Name" : "Semicolon", "Regex" : ";", "ConvertFunction" : "void" }
		{ "Name" : "Return", "Regex" : "return", "ConvertFunction" : "void" }
		{ "Name" : "Extern", "Regex" : "return", "ConvertFunction" : "void" }
		{ "Name" : "Else", "Regex" : "else", "ConvertFunction" : "void" }
		{ "Name" : "Foreach", "Regex" : "foreach", "ConvertFunction" : "void" }
		{ "Name" : "For", "Regex" : "for", "ConvertFunction" : "void" }
		{ "Name" : "True", "Regex" : "true", "ConvertFunction" : "void" }
		{ "Name" : "False", "Regex" : "false", "ConvertFunction" : "void" }
	],
	"Rules" : [
		{ "Name" : "Start", "Expression" : [
			{ "Rule" : "Decl(start)", "Id" : "Start" }
			]
		},
		{ "Name" : "Decl", "Expression" : [
			{ "Rule" : "FunctionDecl(func)", "Id" : "Function"}
			{ "Rule" : "Extern ; FunctionPrototypeDecl(funcDecl) ; Semicolon", 
				"Id" : "FunctionDecl"}
			]
		},
		{ "Name" : "FunctionDecl", "Expression" : [
			{ "Rule" : 
				"FunctionPrototypeDecl(decl) ; BlockStatement(statements)", 
				"Id" : "FunctionWithBlockStmt" }
			]
		},
		{ "Name" : "FunctionPrototypeDecl", "Expression" : [
			{ "Rule" : "Def ; Type(returnType) ; Identifier(identifier) ; "\
					"Lparen ; ArgumentList(argList) ; Rparen",
				"Id" : "WithArgList" }
			{ "Rule" : "Def ; Type(returnType) ; Identifier(identifier) ; "\
				"Lparen ; Rparen", "Id" : "WithoutArgList" }
			]
		},
		{ "Name" : "StatementList", "Expression" : [
			{ "Rule" : "Statement(stmt)" , "Id" : "Block" }
			{ "Rule" : "Statement(stmt) ; StatementList(follow)" , 
				"Id" : "BlockStatementList" }
			]
		},
		{ "Name" : "Statement", "Expression" : [
			{ "Rule" : "BlockStatement(blockstmt)" , "Id" : "Block" }
			{ "Rule" : "ExpressionStatement(exprstmt)" , "Id" : "Expr" }
			{ "Rule" : "IterationStatement(iterstmt)" , "Id" : "Iteration" }
			{ "Rule" : "ReturnStatement(retstmt)" , "Id" : "Return" }
			{ "Rule" : "BranchStatement(branchstmt)" , "Id" : "Branch" }
			{ "Rule" : "ForStatement(forstmt)" , "Id" : "For" }
			{ "Rule" : "WhileStatement(whilestmt)" , "Id" : "While" }
			{ "Rule" : "DoWhileStatement(dowhilestmt)" , "Id" : "DoWhile" }
			]
		},
		{ "Name" : "DoWhileStatement", "Expression" : [
			# without label
			{ "Rule" : "Do ; BlockStatement(stmt) ; While ; Lparen ; "\
				"ConditionalExpression(cond) ; Rparen ; Semicolon",
				"Id" : "Cond"}
			{ "Rule" : "Do ; BlockStatement(stmt) ; While ; Lparen ; "\
				"Rparen ; Semicolon", "Id" : "WithoutCond"}
			# with label
			{ "Rule" : "Do ; BlockStatement(stmt) ; Identifier(label) ; "\
				"While ; Lparen ; ConditionalExpression(cond) ; Rparen ; "\
				"Semicolon", "Id" : "CondLabel"}
			{ "Rule" : "Do ; BlockStatement(stmt) ; Identifier(label) ; "\
				"While ; Lparen ; Rparen ; Semicolon", 
				"Id" : "WithoutCondLabel"}
			]
		},
		{ "Name" : "WhileStatement", "Expression" : [
			# without label
			{ "Rule" : "While ; Lparen ; ConditionalExpression(cond) ; "\
				"Rparen ; BlockStatement(stmt)", "Id" : "Cond"}
			{ "Rule" : "While ; Lparen ; Rparen ; BlockStatement(stmt)", 
				"Id" : "WhileTrue"}
	
			# with label
			{ "Rule" : "While ; Lparen ; ConditionalExpression(cond) ; "\
				"Rparen ; Identifier(label) ; BlockStatement(stmt)", 
				"Id" : "Cond"}
			{ "Rule" : "While ; Lparen ; Rparen ; Identifier(label) ; "\
				"BlockStatement(stmt)", 
				"Id" : "WhileTrue"}
			]
		},
		{ "Name" : "ForStatement", "Expression" : [
			# without label
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon ; Expression(incre) "\
				"; Rparen ; BlockStatement(stmt) " , "Id" : "InitTestInc" }
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon "\
				"; Rparen ; BlockStatement(stmt) " , "Id" : "InitTest" }
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; "\
				"Semicolon ; Expression(incre) "\
				"; Rparen ; BlockStatement(stmt) " , "Id" : "InitInc" }
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; Semicolon "\
				"; Rparen ; BlockStatement(stmt) " , "Id" : "Init" }
			{ "Rule" : "For ; Lparen ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon ; Expression(incre) "\
				"; Rparen ; BlockStatement(stmt) " , "Id" : "TestInc" }
			{ "Rule" : "For ; Lparen ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon ; "\
				"BlockStatement(stmt) " , "Id" : "Test" }
			{ "Rule" : "For ; Lparen ; Semicolon ; Semicolon ; "\
				"Expression(incre) "\
				"; Rparen ; BlockStatement(stmt) " , "Id" : "Inc" }
			{ "Rule" : "For ; Lparen ; Semicolon ; Semicolon ; "\
				"Expression(incre) ; Rparen ; BlockStatement(stmt) ",
				"Id" : "Inc" }
			{ "Rule" : "For ; Lparen ; Semicolon ; Semicolon ; Rparen ; "\
				"BlockStatement(stmt) " , "Id" : "WhileTrue" }
			# with label
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon ; Expression(incre) "\
				"; Rparen ; Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "InitTestIncLabel" }
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon "\
				"; Rparen ; Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "InitTestLabel" }
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; "\
				"Semicolon ; Expression(incre) "\
				"; Rparen ; Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "InitIncLabel" }
			{ "Rule" : "For ; Lparen ; VarDeclPrefix(itPrefix) ; "\
				"VarDeclDirectInit(itInit) ; Semicolon ; Semicolon "\
				"; Rparen ; Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "InitLabel" }
			{ "Rule" : "For ; Lparen ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon ; Expression(incre) "\
				"; Rparen ; Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "TestIncLabel" }
			{ "Rule" : "For ; Lparen ; Semicolon ; "\
				"ConditionalExpression(test) ; Semicolon ; Rparen ;"\
				"Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "TestLabel" }
			{ "Rule" : "For ; Lparen ; Semicolon ; Semicolon ; "\
				"Expression(incre) "\
				"; Rparen ; Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "IncLabel" }
			{ "Rule" : "For ; Lparen ; Semicolon ; Semicolon ; "\
				"Expression(incre) ; Rparen ; Identifier(label) ; "\
				"BlockStatement(stmt) ", "Id" : "IncLabel" }
			{ "Rule" : "For ; Lparen ; Semicolon ; Semicolon ; Rparen ; "\
				"Identifier(label) ; BlockStatement(stmt) " , 
				"Id" : "WhileTrueLabel" }
			]
		},
		{ "Name" : "BranchStatement", "Expression" : [
			{ "Rule" : "IfStatement(ifStmt)", "Id" : "If"}
			]
		}
		{ "Name" : "IfStatement", "Expression" : [
			{ "Rule" : "If ; Lparen ; ConditionalExpression(condExpr)"\
				" ; Rparen ; BlockStatement(thanBranch)", "Id" : "If" }

			{ "Rule" : "If ; Lparen ; ConditionalExpression(condExpr)"\
				" ; Rparen ; BlockStatement(thanBranch) ; "\
				"IfFollowStatement(follow)" , "Id" : "IfFollow" }
			]
		},
		{ "Name" : "IfFollowStatement", "Expression" : [
			{ "Rule" : "Else ; BlockStatement(stmt)", "Id" : "Else" }
			{ "Rule" : "Else ; If ; Lparen ; ConditionalExpression(cond) ; "\
				"Rparen ; BlockStatement(stmt)", "Id" : "ElseIf" }
			{ "Rule" : "Else ; If ; Lparen ; ConditionalExpression(cond) ; "\
				"Rparen ; BlockStatement(stmt) ; IfFollowStatement(follow)", 
				"Id" : "ElseIfFollow" }
			]
		},
		{ "Name" : "ReturnStatement", "Expression" : [
			{ "Rule" : "Return ; ConditionalExpression(condExpr)" , 
				"Id" : "ReturnConditional" }
			{ "Rule" : "Return" , "Id" : "Return" }
			]
		},
		{ "Name" : "BlockStatement", "Expression" : [
			{ "Rule" : "Lcurly ; Rcurly" , "Id" : "Empty" }
			{ "Rule" : "Lcurly ; StatementList(stmtList) ; Rcurly" , 
				"Id" : "StmtList" }
			]
		},
		{ "Name" : "IterationStatement", "Expression" : [
			{ "Rule" : "While ; Lparen ; Expression(expr) ; Rparen ; "\
				"BlockStatement(stmt)" , "Id" : "While" }
			{ "Rule" : "Do ; BlockStatement(stmt) ; While ; Lparen ; "\
				"Expression(expr) ; Rparen ; Semicolon", "Id" : "While" }
			]
		},
		{ "Name" : "ExpressionStatement", "Expression" : [
			{ "Rule" : "Expression(expr) ; Semicolon" , "Id" : "Expr" }
			{ "Rule" : "Semicolon" , "Id" : "NoExpr" }
			]
		},
		{ "Name" : "Expression", "Expression" : [
			{ "Rule" : "AssignmentExpression(expr)" , "Id" : "Next" }
			]
		},
		{ "Name" : "Type", "Expression" : [
			{ "Rule" : "BasicType(type)" , "Id" : "BasicType" },
			{ "Rule" : "BasicType(type) ; TypeFollow(follow)" , 
				"Id" : "BasicTypeFollow" },
			]
		},
		{ "Name" : "BasicType", "Expression" : [
			{ "Rule" : "Byte" , "Id" : "Byte" },
			{ "Rule" : "Short" , "Id" : "Short" },
			{ "Rule" : "Int" , "Id" : "Int" },
			{ "Rule" : "Long" , "Id" : "Long" },
			{ "Rule" : "Ubyte" , "Id" : "Ubyte" },
			{ "Rule" : "Uint" , "Id" : "Uint" },
			{ "Rule" : "Ushort" , "Id" : "Ushort" },
			{ "Rule" : "Ulong" , "Id" : "Ulong" },
			{ "Rule" : "Float" , "Id" : "Float" }
			]
		},
		{ "Name" : "TypeFollow", "Expression" : [
			{ "Rule" : "Lbrack ; Rbrack" , "Id" : "DynamicArray" },
			{ "Rule" : "Lbrack ; Rbrack ; TypeFollow(follow)" , 
				"Id" : "DynamicArrayFollow" }
			]
		},
		{ "Name" : "ArgumentList", "Expression" : [
			{ "Rule" : "Argument(arg)", "Id" : "Single"}
			{ "Rule" : "Argument(arg) ; Comma ; ArgumentList(follow)", 
				"Id" : "Multiple"}
			]
		},
		{ "Name" : "Argument", "Expression" : [
			{ "Rule" : "VarDeclPrefix(varName) ; VarDeclDeferedInit(type)", 
				"Id" : "VarNameType"}
			{ "Rule" : "ConstDeclPrefix(constName) ; VarDeclDeferedInit(type)", 
				"Id" : "ConstNameType"}
			]
		},
		{ "Name" : "VarDecl", "Expression" : [
			{ "Rule" : "VarDeclPrefix(varPrefix) ; VarDeclDirectInit(direct)", 
				"Id" : "VarDeclDirect"}
			{ "Rule" : "VarDeclPrefix(varPrefix) ; VarDeclDeferedInit(defered)",
				"Id" : "VarDeclDefered"}
			{ "Rule" : "ConstDeclPrefix(constPrefix) ; "\
				"VarDeclDirectInit(direct)", "Id" : "ConstDeclDirect"}
			]
		},
		{ "Name" : "VarDeclPrefix", "Expression" : [
			{ "Rule" : "Var ; Identifier(identifier) " , "Id" : "VarName" },
			]
		},
		{ "Name" : "ConstDeclPrefix", "Expression" : [
			{ "Rule" : "Const ; Identifier(identifier) " , "Id" : "ConstName" },
			]
		},
		{ "Name" : "VarDeclDirectInit", "Expression" : [
			{ "Rule" : "Lparen ; OrOrExpression(init) ; Rparen" , 
				"Id" : "Direct" },
			]
		},
		# VarDeclDeferedInit
		{ "Name" : "VarDeclDeferedInit", "Expression" : [
			{ "Rule" : "Colon ; Type(type)" , "Id" : "Defered" }
			]
		},
		{ "Name" : "AssignmentExpression", "Expression" : [
			{ "Rule" : "ConditionalExpression(drain)" , "Id" : "Cond" },
			{ "Rule" : "ConditionalExpression(drain) ; Assign ; "\
				"AssignmentExpression(source)" , "Id" : "Assign" },
			]
		},
		{ "Name" : "ConditionalExpression", "Expression" : [
			{ "Rule" : "OrOrExpression(orOrExpr)" , "Id" : "OrOr" },
			{ "Rule" : 
				"OrOrExpression(orOrExpr) ; Questionmark ; "\
				"Expression(trueBranch) ; Colon ; "\
				"ConditionalExpression(otherBranch) " , "Id" : "Ternary" },
			]
		},
		{ "Name" : "OrOrExpression", "Expression" : [
			{ "Rule" : "AndAndExpression(andAndExpr)" , "Id" : "AndAnd" },
			{ "Rule" : "AndAndExpression(andAndExpr) ; Logicalor ; "\
				"OrOrExpression(follow)" , "Id" : "LogicalOr" 
			}
			]
		},
		{ "Name" : "AndAndExpression", "Expression" : [
			{ "Rule" : "OrExpression(orExpr)" , "Id" : "Or" },
			{ "Rule" : "OrExpression(orExpr) ; Logicaland ; "\
				"AndAndExpression(follow)" , "Id" : "LogicalAnd" }
			]
		},
		{ "Name" : "OrExpression", "Expression" : [
			{ "Rule" : "XorExpression(xorExpr)" , "Id" : "Xor" },
			{ "Rule" : "XorExpression(xorExpr) ; Xor ; OrExpression(follow)" , 
				"Id" : "Or" }
			]
		},
		{ "Name" : "XorExpression", "Expression" : [
			{ "Rule" : "AndExpression(andExpr)" , "Id" : "And" },
			{ "Rule" : "AndExpression(andExpr) ; Xor ; XorExpression(follow)" , 
				"Id" : "Xor" }
			]
		},
		{ "Name" : "AndExpression", "Expression" : [
			{ "Rule" : "EqualityExpression(equal)" , "Id" : "Equality" },
			{ "Rule" : "EqualityExpression(equal) ; And ; "\
				"AndExpression(follow)" , "Id" : "Equal" }
			]
		},
		{ "Name" : "EqualityExpression", "Expression" : [
			{ "Rule" : "RelExpression(rel)" , "Id" : "Rel" },
			{ "Rule" : "RelExpression(rel) ; Equal ; "\
				"EqualityExpression(follow)" , "Id" : "Equal" },
			{ "Rule" : "RelExpression(rel) ; Bangequal ; "\
				"EqualityExpression(follow)" , "Id" : "NotEqual" },
			{ "Rule" : "RelExpression(rel) ; Is ; EqualityExpression(follow)" , 
				"Id" : "Is" },
			{ "Rule" : "RelExpression(rel) ; Bangis ; "\
				"EqualityExpression(follow)" , "Id" : "NotIs" },
			]
		},
		{ "Name" : "RelExpression", "Expression" : [
			{ "Rule" : "ShiftExpression(shift)" , "Id" : "Shift" },
			{ "Rule" : "ShiftExpression(shift) ; Less ; RelExpression(follow)",
				 "Id" : "Less" },
			{ "Rule" : "ShiftExpression(shift) ; Lessequal ; "\
				"RelExpression(follow)" , "Id" : "Lessequal" },
			{ "Rule" : "ShiftExpression(shift) ; Greater ; "\
				"RelExpression(follow)" , "Id" : "Greater" },
			{ "Rule" : "ShiftExpression(shift) ; Greaterequal ; "\
				"RelExpression(follow)" , "Id" : "Greaterequal" },
			]
		},
		{ "Name" : "ShiftExpression", "Expression" : [
			{ "Rule" : "AddExpression(add)" , "Id" : "Add" },
			{ "Rule" : "AddExpression(add) ; Leftshift ; "\
				"ShiftExpression(follow)" , "Id" : "LeftShift" },
			{ "Rule" : "AddExpression(add) ; Rightshift ; "\
				"ShiftExpression(follow)" , "Id" : "RightShift" },
			]
		},
		{ "Name" : "AddExpression", "Expression" : [
			{ "Rule" : "MulExpression(mul)" , "Id" : "Mul" },
			{ "Rule" : "MulExpression(mul) ; Plus ; AddExpression(follow)" , 
				"Id" : "Plus" },
			{ "Rule" : "MulExpression(mul) ; Minus ; AddExpression(follow)" , 
				"Id" : "Minus" },
			]
		},
		{ "Name" : "MulExpression", "Expression" : [
			{ "Rule" : "CastExpression(cast)" , "Id" : "Cast" },
			{ "Rule" : "CastExpression(cast) ; Star ; MulExpression(follow)" , 
				"Id" : "Multi" },
			{ "Rule" : "CastExpression(cast) ; Div ; MulExpression(follow)" , 
				"Id" : "Div" },
			{ "Rule" : "CastExpression(cast) ; Modulo ; MulExpression(follow)",
				 "Id" : "Modulo" },
			]
		},
		{ "Name" : "CastExpression", "Expression" : [
			{ "Rule" : " UnaryExpression(unaryFollow)" , "Id" : "Unary" },
			{ "Rule" : " Cast ; Lparen ;  Identifier(type) ; Rparen ; "\
				"CastExpression(follow)" , "Id" : "Cast" },
			]
		},
		{ "Name" : "UnaryExpression", "Expression" : [
			{ "Rule" : "PostfixExpression(expr)" , "Id" : "Post" },
			{ "Rule" : "Plusplus ; UnaryExpression(follow)", "Id" : "IncUnary" }
			{ "Rule" : "Plus ; UnaryExpression(follow)" , "Id" : "PlusUnary" }
			{ "Rule" : "Minus ; UnaryExpression(follow)" , "Id" : "MinusUnary" }
			{ "Rule" : "Bang ; UnaryExpression(follow)" , "Id" : "BangUnary" }
			{ "Rule" : "Concat ; UnaryExpression(follow)" , 
				"Id" : "ConcatUnary" },
			{ "Rule" : "And ; UnaryExpression(follow)" , "Id" : "AndUnary" }
			{ "Rule" : "Star ; UnaryExpression(follow)" , "Id" : "StarUnary" }
			{ "Rule" : "Minusminus ; UnaryExpression(follow)" , 
				"Id" : "DecUnary" }
			]
		},
		{ "Name" : "PostfixExpression", "Expression" : [
			{ "Rule" : "PrimaryExpression(primaryExpr)", "Id" : "Ident" },
			{ "Rule" : "PrimaryExpression(primaryExpr) ; "\
				"PostfixNextExpression(follow)", "Id" : "IdentPostfixNext" },
			]
		},
		{ "Name" : "PostfixNextExpression", "Expression" : [
			{ "Rule" : "Dot ; PostfixNextExpression(followPost)", 
				"Id" : "DotPostfixNext" },
			{ "Rule" : "Dot ; PrimaryExpression(followPrimary)", 
				"Id" : "DotPrimary" },
			{ "Rule" : "Dot ; PrimaryExpression(followPrimary) ; "\
				"PostfixNextExpression(followPost)", 
				"Id" : "DotPrimaryPostfixNext" 
			},
			{ "Rule" : "Lparen ; Rparen", "Id" : "Call" },
			{ "Rule" : "Lparen ; Rparen ; PostfixNextExpression(followPost)", 
				"Id" : "CallPostFixNext" },
			{ "Rule" : "Lbrack ; Expression(expr) ; Rbrack", 
				"Id" : "ArrayExpr" },
			{ "Rule" : "Lbrack ; Expression(expr) ; Rbrack ; "\
				"PostfixNextExpression(followPost)", 
				"Id" : "ArrayExprPostfixNext" }
			]
		},
		{ "Name" : "PrimaryExpression", "Expression" : [
			{ "Rule" : "Identifier(value)", 
				"Id" : "PrimaryExpressionIdentifier" },
			{ "Rule" : "Int_Value(value) ", "Id" : "Value" },
			{ "Rule" : "True ", "Id" : "True" },
			{ "Rule" : "False ", "Id" : "False" },
			{ "Rule" : "Lparen ; Expression(expr) ; Rparen", 
				"Id" : "PrimaryExpressionExpression" }
			]
		}
	]
}
