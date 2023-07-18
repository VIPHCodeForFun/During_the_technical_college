# Information about labor delivery

According to the laboratory, only Assingment A must be made for the delivery. 

Extra IntelliJ had to be installed for the delivery...
1) Create a java project using your local jdk (>=11)
1) Place the provided xmlrpc-demo in your source folder
1) Right-click the root-project folder selecting "Open Module Settings".
1) In Dialog "Project Structure" in the Group "Project Settings" choose
   "Libraries" on the very left side.
1) Click on the "+" icon and select "From Maven..."
1) Search for "org.apache.xmlrpc:xmlrpc-client:3.1.3" which should appear in
   the drop-down.
1) When "org.apache.xmlrpc:xmlrpc-client:3.1.3" got selected press "OK" on the
   bottom. Press "OK" a second time.
1) Repeat the same process for the server components
   "org.apache.xmlrpc:xmlrpc-server:3.1.3"
1) When finally both libriaries are listed press "ok" in the "Project Structure"
   Dialog

long currentTimeSystemMillis() could NOT be converted with long "Client faild to build stream" to avoid data loss the "String" was used. 

# General comments

Your code style is a mirror of your mind! Use comments where necessary, take
care for clean indentation. If your program does not compile then it receives
zero points.

Try to use the concepts and mechanisms we learned in the lecture when
appropriate. For instance, use packages, javadoc comments, and so on without
being explicitly mentioned in the assignments.


# General hints

Use the code of the lecture as a basis. First try to make them run on your
system to check that libraries and infrastructure is working. Then implement
the assignments. You can heavily reuse the lecture code as a template for your
task.


# Assignment A: Time server

Write a little XML-RPC time server. That is, write an XML-RPC service that
implements the interface com.timeserver.TimeServer, which provides two methods:

  long currentTimeSystemMillis()
  String currentTimeGregorianPretty()

The former returns the current time in UNIX epoch, i.e., number of microseconds
ticks since Jan 1, 1970 at 0:00 UTC.

The latter returns the current point in time as String for the Gregorian
calendar for the default time zone. It could return something like "Thu Apr 09
09:51:39 CEST 2020".

Implement a demo client TimeServerClient that accesses those two methods and
outputs the current time. Its output could like like

    $ java TimeServerClient
    Gregorian time: Thu Apr 09 11:48:36 CEST 2020
    System time: 1586425716666

Have a look at the classes and interfaces System, Calendar, GregorianCalendar.
Note that the Java foundation classes explicitly separate the concept of
"point in time" and "calendar". This is a bit like separating the concept of
"length" from "unit".

A personal note: History has proven many times that you should never
underestimate the complexity of calendar time as a software developer! You want
to know what the Y2038 problem is or why you probably cannot set an alert with
second precision for next year in UTC then listen to this Chaosradio podcast
episode: https://chaosradio.de/cr257-das-jahr-2038-problem
You can learn something about long lasting design decisions in this episode.

Hint: In order to enable marshalling of long values you need to enable
extensions for the server and client. Look for setEnabledForExtensions(true) in
https://ws.apache.org/xmlrpc/server.html

A typical implementation of this assignment has about 120 lines of code.


# Assignment B: Monte Carlo computation of pi

Write a RMI service that computes pi by means of a Monte Carlo method. The idea
is quite simple: Consider the plane, the unit disk at the origin and the unit
square [0,1] x [0,1]. Then the square intersected with the disk gives a quarter
disk:

                         -  +-------------------------+
                         ^  |****                     |
                         |  |***********              |
                         |  |**************           |
                         |  |*****************        |
                         |  |*******************      |
                         |  |*********************    |
                       1 |  |**********************   |
                         |  |***********************  |
                         |  |************************ |
                         |  |*************************|
                         |  |*************************|
                         |  |*************************|
                         v  |*************************|
                         -  +-------------------------+

                            |<----------------------->|
                                         1


Take now a uniformly random point (x, y) in the unit square. With probability
of pi/4 the point will be in the quarter disk. If we place 1000 such sample
points in the unit square then about 785.4 of them will be in the quarter disk.

In order to compute pi we compute N such sample points (x, y) and count the
number K of points with `x^2 + y^2 <= 1`. Then pi is approximately 4 * K / N.
For instance, if K = 780 out of N = 1000 points lie in the quarter disk then pi
is determined as 3.12.

This is your task:

* Implement a remote object that computes a uniformly random number in the
  interval [0,1]. The remote interface should be called com.mcpi.Random and
  provide a method `double uniform()` that gives a uniformly random number in
  the range [0, 1).

* Implement a remote object that computes pi and uses the above remote object
  to compute random numbers. The remote interface should be called
  com.mcpi.MonteCarloPi and provide a method `double compute(int N)` that
  uses the above formula. (You can rename the parameter N if you wish.)

* Implement a demo client called PiClient that uses the MonteCarloPi service to
  compute pi with different N: 10, 1000, 20000. It could output something
  like this:

        $ java PiClient
        Pi is 3.6 with N = 10
        Pi is 3.2 with N = 1000
        Pi is 3.1312 with N = 20000

A typical implementation of this assignment has about 150 lines of code.