#pragma once

#include <bitset>
#include "ToyUtility/Prerequisites/PreDefine.h"
#include "ToyUtility/Container/List.h"
#include "ToyUtility/String/String.h"
#include "TRL/TRLCommonType.h"
#include "TRL/details/TRLSL/Token.h"


namespace TRL
{

template<typename T, int chunkSize = 8>
class Pool
{
public:
	using ElementType = T;

	T* New()
	{
		if (m_Chunks.size() == 0 || m_SizeOfEveryChunk.back() == chunkSize)
		{
			m_Chunks.push_back(new T[chunkSize]);
			m_SizeOfEveryChunk.push_back(0);
		}

		return m_Chunks.back()[m_SizeOfEveryChunk.back()++];
	}

	~Pool()
	{
		for each(auto p in m_Chunks)
		{
			delete[] p;
		}
	}


private:
	ToyUtility::List<T*> m_Chunks;
	ToyUtility::List<int> m_SizeOfEveryChunk;
};


// TRL Shader Language Intermediate Representation
class TRLSL_IR
{
public:
    class StringPtr
    {
    public:
        StringPtr()
            :
            m_StrLen(0),
            m_StrPtr(nullptr)
        {}

        bool Empty() const { return m_StrLen == 0; }


    private:
        const char* m_StrPtr;
        ToyUtility::uint32 m_StrLen;
    };

    struct Type
    {
    public:
        enum TypeBitsets
        {
            Const,
            In,
            Out,
            Uniform,
            Highp,
            Mediump,
            Lowp,

            Void,
            Struct,
        };
        
        Type()
            :
            DataType(GPU_DATA_TYPE_INIT),
            Arrays{1,1,1,1}
        {}


        bool GetTag(TypeBitsets t) { return m_Bitset.test(t); }
        void SetTag(TypeBitsets t, bool value) { m_Bitset.set(t, value); }

        GpuDataType DataType;
        ToyUtility::uint8 Arrays[4]; // Example: arr[4][4][4][4]


    private:
        std::bitset<32> m_Bitset;
    };

    struct StructMember
    {
        StringPtr Name;
        Type Type;
    };

    struct Struct
    {
        StringPtr Name;
        ToyUtility::List<StructMember> Members;
    };

    struct UniformVariable
    {
        StringPtr Name;
        Type Type;
        // init value // TODO
    };

    struct FunctionParam
    {
        Type Type;
        StringPtr Name;
    };

    struct Expression
    {
        enum ExpressionType
        {
            VariableIdentifier,
            Constant,
            LB_Expression_RB,

            ArrayAccess, // PostfixExp__LM__integer_expression__RM,
            FunctionCall,
            MemberFieldAccess, // PostfixExp__DOT__FIELD_SELECTION,
            PostfixInc, // A ++
            PostfixDec, // A --
            PrefixInc, // ++ A
            PrefixDec, // -- A
            UnaryOp__Plus, // + A
            UnaryOp__Dash, // - A
            UnaryOp__Bang, // ! A
            UnaryOp__Tilde, // ~ A
            Mul, // A * B
            Div, // A / B
            Percent, // A % B
            Plus, // A + B
            Dash, // A - B
            LeftShift, // A << B
            RightShift, // A >> B
            Less, // A < B
            Greater, // A > B
            LessEqual, // A <= B
            GreaterEqual, // A >= B
            Equal, // A == B
            NotEqual, // A != B
            BitOp_And, // A & B
            BitOp_ExclusiveOr, // A ^ B
            BitOp_InclusiveOr, // A | B
            LogicOp_And, // A && B
            LogicOp_Or, // A || B
            LogicOp_Question, // A ? B : C
            Assign_Equal, // A = B
            Assign_MulEqual, // A *= B
            Assign_DivEqual, // /=
            Assign_ModEqual, // %=
            Assign_AddEqual, // +=
            Assign_SubEqual, // -=
            Assign_LeftShiftEqual, // <<=
            Assign_RightShiftEqual, // >>=
            Assign_BitOp_AndEqual, // &=
            Assign_BitOp_XOrEqual, // ^=
            Assign_BitOp_OrEqual, // |=

            AnotherExpression, // A, B  `a = 1, b = 3`
        };

        ExpressionType ExpType;
        
        union
        {
            struct
            {
                Expression* A;
                Expression* B;
                Expression* C;
            } Common;

            struct
            {
                Token* Identifier; // TODOH ?
            } VariableIdentifier;

            struct
            {
                // trlsl_parser.y:L116
                Expression* FunctionIdentifier; // IDENTIFIER
                Type* FunctionIdentifier_; // type_specifier
                ToyUtility::List<Expression*>* Params;
            } FunctionCall;
        } _;
    };

    struct Statement
    {
        enum StatementType
        {
            ComponentStatement, // Surrounded by `{` and `}`
            
            DeclarationStatement,
            ExpressionStatement,
            SelectionStatement,
            IterationStatement,
            JumpStatement,
        };

        enum IterationStmtType
        {
            For,
            While,
        };

        enum JumpStmtType
        {
            Break,
            Continue,
            Return,
            Discard,
        };

        StatementType StatementType;
        union
        {
            struct
            {
                ToyUtility::List<Statement>* Statements;
            } ComponentStmt;

            struct
            {
                ToyUtility::List<StringPtr>* VariableNames;
                Type Type;
                // TODOH: init value
            } DeclarationStmt;

            struct
            {
                Expression* Expression;
            } ExpressionStmt;

            struct
            {
                // if statement
                Expression* Condition;
                Statement* ThenStatement;
                Statement* ElseStatement;
            } SelectionStmt;

            struct
            {
                IterationStmtType Type;
                union
                {
                    // while statement
                    struct
                    {
                        Expression* Condition;
                        Statement*  LoopBody;
                    } WhileStmt;
                    
                    // for statement
                    struct
                    {
                        Statement* ForInitStmt;
                        Expression* Condition;
                        Expression* ForEndStmt;
                        Statement* LoopBody;
                    } ForStmt;
                } _;
            } IterationStmt;

            struct
            {
                JumpStmtType Type;

                union
                {
                    struct
                    {
                        Expression* RetExpression;
                    } ReturnStmt;
                } _;
            } JumpStmt;
        } _;
    };

    struct Function
    {
        StringPtr                           Name;
        Type                                ReturnType;
        ToyUtility::List<FunctionParam>     Params;
        Statement                           FunctionImpl;
    };

    enum class PragmaCmdType
    {
        Vertex, // Vertex Shader
        Fragment, // Fragment Shader
    };

    struct Pragma
    {
        PragmaCmdType CmdType;
        union
        {
            struct
            {
                StringPtr FunctionName;
            } Vertex;

            struct
            {
                StringPtr FunctionName;
            } Fragment;
        } _;
    };


public:
    TRLSL_IR()
    {}

	const ToyUtility::List<Struct>& GetStructs() const { return m_Structs; }


private:
    ToyUtility::List<Struct> m_Structs;
    ToyUtility::List<UniformVariable> m_UniformVariables;
    ToyUtility::List<Function> m_Functions;
    ToyUtility::List<Pragma> m_Pragmas;

	Pool<Statement> m_StatementPool;
	Pool<Expression> m_ExpressionPool;
};


} // end of namespace TRL