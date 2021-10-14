-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM interviews WHERE year = 2020 AND day = 28 AND month = 7;
SELECT activity, license_plate, hour, minute FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;
-- possible thief's license
exit | 5P2BI95 | 10 | 16
exit | 94KL13X | 10 | 18
exit | 6P58WS2 | 10 | 18
exit | 4328GD8 | 10 | 19
exit | G412CB7 | 10 | 20
exit | L93JTIZ | 10 | 21
exit | 322W7JE | 10 | 23
exit | 0NTHK55 | 10 | 23
exit | 1106N58 | 10 | 35
--interviews
161 | Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away.
If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
162 | Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the
courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
163 | Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute.
In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked
the person on the other end of the phone to purchase the flight ticket.
SELECT people.id FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.person_id = atm_transactions.id
WHERE person_id IN
(SELECT atm_transactions.id 
WHERE atm_location = "Fifer Street" AND year = 2020 AND month = 7 AND day = 28);

SELECT account_number, transaction_type FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

28500762 | withdraw
28296815 | withdraw
76054385 | withdraw
49610011 | withdraw
16153065 | withdraw
86363979 | deposit
25506511 | withdraw
81061156 | withdraw
26013199 | withdraw

SELECT people.id FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN
(SELECT atm_transactions.account_number FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street");

SELECT license_plate FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN
(SELECT atm_transactions.account_number FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street");

SELECT * FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE bank_accounts.account_number IN
(SELECT atm_transactions.account_number FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street");

possible suspects:
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X | 49610011 | 686048 | 2010 | 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
id | name | phone_number | passport_number | license_plate | account_number| creation_year | id | account_number | year | month | day | atm_location | transaction_type | amount
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8 | 28500762 |     | 2014 | 246 |       28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48

SELECT people.id
FROM people
JOIN phone_calls ON people.id = phone_calls.id
WHERE day = 28 AND year = 2020 AND month = 7;
caller         |        reciever
(609) 555-5876 | (389) 555-5198 | 60

(544) 555-8087 | (389) 555-5198 | 595
ERNEST
(367) 555-5533 | (375) 555-8161 | 45

SELECT origin_airport_id, destination_airport_id, hour, minute FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN airports ON origin_airport_id = airports.id
WHERE day = 29 AND airports.id = 8;