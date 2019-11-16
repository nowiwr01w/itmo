(defn common-op [type? op]
  (fn [& vs]
    (apply mapv op vs)))

(def v+ (common-op vector? +))
(def v- (common-op vector? -))
(def v* (common-op vector? *))

(defn matrix? [m]
  (and (vector? m) (every? vector? m)))

(def m+ (common-op matrix? v+))
(def m- (common-op matrix? v-))
(def m* (common-op matrix? v*))

(defn scalar [a, b]
  (apply + (v* a b)))

(defn vect [a b]
  [(- (* (nth a 1) (nth b 2)) (* (nth a 2) (nth b 1)))
   (- (* (nth a 2) (nth b 0)) (* (nth a 0) (nth b 2)))
   (- (* (nth a 0) (nth b 1)) (* (nth a 1) (nth b 0)))
   ])

(defn v*s [a, b]
  (mapv (fn [n] (* n b)) a))

(defn m*s [a, b]
  (mapv
    (fn [n]
      (v*s n b)) a))

(defn m*v [a b]
  (mapv
    (fn [n]
      (scalar n b)) a))

(defn transpose [m]
  (apply mapv vector m))

(defn m*m [a b] (mapv (fn [n] (mapv (fn [m] (scalar n m)) (transpose b))) a))

(defn common-deep-op [op]
  (fn calc [a b]
    (if (vector? a)
      (mapv calc a b)
      (op a b))))

;Shapeless
(def s+
  (common-deep-op +))
(def s-
  (common-deep-op -))
(def s*
  (common-deep-op *))