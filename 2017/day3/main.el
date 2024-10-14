(defun manhattan-distance (n)
  "Calculate the Manhattan distance from square N to square 1 in the spiral grid."
  (if (= n 1)
      0
    (let* ((ring (ceiling (/ (- (sqrt n) 1) 2)))
           (max-value-in-ring (expt (+ (* 2 ring) 1) 2))
           (side-length (* 2 ring))
           (min-value-in-ring (- max-value-in-ring (* 4 side-length)))
           (position (- n min-value-in-ring))
           (offset (mod position side-length))
           (distance (+ ring (abs (- offset ring)))))
      distance)))

(manhattan-distance 12)
(manhattan-distance 23)
(manhattan-distance 1024)
(message "part1")
(message "%d" (manhattan-distance 277678))

(defun get-neighbors (grid x y)
  "Return the sum of all neighbor values around position (X, Y) in the GRID."
  (let ((sum 0))
    (dolist (dx '(-1 0 1))
      (dolist (dy '(-1 0 1))
        (unless (and (= dx 0) (= dy 0))
          (let ((nx (+ x dx))
                (ny (+ y dy)))
            (setq sum (+ sum (or (gethash (cons nx ny) grid) 0)))))))
    sum))

(defun stress-test (input)
  "Perform a stress test and return the first value larger than INPUT."
  (let ((grid (make-hash-table :test 'equal))
        (x 0)
        (y 0)
        (dx 1)
        (dy 0)
        (layer 1)
        (value 1))
    (puthash (cons 0 0) 1 grid)
    (catch 'result
      (while t
        (setq x (+ x dx)
              y (+ y dy)
              value (get-neighbors grid x y))
        (puthash (cons x y) value grid)
        (when (> value input)
          (throw 'result value))
        ;; Update direction based on the spiral pattern
        (cond
         ((and (= dx 1) (= x layer)) (setq dx 0 dy 1))
         ((and (= dy 1) (= y layer)) (setq dx -1 dy 0))
         ((and (= dx -1) (= x (- layer))) (setq dx 0 dy -1))
         ((and (= dy -1) (= y (- layer))) (setq dx 1 dy 0 layer (+ layer 1))))))))

(message "part2")

(message "%d" (stress-test 277678))
	 
