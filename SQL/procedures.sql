DELIMITER //

DROP PROCEDURE IF EXISTS add_expense_to_group;

CREATE PROCEDURE add_expense_to_group (
    IN p_group_id INT,
    IN p_paid_by_username VARCHAR(100),
    IN p_amount DECIMAL(10,2),
    IN p_description VARCHAR(255),
    IN p_participants_shares TEXT -- np. 'alice:40,bob:40,carol:20'
)
BEGIN
    DECLARE v_expense_id INT;
    DECLARE v_pos INT DEFAULT 1;
    DECLARE v_part TEXT;
    DECLARE v_user_name VARCHAR(100);
    DECLARE v_user_id INT;
    DECLARE v_paid_by_id INT;
    DECLARE v_share DECIMAL(10,2);

    -- Pobierz ID użytkownika, który zapłacił
    SELECT id INTO v_paid_by_id FROM users WHERE username = p_paid_by_username LIMIT 1;

    -- Jeśli zapłacający użytkownik nie istnieje – zakończ
    IF v_paid_by_id IS NULL THEN
        SIGNAL SQLSTATE '45000'
            SET MESSAGE_TEXT = 'User paying for the expense not found';
    END IF;

    -- 1. Dodaj wydatek
    INSERT INTO expenses (group_id, paid_by, amount, description)
    VALUES (p_group_id, v_paid_by_id, p_amount, p_description);

    SET v_expense_id = LAST_INSERT_ID();

    -- 2. Parsuj i dodawaj uczestników + udziały
    WHILE LENGTH(p_participants_shares) > 0 DO
        SET v_pos = LOCATE(',', p_participants_shares);

        IF v_pos > 0 THEN
            SET v_part = SUBSTRING(p_participants_shares, 1, v_pos - 1);
            SET p_participants_shares = SUBSTRING(p_participants_shares, v_pos + 1);
        ELSE
            SET v_part = p_participants_shares;
            SET p_participants_shares = '';
        END IF;

        SET v_user_name = SUBSTRING_INDEX(v_part, ':', 1);
        SET v_share = SUBSTRING_INDEX(v_part, ':', -1);

        -- Pobierz user_id na podstawie nazwy
        SELECT id INTO v_user_id FROM users WHERE username = v_user_name LIMIT 1;

        -- Wstaw dane, jeśli użytkownik istnieje
        IF v_user_id IS NOT NULL THEN
            INSERT INTO expense_participants (expense_id, user_id)
            VALUES (v_expense_id, v_user_id);

            INSERT INTO expense_shares (expense_id, user_id, share)
            VALUES (v_expense_id, v_user_id, v_share);
        END IF;
    END WHILE;
END;
//

DELIMITER ;


DELIMITER //

DROP PROCEDURE IF EXISTS add_equal_expense;

CREATE PROCEDURE add_equal_expense (
    IN p_group_id INT,
    IN p_paid_by INT,
    IN p_amount DECIMAL(10,2),
    IN p_description VARCHAR(255),
    IN p_participant_ids TEXT -- np. '5,6,7'
)
BEGIN
    DECLARE v_expense_id INT;
    DECLARE v_pos INT DEFAULT 1;
    DECLARE v_id TEXT;
    DECLARE v_user_id INT;
    DECLARE v_count INT DEFAULT 0;
    DECLARE v_share DECIMAL(10,2);
    DECLARE temp_str TEXT;

    -- policz ilu użytkowników
    SET temp_str = p_participant_ids;
    WHILE LENGTH(temp_str) > 0 DO
        SET v_pos = LOCATE(',', temp_str);
        IF v_pos > 0 THEN
            SET temp_str = SUBSTRING(temp_str, v_pos + 1);
        ELSE
            SET temp_str = '';
        END IF;
        SET v_count = v_count + 1;
    END WHILE;

    -- oblicz udział
    SET v_share = ROUND(p_amount / v_count, 2);

    -- dodaj wydatek
    INSERT INTO expenses (group_id, paid_by, amount, description)
    VALUES (p_group_id, p_paid_by, p_amount, p_description);

    SET v_expense_id = LAST_INSERT_ID();

    -- dodaj uczestników i udziały
    SET temp_str = p_participant_ids;
    WHILE LENGTH(temp_str) > 0 DO
        SET v_pos = LOCATE(',', temp_str);
        IF v_pos > 0 THEN
            SET v_id = SUBSTRING(temp_str, 1, v_pos - 1);
            SET temp_str = SUBSTRING(temp_str, v_pos + 1);
        ELSE
            SET v_id = temp_str;
            SET temp_str = '';
        END IF;

        SET v_user_id = CAST(v_id AS UNSIGNED);

        INSERT INTO expense_participants (expense_id, user_id)
        VALUES (v_expense_id, v_user_id);

        INSERT INTO expense_shares (expense_id, user_id, share)
        VALUES (v_expense_id, v_user_id, v_share);
    END WHILE;
