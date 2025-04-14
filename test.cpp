#include <iostream>
#include <string>
#include <conio.h>     
using namespace std;

// int compareDate(Date bookDue) {
//     int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//     int daysOverdue = 0;
// }

//     // year is different 
//     // Part A: Days remaining in due month
//     int daysInDueMonth = daysInMonth[bookDue.mm - 1];
//     if (bookDue.mm == 2 && isLeapYear(bookDue.yy)) {
//         daysInDueMonth = 29;
//     }
//     daysOverdue = daysInDueMonth - bookDue.dd;

//     // Part B: Remaining months in due year
//     for (int month = bookDue.mm + 1; month <= 12; month++) {
//         daysOverdue += daysInMonth[month - 1];
//         if (month == 2 && isLeapYear(bookDue.yy)) {
//             daysOverdue += 1;
//         }
//     }

//     // Part C: Full years between due year and current year
//     for (int year = bookDue.yy + 1; year < dateTodayVar.yy; year++) {
//         if (isLeapYear(year)) {
//             daysOverdue += 366;
//         } else {
//             daysOverdue += 365;
//         }
//     } 

//     // Part D: Months in current year before current month
//     for (int month = 1; month < dateTodayVar.mm; month++) {
//         daysOverdue += daysInMonth[month - 1];
//         if (month == 2 && isLeapYear(dateTodayVar.yy)) {
//             daysOverdue += 1;
//         }
//     }

//     // Part E: Days in current month
//     daysOverdue += dateTodayVar.dd;

//     return daysOverdue;
// }