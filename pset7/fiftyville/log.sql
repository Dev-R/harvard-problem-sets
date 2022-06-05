


                                 












-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Chamberlin Street';

/*
description
Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

New info:
took place at 10:15am at the Chamberlin Street courthouse
three witnesses who were present at the time(10:15am)
each of their interview transcripts mentions the courthouse.
*/

SELECT hour,minute,activity, license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;

/*
activity

hour | minute | activity | license_plate
10 | 8 | entrance | R3G7486 [SUSPECTED]
10 | 14 | entrance | 13FNH73 [SUSPECTED]
10 | 16 | exit | 5P2BI95[SUSPECTED]
10 | 18 | exit | 94KL13X[SUSPECTED]
10 | 18 | exit | 6P58WS2[SUSPECTED]
10 | 19 | exit | 4328GD8[SUSPECTED]
10 | 20 | exit | G412CB7[SUSPECTED]
10 | 21 | exit | L93JTIZ[SUSPECTED]
10 | 23 | exit | 322W7JE[SUSPECTED]
10 | 23 | exit | 0NTHK55[SUSPECTED]
10 | 35 | exit | 1106N58[SUSPECTED]

    --[NOT SUSPECTED]--
10 | 42 | entrance | NRYN856 [NOT SUSPECTED]
10 | 44 | entrance | WD5M8I6 [NOT SUSPECTED]
10 | 55 | entrance | V47T75I  [NOT SUSPECTED]
XXX
New info:

LISTED ABOVE E
*/

SELECT name,year,month, day, transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28;

/*
interviews
name | year | month | day | transcript
---USELESS--
Jose | 2020 | 7 | 28 | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”[NOT SUSPECTED]
Eugene | 2020 | 7 | 28 | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”[NOT SUSPECTED]
Barbara | 2020 | 7 | 28 | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.[NOT SUSPECTED]


--USEFUL
Ruth | 2020 | 7 | 28 | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. 
                      If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.

Eugene | 2020 | 7 | 28 | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.

Raymond | 2020 | 7 | 28 | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. 
                          The thief then asked the person on the other end of the phone to purchase the flight ticket.
                          
New info:

-within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away

-Earlier this morning,I was walking by the ATM on 'Fifer Street; and saw the thief there withdrawing some money.

-As the thief was leaving the courthouse, they called someone who talked to them for less than a minute
  -planning to take the earliest flight out of Fiftyville tomorrow. 
  -The thief then asked the person on the other end of the phone to purchase the flight ticket.
  
  
  Sequence:
  1-Check activity with ten minutes of the theft, list all suspects within 10:15 + 5-25 mins
  2-Check ATM record on 'Fifer Street and check for mathcing suspects
  3-Match account_number with back_accounts database
    -get person_id
     -use person_id to get his name, phone, pass, licence ...
     
*/

SELECT hour,minute,activity, license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;


/*
activity

*1-Check activity with ten minutes of the theft, list all suspects within 10:15 + 5-25 mins

    --[NOT SUSPECTED]--
hour | minute | activity | license_plate
10 | 8 | entrance | R3G7486 [NOT WITHIN TIME-RANGE]
10 | 14 | entrance | 13FNH73 [NOT WITHIN TIME-RANGE]

    --[SUSPECTED]--
10 | 16 | exit | 5P2BI95[SUSPECTED]
10 | 18 | exit | 94KL13X[SUSPECTED]
10 | 18 | exit | 6P58WS2[SUSPECTED]
10 | 19 | exit | 4328GD8[SUSPECTED]
10 | 20 | exit | G412CB7[SUSPECTED]
10 | 21 | exit | L93JTIZ[SUSPECTED]
10 | 23 | exit | 322W7JE[SUSPECTED]
10 | 23 | exit | 0NTHK55[SUSPECTED]

    --[NOT SUSPECTED]--
10 | 35 | exit | 1106N58[NOT WITHIN TIME-RANGE]
XXX
New info:

    --[SUSPECTES]--
10 | 16 | exit | 5P2BI95[SUSPECTED]
10 | 18 | exit | 94KL13X[SUSPECTED]
10 | 18 | exit | 6P58WS2[SUSPECTED]
10 | 19 | exit | 4328GD8[SUSPECTED]
10 | 20 | exit | G412CB7[SUSPECTED]
10 | 21 | exit | L93JTIZ[SUSPECTED]
10 | 23 | exit | 322W7JE[SUSPECTED]
10 | 23 | exit | 0NTHK55[SUSPECTED]

LISTED ABOVE E
*/


