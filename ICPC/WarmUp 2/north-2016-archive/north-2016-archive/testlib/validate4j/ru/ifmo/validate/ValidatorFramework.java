package ru.ifmo.validate;

public class ValidatorFramework {
    public static void main(String[] args) throws Exception {
        Class<?> validateClass = Class.forName("Validate");
        Validator validator = (Validator) validateClass.newInstance();
        validator.validate(new ValidatingScanner(System.in));
    }
}
