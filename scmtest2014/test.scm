;;; stdlib
(define (filter pred? lst)
  (if (null? lst)
      '()
      (if (pred? (car lst))
          (cons (car lst) (filter pred? (cdr lst)))
          (filter pred? (cdr lst)))))

(define (flatmap func lst)
  (apply append (map func lst)))
      
(define (interval start end)
  (if (= start end)
      '()
      (cons start (interval (+ start 1) end))))

(define (any-of? pred? lst)
  (if (null? lst)
      #f
      (or (pred? (car lst)) (any-of? pred? (cdr lst)))))
(define (none-of? pred? lst)
  (not (any-of? pred? lst)))
(define (all-of? pred? lst)
  (if (null? lst)
      #t
      (and (pred? (car lst)) (all-of? pred? (cdr lst)))))

;;; basic operations
(display "basic operations\n")
(define _1 1)
(define _2 2)
(define (_3) 3)
(display (+ _1 _2 (_3)))   ;;6
(newline)
(display (- _2 (_3)))  ;;-1
(newline)
(display (* _2 (_3)))      ;;6
(newline)
(display (/ _2 (_3)))      ;;2/3
(newline)
(display (quotient _2 (_3)))  ;; 0
(newline)
(display (modulo _2 (_3)))  ;; 2
(newline)
(display (if (= _1 1)
             (_3)
             _2))    ;;3
(newline)

;;; try some big numbers
(newline)
(display "big numbers\n")
(define _4 12345678901234567890)
(define _5 98765432109876543210)
(display (* (- _4 _5) (+ _4 200 _5)))  ;; -9602194792318244175459533629632373116000
(newline)

;;; fast-exp
(newline)
(display "fast-exp\n")
(define (sqr x) (* x x))
(define (odd? n) (= (modulo n 2) 1))

(define (fast-exp a n)
  (if (= n 0)
      1
      (if (odd? n)
          (* a (sqr (fast-exp a (quotient n 2))))
          (sqr (fast-exp a (quotient n 2))))))

(display (fast-exp 2 0)) ;; 1
(newline)
(display (fast-exp 2 5)) ;; 32
(newline)
(display (fast-exp 2 100)) ;; 1267650600228229401496703205376
(newline)

;;; fibonacci
(newline)
(display "fibonacci sequence\n")
(define fib
  (lambda (n)
    (letrec ((calc-fib (lambda (prev now n)
                         (if (= n 0)
                             prev
                             (calc-fib now (+ prev now) (- n 1))))))
      (calc-fib 0 1 n))))

(display (fib 5))  ;; 5
(newline)
(display (fib 20)) ;; 6765
(newline)
;;(fib 32)  ;;2178309
;;(fib 10000)

;;; the computeE
(newline)
(display "compute e\n")
(define (computeE e k f m)
  (if (> k m)
      e
      (computeE (+ e (/ 1.0 f)) (+ k 1) (* f k) m)))

(display (computeE 0 1 1 10000))  ;; 2.7182818##
(newline)

;;; pairs and lists
(newline)
(display "pairs and lists\n")
(display
 (and (equal? '(1 2 3 4) (list 1 2 3 4))
      (equal? (list 1 2 3 4) (cons 1 (cons 2 (cons 3 (cons 4 '())))))
      (equal? (cons 1 (cons 2 (cons 3 (cons 4 '())))) '(1 2 3 4))))  ;; #t
(newline)
(display (pair? '()))  ;; #f
(newline)
(display (list? '()))  ;; #t
(newline)
(display (pair? (cons 1 2))) ;; #t
(newline)
(display (list? (cons 1 2))) ;; #f
(newline)
(display (pair? '(1 2))) ;; #t
(newline)
(display (list? '(1 2))) ;; #t
(newline)

(define lst '(1.1 1 2 #\c))
(display (eqv? (cadr lst) 1))  ;; #t
(newline)
(display (eqv? (list-ref lst (- (length lst) 1)) #\c))  ;; #t
(newline)
(display (memq 2 lst))  ;; (2 #\c)
(newline)
(display (memq 100 lst)) ;; #f
(newline)

(let ((table '((apple 0)
              (banana 1)
              (strawberry 2))))
  (display (assq 'banana table))
  (newline)
  (display (assq 'pineapple table))
  (newline)) ;; (banana 1) #f

(define (hanoi src dest mid n)
  (if (= n 0)
      '()
      (append (hanoi src mid dest (- n 1))
              (list (list src dest))
              (hanoi mid dest src (- n 1)))))

(display (hanoi 'a 'b 'c 3))  ;; ((a b) (a c) (b c) (a b) (c a) (c b) (a b))
(newline)

;;; infinite stream
(newline)
(display "infinite stream\n")
(define (make-stream start step)
  (cons start (lambda () (make-stream (+ start step) step))))
(define (head stream) (car stream))
(define (tail stream) ((cdr stream)))
(define (nth-from stream n)
  (if (= n 0)
      stream
      (nth-from (tail stream) (- n 1))))

(define stream (make-stream 0 1))
(display (head stream))  ;; 0
(newline)
(display (head (nth-from stream 4))) ;; 4
(newline)
(define stream (nth-from stream 100))
(display (head stream)) ;; 100
(newline)

(define (stream-map func . streams)
  (cons (apply func (map head streams)) 
        (lambda () 
          (apply stream-map (append (list func) (map tail streams))))))
(define sqrn-minus-n 
  (stream-map - (stream-map sqr (make-stream 0 1)) (make-stream 0 1)))
(display (head (nth-from sqrn-minus-n 5))) ;; 20
(newline)
(display (head (nth-from sqrn-minus-n 100))) ;; 9900
(newline)


;;; N-queens
(newline)
(display "N-queens")
(newline)
(define (NQU size)
  (define all-cols (interval 1 (+ size 1)))
  (define (valid? n configuration)
    (and (none-of? (lambda (col) (= (car configuration) col)) (cdr configuration))
         (none-of? (lambda (diag) (= (- n (car configuration)) diag))
                   (map - (interval (+ n 1) (+ size 1)) (cdr configuration)))
         (none-of? (lambda (cdiag) (= (+ n (car configuration)) cdiag))
                   (map + (interval (+ n 1) (+ size 1)) (cdr configuration)))))
  
  (define (choose-col n)
    (if (= n (+ size 1))
        (list '())
        (filter
         (lambda (configuration) (valid? n configuration))
         (flatmap
          (lambda (configuration)
            (map (lambda (sel) (cons sel configuration))
                 all-cols))
          (choose-col (+ n 1))))))
  (choose-col 1))
        
(display (length (NQU 8))) ;; 92
(newline)

;;; let-bindings
(newline)
(display "let-bindins")
(newline)
(define var1 1)
(display (let ((var1 2)
               (y (lambda () var1)))
           (y)))  ;; 1
(newline)
(display (let* ((var1 2)
                (y (lambda () var1)))
           (y)))  ;; 2
(newline)
(display (letrec ((var1 2)
                  (y (lambda () var1)))
           (y)))  ;; 2
(newline)
(display (let* ((var1 2)
                (y var1))
           y))  ;; 2
(newline)
