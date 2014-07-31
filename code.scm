(define (A x y)
	(cond ((= y 0) 0)
		  ((= x 0) (* 2 y))
		  ((= y 1) 2)
		  (else (A (- x 1)
				   (A x (- y 1))))))
(A 1 10)
(A 2 4)
(A 3 3)

(define (count-change amount)
	(cc amount 5))
	
(define (cc amount kinds-of-coins)
	(cond ((= amount 0) 1)
		  ((or (< amount 0) (= kinds-of-coins 0)) 0)
		  (else (+ (cc amount
					   (- kinds-of-coins 1))
				   (cc (- amount
					      (first-denomination kinds-of-coins))
					   kinds-of-coins)))))
					   
(define (first-denomination kinds-of-coins)
	(cond ((= kinds-of-coins 1) 1)
		  ((= kinds-of-coins 2) 5)
		  ((= kinds-of-coins 3) 10)
		  ((= kinds-of-coins 4) 25)
		  ((= kinds-of-coins 5) 50)))
		  
(count-change 10)

(define (f g)
  (g 2))
(define (square x) (* x x))
(f square)
(f (lambda (z) (* z (+ z 1))))

(define x (list 1 2 3))
(define y (list 4 5 6))
(append x y)
(cons x y)
(list x y)