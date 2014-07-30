;-- test maker guideline: use dirichlet to compose 2 mixture sets of pure numeric or pure boolean functions, next start random walking in this complete bipartite graph.
;-- numeric primitives: test for gap or strict equality to make it boolean
;-- fact
;-- gcd
;-- expmod
;-- square
;-- mean
;-- +
;-- -
;-- *
;-- /
;--
;-- boolean primitives: conditional branch to make it numeric.
;-- divides?
;-- prime?
;-- boolean?
;-- not
;-- any?
;--
;-- misc primitives: manual test
;-- fib, the stupidest tree recursion version
;-- myE
;-- square-root
;-- hanoi
;
;
;-------------- hello world stuff
;

(define (zipWith f x y) (if (or (null? x) (null? y))
                          (quote ())
                          (cons (f (car x) (car y))
                                (zipWith f (cdr x) (cdr y)))))
(define (fib n)
  (if (= n 0) 0
    (if (= n 1) 1
      (+ (fib (- n 1)) 
         (fib (- n 2))))))

;(fib 22) ;should be 17711
;(fib 30) ;should be 832040
;(fib 32) ;should be 2178309, this may need careful memory management.
;(= (- (fib 32) (fib 31)) (fib 30)) ;should be true

(define (gcd a b)
  (if (= b 0)
    a
    (gcd b (modulo a b))))

(define (square x) (* x x))

(define (fact n) (if (= n 1)
                   1
                   (* n (fact (- n 1)))))

(define (hanoi source dest helper disks)
  (if (> disks 0) (append (hanoi source helper dest (- disks 1))
                                           (list (list source dest))
                                                           (hanoi helper dest source (- disks 1)))
    '()))

;(hanoi 'a 'b 'c 3');should return ((a b) (a c) (b c) (a b) (c a) (c b) (a b))


;-------------- math related stuff
(define (mean . numbers)
    (/ (apply + numbers)
            (length numbers)))

(define (divides? a b) (= (modulo b a) 0))

(define (expmod base e m)
  (if (= e 0) 1
    (if (even? e)
      (modulo (square (expmod base (/ e 2) m))
              m)
      (modulo (* base (expmod base (- e 1) m))
              m))))

(define (prime? n) 
  (define (smallest-divisor n)
    (find-divisor n 2))
  (define (find-divisor m test-divisor)
    (if (> (square test-divisor) n) n
      (if (divides? test-divisor n) test-divisor
        (find-divisor n (+ 1 test-divisor)))))
  (= n (smallest-divisor n)))

(define (fastexp base e)
  (if (= e 0) 1
    (if (even? e)
        (square (fastexp base (/ e 2)))
        (* base (fastexp base (- e 1))))))

(define (computeE e k n m)
  (if (>= n m) e
    (computeE (+ e (/ m n)) (+ k 1) (* n k) m)))

(define myE (computeE (fastexp 10 100) 2 1 (fastexp 10 100))) ;this is a scaled version of E.

;(prime? 11);should be true
;(prime? 7) ;should be true

(define (newton guess function derivative epsilon)
      (define guess2 (- guess (/ (function guess) (derivative guess))))
          (if (< (abs (- guess guess2)) epsilon) guess2
                    (newton guess2 function derivative epsilon)))

(define (square-root a)
      (newton 1 (lambda (x) (- (* x x) a)) (lambda (x) (* 2 x)) 0.000001))

; TODO: more complicated lazy lists in Scheme? reference http://www.haskell.org/haskellwiki/Blow_your_mind
; 
;(define fibs (cons 0 (cons 1 (delay (zipWith + fibs (cdr fibs))))))

