; Jonathan Petersen
; A01236750
; Scheme Jousting
; Tournament Functions

; STEP 4: Tournament -------------------------------------------------------------------------------
; Wrapper function to get the index of the winning knight.
(define (tournament knightList)

	(get-index (playTournament knightList '()) knightList)

)

; Play a single round of the tournament, returning a list of the winning list and losing list.
; (i.e. ((winners) (losers)) )
(define (playRound knightList)

	; (display "---------------------\n")
	; (display knightList) (newline)
	; (display (car knightList) ) (newline)

	(cond 
		; Base Cases
		; Zero or fewer knights remaining
		((< (length knightList) 1)
			; (display "Hit bottom of recursion") (newline)
			(list '() '())
		)
		; One knight remaining
		((eq? (length knightList) 1)
			(display (caddr ((car knightList))))
			(display " gets a bye.")
			(newline)
			(list (car knightList) '())
		)
		
		; Recursive Case
		(else
			(if (eq? (jousting-game ((car knightList)) ((car (cdr knightList)))  ) 1)
				(begin 
					(display (caddr ((car knightList))) )
					(display " wins a tournament match!") 
					(newline) 
					(combinePairs (list (car knightList) (cadr knightList)) (playRound (cddr knightList)))
				)
				(begin 
					(display (caddr ((cadr knightList))))
					(display " wins a tournament match!") 
					(newline) 
					(combinePairs (list (cadr knightList) (car knightList)) (playRound (cddr knightList)))	
				)
			)
		)

	)

)

; Combines two pairs into two new pairs, where the first elements of both original pairs are members
; of the first new pair, and the second elements of the original pairs are members of the second.
(define (combinePairs list1 list2)
	; (display list1) (newline)
	; (display list2) (newline)
	; (display "-------------\n")
	(list (flatten (list (car list1) (car list2))) (flatten (list (cadr list1) (cadr list2))))
)

; Plays a double-elimination tournament, sorting the winners and losers into appropriate lists.
(define (playTournament winners losers)

	(display "Current Winners: ")
	(display winners)
	(newline)

	(display "Current Losers: ")
	(display losers)
	(newline)

	(if (eq? (length winners) 1)	
		(if (eq? (length losers) 1)
			; Only two knights remaining, joust it out.
			(if (eq? (jousting-game ((car winners)) ((car losers))) 1)
				(begin
					(display "!!!!!!!!")
					(display (caddr ((car winners))))
					(display " wins the tournament!!!!!!!!")
					(newline)
					(car winners)
				)
				(begin
					(display "!!!!!!!!")
					(display (caddr ((car losers))))
					(display " wins the tournament!!!!!!!!")
					(newline)
					(car losers)
				)
			)
			; One winner, but more than one loser remaining. Play a losers bracket round, discarding
			; any knights who lose in the losers bracket.
			(playTournament winners (car (playRound losers)))
		)
		; More than one winner remains, play a winners bracket round, moving any knights who lose 
		; into the losers bracket.
		(updateWinners (playRound winners) losers)
	)

)

; Return the (1 based) index of a knight in a list of said knights. Throw all sorts of errors if the
; knight couldn't be found.
(define (get-index knight knightList)

	(if (eqv? (car knightList) knight) 
		1
		(+ (get-index knight (cdr knightList)) 1)
	)

)

; Helper function for playTournament, this function just lets us call playTournament using the same
; parameter in two different ways (for both winners and losers lists).
(define (updateWinners updateList formerLosers)
	(playTournament (car updateList) (append (cadr updateList) formerLosers))
)

; PART 5: Season -----------------------------------------------------------------------------------
; Play a set of tournaments and return a list of how many times each knight won.
(define (season numTournaments knightsList)

	(if (< numTournaments 1)
		; Create a list of 0's for each knight playing.
		(make-list (length knightsList) 0)
		; Increment the list for each time they win.
		(addIndex (season (- numTournaments 1) knightsList) (tournament knightsList) 1)
	)

)

; Creates a list of length k with value v in each spot.
(define (make-list k v)

	(if (< k 1)
		; Base Case
		'()
		; Recursive Case
		(cons v (make-list (- k 1) v))
	)

)

; Add value to the item contained in list1 at position index. This is more versatile than it needs 
; to be, since we only ever add 1 to things.
(define (addIndex list1 index value)

	(if (eq? index 1)
		; Base Case
		(cons (+ value (car list1)) (cdr list1))
		; Recursive Case
		(cons (car list1) (addIndex (cdr list1) (- index 1) value))
	)

)
