package ru.ifmo.validate;

public interface Validator {
    void validate(ValidatingScanner in) throws Exception;
}
