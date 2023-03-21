-- Keep a log of any SQL queries you execute as you solve the mystery.
--DB内のテーブルをリストアップする
.tables
--airports              crime_scene_reports   people
--atm_transactions      flights               phone_calls
--bakery_security_logs  interviews
--bank_accounts         passengers
--schemaで各テーブル内の項目をリストアップ。
.schema crime_scene_reports
--  id INTEGER,
--  year INTEGER,
--  month INTEGER,
--  day INTEGER,
--  street TEXT,
--  description TEXT,
--  PRIMARY KEY(id)
.schema airports
--  id INTEGER,
--  abbreviation TEXT,
--  full_name TEXT,
--  city TEXT,
--  PRIMARY KEY(id)
.schema people
--  id INTEGER,
--  name TEXT,
--  phone_number TEXT,
--  passport_number INTEGER,
--  license_plate TEXT,
--  PRIMARY KEY(id)
.schema flights
--   id INTEGER,
--  origin_airport_id INTEGER,
--  destination_airport_id INTEGER,
--  year INTEGER,
--  month INTEGER,
--  day INTEGER,
--  hour INTEGER,
--  minute INTEGER,
--  PRIMARY KEY(id),
--  FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--  FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
.schema phone_calls
--   id INTEGER,
--  caller TEXT,
--  receiver TEXT,
--  year INTEGER,
--  month INTEGER,
--  day INTEGER,
--  duration INTEGER,
--  PRIMARY KEY(id)
.schema atm_transactons
--  id INTEGER,
--  account_number INTEGER,
--  year INTEGER,
--  month INTEGER,
--  day INTEGER,
--  atm_location TEXT,
--  transaction_type TEXT,
--  amount INTEGER,
--  PRIMARY KEY(id)
.schema bakery_security_logs
--   id INTEGER,
--  year INTEGER,
--  month INTEGER,
--  day INTEGER,
--  hour INTEGER,
--  minute INTEGER,
--  activity TEXT,
--  license_plate TEXT,
--  PRIMARY KEY(id)
.schema interviews
--   id INTEGER,
--  name TEXT,
--  year INTEGER,
--  month INTEGER,
--  day INTEGER,
--  transcript TEXT,
--  PRIMARY KEY(id)
.schema bank_accounts
--   account_number INTEGER,
--  person_id INTEGER,
--  creation_year INTEGER,
--  FOREIGN KEY(person_id) REFERENCES people(id)
.schema passengers
--   flight_id INTEGER,
--  passport_number INTEGER,
--  seat TEXT,
--  FOREIGN KEY(flight_id) REFERENCES flights(id)

--crime_scene_report, flights, phone_calls, atm_transactions,
--bakery_security_logs, interviewの6テーブル間でyear, month, dayが共通。

SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Humphrey Street";
--Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted today with three witnesses who were present at the time– each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.

SELECT transcript FROM interviews WHERE month = 7 AND day = 28;
--Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away.
--If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.

-- I don't know the thief's name, but it was someone I recognized.
-- Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.

-- As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
-- In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
-- The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT license_plate,minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND activity = "exit";
+---------------+--------+ベーカリーから出た車のナンバープレート。偶然だが全て事件から10分以内。
| license_plate | minute |
+---------------+--------+
| 5P2BI95       | 16     |
| 94KL13X       | 18     |
| 6P58WS2       | 18     |
| 4328GD8       | 19     |
| G412CB7       | 20     |
| L93JTIZ       | 21     |
| 322W7JE       | 23     |
| 0NTHK55       | 23     |
| 1106N58       | 35     |
+---------------+--------+
SELECT account_number FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
| 28500762       |--事件のあった時間帯にATMからお金を引き下ろしたアカウント番号
| 28296815       |
| 76054385       |
| 49610011       |
| 16153065       |
| 25506511       |
| 81061156       |
| 26013199       |
 SELECT id,origin_airport_id,destination_airport_id,hour,minute FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
