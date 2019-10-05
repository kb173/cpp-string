#ifndef STRING_STRING_H
#define STRING_STRING_H


#include <cstring>

class String {
public:
    explicit String(const char *_text);

    ~String();

    /// Append a String at the end of this String.
    void concatenate(String other);

    /// Append characters at the end of this String.
    void concatenate(const char *other);

    /// Returns the internal char array representation of this String.
    /// Note that calling concatenate() on the String invalidates this returned pointer.
    const char* c_str() const;

    /// Returns the length of the String (without the terminator).
    size_t getLength() const;

private:
    char* text;

    size_t length;
};


#endif //STRING_STRING_H