SELECT *
FROM atm_transactions
WHERE atm_location = 'Fifer Street' AND  year = 2020 AND month = 7 AND day = 28;


/*
  2-Check ATM record on 'Fifer Street and check for mathcing suspects
  
 *atm_transactions
 
  id | account_number | year | month | day | atm_location | transaction_type | amount
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
275 | 86363979 | 2020 | 7 | 28 | Fifer Street | deposit | 10 [NOT SUSPECTED]
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

    --[SUSPECTES]--
  id | account_number | year | month | day | atm_location | transaction_type | amount
246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35
*/


SELECT * 
FROM bank_accounts 
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = 'Fifer Street' AND  year = 2020 AND month = 7 AND day = 28;


/*
  3-Match account_number with back_accounts database
    3.1-get person_id  < -- [X]
    3.2 -use person_id to get his name, phone, pass, licence ...
    3.3 -use person_id to get license_plate and match license_plate to 28/7
  *bank_accounts
  
    --[SUSPECTES]--
account_number | person_id | creation_year | id | account_number | year | month | day | atm_location | transaction_type | amount
28500762 | 467400 | 2014 | 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
28296815 | 395717 | 2014 | 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
76054385 | 449774 | 2015 | 266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
49610011 | 686048 | 2010 | 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
16153065 | 458378 | 2012 | 269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
86363979 | 948985 | 2010 | 275 | 86363979 | 2020 | 7 | 28 | Fifer Street | deposit | 10
25506511 | 396669 | 2014 | 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
81061156 | 438727 | 2018 | 313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
26013199 | 514354 | 2012 | 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35

    --[MATCHING ACCOUNT NUM SUSPECTES]-
account_number | person_id | creation_year | id | account_number | year | month | day | atm_location | transaction_type | amount
28500762 | 467400 | 2014 | 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
28296815 | 395717 | 2014 | 264 | 28296815 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
76054385 | 449774 | 2015 | 266 | 76054385 | 2020 | 7 | 28 | Fifer Street | withdraw | 60
49610011 | 686048 | 2010 | 267 | 49610011 | 2020 | 7 | 28 | Fifer Street | withdraw | 50
16153065 | 458378 | 2012 | 269 | 16153065 | 2020 | 7 | 28 | Fifer Street | withdraw | 80
25506511 | 396669 | 2014 | 288 | 25506511 | 2020 | 7 | 28 | Fifer Street | withdraw | 20
81061156 | 438727 | 2018 | 313 | 81061156 | 2020 | 7 | 28 | Fifer Street | withdraw | 30
26013199 | 514354 | 2012 | 336 | 26013199 | 2020 | 7 | 28 | Fifer Street | withdraw | 35
*/

SELECT people.*
FROM people 
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = 'Fifer Street' AND  year = 2020 AND month = 7 AND day = 28;

/*
    3.2 -use person_id to get his name, phone, pass, licence ...
    
 *people
id | name | phone_number | passport_number | license_plate
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
948985 | Robert | (098) 555-1164 | 8304650265 | I449449[NOT SUSPECT]
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
458378 | Roy | (122) 555-4581 | 4408372428 | QX4YZN3
395717 | Bobby | (826) 555-1652 | 9878712108 | 30G67EN
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
438727 | Victoria | (338) 555-6650 | 9586786673 | 8X428L0
     
*/
SELECT hour,minute,activity, license_plate
FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;


