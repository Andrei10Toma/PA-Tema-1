# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
# TODO

# nume necesar (build)
build:
	g++ crypto.cpp -o crypto -Wall -Wextra
	g++ stocks.cpp -o stocks -Wall -Wextra
	g++ valley.cpp -o valley -Wall -Wextra
	g++ ridge.cpp -o ridge -Wall -Wextra

run-p1:      # nume necesar
	./crypto

run-p2:      # nume necesar
	./stocks

run-p3:      # nume necesar
	./valley

run-p4:      # nume necesar
	./ridge

clean:		 # nume necesar
	rm -rf crypto stocks valley ridge
