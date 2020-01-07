--1
DECLARE
    v_nume employees.last_name%TYPE := Initcap('&p_nume');
    
    FUNCTION f1 RETURN NUMBER IS
        salariu employees.salary%TYPE;
    BEGIN
        SELECT salary INTO salariu
        FROM employees
        WHERE last_name = v_nume;
        RETURN salariu;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
        WHEN TOO_MANY_ROWS THEN
            DBMS_OUTPUT.PUT_LINE('Prea multi');
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Eroare');
    END f1;
BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || f1);
END;

--2
CREATE OR REPLACE FUNCTION f2
    (v_nume employees.last_name%TYPE DEFAULT 'Bell')
RETURN NUMBER IS
    salariu employees.salary%TYPE;
    BEGIN
        SELECT salary INTO salariu
        FROM employees
        WHERE last_name = v_nume;
        RETURN salariu;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            RAISE_APPLICATION_ERROR(-20000, 'Nu exista ang');
        WHEN TOO_MANY_ROWS THEN
            RAISE_APPLICATION_ERROR(-20001, 'Prea multi ang');
        WHEN OTHERS THEN
            RAISE_APPLICATION_ERROR(-20002, 'Alta err');
END f2;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || f2);
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || f2('Fox'));
END;
/

--3
DECLARE
    v_nume employees.last_name%TYPE := Initcap('&p_nume');
    PROCEDURE p3 IS
        salariu employees.salary%TYPE;
    BEGIN
        SELECT salary INTO salariu
        FROM employees
        WHERE employees.last_name = v_nume;
        DBMS_OUTPUT.PUT_LINE('Salariul este ' || salariu);
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Nu sunt ang');
        WHEN TOO_MANY_ROWS THEN
            DBMS_OUTPUT.PUT_LINE('Prea multi ang');
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Alta err');
    END p3;
BEGIN
    p3;
END;


--4
CREATE OR REPLACE PROCEDURE p4 (v_nume employees.last_name%TYPE DEFAULT 'Lee')
IS
    salariu employees.salary%TYPE;
BEGIN
    SELECT salary INTO salariu
    FROM employees
    WHERE employees.last_name = v_nume;
    DBMS_OUTPUT.PUT_LINE('Salariul este ' || salariu);
END;
/

BEGIN
    p4('Lee');
END;
/

