# Database
The final assignment of the course Yellow belt from Moscow Institute Of Physics And Technology, Yandex and E-Learning Development Fund 

It is needed to develop a database capable of handling the following events:

Add date event - add a pair (date, event) to the database;
Print - print the entire contents of the database;
Find condition - display all records contained in the database that satisfy the condition condition;
Del condition - delete from the database all records that satisfy the condition condition;
Last date - display a record with the last event that happened no later than the given date.

The conditions in the Find and Del commands impose certain restrictions on dates and events, for example:

Find date < 2017-11-06 - find all events that happened before November 6, 2017;
Del event != "holiday" — remove all events from the database, except for "holiday";
Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event" - find all "sport events" that happened in the first half of 2017;
Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event") - remove all "holiday" and "sport event" events that occurred before 2017 from the database.
In commands of both types, conditions can be empty: all events fall under such a condition.

The following programs have been provided: condition_parser.h/cpp; token.h/cpp; main.cpp
