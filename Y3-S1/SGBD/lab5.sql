CREATE OR REPLACE PACKAGE pachet1 AS
    FUNCTION f_numar(v_dept departments.department_id%TYPE)
        RETURN NUMBER;
    FUNCTION f_suma(v_dept departments.department_id%TYPE)
        RETURN NUMBER;
END pachet1;
/

CREATE OR REPLACE PACKAGE BODY pachet1 AS
    FUNCTION f_numar(v_dept departments.department_id%TYPE)
        RETURN NUMBER IS numar NUMBER;
    BEGIN
        SELECT COUNT(*) INTO numar
        FROM employees
        WHERE department_id = v_dept;
    RETURN numar;
    END f_numar;

    FUNCTION f_suma(v_dept departments.department_id%TYPE)
        RETURN NUMBER IS suma NUMBER;
    BEGIN
        SELECT SUM(salary + salary * NVL(commission_pct, 0))
        INTO suma
        FROM employees
        WHERE department_id = v_dept;
    RETURN suma;
    END f_suma;
END pachet1;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE('Numarul de salariati e ' || pachet1.f_numar(80));
    DBMS_OUTPUT.PUT_LINE('Suma alocata e ' || pachet1.f_suma(80));
END;
    
    
    
    
    
    
    
    
    
    
    