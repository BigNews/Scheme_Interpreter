;;; test syntaxes and procedures with side effect

;;; util
(define (show obj)
  (display obj)
  (newline))

(define (title obj)
  (newline)
  (show obj))

(show "Test with side effect")

;;; set!
(title "set!")
(define x 1)
(show x) ;; 1
(set! x 'doremi)
(show x) ;; doremi
(define f (lambda () (set! x "Hello, world!")))
(f)
(show x) ;; Hello, world!

;;; test for lexical scope and let-binding rules
(title "lexical scope and let-bindings")
(define x 'wrong)
(define (f) (set! x 'correct))
((lambda (x)
   (f)) 'still-wrong)
(show x) ;; correct
(define x 'correct)
(letrec ((x "")
         (f (lambda () (set! x 'wrong))))
  (display x)
  (f))
(show x) ;; correct
(define x 'wrong)
(let ((x "")
      (f (lambda () (set! x 'correct))))
  (display x)
  (f))
(show x) ;; correct
(define x 'correct)
(let* ((x "")
       (f (lambda () (set! x 'wrong))))
  (display x)
  (f))
(show x) ;; correct

;;; swap f and g
(title "swap f and g")
(define (f my-position)
  (display "f")
  (if (eq? my-position 'f) 
      (let ((tmp g))
        (g 'g)
        (set! f tmp))
      (set! f g)))
(define (g my-position)
  (display "g")
  (if (eq? my-position 'g)
      (set! g f)
      (let ((tmp f))
        (g 'g)
        (set! g tmp))))
(define (swap-f-g)
  (f 'f)
  (newline))
(swap-f-g) ;; fg
(swap-f-g) ;; gf

;;; lists with side effect
(title "lists with side effect")
(define A (list "Romeo" "and" "Juliet"))
(define B (list "is" "not" "written" "by" "William" "Shakespeare"))
(define sentence (append A B))
(show sentence)
(show "That's wrong!! I'll correct the mistake.")
(set-car! (cdr B) "")
(show sentence)
(show "It's correct now. But remove the unused empty string would look better.")
(set-cdr! B (cddr B))
(show sentence)
(show "Perfect!")

;; (Romeo and Juliet is not written by William Shakespeare)
;; That's wrong!! I'll correct the mistake.
;; (Romeo and Juliet is  written by William Shakespeare)
;; It's correct now. But remove the unused empty string would look better.
;; (Romeo and Juliet is written by William Shakespeare)
;; Perfect!


;;; closure with side effect
(title "closure with side effect")
(define (make-map)
  (define (make-map-impl mmap)
    (lambda (action . args)
      (cond ((eq? action 'get) (get-item mmap (car args)))
            ((eq? action 'set!) (set! mmap (set-item! mmap (car args) (cadr args))))
            ((eq? action 'clear!) (set! mmap '()))
            ((eq? action 'remove!) (set! mmap (remove-item! mmap (car args))))
            ((eq? action 'show-all) (show mmap))
            )))
  
  (define (get-item mmap key)
    (let ((item (assoc key mmap)))
      (if (not item)
          'NULL
          (cdr item))))
  
  (define (set-item! mmap key value)
    (let ((item (assoc key mmap)))
      (if (not item)
          (cons (cons key value) mmap)
          (begin (set-cdr! item value) mmap))))
  
  (define (remove-item! mmap key)
    (define (remove-item-not-first! now key)
      (if (not (null? (cdr now)))
          (if (equal? (caadr now) key)
              (set-cdr! now (cddr now))
              (remove-item-not-first! (cdr now) key))))
    (if (null? mmap)
        mmap
        (if (equal? (caar mmap) key)
            (cdr mmap)
            (begin (remove-item-not-first! mmap key) mmap))))
  
  (make-map-impl '()))

(define mymap (make-map))
(mymap 'set! "Ross Geller" "David Schwimmer")
(mymap 'set! "Monica Geller" "Courteney Cox")
(mymap 'set! "Rachael Green" "Jennifer Aniston")
(mymap 'set! "Phoebe Buffay" "Lisa Kudrow")
(mymap 'set! "Joey Tribbiani" "Matt Leblanc")
(mymap 'set! "Chandler Bing" "Matthew Perry")
(mymap 'set! "Sheldon Cooper" "Jim Parsons")
(mymap 'set! "Leonard Hofstadter" "Johnny Calecki")
(mymap 'set! "Raj Koothrappali" "Kunal Nayyar")
(mymap 'set! "Howard Wolowitz" "Simon Helberg")
(mymap 'set! "Amy Fowler" "Mayim Bialik")
(mymap 'set! "Penny" "Kaley Cuoco")
(mymap 'set! "Bernadette Wolowitz" "Melissa Rauch")

(mymap 'show-all)
(show (mymap 'get "Leonard Hofstadter"))
(show (mymap 'get "Penny"))
(show (mymap 'get "Ross Geller"))
(show (mymap 'get "Rachael Green"))
(show (mymap 'get "Bernadette Wolowitz"))
(mymap 'remove! "Chandler Bing")
(mymap 'remove! "Ross Geller")
(mymap 'remove! "Bernadette Wolowitz")
(show (mymap 'get "Chandler Bing"))
(show (mymap 'get "Ross Geller"))
(show (mymap 'get "Bernadette Wolowitz"))
(mymap 'set! "Phoebe Buffay" "Kudrow")
(show (mymap 'get "Phoebe Buffay"))
(mymap 'set! "Penny" "Cuoco")
(show (mymap 'get "Penny"))
(mymap 'set! "Monica Geller" "Cox")
(show (mymap 'get "Monica Geller"))
(mymap 'clear!)
(mymap 'show-all)

;;((Bernadette Wolowitz . Melissa Rauch) (Penny . Kaley Cuoco) (Amy Fowler . Mayim Bialik) (Howard Wolowitz . Simon Helberg) (Raj Koothrappali . Kunal Nayyar) (Leonard Hofstadter . Johnny Calecki) (Sheldon Cooper . Jim Parsons) (Chandler Bing . Matthew Perry) (Joey Tribbiani . Matt Leblanc) (Phoebe Buffay . Lisa Kudrow) (Rachael Green . Jennifer Aniston) (Monica Geller . Courteney Cox) (Ross Geller . David Schwimmer))
;;Johnny Calecki
;;Kaley Cuoco
;;David Schwimmer
;;Jennifer Aniston
;;Melissa Rauch
;;null
;;null
;;null
;;Kudrow
;;Cuoco
;;Cox
;;()
