INSERT INTO users (username, email, hashed_password)
VALUES ('alice', 'alice@example.com', 'hash1'),
       ('bob', 'bob@example.com', 'hash2'),
       ('carol', 'carol@example.com', 'hash3'),
       ('dave', 'dave@example.com', 'hash4'),
       ('eva', 'eva@example.com', 'hash5'),
       ('frank', 'frank@example.com', 'hash6'),
       ('grace', 'grace@example.com', 'hash7'),
       ('hank', 'hank@example.com', 'hash8'),
       ('ivy', 'ivy@example.com', 'hash9'),
       ('jack', 'jack@example.com', 'hash10'),
       ('kate', 'kate@example.com', 'hash11'),
       ('leo', 'leo@example.com', 'hash12'),
       ('mia', 'mia@example.com', 'hash13'),
       ('nick', 'nick@example.com', 'hash14'),
       ('olga', 'olga@example.com', 'hash15'),
       ('pete', 'pete@example.com', 'hash16'),
       ('quinn', 'quinn@example.com', 'hash17'),
       ('rose', 'rose@example.com', 'hash18'),
       ('sam', 'sam@example.com', 'hash19'),
       ('tina', 'tina@example.com', 'hash20');

-- Grupy
INSERT INTO group_table (name, created_by)
VALUES ('Tatry Trip', 1),
       ('Sylwester 2024', 2);

-- Członkowie grup
INSERT INTO group_members (group_id, user_id)
VALUES (1, 1),
       (1, 2),
       (1, 3),
       (1, 4),
       (1, 5),
       (2, 6),
       (2, 7),
       (2, 8),
       (2, 9),
       (2, 10);

-- Wydatki
INSERT INTO expenses (group_id, paid_by, amount, description)
VALUES (1, 1, 500, 'Zakwaterowanie'),
       (1, 2, 250, 'Paliwo'),
       (1, 3, 150, 'Jedzenie'),
       (2, 6, 800, 'Dom na sylwestra'),
       (2, 7, 100, 'Alkohol');

-- Uczestnicy i udziały

-- Dla wydatku 1 (500 zł, 5 osób)
INSERT INTO expense_participants (expense_id, user_id)
VALUES (1, 1),
       (1, 2),
       (1, 3),
       (1, 4),
       (1, 5);
INSERT INTO expense_shares (expense_id, user_id, share)
VALUES (1, 1, 100),
       (1, 2, 100),
       (1, 3, 100),
       (1, 4, 100),
       (1, 5, 100);

-- Dla wydatku 4 (800 zł, 5 osób)
INSERT INTO expense_participants (expense_id, user_id)
VALUES (4, 6),
       (4, 7),
       (4, 8),
       (4, 9),
       (4, 10);
INSERT INTO expense_shares (expense_id, user_id, share)
VALUES (4, 6, 160),
       (4, 7, 160),
       (4, 8, 160),
       (4, 9, 160),
       (4, 10, 160);

-- Payments
INSERT INTO payments (group_id, from_user, to_user, amount, status)
VALUES (1, 2, 1, 100, 'pending'),
       (1, 3, 1, 100, 'pending'),
       (1, 4, 1, 100, 'pending'),
       (1, 5, 1, 100, 'completed'),
       (2, 7, 6, 160, 'pending'),
       (2, 8, 6, 160, 'completed'),
       (2, 9, 6, 160, 'pending'),
       (2, 10, 6, 160, 'pending');


INSERT INTO users (id, username, email, hashed_password)
VALUES (21, 'zoe', 'zoe@example.com', 'hash21');

-- Dodanie 5 nowych grup
INSERT INTO group_table (name, created_by)
VALUES ('Wakacje Grecja 2024', 3),       -- id 3
       ('Wspólne Mieszkanie', 4),        -- id 4
       ('Impreza Urodzinowa', 5),        -- id 5
       ('Wyjazd Integracyjny', 1),       -- id 6
       ('Świąteczne Spotkanie', 2);      -- id 7

-- Dodanie członków do nowych grup
-- Użytkownicy 1, 5 i 10 będą we wszystkich grupach
-- Każdy inny użytkownik będzie w co najmniej 2 grupach
INSERT INTO group_members (group_id, user_id)
VALUES 
-- Grupa 3 (Wakacje Grecja 2024)
(3, 1),  -- alice (wszędzie)
(3, 5),  -- eva (wszędzie)
(3, 10), -- jack (wszędzie)
(3, 2),  
(3, 3),
(3, 4),
(3, 6),

-- Grupa 4 (Wspólne Mieszkanie)
(4, 1),  -- alice
(4, 5),  -- eva
(4, 10), -- jack
(4, 7),
(4, 8),
(4, 9),
(4, 11),

-- Grupa 5 (Impreza Urodzinowa)
(5, 1),  -- alice
(5, 5),  -- eva
(5, 10), -- jack
(5, 12),
(5, 13),
(5, 14),
(5, 15),

-- Grupa 6 (Wyjazd Integracyjny)
(6, 1),  -- alice
(6, 5),  -- eva
(6, 10), -- jack
(6, 16),
(6, 17),
(6, 2),
(6, 3),

-- Grupa 7 (Świąteczne Spotkanie)
(7, 1),  -- alice
(7, 5),  -- eva
(7, 10), -- jack
(7, 18),
(7, 19),
(7, 20),
(7, 4);
