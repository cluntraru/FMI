-- 4
SELECT category, count(*), count(distinct t.title_id)
FROM
    title t,
    rental r
WHERE
    t.title_id = r.title_id
GROUP BY category
HAVING count(*) = (
    SELECT
        max(count(*))
    FROM
        title t,
        rental r
    WHERE
        t.title_id = r.title_id
    GROUP BY
        category
);

-- 5
SELECT
    count(*)
FROM (
    SELECT
        book_date, act_ret_date
    FROM
        RENTAL
    WHERE
        act_ret_date IS NOT NULL
        AND (
            CURRENT_DATE > act_ret_date
            OR
            CURRENT_DATE < book_date
    )
)