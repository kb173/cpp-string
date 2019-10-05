#include "String.h"


String::String(const char *_text) : length(strlen(_text)), text(new char[strlen(_text) + 1]) {
    memcpy((void *) text, _text, length + sizeof(char));
}

String::~String() {
    delete[] text;
}

void String::concatenate(String other) {
    concatenate(other.c_str());
}

void String::concatenate(const char *other) {
    size_t new_string_length = strlen(other);
    char *new_string = new char[length + new_string_length + sizeof(char)];

    memcpy(new_string, text, length);
    memcpy(new_string + length, other, new_string_length);

    delete[] text;

    text = new_string;
    length += new_string_length;
}

const char *String::c_str() const {
    return text;
}

size_t String::getLength() const {
    return length;
}
