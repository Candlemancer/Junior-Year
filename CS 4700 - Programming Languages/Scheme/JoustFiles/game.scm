; Jonathan Petersen
; A01236750
; Scheme Jousting
; Joust Game Functions

; STEP 1: Joust ------------------------------------------------------------------------------------
; This function plays one jousting pass between two players
(define (joust player1 player2) 

	(list
		; Check the status of the First Knight
		(if (equal? 'high (cadr player2))
			(if (equal? 'high (car player1))
				(begin 
					(display (caddr player1)) 
					(display " blocked with a high shield! ") 
					#t
				)
				(begin 
					(display (caddr player1)) 
					(display " was unhorsed by a high blow! ") 
					#f
				)
			)
			(cond
			   ((equal? 'high (car player1))
				(begin 
					(display (caddr player1)) 
					(display " was unhorsed by a low blow! ") 
					#f
				))

			   ((equal? 'duck (car player1))
				(begin 
					(display (caddr player1)) 
					(display " was unhorsed while trying to duck! ") 
					#f
				))

			   (else
			   	(begin 
			   		(display (caddr player1)) 
			   		(display " blocked with a low shield! ") #t
			   	))
			)
		)

		; Check the status of the Second Knight
		(if (equal? 'high (cadr player1))
			(if (equal? 'high (car player2))
				(begin 
					(display (caddr player2)) 
					(display " blocked with a high shield! ") 
					#t
				)
				(begin 
					(display (caddr player2)) 
					(display " was unhorsed by a high blow! ") 
					#f
				)
			)
			(cond
			   ((equal? 'high (car player2))
				(begin 
					(display (caddr player2)) 
					(display " was unhorsed by a low blow! ") 
					#f
				))

			   ((equal? 'duck (car player2))
				(begin 
					(display (caddr player2)) 
					(display " was unhorsed while trying to duck! ") 
					#f
				))

			   (else
			   	(begin 
			   		(display (caddr player2)) 
			   		(display " blocked with a low shield! ") 
			   		#t
			   	))
			)
		)
	)

)


; STEP 2: Jousting Game ----------------------------------------------------------------------------
; Wrapper function to maintain inter-student compatiblity
(define (jousting-game knight1 knight2)

	; Magic number is the recursive depth.
	(recursive-jousting-game knight1 knight2 100)

)

; This function puts a bound on the maximum number of times two knights can tie.
(define (recursive-jousting-game knight1 knight2 depth)

	(if (> depth 0)
	   	(check-victory knight1 knight2 (joust knight1 knight2) (- depth 1))

	   	; In case of deadlock ties, randomly decide a winner
	   	(if (>= (random 10) 5)
	   		1
	   		2
	   	)
	)

)

; Actually play a game, and return the results. Note that this function runs in parallel recursion
; to recursive-jousting-game.
(define (check-victory knight1 knight2 joustingResults depth)

	(if (xor joustingResults)
		; Base Case
		(cond
		   ((car joustingResults)
			(begin (display "--- ") (display (caddr knight1)) (display " wins!") (newline) 1))
		   (else
		   	(begin (display "--- ") (display (caddr knight2)) (display " wins!") (newline) 2))
		)

		; Recursive Case
		(begin (display "--- The round was a tie.\r") ;(newline) 
			(recursive-jousting-game knight1 knight2 depth)
		)
	)

)

; A simple exclusive or implementation
(define (xor list1)

	(not (equal? (car list1) (cadr list1)))

)
