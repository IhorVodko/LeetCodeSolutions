-- problem : https://leetcode.com/problems/rising-temperature/
-- submission : https://leetcode.com/problems/rising-temperature/submissions/1460045430
-- solution post: https://leetcode.com/problems/rising-temperature/solutions/6072158/postgresql-efficient-readable-code


-- Write your PostgreSQL query statement below
-- runtime 267 ms, beats 56.98 %
-- memory 0.00 mb, beats 100.00 %
SELECT W2.id
FROM Weather W1, Weather W2
WHERE W2.recordDate - W1.recordDate = 1 AND W2.temperature > W1.temperature;
