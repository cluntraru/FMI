--1
CREATE OR REPLACE TRIGGER trig1
    BEFORE UPDATE OR INSERT OR DELETE ON emp_c
BEGIN
    IF (TO_CHAR(SYSDATE, 'D') = 1) OR (TO_CHAR(SYSDATE, 'HH24') NOT BETWEEN 8 AND 20)
    THEN
        RAISE_APPLICATION_ERROR(-20001, 'Tabelul nu poate fi actualizat');
    END IF;
END;
/

DROP TRIGGER trig1;


CREATE OR REPLACE TRIGGER trig2
    BEFORE UPDATE OF salary ON emp_c
    FOR EACH ROW
BEGIN
    IF (:NEW.salary < :OLD.salary) THEN
        RAISE_APPLICATION_ERROR(-20002, 'Salariul nu poate fi micsorat');
    END IF;
END;
/

UPDATE emp_c
SET salary = salary-100
WHERE last_name = 'Lee';
/

--3
CREATE OR REPLACE TRIGGER trig3
    BEFORE UPDATE OF lowest_sal, highest_sal ON job_grades_c
    FOR EACH ROW
    WHEN ((OLD.grade_level = 1 AND NEW.lowest_sal > OLD.lowest_sal) OR (OLD.grade_level = 7 AND NEW.highest_sal < OLD.highest_sal))
DECLARE
    min_sal employees.salary%TYPE;
    max_sal employees.salary%TYPE;
BEGIN
    SELECT MIN(salary) INTO min_sal FROM employees;
    SELECT MAX(salary) INTO max_sal FROM employees;
    
    IF min_sal < :NEW.lowest_sal OR max_sal > :NEW.highest_sal THEN
        RAISE_APPLICATION_ERROR(-20002, 'Interval gresit');
    END IF;
END;
/

UPDATE job_grades_c
SET lowest_sal = 30000
WHERE grade_level = 1;
/