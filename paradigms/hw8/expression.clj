(defn constant [value] (constantly value))
(defn variable [varName] (fn [values] (values varName)))
(defn operation [opName] (fn [& args] (fn [vars] (apply opName (map #(% vars) args)))))

(defn div [a b] (/ (double a) b))
(defn minimum [& args] (reduce (fn [a, b] (Math/min a b)) (first args) (rest args)))
(defn maximum [& args] (reduce (fn [a, b] (Math/max a b)) (first args) (rest args)))

(def add (operation +))
(def subtract (operation -))
(def multiply (operation *))
(def divide (operation div))
(def negate (operation -))
(def min (operation minimum))
(def max (operation maximum))
(def square (operation (fn [arg] (* arg arg))))
(def sqrt (operation (fn [arg] (Math/sqrt (Math/abs arg)))))
(def avg (operation (fn [& args] (/ (apply + args) (count args)))))
(def med (operation (fn [& arg] (nth (sort arg) (int (/ (count arg) 2))))))

(def operations {'+      add,
                 '-      subtract,
                 '*      multiply,
                 '/      divide,
                 'negate negate,
                 'min    min,
                 'max    max,
                 'square square,
                 'sqrt   sqrt,
                 'med    med,
                 'avg    avg
                 })

(defn parse [expression]
  (cond
    (number? expression) (constant expression)
    (symbol? expression) (variable (str expression))
    (list? expression) (apply (operations (first expression)) (map parse (rest expression)))))

(defn parseFunction [expression] (parse (read-string expression)))