package ru.ifmo.rain.larionov.implementor;

import info.kgeorgiy.java.advanced.implementor.Impler;
import info.kgeorgiy.java.advanced.implementor.ImplerException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Arrays;
import java.util.stream.Collectors;

public class Implementor implements Impler {

    @Override
    public void implement(Class<?> token, Path root) throws ImplerException {
        isGoshaAsshole(token, root);
        Path folderPath = root.resolve(token.getPackage() != null ?
                token.getPackage().getName().replace('.', File.separatorChar) :
                "");
        Path filePath = folderPath.resolve(token.getSimpleName() + "Impl.java");
        try {
            Files.createDirectories(folderPath);
        } catch (IOException e) {
            throw new ImplerException("Can't create output file directories: " + e.getMessage());
        }
        try (BufferedWriter writer = Files.newBufferedWriter(filePath)) {
            writer.write(generatePackage(token)); // package
            writer.write(generateTitle(token)); // public class className implements interfaceName
            writer.write(" {" + System.lineSeparator());
            for (Method method : token.getMethods()) {
                int modifiers = method.getModifiers(); // private, public, etc.
                if (Modifier.isAbstract(modifiers)) {
                    modifiers -= Modifier.ABSTRACT; // Смотрим тесты Гоши
                }
                if (Modifier.isTransient(modifiers)) {
                    modifiers -= Modifier.TRANSIENT;
                }
                writer.write(generateAnnotations(method)); // @Override
                writer.write(generateModifiers(method, modifiers)); // Long
                writer.write(generateArguments(method)); // (final String)
                writer.write(generateExceptions(method)); // throw something
                writer.write(generateInnerCode(method)); // { return something }
            }
            writer.write("}");
        } catch (IOException e) {
            throw new ImplerException(e.getMessage());
        }
    }

    private void isGoshaAsshole(Class<?> token, Path root) throws ImplerException {
        if (token == null) {
            throw new ImplerException("Not null token is required");
        } else if (root == null) {
            throw new ImplerException("Not null root is required");
        } else if (!token.isInterface()) {
            throw new ImplerException("Implementor supports only interfaces");
        }
    }

    private String generatePackage(Class<?> token) {
        String packageName = token.getPackage().getName();
        return (packageName != null ? ("package " + packageName + ";") : "") + System.lineSeparator();
    }

    private String generateTitle(Class<?> token) {
        String interfaceName = token.getSimpleName();
        String className = interfaceName + "Impl";
        int modifiers = token.getModifiers();
        if (Modifier.isAbstract(modifiers)) {
            modifiers -= Modifier.ABSTRACT;
        }
        if (Modifier.isInterface(modifiers)) {
            modifiers -= Modifier.INTERFACE;
        }
        return String.format("%s class %s implements %s", Modifier.toString(modifiers), className, interfaceName);
    }

    private String generateAnnotations(Method method) {
        return Arrays.stream(method.getAnnotations())
                .map(p -> "@" + p.annotationType().getCanonicalName())
                .collect(Collectors.joining(System.lineSeparator())) + System.lineSeparator();
    }

    private String generateModifiers(Method method, int modifiers) {
        return (System.lineSeparator() + " " + Modifier.toString(modifiers) + " " +
                method.getReturnType().getCanonicalName() + " " + method.getName());
    }

    private String generateArguments(Method method) {
        return ("(" + Arrays.stream(method.getParameters())
                .map(parameter -> parameter.getType().getCanonicalName() + " " + parameter.getName())
                .collect(Collectors.joining(", ")) + ")");
    }

    private String generateExceptions(Method method) {
        return (method.getExceptionTypes().length != 0
                ? (" throws " + Arrays.stream(method.getExceptionTypes()).map(Class::getCanonicalName).
                        collect(Collectors.joining(", ")))
                : "");
    }

    private String generateInnerCode(Method method) {
        StringBuilder innerCode = new StringBuilder(" {" + System.lineSeparator());
        if (method.getReturnType() != void.class) {
            innerCode.append(generateReturn(method));
        }
        return innerCode
                .append(System.lineSeparator())
                .append(" }")
                .append(System.lineSeparator()).toString();
    }

    private String generateReturn(Method method) {
        StringBuilder ret = new StringBuilder("return ");
        if (method.getReturnType() == boolean.class) { // значения по умолчанию, из условия

            ret.append("false");
        } else if (method.getReturnType().isPrimitive()) {
            ret.append("0");
        } else {
            ret.append("null");
        }
        return ret.append(";").toString();
    }
}