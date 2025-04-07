#bilans rozliczeń w grupie
CREATE OR REPLACE VIEW view_group_balances AS
SELECT g.id            AS group_id,
       u_from.username AS from_user,
       u_to.username   AS to_user,
       SUM(p.amount)   AS balance_due
FROM payments p
         JOIN group_table g ON p.group_id = g.id
         JOIN users u_from ON p.from_user = u_from.id
         JOIN users u_to ON p.to_user = u_to.id
WHERE p.status != 'completed'
GROUP BY g.id, p.from_user, p.to_user;

#Historia wydatkow w grupie
CREATE OR REPLACE VIEW view_group_expenses_details AS
SELECT g.id        AS group_id,
       g.name      AS group_name,
       e.id        AS expense_id,
       e.description,
       e.amount,
       u.username  AS paid_by,
       ep.user_id  AS participant_id,
       u2.username AS participant_name,
       es.share
FROM expenses e
         JOIN group_table g ON e.group_id = g.id
         JOIN users u ON e.paid_by = u.id
         JOIN expense_participants ep ON ep.expense_id = e.id
         JOIN users u2 ON ep.user_id = u2.id
         JOIN expense_shares es ON es.expense_id = e.id AND es.user_id = ep.user_id;
