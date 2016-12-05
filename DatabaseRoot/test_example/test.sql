CREATE DATABASE orderDB
DROP DATABASE orderDB
SHOW DATABASES
USE orderDB
SHOW TABLES
CREATE TABLE customer(id int(10) NOT NULL,name char(25) NOT NULL,gender char(1) NOT NULL,PRIMARY KEY(id))
DROP TABLE customer
DESC customer
INSERT INTO customer VALUES (300001, 'CHAD CABELLO', 'F')
INSERT INTO orders VALUES (315000,200001,'eight')
DELETE FROM publisher WHERE state='CA'
UPDATE book SET title='Nine Times Nine' WHERE authors='Anthony Boucher'
SELECT * FROM publisher WHERE nation='CA'
SELECT title FROM book WHERE authors is null
SELECT book.title,orders.quantity FROM book,orders WHERE book.id=orders.book_id AND orders.quantity>8
CREATE INDEX customer(name)
DROP INDEX customer(name)
CREATE TABLE customer (id int(10) NOT NULL,name char(25) NOT NULL,gender char(1) NOT NULL,CHECK (gender in('F','M')),PRIMARY KEY (id));
UPDATE book SET publisher_id='106001' WHERE title=' Standing in the Shadows'
SELECT title,authors FROM book WHERE authors like '%David%'
SELECT customer.name,book.title,orders.quantity FROM customer,book,orders WHERE orders.customer_id=customer.id AND orders.book_id=book.id AND orders.quantity > 9
SELECT SUM(quantity) FROM orders
SELECT AVG(quantity) FROM orders
SELECT MAX(quantity) FROM orders
SELECT MIN(quantity) FROM orders
SELECT customer_id,SUM(quantity) FROM orders GROUP BY customer_id