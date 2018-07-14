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

#define USE_POOL(TypeName)                                                  \
private:                                                                    \
    Pool<TypeName> m_##TypeName##Pool;                                      \
public:                                                                     \
    TypeName* New##TypeName() { return m_##TypeName##Pool.New(); }


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

        ToyUtility::String ToString() const { return ToyUtility::String(m_StrPtr, m_StrLen); }


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


        bool GetTag(TypeBitsets t) const { return m_Bitset.test(t); }
        void SetTag(TypeBitsets t, bool value) { m_Bitset.set(t, value); }
        bool IsArray() const { return !(Arrays[0] == 1 && Arrays[1] == 1 && Arrays[2] == 1 && Arrays[3] == 1); }
        int GetArraySize() const { return 4; }

        GpuDataType DataType;
        ToyUtility::uint8 Arrays[4]; // Example: arr[4][4][4][4]
        StringPtr Str;


    private:
        std::bitset<32> m_Bitset;
    };

    struct StructMember
    {
        Type Type;
        StringPtr Name;
        StringPtr Semantic;
    };

    struct Struct
    {
        bool IsValid() const { return !Name.Empty(); }

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

    struct ExpressionBase
    {
        ExpressionType ExpType;
    };

    struct ExpressionCommon : public ExpressionBase
    {
        ExpressionBase* A;
        ExpressionBase* B;
        ExpressionBase* C;
    };

    struct ExpressionVariableIdentifier : public ExpressionBase
    {
        Token* Identifier; // TODOH ?
    };

    struct ExpressionFunctionCall : public ExpressionBase
    {
        // trlsl_parser.y:L116
        ExpressionBase* FunctionIdentifier; // IDENTIFIER
        Type* FunctionIdentifier_; // type_specifier
        ToyUtility::List<ExpressionBase*> Params;
    };

    enum StatementType
    {
        ComponentStatement, // Surrounded by `{` and `}`
            
        DeclarationStatement,
        ExpressionStatement,
        SelectionStatement,
        IterationStatement,
        JumpStatement,
    };

    struct StatementBase
    {
        StatementType StatementType;
    };

    struct StatementComponent : public StatementBase
    {
        ToyUtility::List<StatementBase> Statements;
    };

    struct StatementDeclaration : public StatementBase
    {
        ToyUtility::List<StringPtr> VariableNames;
        Type Type;
        // TODOH: init value
    };

    struct StatementExp : public StatementBase
    {
        ExpressionBase* Expression;
    };

    struct StatementSelection : public StatementBase
    {
        // if statement
        ExpressionBase* Condition;
        StatementBase* ThenStatement;
        StatementBase* ElseStatement;
    };

    struct StatementIterationBase : public StatementBase
    {
        enum IterationStmtType
        {
            For,
            While,
        };

        IterationStmtType Type;
    };

    struct StatementIterationWhile
    {
        ExpressionBase* Condition;
        StatementBase*  LoopBody;
    };

    struct StatementIterationFor
    {
        StatementBase* ForInitStmt;
        ExpressionBase* Condition;
        ExpressionBase* ForEndStmt;
        StatementBase* LoopBody;
    };

    struct StatementJump : public StatementBase
    {
        enum JumpStmtType
        {
            Break,
            Continue,
            Return,
            Discard,
        };

        JumpStmtType Type;

        ExpressionBase* RetExpression; // Return statement
    };

    struct Function
    {
        Function()
            :
            FunctionImpl(nullptr)
        {}


        bool IsValid() const { return FunctionImpl != nullptr; }


        StringPtr                           Name;
        Type                                ReturnType;
        ToyUtility::List<FunctionParam>     Params;
        StatementBase*                      FunctionImpl;
    };

    enum class PragmaCmdType
    {
        __None,

        Vertex, // Vertex Shader
        Fragment, // Fragment Shader
    };

    struct Pragma
    {
        Pragma()
            :
            CmdType(PragmaCmdType::__None)
        {}

        bool IsValid() const { return CmdType != PragmaCmdType::__None; }


        PragmaCmdType CmdType;
        StringPtr FunctionName;
    };


public:
    TRLSL_IR()
    {}

	const ToyUtility::List<Struct>& GetStructs() const { return m_Structs; }
	const ToyUtility::List<UniformVariable>& GetUniformVariables() const { return m_UniformVariables; }
	const ToyUtility::List<Function>& GetFunctions() const { return m_Functions; }
	const ToyUtility::List<Pragma>& GetPragmas() const { return m_Pragmas; }

    const Struct& FindStruct(const ToyUtility::String& name) const;
    const UniformVariable& FindUniformVariable(const ToyUtility::String& name) const;
    const Function& FindFunction(const ToyUtility::String& name) const;

    const Pragma& FindPragma(PragmaCmdType pragmaType) const;

    const Struct& FindStruct(const StringPtr& strPtr) const;
    const UniformVariable& FindUniformVariable(const StringPtr& strPtr) const;
    const Function& FindFunction(const StringPtr& strPtr) const;


private:
    ToyUtility::List<Struct> m_Structs;
    ToyUtility::List<UniformVariable> m_UniformVariables;
    ToyUtility::List<Function> m_Functions;
    ToyUtility::List<Pragma> m_Pragmas;

    USE_POOL(StatementComponent)
    USE_POOL(StatementDeclaration)
    USE_POOL(StatementExp)
    USE_POOL(StatementSelection)
    USE_POOL(StatementIterationWhile)
    USE_POOL(StatementIterationFor)
    USE_POOL(StatementJump)

    USE_POOL(ExpressionCommon)
    USE_POOL(ExpressionFunctionCall)
    USE_POOL(ExpressionVariableIdentifier)
};


} // end of namespace TRL