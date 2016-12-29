1. 

INSERT INTO customer VALUES (300001, 'CHAD CABELLO', 'F');
#在customer表中插入一条数据(300001, CHAD CABELLO, ‘F’)。如果主键出现重复，应报错，阻止插入数据。

2. 

INSERT INTO orders VALUES (315000,200001,'eight');
#orders表的quantity字段的数据类型为整型，出现该语句应报错，提示quantity字段数据类型必须是整型，阻止插入数据。

3.

SELECT * FROM publisher WHERE state='CA';
DELETE FROM publisher WHERE state='CA';
#删除所有加州的出版商。
SELECT * FROM publisher WHERE state='CA';
SELECT * FROM publisher;

4. 

SELECT * from book where authors= 'Anthony Boucher';
UPDATE book SET title='Nine Times Nine' WHERE authors='Anthony Boucher';
#把作者Anthony Boucher的书的书名改为Nine Times Nine。
SELECT * from book where authors='Anthony Boucher';

5.

SELECT * FROM publisher WHERE state='CA';

6.

SELECT title FROM book WHERE authors is null;
#列出authors字段为空的记录的书名。
select * from book where title = 'Anyone Can Have a Happy';

7.

SELECT book.title,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8;
#列出订购数大于8本的书的书名以及相应的订购数量。



#EXPAND 
8. 

CREATE INDEX customer(name);
DROP INDEX customer(name);

9.

SELECT customer.name,book.title,orders.quantity FROM customer,book,orders WHERE orders.customer_id=customer.id AND orders.book_id=book.id AND orders.quantity > 9;
#列出订购数量大于9的订单中顾客的姓名、书名以及相应的订购数量。

10. 

drop table customer;

CREATE TABLE customer (
	id int(10) NOT NULL,
	name char(25) NOT NULL,
	gender char(1) NOT NULL,
	CHECK (gender in('F','M')),
	PRIMARY KEY (id)
);



#success
INSERT INTO customer VALUES (300001,'CHAD CABELLO','F');
SELECT * from customer;
#error 'S' not checked
INSERT INTO customer VALUES (300002,'CHAD CABELLO','S');
SELECT * from customer;

11.

SELECT title,authors FROM book WHERE authors like '%David%';

12.

SELECT SUM(quantity) FROM orders;# 求出所有订单的订购总量。
SELECT AVG(quantity) FROM orders;# 求出每个订单的平均订购量。
SELECT MAX(quantity) FROM orders;# 求出所有订单中最大订购量。
SELECT MIN(quantity) FROM orders;# 求出所有订单中最小订购量。

13.

SELECT customer_id,SUM(quantity) FROM orders GROUP BY customer_id;# 求出所有订单中每个顾客订购书的总量。
SELECT customer_id,SUM(quantity) FROM orders GROUP BY quantity;# 求出所有订单中每个顾客订购书的总量。
SELECT publisher_id,title,authors,AVG(copies) FROM book GROUP BY publisher_id;