+----+-------------------+------------------------+------+--------+事件が起きた次の日のフライトのidと出発地の空港のidと行先の空港のidと空港を出た時と分
| id | origin_airport_id | destination_airport_id | hour | minute |
+----+-------------------+------------------------+------+--------+多分origin_airport_idがすべて８で同じ場所なので８はフィフティヴィルを示すid
| 36 | 8                 | 4                      | 8    | 20     |
| 43 | 8                 | 1                      | 9    | 30     |
| 23 | 8                 | 11                     | 12   | 15     |
| 53 | 8                 | 9                      | 15   | 20     |
| 18 | 8                 | 6                      | 16   | 0      |
+----+-------------------+------------------------+------+--------+
SELECT id,abbreviation,full_name,city FROM airports WHERE id = 8 OR id = 4 OR id = 1 OR id = 11 OR id = 9 OR id = 6;
+----+--------------+-------------------------------------+---------------+
| id | abbreviation |              full_name              |     city      |
+----+--------------+-------------------------------------+---------------+出発地はフィフティヴィル
| 1  | ORD        --| O'Hare International Airport        | Chicago       |
| 4  | LGA          | LaGuardia Airport                   | New York City |
| 6  | BOS          | Logan International Airport         | Boston        |
| 8  | CSF          | Fiftyville Regional Airport         | Fiftyville    |
| 9  | HND          | Tokyo International Airport         | Tokyo         |
| 11 | SFO          | San Francisco International Airport | San Francisco |
+----+--------------+-------------------------------------+---------------+
SELECT person_id,account_number FROM bank_accounts WHERE account_number = "28500762" OR account_number = "28296815" OR account_number = "76054385"
OR account_number = "49610011" OR account_number = "16153065" OR account_number = "25506511" OR account_number = "81061156" OR account_number = "26013199";
+-----------+----------------+事件のあった時間帯にATMからお金を引き下ろしたアカウントの持ち主
| person_id | account_number |
+-----------+----------------+
| 686048    | 49610011       |
| 514354    | 26013199       |
| 458378    | 16153065       |
| 395717    | 28296815       |
| 396669    | 25506511       |
| 467400    | 28500762       |
| 449774    | 76054385       |
| 438727    | 81061156       |
+-----------+----------------+
 SELECT name,phone_number FROM people WHERE (id = "686048" OR id = "514354" OR id = "458378" OR id = "395717" OR id = "396669" OR id = "467400" OR id = "449774" OR id = "438727")
   ...> AND (license_plate = "5P2BI95" OR license_plate = "94KL13X" OR license_plate = "6P58WS2" OR LICENSE_PLATE = "4328GD8"
   ...> OR license_plate = "G412CB7" OR license_plate = "L93JTIZ" OR license_plate = "322W7JE" OR license_plate = "0NTHK55" OR license_plate = "1106N58");
+--------+----------------+事件後にベーカリーを出た車の持ち主かつ事件のあった時間帯にATMをお金を引き下ろした人間の名前と電話番号
|  name  |  phone_number  |
+--------+----------------+
| Iman   | (829) 555-5269 |
| Taylor | (286) 555-6063 |
| Luca   | (389) 555-5198 |
| Diana  | (770) 555-1861 |
| Bruce  | (367) 555-5533 |
+--------+----------------+
 SELECT passengers.passport_number, people.name FROM passengers INNER JOIN people ON passengers.passport_number = people.passport_number WHERE flight_id = "36";
+-----------------+--------+次の日の一番最初の便に乗っていた人の名前とパスポートの番号
| passport_number |  name  |
+-----------------+--------+
| 7214083635      | Doris  |
| 1695452385      | Sofia  |
| 5773159633      | Bruce  |
| 1540955065      | Edward |
| 8294398571      | Kelsey |
| 1988161715      | Taylor |
| 9878712108      | Kenny  |
| 8496433585      | Luca   |
+-----------------+--------+
CREATE TABLE yougisya_number AS SELECT name,phone_number FROM people
WHERE (id = "686048" OR id = "514354" OR id = "458378" OR id = "395717" OR id = "396669" OR id = "467400" OR id = "449774" OR id = "438727")
AND (license_plate = "5P2BI95" OR license_plate = "94KL13X" OR license_plate = "6P58WS2" OR LICENSE_PLATE = "4328GD8"
OR license_plate = "G412CB7" OR license_plate = "L93JTIZ" OR license_plate = "322W7JE" OR license_plate = "0NTHK55" OR license_plate = "1106N58");

