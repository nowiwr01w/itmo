(defn evaluate [expression, applyMap] ((.evaluate expression) applyMap))
(defn toString [expression] (.toStr expression))
(defn diff [expression, diffVarName] ((.diff expression) diffVarName))
 
(definterface BaseInterface
  (evaluate [])
  (toStr [])
  (diff []))
 
(declare ZERO)
(declare ONE)
(declare TWO)
 
(deftype Const [value]
  BaseInterface
  (evaluate [this] (fn [applyMap] value))
  (toStr [this] (format "%.1f" (double value)))
  (diff [this] (fn [diffVarName] ZERO)))
 
(defn Constant [value] (Const. value))
 
(def ZERO (Constant 0))
(def ONE (Constant 1))
(def TWO (Constant 2))
 
(deftype Var [varName]
  BaseInterface
  (evaluate [this] (fn [applyMap] (applyMap varName)))
  (toStr [this] (str varName))
  (diff [this] #(if (= % varName) ONE ZERO)))
 
(defn Variable [varName] (Var. varName))
 
(deftype newOperator [evalFun, opName, args, diffFun]
  BaseInterface
  (evaluate [this] #(apply evalFun (map (fn [x] (evaluate x %)) args)))
  (toStr [this] (str "(" opName " " (clojure.string/join " " (map toString args)) ")"))
  (diff [this] #(apply diffFun (concat args (map (fn [x] (diff x %)) args)))))
 
(defn Add [& args] (newOperator. +, "+", args,
                                 (fn [a b da db] (Add da db))))
 
(defn Subtract [& args] (newOperator. -, "-", args,
                                      (fn [a b da db] (Subtract da db))))
 
(defn Multiply [& args] (newOperator. *, "*", args,
                                      (fn [a b da db] (Add
                                                        (Multiply da b)
                                                        (Multiply a db)))))
 
(defn Divide [& args] (newOperator. #(/ %1 (double %2)), "/", args,
                                    (fn [a b da db] (Divide
                                                      (Subtract
                                                        (Multiply da b)
                                                        (Multiply a db))
                                                      (Multiply b b)))))
 
 
(defn Negate [& arg] (newOperator. -, "negate", arg,
                                   (fn [a da] (Negate da))))
 
(declare Sinh)
(declare Cosh)
 
(defn Sinh [& arg] (newOperator. #(Math/sinh %), "sinh", arg,
                                 (fn [a da] (Multiply da (Cosh a)))))
 
(defn Cosh [& arg] (newOperator. #(Math/cosh %), "cosh", arg,
                                 (fn [a da] (Multiply da (Sinh a)))))
 
(def operations {'+      Add,
                 '-      Subtract,
                 '*      Multiply,
                 '/      Divide,
                 'negate Negate,
                 'sinh   Sinh,
                 'cosh   Cosh
                 })
 
(defn parse [expression]
  (cond
    (number? expression) (Constant expression)
    (symbol? expression) (Variable (str expression))
    (list? expression) (apply (operations (first expression)) (map parse (rest expression)))
    ))
 
(defn parseObject [s] (parse (read-string s)))