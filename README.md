# Operating_System
College Project on implementing scheduling

# Question for the code is
Sudesh Sharma is a Linux expert who wants to have an online system where he can 
handle student queries. Since there can be multiple requests at any time he wishes to dedicate 
a fixed amount of time to every request so that everyone gets a fair share of his time. He will 
log into the system from 10am to 12am only. He wants to have separate requests queues for 
students and faculty. Implement a strategy for the same. The summary at the end of the 
session should include the total time he spent on handling queries and average query time.

# Explation of the problem
In this problem we were asked to make a system which will handle the multiple request which can have any arrival time but the arrival time must be from 10:00 am to 12:00 am which means 14 hrs. is dedicated to handle the queries of both faculties and students. As Sudesh want to gives the fixed amount to every request as he want to give the fair share of time to each query so we have to use Round-Robin algorithm with time quantum equal to time he want to give to each query. In round robin we give each request an equal share of time after at that time give the chance to the next request if any other request is available for the time equal to quantum time if burst time is greater than the time quantum else it will run for time equal to its burst time.
In this we were also asked to maintain two queue one for student query and one for faculty query. If we have the query of both faculty and student arrive at same time then we give the preference to the faculty then student
