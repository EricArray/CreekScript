# Creek Script
Scripting language for application extension.

## Features:
* Expression based syntax
* Duck typing
* Lambda functions
* Classes
* Dynamic libraries

## C++ interface:
* Template C++ function to create intefaces

## Example script:
```
/// Represents a person.
class Person {
    /// Instance initializer.
    func init(self, name, gender) {
        self::name = name; // set attribute `name`
        self::gender = gender; // set attribute `gender`
    }
    /// Print a greeting to this person.
    func greet(self) {
        print("Hello, "+self::name+"!", "\n");
    }
}
// an array of persons
var persons = [
    Person("Francisca", "F"),
    Person("Silvestre", "M"),
    Person("Diana",     "F"),
];
for person in persons {
    person.greet(); // call method `greet` of person's class
    // if-block as an expression
    print("Gender: " + if person::gender=="F" {"female"} else {"male"} + "\n");
}
```
