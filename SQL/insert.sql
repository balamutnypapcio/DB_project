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