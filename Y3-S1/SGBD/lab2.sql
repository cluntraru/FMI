--DECLARE
--    TYPE emp_record IS RECORD (
--        cod employees.employee_id%TYPE,
--        salariu employees.salary%TYPE,
--        job employees.job_id%TYPE
--    );
--    v_ang emp_record;
--BEGIN
----    1. b)
--    SELECT employee_id, salary, job_id
--    INTO v_ang
--    FROM employees
--    WHERE employee_id = 101;
--
----    1. c)
----    DELETE FROM emp_c
----    WHERE employee_id = 100
----    RETURNING employee_id, salary, job_id INTO v_ang;
--    
----    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || v_ang.cod || ' si jobul ' ||
----                        v_ang.job || ' are salariul ' || v_ang.salariu);
--END;
--
--
--DECLARE
--    ang0    employees%ROWTYPE;
--    ang1    employees%ROWTYPE;
--BEGIN
--    DELETE FROM emp_c
--    WHERE employee_id = 101
--    RETURNING employee_id, salary, job_id INTO ang0;
--    
--    DBMS_OUTPUT.PUT_LINE('Angajatul cu codul ' || ang0.cod || ' si jobul ' ||
--                        ang0.job || ' are salariul ' || ang0.salariu);
--END;

--4.
--DECLARE
--    TYPE arry IS TABLE OF NUMBER INDEX BY PLS_INTEGER;
--    t arry;
--BEGIN
----    a)
--    FOR i in 1..10 LOOP
--        t(i) := i;
--    END LOOP;
----    
--    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
----    
--    FOR i in t.FIRST..t.LAST LOOP
--        DBMS_OUTPUT.PUT(t(i) || ' ');
--    END LOOP;
----    
--    DBMS_OUTPUT.NEW_LINE;
--    
----    b)
----    FOR i in t.FIRST..t.LAST LOOP
----        IF i MOD 2 = 1 THEN
----            t(i) := NULL;
----        END IF;
----    END LOOP;
----    
----    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
----    
----    FOR i in t.FIRST..t.LAST LOOP
----        DBMS_OUTPUT.PUT(t(i) || ' ');
----    END LOOP;
----    
----    DBMS_OUTPUT.NEW_LINE;
--    
----    c)
--    t.DELETE(2);
----    t.DELETE(t.FIRST);
----    t.DELETE(t.LAST);
--    
--    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
--
--    FOR i in t.FIRST..t.LAST LOOP
--        DBMS_OUTPUT.PUT(t(i) || ' ');
--    END LOOP;
--    
--    DBMS_OUTPUT.NEW_LINE;
--END;

--6
--DECLARE
--    TYPE tablou_imbricat IS TABLE OF NUMBER;
--    t tablou_imbricat := tablou_imbricat();
--BEGIN
----    a)
--    FOR i IN 1..10 LOOP
--        t.EXTEND;
--        t(i) := i;
--    END LOOP;
--    
--    DBMS_OUTPUT.PUT('Tabloul are ' || t.COUNT || ' elemente: ');
--    FOR i IN t.FIRST..t.LAST LOOP
--        DBMS_OUTPUT.PUT(t(i) || ' ');
--    END LOOP;
--    
--END;
