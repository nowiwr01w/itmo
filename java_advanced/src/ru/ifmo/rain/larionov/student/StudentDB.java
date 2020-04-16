package ru.ifmo.rain.larionov.student;

import info.kgeorgiy.java.advanced.student.Student;
import info.kgeorgiy.java.advanced.student.StudentQuery;

import java.util.*;
import java.util.function.BinaryOperator;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;


public class StudentDB implements StudentQuery {

    private final Comparator<Student> mComparator =
            Comparator.comparing(Student::getLastName).thenComparing(Student::getFirstName).thenComparingInt(Student::getId);

    private List<String> mappedStudents(List<Student> students, Function<Student, String> map) {
        return students.stream().map(map).collect(Collectors.toList());
    }

    private List<Student> sortedStudents(Collection<Student> students, Comparator<Student> comparator) {
        return students.stream().sorted(comparator).collect(Collectors.toList());
    }

    private List<Student> filteredStudents(Collection<Student> students, Comparator<Student> comparator, Predicate<Student> predicate) {
        return students.stream().filter(predicate).sorted(comparator).collect(Collectors.toList());
    }

    @Override
    public List<String> getFirstNames(List<Student> list) {
        return mappedStudents(list, Student::getFirstName);
    }

    @Override
    public List<String> getLastNames(List<Student> list) {
        return mappedStudents(list, Student::getLastName);
    }

    @Override
    public List<String> getGroups(List<Student> list) {
        return mappedStudents(list, Student::getGroup);
    }

    @Override
    public List<String> getFullNames(List<Student> list) {
        return mappedStudents(list, student -> String.format("%s %s", student.getFirstName(), student.getLastName()));
    }

    @Override
    public Set<String> getDistinctFirstNames(List<Student> list) {
        return new TreeSet<>(getFirstNames(list));
    }

    @Override
    public String getMinStudentFirstName(List<Student> list) {
        return list.stream().min(Student::compareTo).map(Student::getFirstName).orElse("");
    }

    @Override
    public List<Student> sortStudentsById(Collection<Student> collection) {
        return sortedStudents(collection, Student::compareTo);
    }

    @Override
    public List<Student> sortStudentsByName(Collection<Student> collection) {
        return sortedStudents(collection, mComparator);
    }

    @Override
    public List<Student> findStudentsByFirstName(Collection<Student> collection, String firstName) {
        return filteredStudents(collection, mComparator, student -> student.getFirstName().equals(firstName));
    }

    @Override
    public List<Student> findStudentsByLastName(Collection<Student> collection, String lastName) {
        return filteredStudents(collection, mComparator, student -> student.getLastName().equals(lastName));
    }

    @Override
    public List<Student> findStudentsByGroup(Collection<Student> collection, String group) {
        return filteredStudents(collection, mComparator, student -> student.getGroup().equals(group));
    }

    @Override
    public Map<String, String> findStudentNamesByGroup(Collection<Student> collection, String group) {
        return collection
                .stream()
                .filter(student -> student.getGroup().equals(group))
                .collect(Collectors.toMap(Student::getLastName, Student::getFirstName, BinaryOperator.minBy(String::compareTo)));
    }
}