SELECT people.*
FROM people 
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.atm_location = 'Fifer Street' AND  atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28
AND courthouse_security_logs.hour = 10;
/*
3.3 -use person_id to license_plate and match license_plate to 28/7 in the court house
*people

id | name | phone_number | passport_number | license_plate
686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE
396669 | Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
449774 | Madison | (286) 555-6063 | 1988161715 | 1106N58
     
*/


SELECT DISTINCT phone_calls.caller, phone_calls.receiver, phone_calls.duration, people.*
FROM phone_calls 
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN people ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND duration <= 60
AND (courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 30)
AND courthouse_security_logs.activity = 'exit';


/*

-As the thief was leaving the courthouse, they called someone who talked to them for less than a minute
  -planning to take the earliest flight out of Fiftyville tomorrow. 
  
  -The thief then asked the person on the other end of the phone to purchase the flight ticket
  
 4.0-Use people phone_number to access phone_calls on 28/07/28 within time range
  4.1-Check for phone calls less than 1 min
  
  
caller | receiver | id | name | phone_number | passport_number | license_plate
(130) 555-0289 | (996) 555-8899 | 51 | 398010 | Roger | (130) 555-0289 | 1695452385 | G412CB7
(499) 555-9472 | (892) 555-8872 | 36 | 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55
(367) 555-5533 | (375) 555-8161 | 45 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X
(609) 555-5876 | (389) 555-5198 | 60 | 561160 | Kathryn | (609) 555-5876 | 6121106406 | 4ZY7I8T
(499) 555-9472 | (717) 555-1342 | 50 | 560886 | Evelyn | (499) 555-9472 | 8294398571 | 0NTHK55[DUPLICATED]
(770) 555-1861 | (725) 555-3243 | 49 | 514354 | Russell | (770) 555-1861 | 3592750733 | 322W7JE


*/


SELECT DISTINCT phone_calls.caller ,phone_calls.receiver, phone_calls.duration, people.*
FROM phone_calls 
JOIN people ON phone_calls.receiver = people.phone_number
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND duration <= 60
AND phone_calls.caller IN
(
SELECT DISTINCT phone_calls.caller
FROM phone_calls 
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN people ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND duration <= 60
AND (courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 30)
AND courthouse_security_logs.activity = 'exit'
)
;


/*
  4.2-Get receiver info:
  ->Use reciever phone -> get his ID,name etc -> access bank_account -> atm transaction(withdraw) -> Check Passengers for matching passports (caller, receiver are both leaveing tmw at 6 - 12 AM)
  .Receiver who made a ticket purchase out of Fiftyville for the earliest flight tmw
  .Receiver had a direct contact with one of the 6 suspects

  
                         --[SUSPECTES]--
                         
caller | receiver | duration | id | name | phone_number | passport_number | license_plate
(130) 555-0289 | (996) 555-8899 | 51 | 567218 | Jack | (996) 555-8899 | 9029462229 | 52R0Y8U
(499) 555-9472 | (892) 555-8872 | 36 | 251693 | Larry | (892) 555-8872 | 2312901747 | O268ZZ0
(367) 555-5533 | (375) 555-8161 | 45 | 864400 | Berthold | (375) 555-8161 |  | 4V16VO0
(609) 555-5876 | (389) 555-5198 | 60 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8
(499) 555-9472 | (717) 555-1342 | 50 | 626361 | Melissa | (717) 555-1342 | 7834357192 | 
(770) 555-1861 | (725) 555-3243 | 49 | 847116 | Philip | (725) 555-3243 | 3391710505 | GW362R6


*/




SELECT DISTINCT phone_calls.caller, phone_calls.receiver, people.*
FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND duration <= 60
AND phone_calls.caller IN
(
SELECT DISTINCT phone_calls.caller
FROM phone_calls 
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN people ON phone_calls.caller = people.phone_number
WHERE (phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60)
AND (courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 30 AND courthouse_security_logs.activity = 'exit')
)
;


