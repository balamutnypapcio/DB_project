DELIMITER //
CREATE TRIGGER check_expense_completion
    AFTER INSERT
    ON payments
    FOR EACH ROW
BEGIN
    DECLARE total_share DECIMAL(10, 2);
    DECLARE total_paid DECIMAL(10, 2);

    -- Oblicz sumę udziałów w danym wydatku
    SELECT SUM(share)
    INTO total_share
    FROM expense_shares es
             JOIN expenses e ON es.expense_id = e.id
    WHERE e.group_id = NEW.group_id;

    -- Oblicz sumę zapłaconych już płatności w grupie
    SELECT SUM(amount)
    INTO total_paid
    FROM payments
    WHERE group_id = NEW.group_id
      AND status = 'completed';

    -- Jeśli wyrównane, zaktualizuj wszystkie płatności jako completed
    IF total_share <= total_paid THEN
        UPDATE payments
        SET status = 'completed'
        WHERE group_id = NEW.group_id;
    END IF;
END;
//
DELIMITER ;

DELIMITER //

CREATE TRIGGER anonimize_user_data_after_delete
AFTER UPDATE ON users
FOR EACH ROW
BEGIN
    IF NEW.is_deleted = TRUE AND OLD.is_deleted = FALSE THEN
        -- Anonimizuj dane użytkownika
        UPDATE users
        SET 
            username = CONCAT('anon_user_', NEW.id),
            email = CONCAT('anon', NEW.id, '@example.com'),
            hashed_password = 'deleted_user',
            created_at = OLD.created_at -- zachowaj datę rejestracji
        WHERE id = NEW.id;
    END IF;
END;
//

DELIMITER ;
