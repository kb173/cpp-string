#include <iostream>
#include <cstring>

class String {
public:
    /// Create a new empty String
    String();

    /// Create a new String out of a char array.
    /// The given character array must be \0-terminated.
    explicit String(const char *stringText);

    /// Copy constructor
    String(const String &other);

    /// Copy assignment operator
    String &operator=(const String &other);

    /// Move constructor
    String(String &&other);

    /// Move assignment operator
    String &operator=(String &&other);

    /// += operators for concatenate
    /// Used in the + operator as well (defined outside the class)
    String &operator+=(const String &other);
    String &operator+=(const char *other);

    /// Conversion to char pointer
    operator const char *() const;

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

String::String() : String("") {}

String::String(const char *stringText) : length(strlen(stringText)), text(new char[length + sizeof(char)]) {
    memcpy(text, stringText, length + sizeof(char));
}

String::String(const String &other) : length(other.getLength()), text(new char[length + sizeof(char)]) {
    memcpy(text, other.c_str(), length + sizeof(char));
}

String &String::operator=(const String &other) {
    // TODO: We could also check whether the other string has the same capacity as this one, and if so, reuse the
    //  current char array. However, this would introduce another check which might cost more performance than it
    //  gains (since the length will rarely be the same)
    if (this != &other) {
        length = other.length;

        // Delete old text and create new
        delete[] text;

        text = new char[length + sizeof(char)];

        // Copy text
        memcpy(text, other.c_str(), length + sizeof(char));
    }

    return *this;
}

String::String(String &&other) : length(other.length), text(other.text) {
    other.text = nullptr;
    other.length = 0;
}

String &String::operator=(String &&other) {
    if (this != &other) {
        delete[] text;

        text = other.text;
        length = other.length;

        other.text = nullptr;
        other.length = 0;
    }

    return *this;
}

String &String::operator+=(const String &other) {
    concatenate(other);
    return *this;
}

String &String::operator+=(const char *other) {
    concatenate(other);
    return *this;
}

String operator+(String left, const String &right) {
    left += right;
    return left;
}

String operator+(String left, const char *right) {
    left += right;
    return left;
}

// TODO: Should cases like `"Hello" + String("World")` be handled?
//  I think not; it would be up to `const char *` to handle that, since getting a String after adding something
//  to a `const char *` is strange. It could look like this however:
//String operator+(const char *left, const String &right) {
//    String left_string = String(left);
//    left_string += right;
//    return left_string;
//}

String::operator const char *() const {
    return this->c_str();
}

String::~String() {
    delete[] text;
}

void String::concatenate(const String &other) {
    concatenate(other.c_str());
}

void String::concatenate(const char *other) {
    // Allocate the new text
    size_t newStringLength = strlen(other);
    char *newString = new char[length + newStringLength + sizeof(char)];

    // Copy current string, and other string after it
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

    String added = testString + String(" again!");

    std::cout << "Test output: |" << added << "|" << std::endl;
    std::cout << "Length: " << added.getLength() << std::endl;

    added += "+1";

    std::cout << "Test output: |" << added << "|" << std::endl;
    std::cout << "Length: " << added.getLength() << std::endl;

    added += String("+2");

    std::cout << "Test output: |" << added << "|" << std::endl;
    std::cout << "Length: " << added.getLength() << std::endl;

    const String addedConst = added + "+3";

    std::cout << "Test output: |" << addedConst << "|" << std::endl;
    std::cout << "Length: " << addedConst.getLength() << std::endl;

    const String total = added + addedConst;

    std::cout << "Test output: |" << total << "|" << std::endl;
    std::cout << "Length: " << total.getLength() << std::endl;

    return 0;
}