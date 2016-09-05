#include <string>


namespace creek
{
    class Variable;


    /// Base class for variables' data.
    class Data
    {
    public:
        virtual ~Data() = default;

        
        /// Get data class name.
        virtual std::string class_name();


        /// Get debug text.
        virtual std::string debug_text();

        /// Get the bool value of this data.
        virtual bool bool_value();

        /// Set the bool value of this data.
        virtual void bool_value(bool new_value);

        /// Get the float value of this data.
        virtual float float_value();

        /// Set the float value of this data.
        virtual void float_value(float new_value);

        /// Get the string value of this data.
        virtual std::string string_value();

        /// Set the string value of this data.
        virtual void string_value(const std::string& new_value);


        /// Get the data at index.
        virtual Data* index(Data* key);

        /// Set the data at index.
        virtual void index(Data* key, Data* new_data);


        /// Binary operation: addition.
        virtual Data* add(Data* other);

        /// Binary operation: subtraction.
        virtual Data* sub(Data* other);

        /// Binary operation: multiplication.
        virtual Data* mul(Data* other);

        /// Binary operation: divison.
        virtual Data* div(Data* other);

        /// Binary operation: modulo.
        virtual Data* mod(Data* other);

        /// Binary operation: exponentiation.
        virtual Data* exp(Data* other);

        /// Unary operation: minus.
        virtual Data* min();

        /// Binary operation: bitwise and.
        virtual Data* bit_and(Data* other);

        /// Binary operation: bitwise or.
        virtual Data* bit_or(Data* other);

        /// Binary operation: bitwise xor.
        virtual Data* bit_xor(Data* other);

        /// Unary operation: bitwise not.
        virtual Data* bit_not();
    };
}