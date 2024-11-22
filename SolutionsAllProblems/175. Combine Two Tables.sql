-- problem : https://leetcode.com/problems/combine-two-tables/description/
-- submission : https://leetcode.com/problems/combine-two-tables/submissions/1459989434
-- solution post: https://leetcode.com/problems/combine-two-tables/solutions/6071936/postgresql-efficient-readable-code


-- Write your PostgreSQL query statement below
-- runtime 242 ms, beats 92.84 %
-- memory 0.00 mb, beats 100.00 %
SELECT P.firstName, P.lastName, A.city, A.state
FROM Person P LEFT JOIN Address A ON P.personId = A.personId
;