END;
//

DELIMITER ;


DELIMITER //

DROP PROCEDURE IF EXISTS create_group;

CREATE PROCEDURE create_group (
    IN p_group_name VARCHAR(100),
    IN p_created_by INT,
    IN p_user_names TEXT -- np. 'alice,bob,carol'
)
BEGIN
    DECLARE v_group_id INT;
    DECLARE v_pos INT DEFAULT 1;
    DECLARE v_user_name TEXT;
    DECLARE temp_str TEXT;
    DECLARE real_user_id INT;

    -- 1. Dodaj grupę
    INSERT INTO group_table (name, created_by)
    VALUES (p_group_name, p_created_by);

    SET v_group_id = LAST_INSERT_ID();

    -- 2. Dodaj użytkowników do grupy
    SET temp_str = p_user_names;

    WHILE LENGTH(temp_str) > 0 DO
        SET v_pos = LOCATE(',', temp_str);
        IF v_pos > 0 THEN
            SET v_user_name = SUBSTRING(temp_str, 1, v_pos - 1);
            SET temp_str = SUBSTRING(temp_str, v_pos + 1);
        ELSE
            SET v_user_name = temp_str;
            SET temp_str = '';
        END IF;

        -- Szukaj ID po imieniu
        SELECT id INTO real_user_id FROM users WHERE username = v_user_name LIMIT 1;

        IF real_user_id IS NOT NULL THEN
            INSERT INTO group_members (group_id, user_id)
            VALUES (v_group_id, real_user_id);
        END IF;
    END WHILE;
END;
//
DELIMITER ;

DELIMITER //

DROP PROCEDURE IF EXISTS delete_group_by_name;

CREATE PROCEDURE delete_group_by_name(IN p_group_name VARCHAR(100))
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE v_group_id INT;
    DECLARE cur CURSOR FOR
        SELECT id FROM group_table WHERE name = p_group_name;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    -- 1. Otwórz kursor i przejdź po każdej pasującej grupie
    OPEN cur;

    read_loop: LOOP
        FETCH cur INTO v_group_id;
        IF done THEN
            LEAVE read_loop;
        END IF;

        -- 2. Usuń powiązanych członków
        DELETE FROM group_members WHERE group_id = v_group_id;

        -- 3. Usuń grupę
        DELETE FROM group_table WHERE id = v_group_id;
    END LOOP;

    CLOSE cur;
END;
//

DELIMITER ;


DELIMITER //

DROP PROCEDURE IF EXISTS delete_group_by_id;

CREATE PROCEDURE delete_group_by_id(IN p_group_id INT)
BEGIN
    -- Usuń powiązanych członków
    DELETE FROM group_members WHERE group_id = p_group_id;

    -- Usuń grupę
    DELETE FROM group_table WHERE id = p_group_id;
END;
//

DELIMITER ;



DELIMITER //

DROP PROCEDURE IF EXISTS delete_expense_by_name;

CREATE PROCEDURE delete_expense_by_name (
    IN p_description VARCHAR(255)
)
BEGIN
    DECLARE v_expense_id INT;

    -- Znajdź ID wydatku na podstawie opisu
    SELECT id INTO v_expense_id
    FROM expenses
    WHERE description = p_description
    LIMIT 1;

    -- Usuń, jeśli znaleziono
    IF v_expense_id IS NOT NULL THEN
        DELETE FROM expense_shares WHERE expense_id = v_expense_id;
        DELETE FROM expense_participants WHERE expense_id = v_expense_id;
        DELETE FROM expenses WHERE id = v_expense_id;
    END IF;
END;
//

DELIMITER ;


DELIMITER //

DROP PROCEDURE IF EXISTS delete_expense_by_id;

CREATE PROCEDURE delete_expense_by_id (
    IN p_expense_id INT
)
BEGIN
    DELETE FROM expense_shares WHERE expense_id = p_expense_id;
    DELETE FROM expense_participants WHERE expense_id = p_expense_id;
    DELETE FROM expenses WHERE id = p_expense_id;
END;
//

DELIMITER ;