/*
  4.2-Get receiver info:
  ->Use reciever phone -> get his ID,name etc -> access bank_account -> atm transaction(withdraw) -> Check Passengers for matching passports (caller, receiver are both leaveing tmw at 6 - 12 AM)

  
                         --[SUSPECTES]--
                         
caller | receiver | id | name | phone_number | passport_number | license_plate | id | account_number | year | month | day | atm_location | transaction_type | amount
(609) 555-5876 | (389) 555-5198 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8 | 246 | 28500762 | 2020 | 7 | 28 | Fifer Street | withdraw | 48
(130) 555-0289 | (996) 555-8899 | 567218 | Jack | (996) 555-8899 | 9029462229 | 52R0Y8U | 273 | 69638157 | 2020 | 7 | 28 | Humphrey Lane | withdraw | 20
(130) 555-0289 | (996) 555-8899 | 567218 | Jack | (996) 555-8899 | 9029462229 | 52R0Y8U | 308 | 69638157 | 2020 | 7 | 28 | Humphrey Lane | deposit | 85

*/


SELECT DISTINCT phone_calls.caller, people.*
FROM phone_calls
JOIN people ON phone_calls.receiver = people.phone_number
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number

--JOINING AIRPORT DATABASE
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN airports ON airports.id =  flights.origin_airport_id 
JOIN flights ON flights.id =  passengers.flight_id 

WHERE (phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60)

AND phone_calls.caller IN
(
SELECT DISTINCT phone_calls.caller
FROM phone_calls 
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN people ON phone_calls.caller = people.phone_number
WHERE (phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60)
AND (courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 30 AND courthouse_security_logs.activity = 'exit')
)
AND 
(
flights.year = 2020 AND flights.month = 7 AND flights.day = 28 + 1 AND (flights.hour >= 1 AND flights.hour <= 12)
)
;



/*
  5.-Identifying accomplice name:
  ->Use reciever phone -> get his ID,name etc -> access bank_account -> atm transaction(withdraw) -> Check Passengers for matching passports (caller, receiver are both leaveing tmw at 6 - 12 AM)
                         --[SUSPECTES]--
caller | id | name | phone_number | passport_number | license_plate
(609) 555-5876 | 467400 | Danielle | (389) 555-5198 | 8496433585 | 4328GD8

*/












SELECT * FROM airports WHERE id IN

(
SELECT DISTINCT destination_airport_id
FROM phone_calls
JOIN people ON phone_calls.caller = people.phone_number
JOIN bank_accounts ON bank_accounts.person_id = people.id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number

--JOINING AIRPORT DATABASE
JOIN passengers ON people.passport_number = passengers.passport_number

JOIN flights ON flights.id =  passengers.flight_id 

WHERE (phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60)

AND phone_calls.caller IN
(
SELECT DISTINCT phone_calls.caller
FROM phone_calls 
JOIN courthouse_security_logs ON courthouse_security_logs.license_plate = people.license_plate
JOIN people ON phone_calls.caller = people.phone_number
WHERE (phone_calls.year = 2020 AND phone_calls.month = 7 AND phone_calls.day = 28 AND phone_calls.duration <= 60)
AND (courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 30 AND courthouse_security_logs.activity = 'exit')
)
AND 
(atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28)
AND 
(
flights.year = 2020 AND flights.month = 7 AND flights.day = 28 + 1 AND (flights.hour >= 1 AND flights.hour <= 12)
)
)
;







/*
  6.-Identifying theif name:
  ->Use reciever phone -> get his ID,name etc -> access bank_account -> atm transaction(withdraw) -> Check Passengers for matching passports (caller, receiver are both leaveing tmw at 6 - 12 AM)
                         --[SUSPECTES]--
caller | id | name | phone_number | passport_number | license_plate
(367) 555-5533 | 686048 | Ernest | (367) 555-5533 | 5773159633 | 94KL13X | 5773159633

*/




/*

The THIEF is: Ernest
The thief ESCAPED TO: London
The ACCOMPLICE is: Danielle



*/


