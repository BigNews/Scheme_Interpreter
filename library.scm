;*******************************************************************
;
;						Number Operation Part
;
;*******************************************************************

(define (zero? x) (= x 0))

(define (abs x)
	(if (< x 0)
		(- 0 x)
		x))

;*******************************************************************
;
;						List Part
;
;*******************************************************************

(define (caar x) (car (car x)))
(define (cadr x) (car (cdr x)))
(define (cdar x) (cdr (car x)))
(define (cddr x) (cdr (cdr x)))

(define (caaar x) (car (car (car x))))
(define (caadr x) (car (car (cdr x))))
(define (cadar x) (car (cdr (car x))))
(define (cdaar x) (cdr (car (car x))))
(define (caddr x) (car (cdr (cdr x))))
(define (cdadr x) (cdr (car (cdr x))))
(define (cddar x) (cdr (cdr (car x))))
(define (cdddr x) (cdr (cdr (cdr x))))

(define (caaaar x) (car (car (car (car x)))))
(define (caaadr x) (car (car (car (cdr x)))))
(define (caadar x) (car (car (cdr (car x)))))
(define (cadaar x) (car (cdr (car (car x)))))
(define (cdaaar x) (cdr (car (car (car x)))))
(define (caaddr x) (car (car (cdr (cdr x)))))
(define (cadadr x) (car (cdr (car (cdr x)))))
(define (caddar x) (car (cdr (cdr (car x)))))
(define (cdaadr x) (cdr (car (car (cdr x)))))
(define (cdadar x) (cdr (car (cdr (car x)))))
(define (cddaar x) (cdr (cdr (car (car x)))))
(define (cadddr x) (car (cdr (cdr (cdr x)))))
(define (cdaddr x) (cdr (car (cdr (cdr x)))))
(define (cddadr x) (cdr (cdr (car (cdr x)))))
(define (cdddar x) (cdr (cdr (cdr (car x)))))
(define (cddddr x) (cdr (cdr (cdr (cdr x)))))

(define (even? x) (if (= (remainder x 2) 0) #t #f))
(define (odd? x) (if (= (remainder x 2) 1) #t #f))

(define (equal? x y)
  (if (pair? x)
      (if (pair? y)
          (if (equal? (car x) (car y))
              (equal? (cdr x) (cdr y))
              #f)
          #f
          )
      (eqv? x y)
      )
  )
  
(define (list? x)
  (if (pair? x)
      (list? (cdr x))
      (if (null? x)
          #t
          #f)
      )
  )
  
(define (length x)
  (if (null? x)
	  0
	  (if (pair? x)
		  (+ (length (cdr x)) 1)
		  (c++throw "length : contract violation!")
		)
	)
)

(define (memq obj alist)
  (if (null? alist)
      #f
	  (if (eq? obj (car alist))
	      alist
		  (memq obj (cdr alist))
		  )
   )
)

(define (memv obj alist)
  (if (null? alist)
      #f
	  (if (eqv? obj (car alist))
	      alist
		  (memv obj (cdr alist))
		  )
   )
)

(define (member obj alist)
  (if (null? alist)
      #f
	  (if (equal? obj (car alist))
	      alist
		  (member obj (cdr alist))
		  )
   )
)

(define (mappend x y)
   (if (pair? x)
		(cons (car x) (mappend (cdr x) y))
		(if (null? x)
			y
			(c++throw "mappend: contract violation") 
			)
		))
		
(define (_append x y)
	(if (pair? y)
		(mappend x (_append (car y) (cdr y)))
		(if (null? y)
			x
			(c++throw "_append: contract violation!")
			)
		)
	)
		
(define (append . x) (_append `() x))		

(define (_map proc operand)
	(if (null? operand)
		'()
		(cons (proc (car operand)) (_map proc (cdr operand)))
		)
		)
		
(define (map proc subject . object)
	(if (null? object)
		(_map proc subject)
		(if (null? subject)
			`()
			(cons (apply proc (cons (car subject) (_map car object)))
				(map proc (cdr subject) (apply append (_map cdr object)))))
		)
		)
		
(define (assq obj alist)
	(if (null? alist)
		#f
		(if (eq? obj (caar alist))
			(car alist)
			(assq obj (cdr alist))
			)
	)
)

(define (assv obj alist)
	(if (null? alist)
		#f
		(if (eqv? obj (caar alist))
			(car alist)
			(assv obj (cdr alist))
			)
	)
)

(define (assoc obj alist)
	(if (null? alist)
		#f
		(if (equal? obj (caar alist))
			(car alist)
			(assoc obj (cdr alist))
			)
	)
)

(define (reverse alist)
	(if (null? alist)
		'()
		(append (reverse (cdr alist)) (cons (car alist) nil))))
		
(define list-tail
	(lambda (x k)
		(if (zero? k)
			x
			(list-tail (cdr x) (- k 1)))))
			
(define (list-ref x k)
	(car (list-tail x k)))

;*******************************************************************
;
;						Miscellaneous
;
;*******************************************************************

(define nil '())
(define (not x)
	(if x #f #t))
		
