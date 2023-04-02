-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Checking the crime scene reports for the duck robbery on 28th July 2021 on Humphrey Street.
SELECT * FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Information gained: Time: 10:15 am, Place: Humphrey Street Bakery, 3 Interviews mentioning Bakery.

-- Checking interviews for any evidence.
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28 AND transcript like '%bakery%';
-- Information gained:
    -- Ruth: Within 10 minutes of robbery thief left in car from parking lot - check footage of driveway and parking lot.
    -- Eugene: Suspect was at ATM earlier that morning on Leggett Street withdrawing money.
    -- Raymond: Suspect was on call for less than a minute after robbery, leaving on earliest flight tomorow and suspect's accomplice booking ticket.

-- Checking bakery security logs to locate car that suspect escaped in.
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit';
-- Potential Car Plate Number acquired.

-- Checking ATM transactions for the morning at Legget Street.
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- Potential Account number acquired.

-- Checking phone logs lasting less than a minute on day of crime.
SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60;
-- Potential Caller and receiver number acquired.

-- Getting first flight out of fiftyville on following day of crime.
SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour ASC, minute ASC LIMIT 1;
-- Flight id of first flight out of fifty ville acquired.

-- Getting information of all passengers on the flight.
SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour ASC, minute ASC LIMIT 1);
-- List of passenger passport numbers acquired.

-- Checking the people table for a list of suspects with list of phone numbers, number plates and Passport numbers.
SELECT id, name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60)
AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour ASC, minute ASC LIMIT 1))
AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit');
-- Sophia, Kelsey and Bruce are the suspects.

-- Comparing bank account numbers with people obtained.
SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw');


-- Getting common culprit from both lists.
SELECT name FROM people
WHERE id IN (
    SELECT id FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60)
    AND passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour ASC, minute ASC LIMIT 1))
    AND license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25) AND activity = 'exit')
)
AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
-- Bruce is the criminal.

-- Using Flight id - 36 to get destination.
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);

-- Using phone call to get phone number of accomplice.
SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60
AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce');

-- Using phone number to get name.
SELECT name FROM people WHERE phone_number = (
    SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 and duration < 60
    AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
);