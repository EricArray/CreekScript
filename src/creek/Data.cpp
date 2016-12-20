#include <creek/Data.hpp>

#include <creek/Exception.hpp>
#include <creek/Variable.hpp>
#include <creek/Scope.hpp>


namespace creek
{
    #ifdef CREEK_INSTANCE_COUNT
        int instance_count = 0;
    #endif

    Data::Data()
    {
        #ifdef CREEK_INSTANCE_COUNT
            instance_count += 1;
            std::clong << "Data instance count: " << instance_count << "\n";
        #endif
    }

    Data::~Data()
    {
        #ifdef CREEK_INSTANCE_COUNT
            instance_count -= 1;
            std::clong << "Data instance count: " << instance_count << "\n";
        #endif
    }

    Data* Data::copy() const
    {
        throw Undefined(class_name() + "::copy");
    }

    Data* Data::clone() const
    {
        return copy();
    }

    std::string Data::class_name() const
    {
        return "Data";
    }

    std::string Data::debug_text() const
    {
        throw Undefined(class_name() + "::debug_text");
    }

    /// @brief  Get an expression to duplicate this data.
    /// By default throws an exception saying this data is not const.
    Expression* Data::to_expression() const
    {
        throw Exception("Can't get expression from non-const data");
    }


    /// @brief  Used for garbage collection.
    void Data::garbage_trace()
    {

    }


    bool Data::bool_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::bool_value");
    }

    // void Data::bool_value(bool new_value)
    // {
    //     throw Undefined(class_name() + "::bool_value");
    // }

    char Data::char_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::char_value");
    }

    int Data::int_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::int_value");
    }

    // void Data::int_value(int new_value)
    // {
    //     throw Undefined(class_name() + "::int_value");
    // }

    double Data::double_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::float_value");
    }

    // void Data::float_value(float new_value)
    // {
    //     throw Undefined(class_name() + "::float_value");
    // }

    const std::string& Data::string_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::string_value");
    }

    // void Data::string_value(const std::string& new_value)
    // {
    //     throw Undefined(class_name() + "::string_value");
    // }

    VarName Data::identifier_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::identifier_value");
    }

    const std::vector<Variable>& Data::vector_value(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::vector_value");
    }

    Data* Data::index(const SharedPointer<Scope>& scope, Data* key)
    {
        throw Undefined(class_name() + "::index get");
    }

    Data* Data::index(const SharedPointer<Scope>& scope, Data* key, Data* new_data)
    {
        throw Undefined(class_name() + "::index set");
    }


    /// @name   Object attribute
    /// @{
    /// @brief  Get the attribute.
    Data* Data::attr(const SharedPointer<Scope>& scope, VarName key)
    {
        throw Undefined(class_name() + "::attr get");
    }

    /// @brief  Set the attribute.
    Data* Data::attr(const SharedPointer<Scope>& scope, VarName key, Data* new_data)
    {
        throw Undefined(class_name() + "::attr set");
    }
    /// @}


    Data* Data::add(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::add");
    }

    Data* Data::sub(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::sub");
    }

    Data* Data::mul(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::mul");
    }

    Data* Data::div(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::div");
    }

    Data* Data::mod(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::mod");
    }

    Data* Data::exp(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::exp");
    }

    Data* Data::unm(const SharedPointer<Scope>& scope)
    {
        throw Undefined(class_name() + "::unm");
    }

    Data* Data::bit_and(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::bit_and");
    }

    Data* Data::bit_or(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::bit_or");
    }

    Data* Data::bit_xor(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::bit_xor");
    }

    Data* Data::bit_not(const SharedPointer<Scope>& scope)
    {
        throw Undefined(class_name() + "::bit_not");
    }

    Data* Data::bit_left_shift(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::bit_left_shift");
    }

    Data* Data::bit_right_shift(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::bit_right_shift");
    }

    int Data::cmp(const SharedPointer<Scope>& scope, Data* other)
    {
        throw Undefined(class_name() + "::cmp");
    }

    Data* Data::call(const SharedPointer<Scope>& scope, std::vector< std::unique_ptr<Data> >& args)
    {
        throw Undefined(class_name() + "::call");
    }

    Data* Data::get_class(const SharedPointer<Scope>& scope) const
    {
        throw Undefined(class_name() + "::get_class");
    }


    /// @brief  Call a method of this object's class.
    /// @param  method_name Name of the method to call.
    /// @param  args        Arguments.
    /// Self will be added as first argument.
    Data* Data::call_method(
        const SharedPointer<Scope>& scope,
        VarName method_name,
        const std::vector<Data*>& args
    ) const {
        std::vector< std::unique_ptr<Data> > up_args;
        up_args.emplace_back(copy());
        for (auto& arg : args)
        {
            up_args.emplace_back(arg);
        }

        Variable class_obj = get_class(scope);
        if (!class_obj)
        {
            throw Exception("This object has no class");
        }
        Variable method = class_obj->attr(scope, method_name);
        return method->call(scope, up_args);
    }


    // `WrongArgNumber` constructor.
    // @param  expected    Number of expected arguments.
    // @param  passed      Number of passed arguments.
    WrongArgNumber::WrongArgNumber(int expected, int passed) :
        m_expected(expected),
        m_passed(passed)
    {
        stream() << "Wrong number of arguments: expected " << expected << ", passed " << passed;
    }
}
