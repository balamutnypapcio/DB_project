# Aplikacja do zarządzania wspólnymi wydatkami

## Opis projektu

Projekt zakłada stworzenie aplikacji desktopowej umożliwiającej użytkownikom wspólne zarządzanie wydatkami w grupach. System jest inspirowany działaniem aplikacji takich jak Tricount i pozwala na dodawanie wydatków, rozdzielanie kosztów, prowadzenie rozliczeń i przeglądanie historii transakcji.

## Główne funkcjonalności

- Rejestracja i logowanie użytkowników
- Tworzenie i zarządzanie grupami wydatków
- Dodawanie wydatków i podział kosztów (równo lub niestandardowo)
- Historia transakcji
- Automatyczne rozliczenia
- Oznaczanie wydatków jako spłacone
- Anonimizacja danych użytkownika po usunięciu konta

## Technologie

- **Język programowania:** Python
- **GUI:** Qt / Terminal
- **Baza danych:** MySQL
- **System kontroli wersji:** Git

## Struktura bazy danych

Baza danych zawiera m.in. następujące tabele:

- `users` – dane użytkowników
- `groups` – grupy wydatków
- `group_members` – członkowie grup
- `expenses` – wydatki
- `expense_shares` – udziały w wydatkach
- `payments` – informacje o płatnościach

Zaimplementowano również:

- **Procedury składowane**:
  - `add_expense_to_group` – dodanie wydatku z niestandardowym podziałem
  - `add_equal_expense` – dodanie wydatku z równym podziałem
  - `create_group` – tworzenie nowej grupy z użytkownikami

- **Triggery**:
  - `check_expense_completion` – automatyczne oznaczanie rozliczeń jako zakończone
  - `anonimize_user_data_after_delete` – anonimizacja danych użytkownika

- **Widoki (views)**:
  - `view_group_balances`
  - `view_group_expenses_details`
  - `view_user_groups`

## Interfejs aplikacji

Aplikacja składa się z kilku ekranów:

1. **Logowanie**
2. **Lista grup użytkownika**
3. **Bilans rozliczeń grupy**
4. **Historia wydatków**
5. **Szczegóły wydatku**
6. **Formularze dodawania wydatku**
7. **Zarządzanie profilem**

## Uruchomienie

1. Skonfiguruj bazę danych MySQL i uruchom skrypty tworzące tabele i procedury.
2. Uruchom aplikację w środowisku Python.
3. Korzystaj z GUI lub wersji terminalowej do testowania funkcjonalności.

## Autorzy

Projekt został wykonany przez:

- Jakub Wilczyński  
- Michał Markuzel  
- Antoni Piałucha  
- Maksymilian Tulewicz
