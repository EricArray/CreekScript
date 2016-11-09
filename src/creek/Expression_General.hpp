#pragma once

#include <creek/Expression.hpp>

#include <memory>
#include <vector>

#include <creek/api_mode.hpp>
#include <creek/Data.hpp>
#include <creek/Variable.hpp>


namespace creek
{
    /// @defgroup   expression_general  General expressions.
    /// @{

    /// @brief  Expression: Copy a constant.
    class CREEK_API ExprConst : public Expression
    {
    public:
        /// @brief  `ExprConst` constructor.
        /// @param  data    Constant data to be copied.
        ExprConst(Data* data);

        Expression* clone() const override;
        bool is_const() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Data> m_data;
    };


    /// @brief  Unary operation of an expression.
    /// @param  op_code     Operation code.
    /// @param  method      Data method to call.
    /// Returns the result of calling `method` of `expr`.
    template<OpCode op_code, Data*(Data::*method)()>
    class CREEK_API ExprUnary : public Expression
    {
    public:
        /// @brief  `ExprUnary` constructor.
        /// @param  expr    Expression for parameter.
        ExprUnary(Expression* expr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_expr;
    };


    /// @brief  Binary operation of expressions.
    /// @param  op_code     Operation code.
    /// @param  method      Data method to call.
    /// Returns the result of calling `method` of `lexpr` with `rexpr`.
    template<OpCode op_code, Data*(Data::*method)(Data*)>
    class CREEK_API ExprBinary : public Expression
    {
    public:
        /// @brief  `ExprBinary` constructor.
        /// @param  lexpr       Expression for left parameter.
        /// @param  rexpr       Expression for right parameter.
        ExprBinary(Expression* lexpr, Expression* rexpr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_lexpr;
        std::unique_ptr<Expression> m_rexpr;
    };


    /// @brief  Expression: Call a function.
    /// Returns value returned by the function.
    class CREEK_API ExprCall : public Expression
    {
    public:
        /// @brief  `ExprCall` constructor.
        /// @param  function    Function expression.
        /// @param  args        Arguments to pass to the function.
        ExprCall(Expression* function, const std::vector<Expression*>& args);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_function;
        std::vector< std::unique_ptr<Expression> > m_args;
    };


    /// @brief  Expression: Call a function with a variadic argument.
    /// Returns value returned by the function.
    class CREEK_API ExprVariadicCall : public Expression
    {
    public:
        /// @brief  `ExprVariadicCall` constructor.
        /// @param  function    Function expression.
        /// @param  args        Arguments to pass to the function.
        /// @param  vararg      Argument to expand before calling.
        ExprVariadicCall(Expression* function, const std::vector<Expression*>& args, Expression* vararg);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_function;
        std::vector< std::unique_ptr<Expression> > m_args;
        std::unique_ptr<Expression> m_vararg;
    };

    /// @brief  Expression: Call a method.
    /// Returns value returned by the function.
    class CREEK_API ExprCallMethod : public Expression
    {
    public:
        /// @brief  `ExprCallMethod` constructor.
        /// @param  object      Object expression.
        /// @param  index       Index to the method.
        /// @param  args        Arguments to pass to the method.
        ExprCallMethod(Expression* object, Expression* index, const std::vector<Expression*>& args);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_object;
        std::unique_ptr<Expression> m_index;
        std::vector< std::unique_ptr<Expression> > m_args;
    };


    /// @brief  Expression: Call a method with a variadic argument.
    /// Returns value returned by the function.
    class CREEK_API ExprVariadicCallMethod : public Expression
    {
    public:
        /// @brief  `ExprVariadicCallMethod` constructor.
        /// @param  object      Object expression.
        /// @param  index       Index to the method.
        /// @param  args        Arguments to pass to the method.
        /// @param  vararg      Argument to expand before calling.
        ExprVariadicCallMethod(Expression* object, Expression* index, const std::vector<Expression*>& args, Expression* vararg);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_object;
        std::unique_ptr<Expression> m_index;
        std::vector< std::unique_ptr<Expression> > m_args;
        std::unique_ptr<Expression> m_vararg;
    };


    /// @brief  Expression: Get array subscript.
    /// Returns value of the array at the index.
    class CREEK_API ExprIndexGet : public Expression
    {
    public:
        /// @brief  `ExprIndexGet` constructor.
        /// @param  array   Expression for the array object.
        /// @param  index   Expression for the index.
        ExprIndexGet(Expression* array, Expression* index);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_array;
        std::unique_ptr<Expression> m_index;
    };


    /// @brief  Expression: Set array subscript.
    /// Returns new value of the array at the index.
    class CREEK_API ExprIndexSet : public Expression
    {
    public:
        /// @brief  `ExprIndexSet` constructor.
        /// @param  array       Expression for the array object.
        /// @param  index       Expression for the index.
        /// @param  value       Expression for the new value.
        ExprIndexSet(Expression* array, Expression* index, Expression* value);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_array;
        std::unique_ptr<Expression> m_index;
        std::unique_ptr<Expression> m_value;
    };


