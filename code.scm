(map + '(1 2 3) '(4 5 6))
(map cadr '((a b) (d e) (g h)))
(map (lambda (n) (* n n)) '(1 2 3 4))

'"abc"

(sqrt 4)
(sqrt 6)
(sqrt 2)
(sqrt -1)
(sqrt 0+2i)
(sqrt 0-2i)
(sqrt 3+3i)
(sqrt 3-4i)
(sqrt 3.0-4.0i)

(apply + (_map sqrt `(3 4 5 6 10 324 235 1+1i 2+2i 3+3i 0+2i -4)))

(apply (if (= 0 0) + *) `(1 4 5))
(apply (if (= 0 1) + *) `(1 4 5))
(apply + (list 3 4))
(define compose
	(lambda (f g)
		(lambda args
			(f (apply g args)))))
((compose sqrt *) 12 75)

(define new-withdraw
	(let ((balance 100))
	   (lambda (amount)
		  (if (>= balance amount)
		      (begin (set! balance (- balance amount))
			         balance)
			  "Insufficient funds"))))

(define (make-withdraw balance)
	(lambda (amount)
		(if (>= balance amount)
			(begin (set! balance (- balance amount))
			       balance)
			"Insufficient funds")))
			
(define W1 (make-withdraw 100))
(define W2 (make-withdraw 100))

(W1 50)
(W2 70)
(W2 40)
(W1 40)

(define (make-account balance)
	(define (withdraw amount)
		(if (>= balance amount)
			(begin (set! balance (- balance amount))
				   balance)
			"Insufficient funds"))
	(define (deposit amount)
		(set! balance (+ balance amount))
		balance)
	(define (dispatch m)
		(cond ((eq? m 'withdraw) withdraw)
			  ((eq? m 'deposit) deposit)
			  ))
	dispatch)
		
(define acc (make-account 100))
((acc 'withdraw) 50)
((acc 'withdraw) 60)
((acc 'deposit) 40)
((acc 'withdraw) 60)

(_map car `((11 22) (-1 #e#x-12)))
(_map cadr `((11 22) (-1 #e#x-12)))
(_map cdr `((11 22) (-1 #e#x-12)))
(_map + '())
(_map + `(1 2))

(let ((count 0))
	(map (lambda (ignored)
	(set! count (+ count 1))
	count)
	'(a b)))
	
(+ 3 4)
((if #f + *) 3 4)
(lambda (x) (+ x x))
((lambda (x) (+ x x)) 4)
(define reverse-subtract
(lambda (x y) (- y x)))
(reverse-subtract 7 10)
(define add4
(let ((x 4))
(lambda (y) (+ x y))))
(add4 6)

((lambda x x) 3 4 5 6)
((lambda (x y . z) z)
3 4 5 6)

(if (> 3 2) 'yes 'no)
(if (> 2 3) 'yes 'no)
(if (> 3 2)
(- 3 2)

(+ 3 2))

(cond ((> 3 2) 'greater)
((< 3 2) 'less)) 
(cond ((> 3 3) 'greater)
((< 3 3) 'less)
(else 'equal)) 

(define e '((a 1) (b 2) (c 3)))
(assq 'a e)
(assq 'b e)
(assq 'd e)
(assq (list 'a) '(((a)) ((b)) ((c))))
(assoc (list 'a) '(((a)) ((b)) ((c))))
(assq 5 '((2 3) (5 7) (11 13)))
(assv 5 '((2 3) (5 7) (11 13)))

(append '(a b) '(c . d))
(append '() 'a)
(append '(x) '(y))
(append '(a) '(b c d))
(append '(a (b)) '((c)))

(list-tail (reverse '(a b c)) 1)
(reverse '(a (b c) d (e (f))))

(list-ref '(a b c d) 2)

(complex? 3+4i)
(complex? 3)
(real? 3)
(real? -2.5+0.0i)
(real? #e1e10)
(rational? 6/10)
(rational? 6/3)
(integer? 3+0i)
(integer? 3.0)
(integer? 8/4)

(abs -7)
(abs 7)
(abs -0.5)
(abs -2+0i)

(not (list 3))
(length '(a b c))
(length '(a (b) (c d e)))
(length '())

(memq 'a '(a b c)) 
(memq 'b '(a b c)) 
(memq 'a '(b c d))
(memq (list 'a) '(b (a) c)) 
(member (list 'a)
'(b (a) c))
(memq 101 '(100 101 102))
(memv 101 '(100 101 102))

(symbol? 'foo)
(symbol? (car '(a b)))
(symbol? "bar")
(symbol? 'nil)
(symbol? '())
(symbol? #f)

(define (hanoi source dest helper disks)
  (if (> disks 0) (append (hanoi source helper dest (- disks 1))
                                           (list (list source dest))
                                                           (hanoi helper dest source (- disks 1)))
    '()))

(hanoi 'a 'b 'c 3);should return ((a b) (a c) (b c) (a b) (c a) (c b) (a b))

(define (divides? a b) (= (modulo b a) 0))

(define (square x) (* x x))

(define (prime? n) 
  (define (smallest-divisor n)
    (find-divisor n 2))
  (define (find-divisor m test-divisor)
    (if (> (square test-divisor) n) n
      (if (divides? test-divisor n) test-divisor
        (find-divisor n (+ 1 test-divisor)))))
  (= n (smallest-divisor n)))
  
(prime? 10)
(prime? 21)
(prime? 23)

(define x 1)
(let ((x 2)
        (f (lambda () x))
        )
    (f))
