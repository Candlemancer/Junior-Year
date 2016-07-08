(load "knights.scm") ; You may need full paths to your files here
(load "game.scm")
(load "tournament.scm")

(display "----Playing a game----\n")
(jousting-game (jonathan-petersen) (king-arthur))
(jousting-game (sir-lancelot) (black-knight))
(display "----Playing a tournament----\n")
(tournament (list black-knight sir-robin king-arthur joan-of-arc))
(display "----Playing a season----\n")
(display (season 50 (list black-knight sir-robin king-arthur joan-of-arc jonathan-petersen))) (newline)