    /// @brief  Expression: Get object attribute.
    /// Returns value of the attribute in the object.
    class CREEK_API ExprAttrGet : public Expression
    {
    public:
        /// @brief  `ExprAttrGet` constructor.
        /// @param  object  Expression for the object.
        /// @param  attr    Attribute name.
        ExprAttrGet(Expression* object, VarName attr);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_object;
        VarName m_attr;
    };


    /// @brief  Expression: Set object attribute.
    /// Returns value of the attribute in the object.
    class CREEK_API ExprAttrSet : public Expression
    {
    public:
        /// @brief  `ExprAttrSet` constructor.
        /// @param  object  Expression for the object.
        /// @param  attr    Attribute name.
        /// @param  value   Expression for the new value.
        ExprAttrSet(Expression* object, VarName attr, Expression* value);

        Expression* clone() const override;
        bool is_const() const override;
        Expression* const_optimize() const override;

        Variable eval(Scope& scope) override;
        Bytecode bytecode(VarNameMap& var_name_map) const override;

    private:
        std::unique_ptr<Expression> m_object;
        VarName m_attr;
        std::unique_ptr<Expression> m_value;
    };

    /// @}
}


// template implementation
#include <creek/Scope.hpp>

namespace creek
{
    template<OpCode op_code, Data*(Data::*method)()>
    ExprUnary<op_code, method>::ExprUnary(Expression* expr) :
        m_expr(expr)
    {

    }

    template<OpCode op_code, Data*(Data::*method)()>
    Expression* ExprUnary<op_code, method>::clone() const
    {
        return new ExprUnary<op_code, method>(m_expr->clone());
    }

    template<OpCode op_code, Data*(Data::*method)()>
    Variable ExprUnary<op_code, method>::eval(Scope& scope)
    {
        Variable v = m_expr->eval(scope);
        Data* d = ((*v)->*method)();
        return Variable(d);
    }

    template<OpCode op_code, Data*(Data::*method)()>
    bool ExprUnary<op_code, method>::is_const() const
    {
        return m_expr->is_const();
    }

    template<OpCode op_code, Data*(Data::*method)()>
    Expression* ExprUnary<op_code, method>::const_optimize() const
    {
        if (is_const())
        {
            Scope scope;
            Variable v = m_expr->eval(scope);
            Data* d = ((*v)->*method)();
            return new ExprConst(d);
        }
        else
        {
            return new ExprUnary(m_expr->const_optimize());
        }
    }

    template<OpCode op_code, Data*(Data::*method)()>
    Bytecode ExprUnary<op_code, method>::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(op_code) << m_expr->bytecode(var_name_map);
    }



    template<OpCode op_code, Data*(Data::*method)(Data*)>
    ExprBinary<op_code, method>::ExprBinary(Expression* lexpr, Expression* rexpr) :
        m_lexpr(lexpr),
        m_rexpr(rexpr)
    {

    }

    template<OpCode op_code, Data*(Data::*method)(Data*)>
    Expression* ExprBinary<op_code, method>::clone() const
    {
        return new ExprBinary<op_code, method>(m_lexpr->clone(), m_rexpr->clone());
    }

    template<OpCode op_code, Data*(Data::*method)(Data*)>
    Variable ExprBinary<op_code, method>::eval(Scope& scope)
    {
        Variable l = m_lexpr->eval(scope);
        Variable r = m_rexpr->eval(scope);
        Data* d = ((*l)->*method)(*r);
        return Variable(d);
    }

    template<OpCode op_code, Data*(Data::*method)(Data*)>
    bool ExprBinary<op_code, method>::is_const() const
    {
        return m_lexpr->is_const() && m_rexpr->is_const();
    }

    template<OpCode op_code, Data*(Data::*method)(Data*)>
    Expression* ExprBinary<op_code, method>::const_optimize() const
    {
        if (is_const())
        {
            Scope scope;
            Variable l = m_lexpr->eval(scope);
            Variable r = m_rexpr->eval(scope);
            Data* d = ((*l)->*method)(*r);
            return new ExprConst(d);
        }
        else
        {
            return new ExprBinary(m_lexpr->const_optimize(), m_rexpr->const_optimize());
        }
    }

    template<OpCode op_code, Data*(Data::*method)(Data*)>
    Bytecode ExprBinary<op_code, method>::bytecode(VarNameMap& var_name_map) const
    {
        return Bytecode() << static_cast<uint8_t>(op_code) << m_lexpr->bytecode(var_name_map) << m_rexpr->bytecode(var_name_map);
    }
}
