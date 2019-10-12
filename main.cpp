#include <iostream>
#include <cstring>

class String {
public:
    /// Create a new empty String
    String();

    /// Create a new String out of a char array.
    /// The given character array must be \0-terminated.
    explicit String(const char *stringText);

    ~String();

    /// Append a String at the end of this String.
    void concatenate(const String &other);

    /// Append characters at the end of this String.
    /// The given character array must be \0-terminated.
    void concatenate(const char *other);

    /// Return the internal char array representation of this String.
    /// Note that calling concatenate() on the String invalidates this returned pointer.
    const char *c_str() const;

    /// Return the length of the String (without the terminator).
    size_t getLength() const;

private:
    size_t length;

    char *text;
};

String::String() : String("") {};

String::String(const char *stringText) : length(strlen(stringText)), text(new char[length + sizeof(char)]) {
    memcpy((void *) text, stringText, length + sizeof(char));
}

String::~String() {
    delete[] text;
}

void String::concatenate(const String &other) {
    concatenate(other.c_str());
}

void String::concatenate(const char *other) {
    size_t newStringLength = strlen(other);
    char *newString = new char[length + newStringLength + sizeof(char)];

    memcpy(newString, text, length);
    memcpy(newString + length, other, newStringLength + sizeof(char));

    delete[] text;

    text = newString;
    length += newStringLength;
}

const char *String::c_str() const {
    return text;
}

size_t String::getLength() const {
    return length;
}

int main() {
    String testString("Hello World!");

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    testString.concatenate("+1");

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    testString.concatenate(String(" Test "));

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    testString.concatenate(testString);

    std::cout << "Test output: |" << testString.c_str() << "|" << std::endl;
    std::cout << "Length: " << testString.getLength() << std::endl;

    String testString2;

    testString2.concatenate(testString);

    std::cout << testString2.c_str() << std::endl;

    return 0;
}