; Jonathan Petersen
; A01236750
; Scheme Jousting
; Knight Definitions

; Define your additional knights here:

; STEP 3: Defining Knights -------------------------------------------------------------------------
; Lancelot has a 0.4 probability of holding his shield
; high, a 0.4 probability of holding his or low, and a 0.2 
; probability of ducking. He also has a probability of 0.5 
; for each lance position.
(define (sir-lancelot)
	(let (
			; 0.2 chance of duck, 0.8 * 0.5 chance for the others.
			(shield (if (>= (random 10) 8) 'duck 
					(if (>= (random 10) 5) 'high 'low)))
			(lance (if (>= (random 10) 5) 'low 'high))
		)		
		(list shield lance "Sir Lancelot")
	)
)

; My own personal knight. Always goes low low.
(define (jonathan-petersen)
	(let (
			(shield 'low)
			(lance 'low)
		)
		(list shield lance "Jonathan Petersen")
	)	
)

; --------------------Example Knights-------------------

; The black knight, being at times without legs and arms,
; is equally likely to hold his shield low and duck
; while generally going for the low blow with his lance.
(define (black-knight) 
	(let (
			(shield (if (>= (random 10) 5) 'low 'duck))
			(lance (if (>= (random 10) 2) 'low 'high))
		)		
		(list shield lance "Black Knight")
	)
)

; "Brave Sir Robin ran away. 
; Bravely ran away away. 
; When danger reared it's ugly head, 
; He bravely turned his tail and fled. 
; Yes, brave Sir Robin turned about 
; And gallantly he chickened out. 
; Bravely taking to his feet, 
; He beat a very brave retreat.
; Bravest of the braaaave, Sir Robin!"
;
; Due to his bravery...Sir Rob almost always ducks
; and, since his eyes are routinely closed during a
; joust, his lance tends to go float high
(define (sir-robin) 
	(let (
			(shield (if (>= (random 10) 2) 'duck 'high))
			(lance (if (>= (random 10) 2) 'high 'low))
		) 
		(list shield lance "Sir Robin")
	)
)

; Joan of Arc is far too noble to ever consider ducking,
; she tends to hold her lance high and her shield low.
(define (joan-of-arc)
	(let (
			(shield (if (>= (random 10) 8) 'high 'low))
			(lance (if (>= (random 10) 2) 'high 'low))
		) 
		(list shield lance "Joan of Arc")
	)
)

; Arthur, King of the Britons has gained much wisdom
; in his quest for the holy grail. Using this wisdom 
; he has decided the best strategy is to always hold
; his shield high and lance low.
(define (king-arthur) 
	(let (
			(shield 'high)
			(lance 'low)
		)
		(list shield lance "King Arthur")
	)
)