CREATE TABLE yougisya_passport AS SELECT passengers.passport_number, people.name
FROM passengers INNER JOIN people ON passengers.passport_number = people.passport_numberWHERE flight_id = "36";
--犯人を絞り込む為にテーブルを２つ作成
 SELECT yougisya_number.phone_number, yougisya_number.name, yougisya_passport.passport_number FROM yougisya_number INNER JOIN yougisya_passport
 ON yougisya_number.name = yougisya_passport.name;
 +----------------+--------+-----------------+容疑者は３人まで絞られた。
|  phone_number  |  name  | passport_number |
+----------------+--------+-----------------+
| (286) 555-6063 | Taylor | 1988161715      |
| (389) 555-5198 | Luca   | 8496433585      |
| (367) 555-5533 | Bruce  | 5773159633      |
+----------------+--------+-----------------+
SELECT caller,receiver,duration FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28
AND (caller = "(286) 555-6063" OR caller = "(389) 555-5198" OR caller = "(367) 555-5533") ORDER BY duration;
+----------------+----------------+----------+2021年７月２８日に容疑者３人が掛けた電話と電話先と通話時間を通話時間順に並べた。
|     caller     |    receiver    | duration |--証言によると通話時間は１分足らず。1分未満で１分に一番近いのは上から２つ目。
+----------------+----------------+----------+２つ目の電話番号はBruceの電話番号。よって犯人はBruce。
| (286) 555-6063 | (676) 555-6554 | 43       |
| (367) 555-5533 | (375) 555-8161 | 45       |
| (367) 555-5533 | (704) 555-5790 | 75       |
| (367) 555-5533 | (344) 555-9601 | 120      |
| (286) 555-6063 | (310) 555-8568 | 235      |
| (367) 555-5533 | (022) 555-4052 | 241      |
+----------------+----------------+----------+
 SELECT id,origin_airport_id,destination_airport_id,hour,minute FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour;
+----+-------------------+------------------------+------+--------+
| id | origin_airport_id | destination_airport_id | hour | minute |
+----+-------------------+------------------------+------+--------+
| 36 | 8                 | 4                      | 8    | 20     |
| 43 | 8                 | 1                      | 9    | 30     |
| 23 | 8                 | 11                     | 12   | 15     |
| 53 | 8                 | 9                      | 15   | 20     |
| 18 | 8                 | 6                      | 16   | 0      |
+----+-------------------+------------------------+------+--------+
SELECT id,abbreviation,full_name,city FROM airports WHERE id = 8 OR id = 4 OR id = 1 OR id = 11 OR id = 9 OR id = 6;
+----+--------------+-------------------------------------+---------------+
| id | abbreviation |              full_name              |     city      |
+----+--------------+-------------------------------------+---------------+
| 1  | ORD        --| O'Hare International Airport        | Chicago       |
| 4  | LGA          | LaGuardia Airport                   | New York City |
| 6  | BOS          | Logan International Airport         | Boston        |
| 8  | CSF          | Fiftyville Regional Airport         | Fiftyville    |
| 9  | HND          | Tokyo International Airport         | Tokyo         |
| 11 | SFO          | San Francisco International Airport | San Francisco |
+----+--------------+-------------------------------------+---------------+
--既に実行済みの２文の結果より逃走先の町はNew York City
 SELECT name FROM people WHERE phone_number = "(375) 555-8161";
 +-------+
| name  |
+-------+
| Robin |
+-------+Bruceと電話していた犯人の名前をpeopleから検索。Robinと判明。