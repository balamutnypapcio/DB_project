Antek, podsumowanie commita Baz Danych 29.05.2025:

Co zostało dodane:
	1. Zostały dodane nowe procedury tj. usuwanie grupy.
	2. Zostały zaktualizowany procedury tj. dodawanie wydatku.
	3. Została wprowadzona opcja dodawania grupy. Aby dodac trzeba wpisać w pole. 
		username np. alice,bob,carol (imona przedzielone przecinkiem)
	4. Została wprowadzona opcja usunięcia grupy.
	5. Została wprowadzona obsługa okna expensesDetailes, gdzie pokazuje faktycznie wartości z BD.
	6. Została wprowadzona opcja dodania wydatku. W participants trzeba podać kto ile zapłacił
		takim kluczem "alice:30,bob:20,carol:5". Oznacza to, że alice zapłaciła 30 dolarów,
		bob 20 dolarów, a carol 5 dolarów. Jako łączny koszt wydatków jest zaciągana kwota z
		amount, a więc nie jest sprawdzane czy suma w amount równa się sumie wydatków poszczególnych
		osób. Może dojść do sytuacji gdzie na stronie szczegóły wydatku pole amount różni się od sumy wydatków
		poszczególnych osób. Ta mechanika mogłaby być w pzrsyzłości polepszona ale troche trzeba by sie 
		bawić z UI.
	7. Została wprowadzona obsługa usuwania wydatku.

Na co trzeba uważać przy uruchamianiu u siebie:
	1. Ze względu, że już miałem postawioną u siebie gotową BD maria to nie chciałem jej zmieniać.
		Zamiast tego zmieniłem nazwe bazy danych, użytkownika i hasło w Qt. Jeżeli odpalasz
		u siebie to musisz wejść do pliku database.h (czy jakoś tak) i zmienić spowrotem te
		stałe tak jak masz u siebie.
