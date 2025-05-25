DELIMITER //

CREATE PROCEDURE add_expense_to_group (
    IN p_group_id INT,
    IN p_paid_by INT,
    IN p_amount DECIMAL(10,2),
    IN p_description VARCHAR(255),
    IN p_participants_shares TEXT -- np. '5:40,6:40,7:40'
)
BEGIN
    DECLARE v_expense_id INT;
    DECLARE v_pos INT DEFAULT 1;
    DECLARE v_part TEXT;
    DECLARE v_user_id INT;
    DECLARE v_share DECIMAL(10,2);

    -- 1. Dodaj wydatek
    INSERT INTO expenses (group_id, paid_by, amount, description)
    VALUES (p_group_id, p_paid_by, p_amount, p_description);

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

        SET v_user_id = SUBSTRING_INDEX(v_part, ':', 1);
        SET v_share = SUBSTRING_INDEX(v_part, ':', -1);

        INSERT INTO expense_participants (expense_id, user_id)
        VALUES (v_expense_id, v_user_id);

        INSERT INTO expense_shares (expense_id, user_id, share)
        VALUES (v_expense_id, v_user_id, v_share);
    END WHILE;
END;
//

DELIMITER ;


DELIMITER //

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

CREATE PROCEDURE create_group (
    IN p_group_name VARCHAR(100),
    IN p_created_by INT,
    IN p_user_ids TEXT -- np. '2,3,4'
)
BEGIN
    DECLARE v_group_id INT;
    DECLARE v_pos INT DEFAULT 1;
    DECLARE v_user_id TEXT;
    DECLARE temp_str TEXT; -- Dodana deklaracja zmiennej temp_str

    -- 1. Dodaj grupę
    INSERT INTO group_table (name, created_by)
    VALUES (p_group_name, p_created_by);

    SET v_group_id = LAST_INSERT_ID();

    -- 2. Dodaj użytkowników do grupy
    SET temp_str = p_user_ids; -- Teraz możemy użyć zadeklarowanej zmiennej
    WHILE LENGTH(temp_str) > 0 DO
        SET v_pos = LOCATE(',', temp_str);
        IF v_pos > 0 THEN
            SET v_user_id = SUBSTRING(temp_str, 1, v_pos - 1);
            SET temp_str = SUBSTRING(temp_str, v_pos + 1);
        ELSE
            SET v_user_id = temp_str;
            SET temp_str = '';
        END IF;

        -- Dodaj do tabeli group_members
        INSERT INTO group_members (group_id, user_id)
        VALUES (v_group_id, CAST(v_user_id AS UNSIGNED));
    END WHILE;
END;
//

DELIMITER ;
